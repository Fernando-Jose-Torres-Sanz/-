#include<iostream>
#include<list>
using namespace std;
//节点的定义
template<class T>
struct ListNode{
	//泛型的结点的初始化
	ListNode(const T& val = T())
	: _data(val)
	, _next(nullptr)
	, _prev(nullptr)
	{}

	ListNode<T>* _next;
	ListNode<T>* _prev;
	T _data;
};
//迭代器的封装
template <class T,class Ref,class Ptr>
struct ListInterator{
	//在迭代器中封一个结点
	typedef ListInterator<T,T&,T*> Self;
	ListNode<T>* _node;
	ListInterator( ListNode<T>* node)
		:_node(node)
	{}
	//解引用
	Ref operator* (){
		return _node->_data;
	}
	Ptr operator-> (){
		return &(_node->_data);
	}
	bool operator!=(const Self& lit){
		if (_node != lit._node){
			return true;
		}
		else{
			return false;
		}
	}
	bool operator==(const Self& lit){
		return _node == lit._node;
	}
	//前置++
	Self& operator++(){
		_node = _node->_next;
		return *this;
	}
	//后置++
	Self operator++(int){
		Self tmp(*this);
		_node = _node->_next;
		return tmp;
	}
};

//template <class T>
//struct ConstListInterator{
//	//在迭代器中封一个结点
//	typedef ConstListInterator<T> Self;
//	ListNode<T>* _node;
//
//	ConstListInterator(ListNode<T>* node)
//		:_node(node)
//	{}
//	//解引用
//	 const T& operator* (){
//		return _node->_data;
//	}
//	const T& operator-> (){
//		return &(_node->_data);
//	}
//
//	bool operator!=(const Self& lit){
//		if (_node != lit._node){
//			return true;
//		}
//		else{
//			return false;
//		}
//	}
//
//	bool operator==(const Self& lit){
//		return _node == lit._node;
//	}
//
//	//前置++
//	Self& operator++(){
//		_node = _node->_next;
//		return *this;
//	}
//	//后置++
//	Self operator++(int){
//		Self tmp(*this);
//		_node = _node->_next;
//		return tmp;
//	}
//	T& operator-> (){
//		return _node->_data;
//	}
//};
//list的主体(当中只存放List的头结点的指针)
template<class T>
class List
{
public:
	typedef ListNode<T> Node;
	typedef  Node*  pNode;
	typedef ListInterator<T,T&,T*> iterator;
	typedef ListInterator<T, const T&,const T*> const_iterator;
	List(){
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
	}
	//头插
	void PushFront(const T& val){
		pNode newNode = new  Node(val);
		newNode->_next = _head->_next;
		_head->_next->_prev = newNode;
		_head->_next = newNode;
		newNode->_prev = _head;
	}
	//头删
	void PopFront(){
		pNode cur = _head->_next;
		_head->_next = cur->_next;
		cur->_next->_prev = _head;
		delete cur;
	}
	//尾插
	void PushBuck(const T& val){
		//申请空间建立心结点
		pNode newNode = new Node(val);
		pNode cur = _head->_prev;
		cur->_next = newNode;
		newNode->_next = _head;
		_head->_prev = newNode;
		newNode->_prev = cur;
	}
	//尾删
	void PopBuck(){
		pNode cur = _head->_prev;
		cur->_prev->_next = _head;
		_head->_prev = cur->_prev;
		delete cur;
	}
	//在POS位置前插入val
	void Insert(iterator pos, const T& val){
		pNode newNode = new Node(val);
		pNode cur = pos._node;
		newNode->_next = cur;
		newNode->_prev = cur->_prev;
		cur->_prev->_next = newNode;
		cur->_prev = newNode;
	}
	//删除pos位置的结点(注意迭代器失效问题)
	iterator Erase(iterator pos){
		//不能删除头结点
		if (pos != end()){
			pNode cur = pos._node;
			pNode next = cur->_next;
			pNode prev = cur->_prev;
			prev->_next = next;
			next->_prev = prev;
			delete cur;
			pos = iterator(next);
		}
		return pos;
	}
	//检查List是否为空
	bool Empty() const {
		return (_head->_next == _head);
	}
	//获取List的长度
	size_t Size()const {
		size_t i = 0;
			pNode cur = _head->_next;
			while (cur != _head){
				cur = cur->_next;
				++i;
		}
			return i;
	}

	void Clear(){
		if (Empty()){
			return;
		}
		pNode cur = _head->_next;
		while (cur != _head){
			_head->_next = cur->_next;
			delete cur;
			cur = _head->_next;
		}
		_head->_next = _head;
		_head->_prev = _head;
	}
	//拷贝构造(深拷贝)
	List(const List<T>& lst){
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
		auto lit = lst.begin();
		while (lit != lst.end()){
			PushBuck(*lst);
		}
	}
	List<T>& operator=(const List<T>& lst){
		swap(_head, lst._head);
		return *this;
	}
	~List(){
		//判断头结点是否存在,如果存在从头结点的下一个结点开始依次删除后面所有的结点
		if (_head){
			pNode cur = _head->_next;
			while (cur != _head){
				//1.先保存当前结点的下一个结点
				//2.删除当前结点
				//将保存的下一个结点更新成为当前的结点
				pNode next = cur->_next;
				delete cur;
				cur = next;
			}
			delete _head;
			_head = nullptr;
		}
	}
	//这里返回的是第一个结点,但是由于对迭代器进行了封装, 因此在这路要调用迭代器的构造函数
	iterator begin(){
		return iterator(_head->_next);
	}
	iterator end(){
		return  iterator(_head);
	}

private:
	//头结点的指针
	pNode _head;
};
template<class T>
void PrintList( List<T>& lst){
	auto lit = lst.begin();
	while (lst.end() != lit){
		cout << *lit << " ";
		++ lit;
	}
	cout << endl;
}

int main(){
	List<int>  lst;	
	lst.PushBuck(1);
	if (lst.Empty()){
		cout << "lst是空的" << endl;
	}
	else{
		cout << "lst是非空的" << endl;
	}

	lst.PushBuck(2);
	lst.PushBuck(3);
	lst.PushBuck(4);
	lst.PushBuck(5); 
	lst.PushBuck(6);
	lst.PopBuck();
	lst.PushFront(0);
	lst.PopFront();
  
	lst.Insert(lst.begin(), 9);
	size_t num = lst.Size();
	cout << num << endl;
	PrintList(lst);
	system("pause");
	return 0;
}