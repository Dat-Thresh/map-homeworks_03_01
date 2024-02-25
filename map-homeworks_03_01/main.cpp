#include <iostream>
#include <thread>
#include <future>

//�������� ������
void print_arr(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void look_for_minimal (int* arr, int i, int i_min, int end, std::promise<int*> prom){
	//��������� �� ������������������ ����������
	for (int j = i + 1; j < end; j++) {
		int buff;
		//���� ��������� ����� ������ ������������ ������������
		if (arr[i_min] > arr[j]) {

			//�������������� �������� ������������ �������
			i_min = j;
			//���� ����������� ������ �� ����� �������� �������� i
			if (i_min != i) {
				//������ �������� �������
				buff = arr[i];
				arr[i] = arr[i_min];
				arr[i_min] = buff;
			}
		
		}
	}
	prom.set_value(arr);
}
//��������� ��������� ���������� ��������

void sort(int* arr, int begin, int end) {
	int buff;
	//�� ����� �������
	for (int i = begin; i < end; i++) {

		std::promise<int*> prom;
		auto ft = prom.get_future();

		int i_min = i;//� ������ ��������� ����� i ���������� ����� ����������� �������� i (��� ��� ���������� i ��� ����� �������������)
		std::async(std::launch::async, look_for_minimal, arr, i, i_min, end, std::move(prom));

		ft.get();

		////��������� �� ������������������ ����������
		//for (int j = i + 1; j < end; j++) {
		//	//���� ��������� ����� ������ ������������ ������������
		//	if (arr[i_min] > arr[j]) {
		//		//�������������� �������� ������������ �������
		//		i_min = j;
		//		//���� ����������� ������ �� ����� �������� �������� i
		//		if (i_min != i) {
		//			//������ �������� �������
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