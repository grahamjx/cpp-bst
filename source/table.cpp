/*
 Name: Joel Graham 
 Course: CS 163
 Programming Assignment #4

 File: table.cpp

 Purpose: This file contains the function definitions for the class "table" found in "table.h".
 These functions are used to carry out proccess that deal with the Table ADT and its corresponding
 data structure (binary search tree). Creating and destroying the table, creating nodes,
 deleting nodes, and searching / extracting data from nodes are some of the operations carried out by this file.

 Input:   This file utilizes input provided from main function as entered by the user as well as from the "rental_info"
 struct which supplies the data for each individual node.

 Output:  Displays a limited amount of information found in each node out to the user (main function).
 */

#include "table.h"
#include <iostream>
#include <cstring> //Included to allow the use of strcpy, strlen in member functions. Also was required for Unix g++ compile.

using namespace std;

//Sets the BST root pointer to null
table::table()
{
    root = NULL;
}

//Destroys the table by removing all the nodes in the BST recursively
table::~table()
{
    destroy_tree(root);
}


/*This function takes in the rental_info object "a_rental" that contains the information entered
 by the user. The object is then passed to the private recursive function "insert_tree" along
 with the root pointer in order to add the item to the BST in the correct position. This function acts
 as a "wrapper" function to protect the client side of the program from accessing the recursive
 insert operation. */

void table::insert(rental_info& a_rental)
{
    insert_tree(root, a_rental);
}


/*This function takes in a character array from main that contains a possible "nickname"
 identifier that the user would like to remove. If the table is empty (BST is empty), the function
 returns zero. If the table is not empty, the removal key, a count integer and the root pointer are
 passed to the private recursive function "remove_tree" which searches and removes the item(s) that
 match the removal key. Since count is passed as a reference into remove_tree, the value of count will be
 the number of items that were found and deleted once the recursion is complete. The value is then returned
 back to the main function "remove" which utlizes the value for displaying certain messages. */

int table::remove(const char removal_key[])
{
    int count = 0;

    if (root == NULL)
        return 0;
    else
        remove_tree(root, removal_key, count);
    return count;
}

/*This function takes in a character array from main that contains a possible "nickname" identifier that the
 user would like to find. It also takes an empty array of rental_info objects so that matching items can be
 added to the array for displaying them back in main. If the table is empty (BST is empty), the function returns zero.
 If the table is not empty, the search_word, a count integer, the empty array of rental_info objects and the root
 pointer are passed to the recursive function "search_nickname" which searches for item(s) that match the search word.
 If an item is found during the recursion, the data is copied into the array using the copy function. In additon, the count
 integer will be updated as items are found. Once the recursive function is complete, this function returns count back
 to the main function "search" which utlizes the value for display certain messages / data. */

int table::retrieve_nickname(const char search_key[], rental_info results[])
{
    int count = 0;

    if (root == NULL)
        return 0;
    else
        search_nickname(root, search_key, results, count);
    return count;
}


/*This function takes in a price range determined by start_price and end_price.
 It also takes in an empty array of rental_info objects so that matching items can be added to the array
 for displaying them back in main. If the table is empty (BST is empty), the function returns zero.
 If the table is not empty, the start_price, the end_price, a count integer, the empty array of rental_info
 objects and the root pointer are passed to the recursive function "search_price" which searches for item(s) that
 fall between the given price range. If an item is found during the recursion, the data is copied into the
 array using the copy function. In additon, the count integer will be updated as items are found. Once the
 recursive function is complete, this function returns count back to the main function "search" which utlizes
 the value for display certain messages / data. */

int table::retrieve_price(const int start_price, const int end_price, rental_info results[])
{
    int count = 0;

    if (root == NULL)
        return 0;
    else
        search_price(root, start_price, end_price, results, count);
    return count;
}


/*This function allows displaying all data in-order. If the table is empty (BST is empty) then the function
 returns zero. If the table is not empty, the root pointer is passed to private recursive function "display_tree"
 which displays all the data currently in the BST in-order. */

int table::display()
{
    if (root == NULL)
        return 0;
    else
        display_tree(root);
    return 1;
}


/*This function takes in two rental objects that are passed as reference. This function is used in order to
 generate a deep copy of the data in each node. to_rental = from_rental will copy the three non-dynamic int variables
 (bedrooms, price, square_feet). Since the other two data variables utilize dynamic character arrays, the memory
 space of the "to" object for both location and nickname is assigned a new char array value that is exactly the size
 of the "from" location and nickname. Once the memory is allocated, the value of location and nickname associated with
 the "from" object is copied to the new memory space of the "to" object. This function is used in a variety of places
 including: insert, insert_tree, search_price, search_nickname, remove_tree. */

void table::copy(rental_info &to_rental, rental_info &from_rental)
{
    to_rental = from_rental;
    to_rental.location = new char[strlen(from_rental.location)+1];
    to_rental.nickname = new char[strlen(from_rental.nickname)+1];
    strcpy(to_rental.location, from_rental.location);
    strcpy(to_rental.nickname, from_rental.nickname);
}

/*This recursive function displays all the data in the BST in-order. This task is accomplished by taking in the root pointer
 and then setting it to root->left for each successive function call. The recursion will continue until root is null which means
 that it has reached the farthest left node. As the recursive frames pop off the program stack, each node's data will be displayed.
 It will then call the recursive function with root set to right->right to see if there is a right child associated with that node.
 This process continues as it pops off the stack, displaying each node's data. Eventually root will be set to the original root's right node
 (if there is one) and the proccess repeats it self in the same manner. Simple terms: displays in this order (left, root, right) with each
 iteration of root representing a potential subtree.*/

void table::display_tree(node * root)
{
    if (root)
    {
        display_tree(root->left);

        cout << "\nBedrooms: " << root->data.bedrooms << endl;
        cout << "Price: " << root->data.price << endl;
        cout << "Square Feet: " << root->data.square_feet << endl;
        cout << "Location: " << root->data.square_feet << endl;
        cout << "Nickname: " << root->data.nickname << endl;

        display_tree(root->right);
    }
}


/*This recursive function is used for adding rental information to the BST. This task is accomplished by taking in a reference to
 the external root pointer as well as the data object that contains new rental information. If root is null, this would mean that the
 tree is empty or the recursive function has reach the end of the tree. For this implementation of the BST, items are always added at
 the leaf, so this one 'if' statement can handle adding any information at the appropriate position. If root is not null when the function
 is called, it compares the new 'nickname' entry with the root->data 'nickname' entry. If the comparison is less than, then the same
 function is called again with the root being set to root->left since smaller items get added to the left side in a BST. If the comparison
 is equal or greater than the current root, the item is added to the right hand side of the BST. It is helpful to remember that for each
 iteration of the function, root is tracking a position in the BST similar to how a 'current' variable is used in irrative loop implementations. */

void table::insert_tree(node * &root, rental_info &a_rental)
{
    if (!root) //Adding data to the BST as a leaf
    {
        root = new node;
        copy(root->data, a_rental); //Data is copied into the tree
        root->left = NULL;
        root->right = NULL;
    }
    else
    {
        if(strcmp(a_rental.nickname, root->data.nickname) < 0) //If the new nickname is less than the current nickname
            insert_tree(root->left, a_rental); //Function is recalled with root set to root->left.
        else
            insert_tree(root->right, a_rental); //If greater than or equal to, function is recalled with root set to root->right.
    }
}


/*This recursive function is used to find items in the BST that fall within a given price range. This function works very similar to
 the display_tree recursive function. The function only gets called if root is not null which is handled by the public function 'retrieve price'.
 The function operates by taking in the root pointer and setting it to root->left. The recursion will continue until root is null which means
 that it has reached the farthest left node. As the recursive frames pop off the program stack, each node's data that is greater/equal to the starting
 price but less then or equal to the ending price will be copied into the results array. It will then call the recursive function with root set to
 right->right to see if there is a right child associated with that node. This process continues as it pops off the stack, coping each node's data
 that matches the criteria. Eventually root will be set to the original root's right node (if there is one) and the proccess repeats it self
 in the same manner. Simple terms: data that falls in the range is copied into the array in this order (left, root, right) with each iteration of root
 representing a potential subtree. */

void table::search_price(node * root, const int price_start, const int price_end, rental_info results[], int& count)
{
    if (root)
    {
        search_price(root->left, price_start, price_end, results, count); //All the way left

        if (root->data.price >= price_start && root->data.price <= price_end) //If item is greater/equal starting price but less/equal to ending price
        {
            copy(results[count], root->data); //If both criteria are met, data is copied into the array
            count++;
        }

        search_price(root->right, price_start, price_end, results, count); //All the way right
    }
}


/*This recursive function is used to finding items in the BST that match a given nickname. If root is initially null
 or becomes null via the recursive process, than the BST is empty or the item was not found. If root it not null, it first
 checks the root->data's 'nickname' to see if it is equal to the passed in search word. If successful, the matching data is
 copied into the passed in 'results' array using the copy function, the count variable is increased and then the function
 is called again with root being set to root->right. This is done to check for the next possible matching item that has the
 same nickname. If the variables do not equal, it compares to see if the search word is less than then root->data's 'nickname'.
 If less than, the is function called again with root being set to root->left. If greater than, function is called with
 root being set to root->right. Function will continue until root becomes null at which point the wrapper function will return
 the count variable back to main and the found results will be displayed.*/

void table::search_nickname(node * root, const char search_word[], rental_info results[],int &count)
{
    if (root)
    {
        if(strcmp(search_word, root->data.nickname) == 0) // If the search word and current nickname match
        {
            copy(results[count], root->data); // Copy the data into the array
            count++;
            search_nickname(root->right, search_word, results, count); //Set root to root->right to look for another matching item
        }
        else if(strcmp(search_word, root->data.nickname) < 0) //If search word is less than current nickname
            search_nickname(root->left, search_word, results, count); //Recalls the function with root set to root->left
        else
            search_nickname(root->right, search_word, results, count); //Sets root to root->right if search word is greater than current nickname.
    }
}

/*This recursive function is used for deleting items from the BST. Since removing items from a BST requires a few special cases, this function
 is best split up into a few parts.

 General: This function takes in a reference to the external root pointer which is called "tracker" in this implementation for clarity. The function
 also takes in a key (nickname) that the user would like to find and remove from the BST. In addition, a count variable is also passed in in order to keep
 track of the number of items that were found and removed from the BST.

 Basics: This function works using recursion and will continue until tracker is equal to null. This will let the wrapper function 'remove' know that the BST is
 empty or that is has finished searching through the whole tree. The three initial checks on the removal key are: 1. If there is a match, 2. If the removal key
 is less than the current 'nickname', 3. If the removal key is greater than the current 'nickname'. These three checks are carried out by the first nested if
 (match), the else if near the bottom of the function (less than) and the final else at the end of the function (greater than).

 1. A Match - If there is a match (the passed in key matches the current root's nickname) then the function begins stepping through the multiple conditionals
 in order to effectively remove the item from the BST.

    Case A: If the item to be removed is a leaf (both the right and left pointers are NULL). Item is removed and that specific instance of root is set to NULL.

    Case B: If the item to be removed is in a node that has one child (right pointer is NOT NULL and the left pointer is NULL). The temporary pointer 'current'
    is set to the item that needs to be removed (tracker). Tracker is then set to the only child (tracker->right) and the old parent (current) is removed.

    Case C: This case is just the reciprocal of Case B. If the item to be removed in in a node that has one child (right pointer is NULL and the left pointer is
    NOT NULL). The temporary pointer 'current' is set to the item that needs to be removed (tracker). Tracker is then set to the only child (tracker->left) and
    the old parent (current) is removed.

    Case D: This case handles the removal of an item if there is two children (both the right and left pointers are NOT NULL). The temporary pointer 'current'
    is set to tracker->right. At this point, the case can be best represented as two separate scenarios.

        Case D-1: After current is set to tracker->right, a check is done to see if that node has any left chldren. This is done in order to find the in-order successor.
        If there is no left children after current is set, then current is the in-order successor. The data is copied from current to tracker, tracker's right pointer
        is set to current's right pointer in order to connect the nodes up. Then current is removed which contains the duplicate data that was copied into tracker.

        Case D-2: If current does have a left child, a simple while loop is used to find the in-order successor. A previous pointer is used to keep track of the node
        just before the one that needs to be removed in order to reconnect the nodes. Once current->left is NULL, we have reach the in-order successor which is set to
        current. The data from current is copied into tracker, the previous->left pointer is set to current's right pointer to connect the nodes and then current
        is deleted.

 2. If removal key is less than the current tracker's nickname, function is recalled with tracker set to tracker->left.

 3. If removal key is greater than the current tracker's nickname, function is recalled with tracker set to tracker->right. */

void table::remove_tree(node * &tracker, const char key[], int& count)
{
    node * current;
    node * previous;

    if (tracker)
    {
        if(strcmp(key, tracker->data.nickname) == 0) //Checks to see if remove_key matches the current tracker's nickname.
        {
            if (tracker->right == NULL && tracker->left == NULL) //Case A: Item to be removed is a leaf
            {
                delete tracker;
                tracker = NULL;
            }

            else if(tracker->right != NULL && tracker->left == NULL) //Case B: Item to be removed has one child (On the Right)
            {
                current = tracker; //Current is set to tracker (item to be removed)
                tracker = tracker->right; //Tracker is set to its child (adopted)
                delete current; //Old item is deleted
                current = NULL;
            }

            else if(tracker->right == NULL && tracker->left != NULL) //Case C: Item to be removed has one child (On the Left)
            {
                current = tracker; //Current is set to tracker (item to be removed)
                tracker = tracker->left; //Tracker is set to its child (adopted)
                delete current; //Old item is deleted
                current = NULL;
            }

            else if(tracker->right != NULL && tracker->left != NULL) //Case D: Item to be removed has two children
            {
                current = tracker->right; //Current is set to tracker's right child

                if (current->left == NULL) //Case D-1: If tracker's right child (current) has no left children, then current is the in-order successor.
                {
                    copy(tracker->data, current->data); //Current's data is copied to to tracker
                    tracker->right = current->right; //Tracker's right pointer is set to current's right pointer to connect up the nodes.
                    delete current; //Duplicate item is removed since its info was copied to a new location
                    current = NULL;
                }
                else
                {
                    while (current->left) //Case D-2: If tracker's right child (current) has a left child
                    {
                        previous = current; //Used to track the previous node
                        current = current->left; //Current is set to current->left to find the left most node
                    }
                    copy(tracker->data, current->data); //Once current->left is Null, current is the in-order successor so the data is copied to tracker.
                    previous->left = current->right; //Previous's left pointer is set to current's right pointer to connect up the nodes.
                    delete current; //Duplicate item is removed since its info was copied to a new location.
                    current = NULL;
                }
            }
            count++;
            remove_tree(tracker, key, count); //The process repeats with standard tracker (since is has been changed via item removal) to find if there is another item
                                              //that matches the same removal key.
        }
        else if(strcmp(key, tracker->data.nickname) < 0)
            remove_tree(tracker->left, key, count);
        else
            remove_tree(tracker->right, key, count);
    }
}

/*This function deletes all the nodes in the BST recursively. Works similar to the display_tree recursive function but instead removes all
the item in post-order. This is done so that when a item is deleted, the function does not trying to access and remove information that was
previous removed. */

void table::destroy_tree(node * &root)
{
    if (root)
    {
        destroy_tree(root->left);
        destroy_tree(root->right);
        if (root != NULL)
            delete root;
        root = NULL;
    }
}
