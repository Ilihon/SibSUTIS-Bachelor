#include <stdio.h>
#include <stdlib.h>
#include <string.h>
main()
{
  char s1[] = "haleluah", s2[10];
  strncpy ( s2, s1, 3 ); // скопировать 3 символа из s1 в s2
puts ( s2 ); // ошибка! нет последнего '\0'


system("PAUSE");
}
