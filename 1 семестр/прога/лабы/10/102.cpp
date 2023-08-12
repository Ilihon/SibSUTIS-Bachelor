#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
 
void clear(char* s) 
{ 
 int i; 
 for (i = 0; i < 20; i++) 
 s[i] = ' '; 
} 
 
main() 
{ 
 char str[10000], strcopy[1000][20], copy[1000][20]; 
 int i, j, v, n, u; 
 gets(str); 
 i = 0; j = 0; 
 u = 0; v = 0; 
 n = 0; 
 while (str[i] != '\0') 
 { 
  if (str[i] != ' ' && str[i] != ',') 
  { 
   strcopy[u][j] = str[i]; 
   j++; 
  } 
  else 
  { 
   j = 0; 
   u++; 
  } 
  i++; 
 } 
 n = 1; 
 for (i = 0; i <= u; i++) 
 { 
  if (strcopy[i][0] == '1') continue; 
  for (j = i+1; j <= u; j++) 
  { 
   if (strcopy[j][0] == '1') continue; 
   if (strcmp(strcopy[i], strcopy[j]) == 0) 
   { 
    strcopy[j][0] = '1'; 
    n++; 
   } 
  } 
  printf("%d ", n); 
  puts(strcopy[i]); 
  n = 1; 
 } 
 system("PAUSE");
 return 0; 
}
