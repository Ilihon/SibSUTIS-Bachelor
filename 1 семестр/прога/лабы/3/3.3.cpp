#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main()
{   int a,b;
    printf("Input year ");  
	scanf("%d",&a);
	b=a%12;
    switch(b)
    {
      case 1: printf ("cock \n");break;
      case 2: printf ("dog \n");break;
      case 3: printf ("pig \n");break;
      case 4: printf ("rat \n");break;
      case 5: printf ("cow \n");break;
      case 6: printf ("tiger \n");break;
      case 7: printf ("rabbit \n");break;
      case 8: printf ("dragon \n");break;
      case 9: printf ("snake \n");break;
      case 10: printf ("horse \n");break;
      case 11: printf ("sheep \n");break;
      case 12: printf ("monkey \n");break;
      default: printf("try again \n"); main();
    }
    system("PAUSE");
    return 0;
}


