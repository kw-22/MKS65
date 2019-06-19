struct node {int i; struct node *next;};

void print_list(struct node *);

struct node *insert_front(struct node *, int);

struct node *free_list(struct node *);
