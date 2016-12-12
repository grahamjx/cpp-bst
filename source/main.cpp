/*
 Name: Joel Graham 
 Course: CS 163
 Programming Assignment #4

 File: main.cpp

 Purpose: This program simulates a rental information database application. Each property will be passed into
 the corresponding ADT which handles storage and manipulation of the data. Each property will be stored in one
 data structures, a binary search tree. The properties are inserted into the BST based on nickname. The user has the
 option to add, remove and search for properties as well as display all stored property information.

 Input: When executing this program, a_table (table.h) object is created as well as an rental_info object
 that passes the user information into the corresponding ADT. The data provided to the table is managed by the struct
 "rental_info" (See rental_info.h). The overall structure of the program back-end is managed by the table class (table.h / table.cpp).

 Output: The rental properties can be displayed in two ways. The main display function displays all the stored
 property information ordered by nickname. This is done by utlizing the "display" table class member function which traverses the
 BST, outputting the data in each node. The second output is done using the search function. An empty array of rental_info objects is
 passed into the "retrieve" table class member function(s) where items that match the requested search word are copied into the array.
 The data inside the "results" array is then displayed to the user.

 All additional output comes from this main.cpp file and relates to the user menu and various user prompts.
 */


#include "table.h"
#include <iostream>
#include <cstring>

using namespace std;

const int MAX_CHAR = 101;

void call_menu(void);
char read_input(const char prompt[]);
void run_input(char command, table& a_table);
void read_string (const char prompt[],char input_string[], int max_char);
void add_rental(table& a_table);
void search(table& a_table);
void display(table& a_table);
void remove(table& a_table);

/*The function primarily handles how the client side of the program is structured. After declaring some class objects and other local variables, the function
 proceeds to displaying the menu screen. User input from the menu is processed through the function 'read_input' before passing 'input' and the object 'a_table'
 as an argument into the 'run_input' function to perform additional processes. When the user is ready to quit the program, the input of 'q' will cause
 the program to terminate. */

int main ()
{
    table a_table;
    char input;

    call_menu();
	input = read_input("Please enter an option from the list: ");
	while (input != 'q')
	{
		run_input(input, a_table);
		call_menu();
		input = read_input("Please enter an option from the list: ");
	}
    return 0;
}

//Displays the menu options to the user.
void call_menu(void)
{
	cout << "\nWelcome to House Search!" << endl
    << "A. Add rental information" << endl
    << "R. Remove rental information" << endl
    << "S. Search rental properties" << endl
    << "D. Display all" << endl
    << "Q. Quit the program" << endl << endl;
}


/* Accepts a prompt from the main() function and displays it. Accepts user input, converts it to lower case
and passes it back to the main() function. */

char read_input(const char prompt[])
{
	char cmd;
	cout << prompt;
	cin >> cmd;

	cin.clear();
	cin.ignore(100, '\n');
	return tolower(cmd);
}


/* User input and object 'a_table' are passed into the function. A switch statement is used to process
 the command argument. The object is passed to this function and then passed again to add_rental in order
 to start adding properties. The objects also get passed as references into remove, search and display
 functions in order to have access to the class member functions. Any command other than the ones
 outlined in the menu is considered invalid and it returns back to main() */

void run_input(char command,table& a_table)
{
	switch (command)
        {
            case 'a': add_rental(a_table);
                break;
            case 'r': remove(a_table);
                break;
            case 's': search(a_table);
                break;
            case 'd': display(a_table);
                break;
        default: cout << "\nInvalid option, please select again." << endl;
            break;
        }
}


/* Prompts the user to enter values for each criteria of the rental property. Those values are passed
 to the set functions so that a_rental data variables are assigned the information. The rental_info
 object is then passed into the table class member function "insert" for insertion into the two data
 structures.
 */
void add_rental(table& a_table)
{
    rental_info a_rental;
    int bedrooms;
    int price;
    int square_feet;
    char location[MAX_CHAR];
    char nickname[MAX_CHAR];

    cout << "\nNumber of Bedrooms (Ex. 3): ";
    cin >> bedrooms;

    cout << "\nPrice (Ex. 900): ";
    cin >> price;

    cout << "\nSquare Feet (Ex. 800): ";
    cin >> square_feet;

    read_string("\nLocation (Ex. NW Portland): ",location,MAX_CHAR);
    read_string("\nProperty Nickname (Ex. Corner House): ", nickname, MAX_CHAR);


    a_rental.location = new char[strlen(location)+1];
    a_rental.nickname = new char[strlen(nickname)+1];

    a_rental.bedrooms = bedrooms;
    a_rental.price = price;
    a_rental.square_feet = square_feet;
    strcpy(a_rental.location, location);
    strcpy(a_rental.nickname, nickname);

    a_table.insert(a_rental);
}


/*Prompts the user how they would like the search for rental properties. If by price, the user is
 asked to enter a price which is passed as a character array into the class function "retrieve"
 along with the search choice and a reference to the rental_info "results" array. If by location,
 the same process takes place except the user is asked for a location. If netiher option is selected,
 the input is invalid and it starts over. Since "retrieve" returns the number of items found and
 deleted, a return of zero will mean that there was no items found for deletion. If the return value
 is greater than zero than a for loop is used to go through the "results" array and display each
 property that matched the search word. */

void search(table& a_table)
{
    rental_info results[MAX_CHAR];
    int size;
    char search_word[MAX_CHAR];
    int price_start;
    int price_end;
    int choice = 0;

    while (choice == 0)
    {
        cout << "\nHow would you like to search through the rental properties?" << endl
        << "1. By Nickname" << endl
        << "2. By Price" << endl
        <<"\nPlease enter an option from the list: ";
        cin >> choice;

        if (choice == 1)
        {
            read_string("\nPlease enter a nickname to search for (Ex. Corner lot): ",search_word,MAX_CHAR);
            size = a_table.retrieve_nickname(search_word,results);
        }
        else if(choice == 2)
        {
            cout << "\nEnter a starting price (Ex. 400): ";
            cin >> price_start;
            cout << "\nEnter an ending price (Ex. 900): ";
            cin >> price_end;

            size = a_table.retrieve_price(price_start, price_end, results);
        }
        else
        {
            cout << "\nInvalid input, please try again." << endl;
        }

    }

    if (size == 0)
    {
        cout << "\nSorry, no results were found using that search word." << endl;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            cout << "\nResult #" << (i+1) << ":" << endl;
            cout << "Bedrooms: " << results[i].bedrooms << endl;
            cout << "Price: " << results[i].price << endl;
            cout << "Square Feet: " << results[i].square_feet << endl;
            cout << "Location: " << results[i].location << endl;
            cout << "Nickname: " << results[i].nickname << endl;
        }
    }
}


/*Displays all the properties in the doubly linked list which is ordered by price. A return of zero
 means that the list is empty and more items need to be added. */

void display(table& a_table)
{
    int check;

    check = a_table.display();
    if(check == 0)
    {
        cout << "\nNo rental information available, please add some to the database." << endl;
    }
}

/*Prompts the user for a location they want to delete. The location is passed into the "remove"
 table class member function which searches for a match and deletes the item(s) if they exist.
 A return of zero means no items were found and deleted. If the return is greater than zero
 it lets the user know how many item(s) matched the entered location and were delete. */

void remove(table& a_table)
{
    int remove;
    char nickname[MAX_CHAR];

    read_string("\nPlease enter a nickname description that you would like to delete (Ex. Corner lot): ",nickname,MAX_CHAR);
    remove = a_table.remove(nickname);

    if (remove == 0)
    {
        cout << "\nNo rental information was found matching that location." << endl;
    }
    else
    {
        cout << "\n" << remove << " item(s) matched the nickname '" << nickname << "' and were deleted." << endl;
    }

}

/*This function accepts a prompt, a string of characters and a max length in which to process user input. Essentially, before the data is stored into
 and object, it is cut down to it's approximate size since the user is only allowed a certain number of characters for each data field. */

void read_string (const char prompt[],char input_string[], int max_char)
{
	cout << prompt;
	cin.get(input_string, max_char, '\n');
	while(!cin)
	{
		cin.clear ();
		cin.ignore (100, '\n');
		cin.get(input_string, max_char, '\n');
	}

	cin.clear();
	cin.ignore (100, '\n');
}
