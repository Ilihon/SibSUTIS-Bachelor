#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main()
{   int m;
    printf("Input number of months:\n");  
	scanf("%d",&m);
    switch(m)
    {
      case 1:case 2:case 3:
      	printf("1 polovina goda \n1 kvartal"); break;
       case 4 :case 5: case 6:
       printf("1 polovina goda \n2 kvartal"); break;
        case 7:case 8: case 9:
       printf("2 polovina goda \n3 kvartal"); break;
     case 10:case 11: case 12:
       printf("2 polovina goda \n4 kvartal"); break;
      default: printf("please,input true months \n"); 
    }
    system("PAUSE");
    return 0;
}

