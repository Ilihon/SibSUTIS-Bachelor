#include <stdio.h>
#include <stdlib.h>
#include <string.h>
main()
{
  char s1[] = "haleluah", s2[10];
  strncpy ( s2, s1, 3 ); // ����������� 3 ������� �� s1 � s2
puts ( s2 ); // ������! ��� ���������� '\0'


system("PAUSE");
}
