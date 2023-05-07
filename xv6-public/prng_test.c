#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
	printf(1, "Testing for PRNG calls \n");

	uint min =999999999, max=0, sum=0;
	int size = 1000, i=0;
	for (; i<size;i++){
		unsigned int rand_num= prng();
		printf(1, "Random num for iteration %d -> %d\n", i, rand_num);
		if(rand_num<min)
			min=rand_num;
		if(rand_num>max)
			max=rand_num;
		sum+=rand_num/size;
	}

	printf(1, "\nAvg - %d \n",sum);
	printf(1, "\nMax - %d \n",max);
	printf(1, "\nMin - %d \n",min);

	exit();

}