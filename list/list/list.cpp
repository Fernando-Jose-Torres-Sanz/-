#include<iostream>
#include<list>
using namespace std;
//�ڵ�Ķ���
template<class T>
struct ListNode{
	//���͵Ľ��ĳ�ʼ��
	ListNode(const T& val = T())
	: _data(val)
	, _next(nullptr)
	, _prev(nullptr)
	{}

	ListNode<T>* _next;
	ListNode<T>* _prev;
	T _data;
};
//�������ķ�װ
template <class T,class Ref,class Ptr>
struct ListInterator{
	//�ڵ������з�һ�����
	typedef ListInterator<T,T&,T*> Self;
	ListNode<T>* _node;
	ListInterator( ListNode<T>* node)
		:_node(node)
	{}
	//������
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
	//ǰ��++
	Self& operator++(){
		_node = _node->_next;
		return *this;
	}
	//����++
	Self operator++(int){
		Self tmp(*this);
		_node = _node->_next;
		return tmp;
	}
};

//template <class T>
//struct ConstListInterator{
//	//�ڵ������з�һ�����
//	typedef ConstListInterator<T> Self;
//	ListNode<T>* _node;
//
//	ConstListInterator(ListNode<T>* node)
//		:_node(node)
//	{}
//	//������
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
//	//ǰ��++
//	Self& operator++(){
//		_node = _node->_next;
//		return *this;
//	}
//	//����++
//	Self operator++(int){
//		Self tmp(*this);
//		_node = _node->_next;
//		return tmp;
//	}
//	T& operator-> (){
//		return _node->_data;
//	}
//};
//list������(����ֻ���List��ͷ����ָ��)
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
	//ͷ��
	void PushFront(const T& val){
		pNode newNode = new  Node(val);
		newNode->_next = _head->_next;
		_head->_next->_prev = newNode;
		_head->_next = newNode;
		newNode->_prev = _head;
	}
	//ͷɾ
	void PopFront(){
		pNode cur = _head->_next;
		_head->_next = cur->_next;
		cur->_next->_prev = _head;
		delete cur;
	}
	//β��
	void PushBuck(const T& val){
		//����ռ佨���Ľ��
		pNode newNode = new Node(val);
		pNode cur = _head->_prev;
		cur->_next = newNode;
		newNode->_next = _head;
		_head->_prev = newNode;
		newNode->_prev = cur;
	}
	//βɾ
	void PopBuck(){
		pNode cur = _head->_prev;
		cur->_prev->_next = _head;
		_head->_prev = cur->_prev;
		delete cur;
	}
	//��POSλ��ǰ����val
	void Insert(iterator pos, const T& val){
		pNode newNode = new Node(val);
		pNode cur = pos._node;
		newNode->_next = cur;
		newNode->_prev = cur->_prev;
		cur->_prev->_next = newNode;
		cur->_prev = newNode;
	}
	//ɾ��posλ�õĽ��(ע�������ʧЧ����)
	iterator Erase(iterator pos){
		//����ɾ��ͷ���
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
	//���List�Ƿ�Ϊ��
	bool Empty() const {
		return (_head->_next == _head);
	}
	//��ȡList�ĳ���
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
	//��������(���)
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
		//�ж�ͷ����Ƿ����,������ڴ�ͷ������һ����㿪ʼ����ɾ���������еĽ��
		if (_head){
			pNode cur = _head->_next;
			while (cur != _head){
				//1.�ȱ��浱ǰ������һ�����
				//2.ɾ����ǰ���
				//���������һ�������³�Ϊ��ǰ�Ľ��
				pNode next = cur->_next;
				delete cur;
				cur = next;
			}
			delete _head;
			_head = nullptr;
		}
	}
	//���ﷵ�ص��ǵ�һ�����,�������ڶԵ����������˷�װ, �������·Ҫ���õ������Ĺ��캯��
	iterator begin(){
		return iterator(_head->_next);
	}
	iterator end(){
		return  iterator(_head);
	}

private:
	//ͷ����ָ��
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
		cout << "lst�ǿյ�" << endl;
	}
	else{
		cout << "lst�Ƿǿյ�" << endl;
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