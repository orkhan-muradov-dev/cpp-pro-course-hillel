#include <iostream>
#include <vector>
#include <algorithm>

class BigData {
private:
	int* data;
	size_t size;

public:
	BigData(const size_t s) : size(s){
		std::cout << "Constructor has been called." << std::endl;

		data = new int[size]{};
	}

	// Конструктор з використанням std::initializer_list 
	BigData(std::initializer_list<int> initList) : size(initList.size()) {
		std::cout << "Initializer_list constructor has been called." << std::endl;

		data = new int[size];
		size_t i = 0;
		for (int val : initList) {
			data[i++] = val;
		}
	}

	~BigData() {
		std::cout << "Destructor has been called." << std::endl;

		delete[] data;
	}

	// Конструктор копіювання
	BigData(const BigData& other) : size(other.size) {
		std::cout << "Copy constructor has been called." << std::endl;

		data = new int[other.size];
		for (size_t i = 0; i < other.size; i++){
			data[i] = other.data[i];
		}
	}

	// Оператор копіювання
	BigData& operator=(const BigData& other) {
		std::cout << "Copy assignment operator has been called." << std::endl;

		if (this != &other) {
			delete[] data;

			size = other.size;
			data = new int[size];
			for (size_t i = 0; i < other.size; i++) {
				data[i] = other.data[i];
			}
		}
		return *this;
	}

	// Конструктор переміщення
	BigData(BigData&& other) noexcept {
		std::cout << "Move constructor has been called." << std::endl;

		this->data = other.data;
		this->size = other.size;

		other.data = nullptr;
		other.size = 0;
	}

	// Оператор переміщення
	BigData& operator=(BigData&& other) noexcept {
		std::cout << "Move assignment operator has been called." << std::endl;
		
		if (this != &other) {
			delete[] data;

			this->data = other.data;
			this->size = other.size;

			other.data = nullptr;
			other.size = 0;
		}
		return *this;
	}
	
	int& operator[](size_t index){
		if (index >= size) {
			throw std::out_of_range("Index out of bounds.");
		}
		return data[index];
	}

	const int& operator[](size_t index) const {
		if (index >= size) {
			throw std::out_of_range("Index out of bounds.");
		}
		return data[index];
	}

	void print() const{
		std::cout << "[";
		for (size_t i = 0; i < size; ++i) {
			std::cout << data[i];
			if (i < size - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "]" << std::endl;
	}
};

template <typename T>
void printVec(std::vector<T>& vec)
{
	std::cout << "[";
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i];
		if (i < vec.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "]" << std::endl;
}

int main() {
	std::cout << "-------- Initializing with size --------" << std::endl;
	BigData bigData(10);
	std::cout << "bigData: ";
	bigData.print();

	std::cout << "\n----- Initializing with initializer_list -----" << std::endl;
	BigData initListData = { 1, 2, 3, 4, 5 };
	std::cout << "initListData: ";
	initListData.print();

	std::cout << "\n---------------- Copy Constructor ----------------" << std::endl;
	BigData copiedData(bigData);
	std::cout << "bigData (original): ";
	bigData.print();
	std::cout << "copiedData: ";
	copiedData.print();

	std::cout << "\n-------------- Copy Assignment Operator --------------" << std::endl;
	BigData assignedData(2);
	std::cout << "assignedData (before assignment): ";
	assignedData.print();
	assignedData = initListData;	
	std::cout << "assignedData (after assignment): ";
	assignedData.print();
	std::cout << "initListData (original, not deleted): ";
	initListData.print();
	
	std::cout << "\n---------------------- Move Constructor ----------------------" << std::endl;
	BigData willBeMovedData(10);
	for (size_t i = 0; i < 10; ++i) {
		willBeMovedData[i] = static_cast<int>(i + 1);
	}
	std::cout << "willBeMovedData (before move): ";
	willBeMovedData.print();

	BigData movedData(std::move(willBeMovedData)); // move(movedObj) = static_cast<obj&&>(movedObJ)
	std::cout << "movedData: ";
	movedData.print();
	std::cout << "willBeMovedData (deleted): ";
	willBeMovedData.print();

	std::cout << "\n------ Using operator[] as an accessor/mutator ------" << std::endl;
	BigData accessData = { 10, 20, 30, 40, 50 };
	std::cout << "accessData: ";
	accessData.print();
	std::cout << "Value at index 2: " << accessData[2] << std::endl;
	accessData[2] = 300;
	std::cout << "accessData after modification: ";
	accessData.print();

	std::cout << "\n---------- Lambda Expression Task ----------" << std::endl;
	std::vector<int> vec = { 10, 20, 30, 40, 50 };
	std::cout << "Original vector: ";
	printVec(vec);

	int valueToIncrease = 5;
	std::cout << "Increasing each element by " << valueToIncrease << std::endl;
	std::for_each(vec.begin(), vec.end(), [valueToIncrease](int& element) {
		element += valueToIncrease;
		});

	std::cout << "Vector after increment: ";
	printVec(vec);

	std::cout << "\n------- Destructors -------" << std::endl;

	return 0;
}