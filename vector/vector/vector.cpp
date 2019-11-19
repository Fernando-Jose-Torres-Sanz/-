#include<iostream>
#include<vector>
#include<string>
#include<assert.h>
using namespace std;

template < class T>
class Vector
{
public:
	typedef T* iterator;
	//typedef  const T* iterator const;
	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{}

	void pushbuck(const T& val){
		if (_finish == _endofstorage){
			size_t newcapacity = _start == nullptr ? 1 : 2 * Capacity();
			Reserve(newcapacity);
		}
		*_finish = val;
		_finish++;
	}
	  
	size_t Capacity() const{
		return _endofstorage - _start;
	}

	size_t Size() const{
		return _finish - _start;
	}

	iterator begin(){
		return _start;
	}
	iterator end(){
		return _finish;
	}
	const iterator begin() const{
		return _start;
	}
	const iterator end() const{
		return _finish;
	}

	void Reserve(size_t n){
		int len = Size();
		T* tmp = new T[n];
		//mymcpyǳ����, �����Զ������Ϳ��ܻᷢ�������ͷ�
		/*if (_start){
			mymcapy(tmp, _start, sizeof(T)*len);
			delete[] _start;
		}*/
		if (_start){
			for (int i = 0; i < len; i++)
				tmp[i] = _start[i];
		}
		_start = tmp;
		_finish = _start + len;
		_endofstorage = _start + n;
	}

	T& operator[](size_t pos){
		assert(pos < Size());
		return _start[pso];

	}

	const T& operator[](size_t pos) const{
		assert(pos < Size());
		return _start[pos];

	}
	//���ݵ��µ�����ʧЧ
	//�����뷢�����ݵ�ʱ��, �����������ʧЧ, ���ݵ�����Ҫ�����µĿռ�, ����ԭ�е�����, �ͷ�ԭ�еĿռ�
	//������ָ���ԭ�пռ��޷�����
	void Insert(iterator pos, const T& val){
		assert(pos < _finish&&pos >= _start);
		size_t len = pos - _start;
		if (_finish == _endofstorage){
			size_t newC = _start == nullptr ? 1 : 2 * Capacity();
			Reserve(newC);
		}
		pos = _start - len;
		iterator end= _finish;
		while (end > pos){
			*end = *(end - 1);
			end--;
		}
		*pos = val;
		_finish++;
	}
	//������ʧЧ
	//���ܵ��µ���������Խ��
	//��ȡɾ���ӿڵķ���ֵ, ָ��ɾ��Ԫ�ص���һ��λ��
	iterator erase(iterator pos){
		assert(pos < _finish && pos >= _start);
		iterator begin = pos + 1;
		while (begin < _finish){
			*(begin - 1) = *begin;
			++begin;
		}
		--_finish;
		return pos;
	}
	//�ı�size����
	void Resize(size_t n, const T& val = T()){
		//nС��size,ֱ�ӽ�_finish��ǰ�ƶ�
		if (n <= Size()){
			_finish = _start + n;
		}
		else{
			//n>������ʱ��, ������,�ڽ������ݵ�λ�ø�ֵ��val
			if (n > Capacity()){
				Reserve(n);
				while (_finish!=_start+n){
					*_finish = val;
					_finish++;
				}
			}
		}
	}
	//��������
	Vector(const Vector<T>& v){
		//���
		//���ٿռ�
		_start = new T[v.Capacity()];
		for (int i = 0; i < v.Size(), i++){
			_start[i] = v[i];
		}
		_finish = _start + v.Size();
		_endofstorage = _start + v.Capacity();
		//����
		//�ͷ�ԭ�еĿռ�
	}
	//��ֵ���������
	Vector<T>& operator=(const Vector<T>& v){
		if (this != &v){
			T* tmp = new T[v.Capacity()];
			for (int i = 0; i < v.Size(); i++){
				tmp[i] = v[i];
			}
			if (_start){
				dalete[] _start;
			}
			_start = tmp;
			_finish = _start + v.Size();
			_endofstorage = _start + v.Capacity();
		}
		return *this;
	}
	
	~Vector(){
		if (_start){
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}
	}

private:
	T* _start;
	T* _finish;
	T* _endofstorage;
};
template<class T>
void print(const Vector<T>& v){
	for (int i = 0; i < v.Size(); i++){

		cout << v[i] << " ";
	}
	cout << endl;
}
template<class T>
void printiterator(const Vector<T>& v){
	
	Vector<T>::const_iterator vit = v.begin();
	while (vit != v.end()){
		cout << *vit << endl;
		vit++;
	}
}
int main(){

	Vector<string> v;
	v.pushbuck("hou");
	v.pushbuck("xing"); 
	v.pushbuck("gang");
	v.pushbuck("hao");
	v.pushbuck("shua");
	v.pushbuck("a");
	v.Insert(v.begin() + 1,"heuheu" );
	print(v);

	system("pause");
	return 0;
}


//int main(){
//	vector<int> v;
////��ʼ����������.�ռ��СΪ10 ȫ����ʼ��Ϊ3
//	vector<int> v2(10,3);
//	vector<int>  v3(v2.begin(), v2.end());
//	//��������ʹ��----��begin��ʼ��ֵ��end
//	string s("houxinggang");
//	vector<char>  v4(s.begin(), s.end());
//
//	vector<int>::iterator vit = v2.begin();
//	while (vit != v2.end()){
//
//		cout << *vit << endl;
//		++vit;
//
//	}
//	vector<int> v7;
//	v7.push_back(1);
//	v7.push_back(2);
//	v7.push_back(3);
//	v7.push_back(4);
//	auto vit = v7.begin();
//	cout << *vit << endl;
//	//insert�������������ʧЧ(���ͷ���ԭ���Ŀռ� )
//	//�������֮�����»�ȡ���������ܼ���ʹ��
//	v7.insert(v7.begin() + 3, 0);
//	vit = v7.begin();
//	//Ҳ�п�����ɵ�����ʧЧ(���µ���������Խ��)
//	//ɾ�����֮����Ҫ��ȡ���ķ���ֵ
//	vit=v7.erase(vit);
//	cout << *vit << endl;
//	//���(sizeΪ0,capacity������)
//	v7.clear();
//	
//	system("pause");
//	return 0;
//}