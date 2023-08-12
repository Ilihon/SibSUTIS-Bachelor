#include <iostream>
#include <math.h>
using namespace std;

void chislo(int x)
{
     if ((x/2)>0)
     {
     chislo(x/2);
     } 
     cout << (x%2);
     return;
}

main() 
{
	int x;
	cin >> x;
chislo(x);     
cout <<endl;  
system ("Pause");
return 0;
}
