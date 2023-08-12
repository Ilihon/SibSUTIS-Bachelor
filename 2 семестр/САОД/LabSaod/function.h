
struct stack {
	struct stack *next;
	union {
		int data;
		unsigned char digit [sizeof(int)];
	};
};

struct Queue {
	stack *head;
	stack *tail;
};


void FillIncStack (struct stack **head, int n);
void FillIncQueue (struct stack **head, struct stack **tail, int n);
void FillDecStack (struct stack **head, int n);
void FillDecQueue (struct stack **head, struct stack **tail, int n);
void FillRandStack (struct stack **head, int n);
void FillRandQueue (struct stack **head, struct stack **tail, int n);
void DeleteStack (struct stack **head);
void DeleteQueue (struct stack **head, struct stack **tail);
void CheckSumStack (struct stack *head);
void RunNumberStack (struct stack *head);
void PrintStack (struct stack *head);
void StackToQueue (struct stack **head, struct stack **tail);
void Swap (int &x, int &y);
void Hash (int m, stack **head, stack **tail, Queue q[]);
void HashSearch (int m, Queue q[]);


