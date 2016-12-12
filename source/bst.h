/*
 Name: Joel Graham 
 Course: CS 163
 Programming Assignment #4

 File: bst.h

 Purpose: This file declares the struct "node". This struct is used to build each node element of the binary search tree.
 Each node is comprised of a "rental_info" data object along with a left and right pointer. The data for each object is set
 to the information passed in from main function "add_rental". The external pointer "root" which points to the root of the tree
 (or internal sub tree when using recursion) is declared in table.h. */

#ifndef BST_H
#define BST_H

#include "rental_info.h"

struct node
{
    rental_info data;
    node * left;
    node * right;
};
#endif
