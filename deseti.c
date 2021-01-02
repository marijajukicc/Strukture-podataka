/*10. Napisati program koji iz datoteke èita postfiks izraz i zatim stvara stablo proraèuna. Iz
gotovog stabla proraèuna upisati u datoteku infiks izraz.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Tree* Branch;
typedef struct Stack* Position;

typedef struct Tree {
	char el;
	Branch left;
	Branch right;
}tree;

typedef struct Stack {
	Branch treePosition;
	Position next;
}stack;

int push(Position, char);
Branch pop(Position);
int insert_branch(Position, Branch);
Branch postfix_file(char*, Branch root, Position head);
Branch postfix_stack(char*, int, Branch root, Position head);
Position Allocation(char );
int push_no(Position p, int el);
int infix_file(FILE*, Branch);
Branch TreeAllocation(char);
int write_in_file(char*, Branch);
int empty_tree(Branch);

int main() {
	char fileName[MAX] = { 0 };
	Position head = (Position)malloc(sizeof(stack));
	head->next = NULL;
	Branch root = NULL;
	printf("Enter the name of the file where postfix is(include .txt): ");
	scanf("%s", fileName);
	root = postfix_file(fileName, root, head);
	printf("Enter the name of the file where you will save infix(include .txt): ");
	scanf("%s", fileName);
	write_in_file(fileName, root);
	return 0;
}

Branch postfix_file(char* fileName, Branch root, Position head) {
	FILE *fp = fopen(fileName, "r");
	char *temp = NULL;
	if (!fp) {
		printf("Error in opening the file\n");
		return NULL;
	}
	int size = 0;

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);

	temp = (char*)malloc((size + 1) * sizeof(char*));
	fscanf(fp, "%[^\n]", temp);
	fclose(fp);

	temp[size] = '\0';
	printf("%s\n", temp);

	root = postfix_stack(temp, size, root, head);
	return root;
}

Branch postfix_stack(char* temp, int size, Branch root, Position head) {
	int el = 0, fja = 0, current = 0, brojac = 0;
	char ch = 0;
	do {
		printf("Uzimamo prvi s reda :%s\n", temp);
		fja = sscanf(temp, "%d %n", &el, &current);
		if (fja == 0) {
			fja = sscanf(temp, "%c %n", &ch, &current);
			if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
				root = TreeAllocation(ch);
				root->right = pop(head);
				root->left = pop(head);
				insert_branch(head, root);
			}
		}
		else if (fja != 0 && fja != -1)
			push_no(head, el);
		temp += current;
		brojac += current;
	} while (brojac < (size));


	return root;
}

int insert_branch(Position head, Branch root) {
	Position new = (Position)malloc(sizeof(stack));
	new->next = head->next;
	head->next = new;
	new->treePosition = root;
	return 0;
}

int push_no(Position p, int el) {
	char br = (char)el + '0';
	push(p, br);
	return 0;
}

int push(Position p, char ch) {

	Position q = Allocation(ch);
	if (q == NULL) {
		printf("Allocation failed\n");
		return -1;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}
Branch pop(Position p) {
	if (p->next == NULL) {
		printf("Stack is empty!\n");
		return NULL;
	}
	Position temp = p->next;
	Branch popped = temp->treePosition;
	p->next = temp->next;
	free(temp);
	return popped;
}

Position Allocation(char el) {
	Position new = (Position)malloc(sizeof(stack));
	if (!new) {
		printf("Stack allocation failed\n");
		return NULL;
	}
	new->next = NULL;
	new->treePosition = TreeAllocation(el);
	return new;
}

Branch TreeAllocation(char el) {
	Branch new = (Branch)malloc(sizeof(tree));
	if (!new) {
		printf("Tree allocation failed\n");
		return NULL;
	}
	new->left = NULL;
	new->right = NULL;
	new->el = el;
	return new;
}
int write_in_file(char* fileName, Branch root) {
	FILE* fp = NULL;
	fp = fopen(fileName, "w");
	if (!fp) {
		printf("Error in opening the file!\n");
		return -1;
	}
	infix_file(fp, root);
	empty_tree(root);
	fclose(fp);
	return 0;
}

int infix_file(FILE* fp, Branch root) {
	if (root == NULL)
		return -1;
	if (root) {
		if (root->left != NULL && root->right != NULL)
			fprintf(fp, "(");
		infix_file(fp, root->left);
		fprintf(fp, "%c", root->el);
		infix_file(fp, root->right);
		if (root->right == NULL)
			return 0;
		fprintf(fp, ")");
	}
	return 0;
}
int empty_tree(Branch root) {
	if (root == NULL)
		return -1;
	empty_tree(root->left);
	empty_tree(root->right);
	free(root);
	return 0;
}
