#include <stdio.h>

/*
 argc ---> number of arguments
 argv ---> each cli argument is passed as a string to the sw
 */
int main (int argc, char* argv[])
{
	printf("%d arguments were put in\n",argc);
	
	printf("---------\n");
	for (int i = 0; i < argc; i++)
	{
		/*
		 * - the first argument is the ./cli_test
		 * - the following arguments are the texts are the strings,
		 *   that are provided next
		 * */
		printf("argument #%d is %s\n",i, argv[i]);
	}

	return 0;
}
