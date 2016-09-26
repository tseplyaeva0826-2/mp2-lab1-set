#include "tbit_field.h"
#include "stdlib.h"

tbit_field :: tbit_field( int l)
{
	N=l;
	memsize= (l+sizeof(int)*8-1)/(sizeof(int)*8);
}

tbit_field :: tbit_field(const tbit_field &ab)
{
	N=ab.N;
	memsize=ab.memsize;
	p=new int[memsize];
	if (p != NULL) 
	{
		for (int i=0; i<memsize; i++) { p[i] =ab.p[i]; }
	}
}

tbit_field :: ~tbit_field()
{
	delete p;
	p = NULL;
}

int tbit_field :: getindex(int i)
{
	int c;
	c= i/(sizeof(int)*8);
	return c;
}

int tbit_field :: getmask(int i)
{
	int m;
	m= i%(sizeof(int)*8);            //??????????
	int j = i<<m; 
	 return j;
}


 bool  