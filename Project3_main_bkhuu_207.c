// Brandon Khuu G00975967
// CS 262, Lab Section 207
// Project 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Project3_llist_bkhuu_207.h"

#define GENSIZE 35
#define FNAME 25

// print the main menu
void mainMenu()
{
   printf("Read Passenger Manifest.................1\n");
   printf("Embark all passengers...................2\n");
   printf("Passenger Information...................3\n");
   printf("Print Menu..............................4\n");
   printf("Debark all passengers...................5\n");
   printf("Quit....................................6\n");
   printf("\n");
}

// print the passenger info menu
void passengerInfo()
{
   printf("Embark Passenger........................1\n");
   printf("Debark Passenger........................2\n");
   printf("Passenger OnBoard Purchase..............3\n");
   printf("Passenger OffBoard Purchase.............4\n");
   printf("Synchronize Passenger Lists.............5\n");
   printf("Return to Main Menu.....................6\n");
   printf("\n");
}

// display the print menu
void printMenu()
{
   printf("Print Account for Single Passenger......1\n");
   printf("Print All Passenger Accounts............2\n");
   printf("Print Accounts for onShip Passengers....3\n");
   printf("Print Accounts for offShip Passengers...4\n");
   printf("Return to Main Menu.....................5\n");
   printf("\n");
}

int main()
{
   FILE *input; // create file variable
   char buffer[GENSIZE]; // buffer to read input
   char filename[GENSIZE]; // string to hold filename
   char choice = 0; // menu choice
   int on = 1; // program loop
   int subon = 0; // inner loops
   int id = 0; // passenger id
   char fname[FNAME]; // first name
   char lname[GENSIZE]; // last name
   double purchase = 0.00; // money spent

   node *onhead = NULL; // pointer to the onShip list head
   node *offhead = NULL; // pointer to the offShip list head
   node *temp = NULL; // pointer a node
   node *temp2 = NULL;

   // loop until program is exited
   while (on == 1)
   {
      mainMenu();
      printf("Enter a choice: "); // Prompt the user for valid input
      fgets(buffer, GENSIZE, stdin);  // Read the input from the keyboard and store it in the input variable
      sscanf(buffer, "%c", &choice);  // Extract the character value from input and store it in choice
      printf("\n");

      switch (choice)
      {
         case '1':
            printf("Enter a filename containing the Passenger Manifest: "); // Prompt the user for an input file
            fgets(buffer, GENSIZE, stdin);  // Read the input from the keyboard and store it in the buffer
	    sscanf(buffer, "%s", filename); // Extract the string from buffer and store it in filename
	    printf("\n");
            input = fopen(strcat(filename, ".txt"), "r"); // Open input file
	    if (input == NULL) { // Make sure file was opened properly
               printf("Couldn't open the file...\n"); // Print error message
	       printf("\n");
               break;
            }
	    // loop while input can be read in sets of 3
	    while (fscanf(input, "%d %s %s", &id, fname, lname) == 3)
	    {
               insertNodeSorted(&offhead, makeNode(id, fname, lname)); // create and insert node into off-board list
	    }
	    fclose(input); // Close the input file
            break;
         case '2':
	    temp = offhead; // set temp to offhead
	    // loop until the off-board list is empty
	    while (offhead != NULL)
	    {
	       temp = offhead; // set temp to offhead
	       offhead = offhead->next; // set head to head next
	       if (temp->person.location == 1)
	       {
                  printf("%s ", temp->person.fname); // print first name
                  printf("%s must have slipped past security.\n", temp->person.lname); // print last name
		  printf("\n");
	       }
	       else
	       {
	          temp->person.location = 1; // set temp location to on-board
	       }
               insertNodeSorted(&onhead, removeNode(&temp, temp->person.id)); // remove temp from off-board list and insert into on-board
            }
            break;
         case '3':
	    subon = 1;
            while (subon == 1)
	    {
               passengerInfo();
               printf("Enter a choice: "); // Prompt the user for valid input
               fgets(buffer, GENSIZE, stdin);  // Read the input from the keyboard and store it in the input variable
               sscanf(buffer, "%c", &choice);  // Extract the character value from input and store it in choice
               printf("\n");

               switch (choice)
               {
                  case '1':
                     printf("Enter a Passenger ID: "); // Prompt the user for valid input
                     fgets(buffer, GENSIZE, stdin);  // Read the input from the keyboard and store it in the input variable
                     sscanf(buffer, "%d", &id);  // Extract the integer value from input and store it in id
                     printf("\n");

		     if (findNode(offhead, id) != NULL) // node is in off-board list
                     {
			temp = removeNode(&offhead, id); // remove node from off-board list
	                if (temp->person.location == 1)
	                {
                           printf("%s ", temp->person.fname); // print first name
                           printf("%s must have slipped past security.\n", temp->person.lname); // print last name
		           printf("\n");
	                }
	                else
	                {
	                   temp->person.location = 1; // set temp location to on-board
	                }
                        insertNodeSorted(&onhead, temp); // insert node into on-board list
		     }
		     else
	             {
                        if (findNode(onhead, id) != NULL) // node is in on-board list
			{
                           printf("Passenger already on-board.\n");
		           printf("\n");
		        }
			else
			{
                           printf("Passenger ID not found...\n"); // print error message
			   printf("\n");
			}
	             }
                     break;
                  case '2':
                     printf("Enter a Passenger ID: "); // Prompt the user for valid input
                     fgets(buffer, GENSIZE, stdin);  // Read the input from the keyboard and store it in the input variable
                     sscanf(buffer, "%d", &id);  // Extract the integer value from input and store it in id
                     printf("\n");

		     if (findNode(onhead, id) != NULL) // node is in on-board list
                     {
			temp = removeNode(&onhead, id); // remove node from on-board list
	                if (temp->person.location == 0)
	                {
                           printf("%s ", temp->person.fname); // print first name
                           printf("%s must have slipped past security.\n", temp->person.lname); // print last name
		           printf("\n");
	                }
	                else
	                {
	                   temp->person.location = 0; // set temp location to off-board
	                }
                        insertNodeSorted(&offhead, temp); // insert node into off-board list
		     }
		     else
	             {
                        if (findNode(offhead, id) != NULL) // node is in off-board list
			{
                           printf("Passenger already off-board.\n");
		           printf("\n");
		        }
			else
			{
                           printf("Passenger ID not found...\n"); // print error message
			   printf("\n");
			}
	             }
                     break;
                  case '3':
                     printf("Enter a Passenger ID: "); // Prompt the user for valid input
                     fgets(buffer, GENSIZE, stdin);  // Read the input from the keyboard and store it in the input variable
                     sscanf(buffer, "%d", &id);  // Extract the integer value from input and store it in id
                     printf("\n");

                     printf("Amount of Purchase: $"); // Prompt the user for valid input
                     fgets(buffer, GENSIZE, stdin);  // Read the input from the keyboard and store it in the input variable
                     sscanf(buffer, "%lf", &purchase);  // Extract the double value from input and store it in purchase
                     printf("\n");

		     temp = findNode(onhead, id);
		     if (temp != NULL) // node is in on-board list
                     {
	                if (temp->person.location == 0)
	                {
                           printf("%s ", temp->person.fname); // print first name
                           printf("%s has an incorrect location.\n", temp->person.lname); // print last name
		           printf("\n");
			   temp->person.location = 1; // set temp location to on-board
	                }
			temp->person.balance += purchase; // update balance
		     }
		     else
	             {
			temp = findNode(offhead, id);
                        if (temp != NULL) // node is in off-board list
			{
                           printf("%s ", temp->person.fname); // print first name
                           printf("%s must have slipped past security.\n", temp->person.lname); // print last name
		           printf("\n");
	                   temp->person.location = 1; // set temp location to on-board
			   temp->person.balance += purchase; // update balance
		        }
			else
			{
                           printf("Passenger ID not found...\n"); // print error message
			   printf("\n");
			}
	             }
                     break;
                  case '4':
                     printf("Enter a Passenger ID: "); // Prompt the user for valid input
                     fgets(buffer, GENSIZE, stdin);  // Read the input from the keyboard and store it in the input variable
                     sscanf(buffer, "%d", &id);  // Extract the integer value from input and store it in id
                     printf("\n");

                     printf("Amount of Purchase: $"); // Prompt the user for valid input
                     fgets(buffer, GENSIZE, stdin);  // Read the input from the keyboard and store it in the input variable
                     sscanf(buffer, "%lf", &purchase);  // Extract the double value from input and store it in purchase
                     printf("\n");

		     temp = findNode(offhead, id);
		     if (temp != NULL) // node is in off-board list
                     {
	                if (temp->person.location == 1)
	                {
                           printf("%s ", temp->person.fname); // print first name
                           printf("%s has an incorrect location.\n", temp->person.lname); // print last name
		           printf("\n");
			   temp->person.location = 0; // set temp location to off-board
	                }
			temp->person.balance += purchase; // update balance
		     }
		     else
	             {
			temp = findNode(onhead, id);
                        if (temp != NULL) // node is in on-board list
			{
                           printf("%s ", temp->person.fname); // print first name
                           printf("%s must have slipped past security.\n", temp->person.lname); // print last name
		           printf("\n");
	                   temp->person.location = 0; // set temp location to off-board
			   temp->person.balance += purchase; // update balance
		        }
			else
			{
                           printf("Passenger ID not found...\n"); // print error message
			   printf("\n");
			}
	             }
                     break;
                  case '5':
	             temp = offhead; // set temp to offhead
	             // loop through the off-board list
	             while (temp != NULL)
	             {
	                if (temp->person.location == 1) // wrong list
	                {
			   temp2 = temp->next; // set temp2 to temp next
                           insertNodeSorted(&onhead, removeNode(&offhead, temp->person.id)); // remove temp from off-board list and insert into on-board
	                }
			else
		        {
			   temp2 = temp->next; // set temp2 to temp next
			}
			temp = temp2; // set temp to temp2
                     }
	             temp = onhead; // set temp to onhead
	             // loop through the on-board list
	             while (temp != NULL)
	             {
	                if (temp->person.location == 0) // wrong list
	                {
		           temp2 = temp->next; // set temp2 to temp next
                           insertNodeSorted(&offhead, removeNode(&onhead, temp->person.id)); // remove temp from on-board list and insert into off-board
	                }
			else
		        {
			   temp2 = temp->next; // set temp2 to temp next
			}
			temp = temp2; // set temp to temp2
                     }
                     break;
                  case '6':
                     subon = 0; // Return to main menu
                     break;	   
                  default:
                     printf("Not a valid choice.\n"); // Display error message.
		     printf("\n");
               } 
	    }
            break;
         case '4':
	    subon = 1;
            while (subon == 1)
	    {
               printMenu();
               printf("Enter a choice: "); // Prompt the user for valid input
               fgets(buffer, GENSIZE, stdin);  // Read the input from the keyboard and store it in the input variable
               sscanf(buffer, "%c", &choice);  // Extract the character value from input and store it in choice
               printf("\n");

               switch (choice)
               {
                  case '1':
                     printf("Enter a Passenger ID: "); // Prompt the user for valid input
                     fgets(buffer, GENSIZE, stdin);  // Read the input from the keyboard and store it in the input variable
                     sscanf(buffer, "%d", &id);  // Extract the integer value from input and store it in id
                     printf("\n");
		     temp = findNode(onhead, id);
		     if (temp == NULL) // not in on-board list
		     {
                        temp = findNode(offhead, id); 
		        if (temp == NULL) // not in off-board list
		        {
                           printf("Passenger ID not found...\n"); // print error message
			   printf("\n");
		        }
			else
		        {
			   printPass(temp); // print passenger
	                }
		     }
		     else
		     {
                        printPass(temp); // print passenger
		     }
                     break;
                  case '2':
		     if (onhead == NULL) // on-board list is empty
		     {
                        printf("All passengers are off-board.\n");
			printf("\n");
	             }
		     else
		     {
                        printf("On-board Passengers:\n");
                        printList(onhead); // print on-board list
		     }
		     if (offhead == NULL) // off-board list is empty
		     {
                        printf("All passengers are on-board.\n");
			printf("\n");
	             }
		     else
		     {
                        printf("Off-board Passengers:\n");
                        printList(offhead); // print off-board list
		     }
                     break;
                  case '3':
		     if (onhead == NULL) // on-board list is empty
		     {
                        printf("All passengers are off-board.\n");
			printf("\n");
	             }
		     else
		     {
                        printf("On-board Passengers:\n");
                        printList(onhead); // print on-board list
		     }
                     break;
                  case '4':
		     if (offhead == NULL) // off-board list is empty
		     {
                        printf("All passengers are on-board.\n");
			printf("\n");
	             }
		     else
		     {
                        printf("Off-board Passengers:\n");
                        printList(offhead); // print off-board list
		     }
                     break;
                  case '5':
                     subon = 0; // Return to main menu
                     break;	   
                  default:
                     printf("Not a valid choice.\n"); // Display error message.
		     printf("\n");
               }
	    }
            break;
         case '5':
	    temp = onhead; // set temp to onhead
	    // loop until the on-board list is empty
	    while (onhead != NULL)
	    {
	       temp = onhead; // set temp to onhead
	       onhead = onhead->next; // set head to head next
	       if (temp->person.location == 0)
	       {
                  printf("%s ", temp->person.fname); // print first name
                  printf("%s must have slipped past security.\n", temp->person.lname); // print last name
		  printf("\n");
	       }
	       else
	       {
	          temp->person.location = 0; // set temp location to off-board
	       }
               insertNodeSorted(&offhead, removeNode(&temp, temp->person.id)); // remove temp from on-board list and insert into off-board
            }
            calculateTotal(offhead);
            break;
         case '6':
            on = 0; // Exit the program
            deleteList(&onhead); // delete on-board list
	    deleteList(&offhead); // delete off-board list
	    onhead = NULL;
	    offhead = NULL;
            printf("Program terminated.\n");
            break;	   
         default:
            printf("Not a valid choice.\n"); // Display error message.
	    printf("\n");
      }
   }
   return 0;
}


