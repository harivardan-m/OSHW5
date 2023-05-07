#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){
	printf(1, "Testing for nice system call\n");
	int new_priority;

	//Test case 1:
	new_priority=nice(1, 15);

	if(new_priority== 15){
		printf(1, "Successfully called nice(15)\n");
	}
	else{
		printf(1,"Failure in nice(15), Returned priority - %d\n", new_priority);
	}
	ps();

	//Test Case 2:
	new_priority=nice( 1, 50);

	if(new_priority == -1){
		printf(1, "Successfully called nice(50). Priority out of bounds, so it is not valid and does not change\n");
	}
	else{
		printf(1,"Failure in nice(50), Returned priority: %d\n", new_priority);
	}
	ps();


	//Test Case 3:
	new_priority=nice(1, 0);

	if(new_priority== 0){
		printf(1, "Successfully called nice(0)\n");
	}
	else{
		printf(1,"Failure in nice(0), Returned priority - %d\n", new_priority);
	}
	ps();
	exit();




}
