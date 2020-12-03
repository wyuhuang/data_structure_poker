#ifndef LIST
#define LIST


template <typename T>
class List {
	public:
        virtual int getLength() = 0;
        virtual int locate(T data) = 0;
        virtual T get(int index) = 0;
        virtual void insert(T data, int index) = 0;
        virtual T deleteByIndex(int index) = 0;
        virtual bool isEmpty() = 0;
        virtual void printList() = 0;
};

#endif
