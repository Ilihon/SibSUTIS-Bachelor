#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main()
{   int c;
    printf("Input number months:\n");  
	scanf("%d",&c);
    switch(c)
    {
      case -9: printf ("minus nine");break;
      case -8: printf ("minus eight");break;
      case -7: printf ("minus seven");break;
      case -6: printf ("minus six");break;
      case -5: printf ("minus five");break;
      case -4: printf ("minus fore");break;
      case -3: printf ("minus three");break;
      case -2: printf ("minus two");break;
      case -1: printf ("minus one");break;
      case 0: printf (" zero");break;
      case 1: printf ("one");break;
      case 2: printf ("two");break;
      case 3: printf ("three");break;
      case 4: printf ("fore");break;
      case 5: printf ("five");break;
      case 6: printf ("six");break;
      case 7: printf ("seven");break;
      case 8: printf ("eight");break;
      case 9: printf ("nine");break;
     
      default: printf("please enter true number \n"); main();
    }
    system("PAUSE");
    return 0;
}
