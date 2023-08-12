#include <stdlib.h> 
#include <stdio.h> 

using namespace std; 

int main() 
{ int m,d,t; 
printf("Input month,day,year  "); 
scanf("%d %d %d",&m,&d,&t); 
int m1=31; int m2=28; 
if(t%4==0) m2++; 
int m3=31; int m4=30; 
int m5=31; int m6=30; int m7=31; int m8=31; 
int m9=30; int m10=31; int m11=30; 
switch(m)
{ 
case 1: printf ("January %d\n",d); break; 
case 2: printf ("February %d\n",m1+d);break; 
case 3: printf ("March %d\n",m1+m2+d);break; 
case 4: printf ("April %d\n",m1+m2+m3+d);break; 
case 5: printf ("May %d\n",m1+m2+m3+m4+d);break; 
case 6: printf ("June %d\n",m1+m2+m3+m4+m5+d);break; 
case 7: printf ("July %d\n",m1+m2+m3+m4+m5+m6+d);break; 
case 8: printf ("August %d\n",m1+m2+m3+m4+m5+m6+m7+d);break; 
case 9: printf ("September %d\n",m1+m2+m3+m4+m5+m6+m7+m8+d);break; 
case 10: printf ("October %d\n",m1+m2+m3+m4+m5+m6+m7+m8+m9+d);break; 
case 11: printf ("October %d\n",m1+m2+m3+m4+m5+m6+m7+m8+m9+m10+d);break; 
case 12: printf("December %d\n",m1+m2+m3+m4+m5+m6+m7+m8+m9+m10+m11+d);break; 
default: printf("error %d\n"); main(); 

} 
system("PAUSE"); 
return 0;
}

