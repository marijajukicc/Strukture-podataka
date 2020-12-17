#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_DIR_LENGTH 256
//stavi cd.. ne cd ..
//stog unatrag(c: u stog)
//dir ispis
//exit pop,pop dok sog nije prazan
typedef struct Dir* Position;
typedef struct Stack* StackPosition;

typedef struct Dir {
	char name[MAX_DIR_LENGTH];
	Position child;
	Position sibling;
}direkt;

typedef struct Stack{
	Position data;
	StackPosition Next;
	
}stack;

void remove(Position current);
int push(Position);
int pop(Position);
direkt Alokacija();
int md(Position,Position);
int goBack(Position);
int printDir(Position);


int main() {
	direkt c;
	c.child = NULL;
	c.sibling = NULL;

	
	return 0;
}
void remove(Position current) {
	if (current == NULL)
		return;
	remove(current->sibling);
	remove(current->child);
	free(current);
}

int pop(Position a) {
	if (a == NULL) {
		printf("Stog je prazan");
		return;
	}

}