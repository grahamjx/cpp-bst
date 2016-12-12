/*
 Name: Joel Graham 
 Course: CS 163
 Programming Assignment #4

 File: table.h

 Purpose: This file is the core of the Table ADT and the class "table" created in this file acts as the manager of
 the data structures used in the project (Binary Search Tree). This class handles the initialization of the table
 (constructor), storing the data into individual nodes based on nickname (insert, insert_tree), removing data from
 the BST by nickname (remove, remove_tree), retrieving data by nickname or by price range and returning it to the user
 (retrieve_price, retrieve_nickname, search_nickname, search_price), displaying all the stored information back the user
 (display, display_tree) and the destruction of the table (destructor).

 This private section of the "table" class contain the external pointer used by BST. In addition, all the recursive function
 definitions associated with the pulic ADT operations are defined in the section. Also, the copy function used by a variety of
 functions to copy the data out of a rental_info object into the BST or 'results' array is also defined in the private section.

 The public functions act as 'wrappers' which utlize the private recursive functions to carry out direct operations
 on the BST. This is done in order to keep the access to the core data structure operations limited to the class and not provide
 direct access to the client side of the program. */

#ifndef TABLE_H
#define TABLE_H

#include "bst.h"
#include "rental_info.h"


class table
{
public:
    //Constructor
	table();

	//Destructor
	~table();

	void insert(rental_info& a_rental); //Adds a rental BST
    int remove(const char removal_key[]); //Removes a rental from the BST
    int retrieve_price(const int price_start, const int price_end, rental_info results[]); //Retrieves data that falls within the given price range.
    int retrieve_nickname(const char search_key[], rental_info results[]); //Returns items that match the search word back to main via 'results' array
    int display(); //Displays all stored information


private:

    //Recursive function that displays all the stored information in-order. Called by public function 'display'.
    void display_tree(node * root);

    //Recursive function that inserts items in the BST by nickname. Called by public function 'insert'.
    void insert_tree(node * &root, rental_info &a_rental);

    //Recursive function that searches for items that match the given search word. Called by public function 'retrieve_nickname'.
    void search_nickname(node * root, const char search_word[],rental_info results[], int& count);

    //Recursive function that searches for items that fall within the given price range. Called by public function 'retrieve_price'.
    void search_price(node * root, const int price_start, const int price_end, rental_info results[], int& count);

    //Removes items from the BST that match the provided removal key. Called by public function 'remove'.
    void remove_tree(node * &tracker, const char removal_key[], int& count);

    //Recursive function that removes all the items from the BST. Used by Destructor.
    void destroy_tree(node * &root);

    //Copies data from one rental_info object to another
    void copy(rental_info &to_rental, rental_info &from_rental);

    node * root;

};
#endif
