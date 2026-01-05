#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;//for measuring time




void swapRef(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void swapPtr(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}







int main() {
	const int N = 100000000; // 100 million iterations
	int x = 5, y = 10;

	auto start = high_resolution_clock::now();
	for (int i = 0; i < N; i++) {
		swapRef(x, y);
	}
	auto end = high_resolution_clock::now();
	cout << "Reference swap: "<< duration_cast<milliseconds>(end - start).count()<< " ms" << endl;

	x = 5; y = 10;
	start = high_resolution_clock::now();
	for (int i = 0; i < N; i++) {
		swapPtr(&x, &y);
	}
	end = high_resolution_clock::now();
	cout << "Pointer swap: "<< duration_cast<milliseconds>(end - start).count()<< " ms" << endl;
	return 0;
}

