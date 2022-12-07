#include <stdio.h>
#include "instance.c"

int main(int argc, char **argv)
{
	struct Instance instance = InstanceNew(5,1);

	printf("hello world\n");
	return 0;
}
