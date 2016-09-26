#pragma once 

class tbit_field {
	int N; // a lenth of a bitfield (max)
	int *p; //a pointer to an array 
	int memsize; // amount of elements of bitfield

	int getindex(int i); //index in memsize for a bit
	int getmask (int i); //bitmask for bit n 
	bool identifybit (int i);  // to identify if there is a bit on the nth place
public :
	//cunstructors
	 tbit_field (int l);
	 tbit_field (const tbit_field &ab);
	 ~tbit_field();


};