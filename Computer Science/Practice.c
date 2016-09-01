
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct student
{
	char *fName;
	char *lName;
	int pid;
} student;

// This is a pass-by-reference version of the function we saw in structs.c.
// Notice that when we have a pointer to a struct, we have two options for
// accessing its members:
//
//    1. Dereference the pointer, then access the members as normal, with the
//       dot operator (.):
//
//       (*s).lName
//
//    2. Use the arrow operator (->) which takes care of the dereferencing for
//       you:
//
//       s->lName
//
void print_student(student *s)
{
	
	printf("%s, %s (PID: %07d)\n", (*s).lName, (*s).fName, (*s).pid);
	printf("%s, %s (PID: %07d)\n", s->lName, s->fName, s->pid);

	
	s->fName[0] = '\0';
	strcpy(s->lName, "Enough");
	s->pid = 6543210;
}

int main(void)
{
	int n;

	
	student *s = malloc(sizeof(student));
	printf("How many letters are in your first name? ");
	scanf("%d", &n);

	s->fName = malloc(sizeof(char) * (n + 1));
	printf("Enter your first name: ");
	scanf("%s", s->fName);

	
	printf("How many letters are in your last name? ");
	scanf("%d", &n);

	
	s->lName = malloc(sizeof(char) * (n + 1));
	printf("Enter your last name: ");
	scanf("%s", s->lName);

	
	printf("What is the numeric portion of your PID? ");
	scanf("%d", &(s->pid));

	print_student(s);

	printf("%s, %s (PID: %07d)\n", s->lName, s->fName, s->pid);

	
	free(s->lName);
	free(s->fName);
	free(s);

	return 0;
}