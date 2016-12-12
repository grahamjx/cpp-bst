/*
 Name: Joel Graham 
 Course: CS 163
 Programming Assignment #4

 File: rental_info.h

 Purpose: This file declares the struct "rental_info". This struct holds the data that is used by the table class.
 Each variable for a given instance of the struct (a_rental) is set to the information entered by the user in main.
 When the object is passed from main into the table class function "insert", a private recursive function is called
 to handle the insert into the tree. When a new node is created, the table class private function "copy" is called
 which handles the deep copy of the infromation from the passed in object (a_rental) to whatever node requires the
 information (root->data). See "copy" function in table.cpp for more clarification. */

#ifndef RENTAL_INFO_H
#define RENTAL_INFO_H

struct rental_info
{
    int  bedrooms;
	int  price;
	int  square_feet;
    char* location;
    char* nickname;
};
#endif
