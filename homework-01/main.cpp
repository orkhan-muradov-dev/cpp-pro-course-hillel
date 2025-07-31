#include <iostream>
#include <vector>

using namespace std;

template <typename F>
void randFillVec(vector<F>& v, size_t size = 5)
{
	v.resize(size);
	for (auto& element : v)
		element = rand() % 1000;
}

template <typename R>
void rangeLoop(const vector<R>& v)
{
	cout << "Vector type: " << typeid(R).name() << endl
	     << "Range based loop: ";
	size_t count = 0;
	for (const auto& element : v)
	{
		cout << element;
		if (++count < v.size()) { cout << ", "; }
	}
	cout << endl;
}

template <typename I>
void iteratorLoop(const vector<I>& v)
{
	cout << "Vector type: " << typeid(I).name() << endl
		 << "Iterator based loop: ";
	for (auto it = v.begin(); it != v.end(); ++it)
		cout << *it << (it != (v.end() - 1) ? ", ": "");
	cout << endl;
}

void main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	vector<string> vString({ "parents", "siblings", "children", "grandparents", "relatives" });
	vector<int> vNum;
	randFillVec(vNum);

	cout << "\t\t\tAuto and range-based loops\n" << endl;
	rangeLoop(vString);
	cout << endl;
	iteratorLoop(vNum);
}