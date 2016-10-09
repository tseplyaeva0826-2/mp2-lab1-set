#include "tbit_field.h"
#include "stdlib.h"


//-------------------CONSTRUCTERS----------------------------

tbit_field :: tbit_field( int l)
{
	N=l;
	psize= (l+sizeof(int)*8-1)/(sizeof(int)*8);
}

tbit_field :: tbit_field(const tbit_field &ab)
{
	N=ab.N;
	psize=ab.psize;
	p=new int[psize];
	if (p != NULL) 
	{
		for (int i=0; i<psize; i++) { p[i] =ab.p[i]; }
	}
}

tbit_field :: ~tbit_field()
{
	delete p;
	p = NULL;
}

//------------------------------------------------------------


int tbit_field :: getindex(int i)
{
	int c;
	c= i/(sizeof(int)*8);
	return c;
}

int tbit_field :: getmask(int i)
{
	int m;
	m= i%(sizeof(int)*8);            
	int j = i<<m; 
	 return j;
}



//----------ACCESS TO BIT-------------------------------------


 bool  tbit_field :: identifybit (int i)
 {
	 bool b;
	 b= p[getindex(i)]&&getmask(i);
	 if ((i>-1)&&(i<i))
		 return b;
	 else return 0;
 }

 int tbit_field :: getlength (void) 
 {
	 return N;
 }

 void tbit_field :: setbit ( int i)
 {
	 if ( (i>-1) && ( i< N))
		 p[getindex(i)]=p[getindex(i)] | getmask(i);

 }

 void tbit_field :: clrbit ( int i)
 {
	 if ( (i>-1) && ( i< N))
		 p[getindex(i)]=p[getindex(i)] & ~getmask(i);

 }





 //----------BIT OPERATIONS-------------------------------------------

 int tbit_field :: operator== ( tbit_field &ab) //comp
 {
	 int res=1;
	 if ( N!= ab.N) res=0;
	 else
	 for (int i=0; i< N; i++)
		 if ( p[i]!=ab.p[i]) 
		 {
			 res=0; break;
		 }
	return res;
 }

 tbit_field& tbit_field:: operator= (tbit_field &ab) //assing
 {
	 N=ab.N;
	 if ( psize != ab.psize)
	 { psize = ab.psize;
	   if ( p!= NULL ) delete p;
	   p = new int[psize];
	 }
	 if ( p!=NULL )
		 for ( int i=0; i< N; i++)
			 p[i]=ab.p[i];
	 return *this;
 }

 tbit_field  tbit_field:: operator|  (tbit_field &ab)
 {
	 int i, len = N;
	 if( ab.N> len) len = ab.N;
	 tbit_field L(len);
	 for (i=0; i< psize; i++) L.p[i]=p[i];
	 for (i=0; i< ab.psize; i++) L.p[i]= L.p[i] | ab.p[i];
	 return L;
 }

 tbit_field  tbit_field:: operator&  (tbit_field &ab)
 {
	 int i, len = N;
	 if( ab.N> len) len = ab.N;
	 tbit_field L(len);
	 for (i=0; i< psize; i++) L.p[i]=p[i];
	 for (i=0; i< ab.psize; i++) L.p[i]= L.p[i] & ab.p[i];
	 return L;
 }
  
 tbit_field  tbit_field:: operator~  (void)
 {
	 int len =N;
	 tbit_field L(len);
	 for ( int i=0; i<psize;i++)
		 L.p[i]= ~p[i];
	 return L;
 }

 //-------------------FRIEND--------------------------------------------

 istream &operator>>(istream &istr, tbit_field &ab)
 {
	 int i=0;
	 char ch;
	 
	 do {istr >> ch;} while (ch != ' ');

	 while (1) 
	 { istr >>ch;
	 if (ch=='0') ab.clrbit(i++);
	 else 
	if (ch=='1') ab.setbit(i++); else break;
	 }
	 return istr;

 }

 ostream &operator<<(ostream &ostr, tbit_field &ab)
 {
	 int len = ab.getlength();
	 for (int i =0; i<len; i++)
		 if (ab.identifybit(i)) ostr <<'1'; else ostr <<'0';
	 return ostr;
 }