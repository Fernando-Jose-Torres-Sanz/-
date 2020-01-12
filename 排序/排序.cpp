#include<iostream>
#include<vector>
using namespace std;

class Sort{
public:
	Sort(vector<int>& arr){
		swap(_arr, arr);
	}
	//冒泡排序
	void BobSort(){
		int len = _arr.size();
		for (int  i = 0; i < len; i++){
			for (int j = 0; j < len - i - 1; j++){
				if (_arr[j] > _arr[j + 1]){
					swap(_arr[j], _arr[j + 1]);
				}
			}
		}
	}
	//插入排序
	void InsertSort(){

	}
	//快速排序
	void QuickSort(){
		int len = _arr.size();
		QucikSortInnder(0, len - 1);
	}
	//归并排序
	void MergeSort(){
		int len = _arr.size();
		vector<int> extra;
		extra.resize(len);
		MergeSortInnder(0, len, extra);
	}

	void Print(){
		for (int i = 0; i < _arr.size(); i++){
			cout << _arr[i] << " ";
		}
		cout << endl;
	}
private:
	vector<int> _arr;
	void QucikSortInnder(int left,int right){
		if (left == right){
			return;
		}
		if (left > right){
			return;
		}
		int d = partition_2(left, right);
		QucikSortInnder(left, d - 1);
		QucikSortInnder(d + 1, right);
	}
	//内部处理方法一
	int partition_1(int left,int right){
		int begin = left;
		int end = right;
		int pivot = _arr[right];
		while (begin < end){
 			while (begin < end && _arr[begin] <= pivot){
				begin++;
			}
			while (begin < end && _arr[end] >= pivot){
				end--;
			}
			swap(_arr[begin], _arr[end]);
		}
		swap(_arr[end], _arr[right]);
		return begin;
	}
	//内部处理方法二
	int partition_2(int left, int right){
		int begin = left;
		int end = right;
		int pivot = _arr[right];
		while (begin < end){
			while (begin < end){
				if (_arr[begin] <= pivot)
					begin++;
				else{
					_arr[end] = _arr[begin];
					break;
				}
			}
			while (begin < end){
				if (_arr[end] >= pivot)
					end--;
				else{
					_arr[begin] = _arr[end];
					break;
				}
			}
		}
		_arr[end] = pivot;
		return end;
	}

	//[ left , right )
	void MergeSortInnder(int left, int right, vector<int>& extra){
		if (left >= right){
			return;
		}
		if (left + 1 == right){
			return;
		}
		int mid = left + (right - left) / 2;
		MergeSortInnder(left, mid, extra);
		MergeSortInnder(mid, right, extra);
		Merge(left, mid, right,extra);
	}
	void Merge(int left, int mid, int right, vector<int>& extra){
		int size = right - left;

		int i = left;
		int j = right;
		int k = left;
		while (i < mid && j < right){
			if (_arr[i] <= _arr[j]){
				extra[k++] = _arr[i++];
			}
			else{
				extra[k++] = _arr[j++];
			}
		}
		while (i < mid){
			extra[k++] = _arr[i++];
		}
		while (j < right){
			extra[k++] = _arr[j++];
		}
		swap(_arr, extra);
	}

};
int main(){
	vector<int> arr = { 9, 5, 2, 7, 3, 6, 4 };
	Sort so(arr);
	so.Print();
	so.MergeSort();
	so.Print();
	system("pause");
	return 0;
}