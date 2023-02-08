typedef struct queue;
struct queue
{
	struct element* previous;
	int number;
	int priority;
	struct element* next;
};
struct element
{
	struct queue* head;
	struct queue* tail;

};

void push(int element, struct element* el);
void insert(int number, int pr, struct element* el);

void pop(struct element* el);
void qremove(struct element* el);

void merge_two_el(struct element* a, struct element* b);

void order(struct element* el);

void print(struct element* el);

