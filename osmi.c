/*8. Napisati program koji pomoæu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Toènije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct Directory* TreePosition;
typedef struct Stack* Position;

typedef struct Directory {
	char name[MAX];
	TreePosition child;
	TreePosition sibling;
}dir;

typedef struct Stack {
	TreePosition el;
	Position next;
}stack;

int menu(Position, TreePosition);
Position stack_allocation();
TreePosition tree_allocation();
TreePosition new_branch(char*);
int push(Position, TreePosition);
TreePosition pop(Position);
TreePosition new_directory(TreePosition, char*);
int print_stack(Position);
int remove_directories(TreePosition);
TreePosition find_directory(char*, TreePosition);
int print_directories(TreePosition);

int main() {
	TreePosition root = new_branch("C:");;
	Position head = stack_allocation();

	if (head == NULL)
		return -2;
	if (root == NULL)
		return -1;

	push(head, root);
	menu(head, root);

	return 0;
}

int menu(Position head, TreePosition root) {
	TreePosition current = root;
	int i = 1;

	printf("Now you are in main directory\n");
	printf("Type one of these commands: md (NameOfDir),cd (NameOfDir),cd..,or exit(and remove directories)\n\n");
	print_stack(head->next);

	while (i) {
		char userEnters[MAX];
		char command[(MAX / 2) - 1] = "";
		char nameOfDirectory[(MAX / 2) - 1] = "";

		fgets(userEnters, MAX, stdin);
		sscanf(userEnters, "%s %s", command, nameOfDirectory);

		if (!strcmp(command, "cd..")) {
			if (current == root) {
				printf("\nThis is main directory\n");
				print_stack(head->next);
			}
			else {
				current = pop(head);
				print_stack(head->next);
			}
		}
		else if (!strcmp(command, "dir")) {
			print_directories(current);
			print_stack(head->next);
		}
		else if (!strcmp(command, "cd") && strcmp(nameOfDirectory, "") != 0) {
			TreePosition temp = current;
			current = find_directory(nameOfDirectory, current->child);
			if (current == NULL) {
				printf("\nDirectory '%s' is not found.\n", nameOfDirectory);
				print_stack(head->next);
				current = temp;
			}
			else {
				push(head, current);
				print_stack(head->next);
			}
		}
		else if (!strcmp(command, "md") && strcmp(nameOfDirectory, "") != 0) {
			current = new_directory(current, nameOfDirectory);
			print_stack(head->next);
		}
		else if (!strcmp(command, "exit")) {
			i = remove_directories(current);
		}
		else {
			printf("The command '%s' is not defined.Try again.\n", command);
			print_stack(head->next);
		}
	}
	return 0;
}
int remove_directories(TreePosition current) {
	if (current == NULL)
		return 0;
	remove_directories(current->sibling);
	remove_directories(current->child);
	free(current);
	return 0;
}
TreePosition new_branch(char* name) {
	TreePosition root = tree_allocation();
	strcpy(root->name, name);
	return root;
}
Position stack_allocation() {
	Position p;

	p = (Position)malloc(sizeof(stack));
	if (p == NULL) {
		printf("Can't allocate inside of stack\n");
		return NULL;
	}
	p->next = NULL;
	p->el = NULL;
	return p;
}
TreePosition tree_allocation() {
	TreePosition p;

	p = (TreePosition)malloc(sizeof(dir));
	if (p == NULL) {
		printf("Can't allocate new branch\n");
		return NULL;
	}
	p->sibling = NULL;
	p->child = NULL;
	return p;
}
int print_stack(Position p) {
	char directory[MAX] = "";

	while (p != NULL) {
		strcat(directory, p->el->name);
		strcat(directory, "\\");
		p = p->next;
	}
	strcat(directory, ">");
	printf("%s ", directory);
	return 0;
}
int push(Position p, TreePosition el) {
	Position q = stack_allocation();

	if (q == NULL)
		return -1;
	q->el = el;
	while (p->next != NULL)
		p = p->next;
	p->next = q;
	return 0;
}
TreePosition pop(Position p) {
	Position tmp = p;

	while (tmp->next != NULL) {
		p = tmp;
		tmp = tmp->next;
	}
	p->next = tmp->next;
	free(tmp);
	return p->el;
}
TreePosition new_directory(TreePosition p, char* Name) {
	TreePosition q = new_branch(Name);

	if (q == NULL)
		return NULL;
	if (p->child == NULL)
		p->child = q;
	else {
		TreePosition temp = p->child;
		while (temp->sibling != NULL)
			temp = temp->sibling;

		temp->sibling = q;
	}
	return p;
}
TreePosition find_directory(char* dir_name, TreePosition p) {
	while (p != NULL) {
		if (!strcmp(p->name, dir_name))
			return p;
		p = p->sibling;
	}
	return NULL;
}
int print_directories(TreePosition p) {
	if (p->child == NULL) {
		printf("\tDirectory %s is empty!\n", p->name);
		return -1;
	}
	printf("\tInside of directory %s we have:\n", p->name);
	p = p->child;
	while (p != NULL) {
		printf("\t%s\n", p->name);
		p = p->sibling;
	}
	return 0;
}