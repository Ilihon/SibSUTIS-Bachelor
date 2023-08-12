#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* clear(char* s)
{
      int i;
      for (i = 0; i < 20; i++)
      s[i] = ' ';
      return s;
}

main()
{
	char str[10000], strcopy[1000][20], copy[20];
	int i, j, v, n, u;
	gets(str);
	i = 0; j = 0;
	u = 0;
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
	for (i = 0; i <= u; i++)
	{
		for (j = i+1; j <= u; j++)
		{
			if (strcmp(strcopy[i], strcopy[j]) > 0)
			{
				strcpy(copy, strcopy[i]);
				strcpy(strcopy[i], strcopy[j]);
				strcpy(strcopy[j], copy);
			}
			clear(copy);
		}
	}
	for (i = 0; i <= u; i++)
		puts(strcopy[i]);
		system("PAUSE");
	return 0;
}
