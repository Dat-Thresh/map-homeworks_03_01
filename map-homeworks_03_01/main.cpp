#include <iostream>
#include <thread>
#include <future>

//печатает массив
void print_arr(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void look_for_minimal (int* arr, int i, int i_min, int end, std::promise<int*> prom){
	//пробегаем по неотсортированному промежутку
	for (int j = i + 1; j < end; j++) {
		int buff;
		//если встречаем число меньше запомненного минимального
		if (arr[i_min] > arr[j]) {

			//перезаписываем значение минимального индекса
			i_min = j;
			//если минимальный индекс не равен текущему значению i
			if (i_min != i) {
				//меняем элементы местами
				buff = arr[i];
				arr[i] = arr[i_min];
				arr[i_min] = buff;
			}
		
		}
	}
	prom.set_value(arr);
}
//сортирует указанный промежуток выборкой

void sort(int* arr, int begin, int end) {
	int buff;
	//по всему массиву
	for (int i = begin; i < end; i++) {

		std::promise<int*> prom;
		auto ft = prom.get_future();

		int i_min = i;//с каждой итерацией цикла i записываем новое минимальное значение i (так как предыдущие i уже будут отсортированы)
		std::async(std::launch::async, look_for_minimal, arr, i, i_min, end, std::move(prom));

		ft.get();

		////пробегаем по неотсортированному промежутку
		//for (int j = i + 1; j < end; j++) {
		//	//если встречаем число меньше запомненного минимального
		//	if (arr[i_min] > arr[j]) {
		//		//перезаписываем значение минимального индекса
		//		i_min = j;
		//		//если минимальный индекс не равен текущему значению i
		//		if (i_min != i) {
		//			//меняем элементы местами
		//			buff = arr[i];
		//			arr[i] = arr[i_min];
		//			arr[i_min] = buff;
		//		}
		//	}
		//}
	}
}





int main() {
	int arr[]{ 1, 5, -1, -23, 56 };


	print_arr(arr, 5);

	try {
		sort(arr, 0, 5);

		print_arr(arr, 5);
	}
	catch (std::exception& er) {
		std::cout << er.what() << std::endl;
	}
	return 0;
}