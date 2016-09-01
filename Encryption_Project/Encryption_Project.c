// encryption_practice.cpp : Defines the entry point for the console application.
// Henry Ton

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

void main_menu()
{
	printf("What would you like to do?:\n");
	printf("Select 1: Encrypt a message\n");
	printf("Select 2: Decrypt a message\n");
}

void encrypt_message(FILE* message)
{
	int i = 0;
	char message_text[100];

	//message_text = malloc(sizeof(char)*100);

	while (i<100)
	{
		fscanf(message, "%c", &message_text[i]);
		printf("%c", message_text[i]);
		i++;
		free(message_text);
	}

}

void decrypt_message(FILE* message)
{
	printf("Hello\n");
}



int main(void)
{
	FILE *message;


	int i, j, option;

	message = fopen("input.txt", "r");

	if (fopen("input.txt", "r") == NULL)
	{
		printf("The file did not open\n");
		fflush(stdout);
		return 0;
	}






	while (1)
	{
		main_menu();
		scanf("%d", &option);

		switch (option)
		{
		case 1: encrypt_message(message);
			break;
		case 2: decrypt_message(message);
			break;
		}







	}
	fclose(message);
	return 0;
}

