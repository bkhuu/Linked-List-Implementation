#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GENSIZE 35
#define FNAME 25

// struct of a passenger
typedef struct _Passenger
{
   int id; // passenger id
   char fname[FNAME]; // first name
   char lname[GENSIZE]; // last name
   double balance; // account balance
   char location; // on-board/off-board
} pass;

// struct of a node
typedef struct _Node
{
   pass person; // data field of node
   struct _Node *next; // pointer to next node in list
} node;

node * makeNode(int id, char fname[], char lname[])
{
   node *newNode = malloc(sizeof(node)); // allocate memory for newNode
   pass newPass;
   // check if malloc was successful
   if (newNode == NULL)
   {
      printf("Something went wrong...\n");
      exit(0);
   }
   newNode->next = NULL; // set newNode next to NULL
   // initialize passenger struct
   newPass.id = id;
   strcpy(newPass.fname, fname);
   strcpy(newPass.lname, lname);
   newPass.balance = 0.00; // default balance
   newPass.location = 0; // default location
   newNode->person = newPass; // add passenger to node
   return newNode;
}

// insert a node into the ordered list
void insertNodeSorted(node **head, node *newNode)
{
	if (*head == NULL) // first node is the head
	{
		*head = newNode; // set head to newNode
	}
	else if ((newNode->person.id) < ((*head)->person.id)) // new head if newNode id is less than head id
	{
		newNode->next = *head; // set newNode next to head
		*head = newNode; // set head to newNode
	}
	else // traverse to the proper insertion point in the list
	{
		node *temp = *head; // temporary node
		while ((temp->next != NULL) && (temp->next->person.id < newNode->person.id))
		{
			temp = temp->next; // set temp to temp next
		}
		newNode->next = temp->next; // set newNode next to temp next
		temp->next = newNode; // set temp next to newNode
	}
}

// print the passengers of the ordered list
void printList(node *head)
{
	node *temp = head; // temporary node
	while (temp != NULL)
	{
		printf("Passenger ID: %d\n", temp->person.id); // print id
		printf("%s ", temp->person.fname); // print first name
		printf("%s\n", temp->person.lname); // print last name
		printf("Account: $%.2lf\n", temp->person.balance); // print balance
		//if (temp->person.location == 1) // for debugging
		//{
                //   printf("On-board\n");
		//}
		//else
		//{
                //   printf("Off-board\n");
		//}
		printf("\n");
		temp = temp->next; // set temp to temp next
	}
}

// print the passenger
void printPass(node *temp)
{
   printf("Passenger ID: %d\n", temp->person.id); // print id
   printf("%s ", temp->person.fname); // print first name
   printf("%s\n", temp->person.lname); // print last name
   printf("Account: $%.2lf\n", temp->person.balance); // print balance
   printf("\n");
}

// free the memory allocated for the list
void deleteList(node **head)
{
	node *temp = *head; // temporary node
	while (*head != NULL)
	{
		temp = *head; // set temp to head
		*head = (*head)->next; // set head to head next
		free(temp); // free the memory of temp
	}
}

// find a node to print
node * findNode(node *head, int id)
{
   node *temp = head; // temporary node
   // traverse to the node
   while ((temp != NULL) && (temp->person.id != id)) // found node if id matches
   {
      temp = temp->next;
   }
   return temp; // return NULL if not found
}

// remove a node from the list
node * removeNode(node **head, int id)
{
   node *retVal = NULL; // node to return
   // no node to remove if list is empty
   if (*head == NULL)
   {
      retVal = NULL;
   }
   // head is the node to remove
   else if ((*head)->person.id == id)
   {
      retVal = *head; // set retVal to head
      *head = retVal->next; // set head to retVal next
      retVal->next = NULL; // set retVal next to NULL
   }
   else
   { // traverse to the node before
      node *temp = *head; // temporary node
      while ((temp->next != NULL) && (temp->next->person.id != id))
      {
         temp = temp->next; // set temp to temp next
      }
      if (temp->next != NULL)
      {
         retVal = temp->next; // set retVal to temp
	 temp->next = retVal->next; // set temp next to retVal next
	 retVal->next = NULL; // set retVal next to NULL
      }
   }
   return retVal;
}

// print the total and average money spent
void calculateTotal(node *head)
{
	node *temp = head; // temporary node
	int ctr = 0; // passenger counter
	double total = 0.00; // total money spent
	while (temp != NULL)
	{
		total += temp->person.balance; // update total
		ctr++;
		temp = temp->next; // set temp to temp next
	}
	printf("Total money spent       $%.2lf\n", total); // print total
	printf("Average Per Passenger   $%.2lf\n", (total/ctr)); // print average
	printf("\n");
}
