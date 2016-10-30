//Tseplyaeva 0826-2

#include <iostream>
using namespace std;
#pragma once 




class tbit_field 
{
	int N;									// a lenth of a bitfield (max)
	int *p;									//a pointer to an array 
	int psize;								// amount of elements of bitfield

	int getindex(int i);				    //index in p for a bit
	int getmask (int i);					//bitmask for bit i 
	
public :

	//cunstructors

	 tbit_field (int l);
	 tbit_field (const tbit_field &ab);
	 ~tbit_field();


	 //access to bits

	 bool identifybit (int i);				 // to identify if there is a bit on the ith place
	 int getlength (void) ;					 // to count bits
	 void setbit (int i);					 //to set a bit on the ith place
	 void  clrbit (int i);					 //to clear a bit from the ith place


	 //bit operations 

	 int operator== ( tbit_field &ab);		 //comparison
	 tbit_field& operator= ( tbit_field &ab);//assingment                                                 
	 tbit_field operator| (tbit_field &ab);  // or
	 tbit_field operator& (tbit_field &ab);  // and 
	 tbit_field operator~ (void);			 // not

	 //friend 

	 friend istream &operator>>(istream &istr , tbit_field &ab);
	 friend ostream &operator<<(istream &ostr , tbit_field &ab);

};