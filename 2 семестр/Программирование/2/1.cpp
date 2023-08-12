#include <iostream>
#include <math.h>
using namespace std;

void chislo()
{
     int x;
     cin >> x;
     if (x==0)
     {
     return;
     } 
     chislo();
     if (x>0)
     cout << x << endl;
     return;
}

main() 
{
chislo();       
system ("Pause");
return 0;
}
