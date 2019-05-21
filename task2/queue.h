typedef int data;
class BasicQueue	
{
public:
	virtual void enqueue(data &c) = 0;
	virtual data  denqueue() = 0;
	virtual unsigned getLength() = 0;

	virtual ~BasicQueue() = 0;
};

class ArrayQueue: public BasicQueue
{
private:
	int lar;
	int hade;
	int tale;
	data * dat;
	int lon;

public:	
	ArrayQueue(int n);
	~ArrayQueue() override;
  	void  enqueue(data &c) override;
	data  denqueue() override;	
	unsigned getLength() override;
};

class ListQueue: public BasicQueue
{
private:
	struct List
	{
		data val;
		List *nod;
	};
	List *first;
	List *last;
	int lon;

public:
	void  enqueue(data &c) override;
	ListQueue();
	~ListQueue() override;
	data denqueue() override;
	unsigned getLength() override;
};
