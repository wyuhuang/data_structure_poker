#include"List.h"
const int MAX_SIZE = 100;//根据实际定义 
template <class T>
class SeqList:public List<T>{
	public:
		SeqList();
		SeqList(T data[], int length);//构造函数负责初始化 
		~SeqList();
		virtual int getLength();
        virtual int locate(T data);
        virtual T get(int index);
        virtual void insert(T data, int index);
        virtual T deleteByIndex(int index);
        virtual bool isEmpty();
        virtual void printList();
        void quickSwapList();
	private:
		T data[MAX_SIZE]; 
		int length = 0;
};
