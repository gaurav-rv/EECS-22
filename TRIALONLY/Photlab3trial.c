#include<stdio.h>
#include<math.h>
#include<stdlib.h>
void main(){
int r,i=1,answer=0,m,j,rem;
printf("Enter a number to be converted to binary \n");
scanf("%d",&m);
    while (m!=0)
    {
        r=m%2;
        m/=2;
        answer+=r*i;
        i*=10;
    }
printf("Binary number is %d",answer);
int pos,num,power,decimal;
printf("\n How many bits would you like posterized? \n");
scanf("%d",&pos);
power= (int) pow(10,(pos));
num= (answer/(power))*10;
printf("%d\n",num);
		for(i=0;i<(pos-1);i++)
		{ num=(num*10)+1;
		}

printf("\nNumber is %d",num);

    while (num!=0)
    {
        rem = num%10;
        num/=10;
        decimal += rem*pow(2,j);
        ++j;
    }
printf("\n The number is %d",decimal);


}
}
