#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){
	printf(1, "Test 1 Lottery Scheduler\n");
	int pid;
	pid=fork();
	if(pid==0){
		getpid();
		nice(getpid(),1);

		int count=0,laps=0;
		while(count<5){
			count++;
			if(laps<5){
				laps++;
				count=0;
				printf(1,"BEST\n");
			}
		}
	}
	else{
		pid=fork();
		if(pid==0){
		getpid();
		nice(getpid(),8);

		int count=0,laps=0;
		while(count<5){
			count++;
			if(laps<5){
				laps++;
				count=0;
				printf(1,"HIGH\n");
			}
		}
	}
	else{
		pid=fork();
		if(pid==0){
		getpid();
		nice(getpid(),8);

		int count=0,laps=0;
		while(count<5){
			count++;
			if(laps<5){
				laps++;
				count=0;
				printf(1,"HIGH\n");
			}
		}
	}
	}
	}
	exit();
}