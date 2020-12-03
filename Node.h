#ifndef NODE
#define NODE

template <typename T>
class Node {
	public:
		Node();
		Node(T data, Node<T>* next);
		~Node();
		T getData();
		void setData(T data);
		Node<T>* getNext();
		void setNext(Node<T>* next);
	private:
		T data;
		Node<T>* next;//指向自己, 不是指向T* 
};

template <typename T>
Node<T>::Node() {
	next = nullptr;	//免得乱指 
}

template <typename T>
Node<T>::Node(T data, Node<T>* next) {
	this->data = data;
	this->next = next;
}

template <typename T>
Node<T>::~Node() {
	
}

template <typename T>
T Node<T>::getData() {
	return data;
}

template <typename T>
void Node<T>::setData(T data) {
	this->data = data;
}

template <typename T>
Node<T>* Node<T>::getNext() {
	return next;
}

template <typename T>
void Node<T>::setNext(Node<T>* next) {
	this->next = next;
}
#endif
