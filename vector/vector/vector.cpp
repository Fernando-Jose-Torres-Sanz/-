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
		//mymcpy浅拷贝, 对于自定义类型可能会发生二次释放
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
	//增容导致迭代器失效
	//当插入发生增容的时候, 会引起迭代器失效, 增容导致需要开辟新的空间, 拷贝原有的内容, 释放原有的空间
	//迭代器指向的原有空间无法访问
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
	//迭代器失效
	//可能导致迭代器访问越界
	//获取删除接口的返回值, 指向被删除元素的下一个位置
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
	//改变size长度
	void Resize(size_t n, const T& val = T()){
		//n小于size,直接将_finish向前移动
		if (n <= Size()){
			_finish = _start + n;
		}
		else{
			//n>容量的时候, 先扩容,在将新扩容的位置赋值成val
			if (n > Capacity()){
				Reserve(n);
				while (_finish!=_start+n){
					*_finish = val;
					_finish++;
				}
			}
		}
	}
	//拷贝构造
	Vector(const Vector<T>& v){
		//深拷贝
		//开辟空间
		_start = new T[v.Capacity()];
		for (int i = 0; i < v.Size(), i++){
			_start[i] = v[i];
		}
		_finish = _start + v.Size();
		_endofstorage = _start + v.Capacity();
		//拷贝
		//释放原有的空间
	}
	//赋值运算符重载
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
////初始化的意义是.空间大小为10 全部初始化为3
//	vector<int> v2(10,3);
//	vector<int>  v3(v2.begin(), v2.end());
//	//迭代器的使用----从begin开始赋值待end
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
//	//insert会引起迭代器的失效(他释放了原来的空间 )
//	//插入完成之后重新获取迭代器才能继续使用
//	v7.insert(v7.begin() + 3, 0);
//	vit = v7.begin();
//	//也有可能造成迭代器失效(导致迭代器访问越界)
//	//删除完成之后需要获取他的返回值
//	vit=v7.erase(vit);
//	cout << *vit << endl;
//	//清空(size为0,capacity还存在)
//	v7.clear();
//	
//	system("pause");
//	return 0;
//}