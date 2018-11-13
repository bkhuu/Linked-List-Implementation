#ifndef Project3_llist_bkhuu_207_H
#define Project3_llist_bkhuu_207_H

#define GENSIZE 35
#define FNAME 25

// struct of a passenger
typedef struct _Passenger
{
   int id; // passenger id
   char fname[25]; // first name
   char lname[35]; // last name
   double balance; // account balance
   char location; // on-board/off-board
} pass;

// struct of a node
typedef struct _Node
{
   pass person; // data field of node
   struct _Node *next; // pointer to next node in list
} node;

node * makeNode(int id, char fname[], char lname[]);

// insert a node into the ordered list
void insertNodeSorted(node **head, node *newNode);

// print the passengers of the ordered list
void printList(node *head);

// print the passenger
void printPass(node *temp);

// free the memory allocated for the list
void deleteList(node **head);

// find a node to print
node * findNode(node *head, int id);

// remove a node from the list
node * removeNode(node **head, int id);

// print the total and average money spent
void calculateTotal(node *head);

#endif
