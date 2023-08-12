# include <stdio.h>
# include <stdlib.h>
const int n=16;
main()
{
	int a[n],h,p,sum,i,m;
	
	sum=0;
	h=0;// h - chetnue
	p=0;// p - ne chetnue
	i=0;
	
		
    printf("write number your card's\n");
	
	for (i=0;i<n;i++)
	
	scanf("%d",&a[i]);
	
    for(i=0;i<n;i++)
    {

	if (i%2==0){
		h=h+a[i];
	}
	else{
		p=p+a[i];
	}
}
    m=(p*2);

    if(m>9)
   {
   	m=m-9;
   }

   sum=h+m;
    if(sum%10==0)
   {
   	printf("\n ALL Right\n");
   	printf("sum=%d\n", sum );
   }
   else{
   	printf("\n Card isn't normal, sorry=( \n ");
   	printf("sum=%d", sum );
   }
	system("PAUSE");
		return 0;
}
