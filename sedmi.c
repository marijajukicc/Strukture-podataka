/*7. Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna rezultat. Stog je potrebno realizirati preko vezane liste.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cvor* Position;
typedef struct Cvor {
	int el;
	Position next;
}cvor;

int citaj_iz_dat(Position);
int operacije(Position, char);
int ispis(Position);
int push(Position, int);
int pop(Position,int*);
Position Alokacija();
int postfix_racunaj(char*, int, Position);

int main() {
	cvor p;
	p.next = NULL;
	citaj_iz_dat(&p);

	return 0;
}

int ispis(Position p) {
	if (p == NULL) {
		printf("\nStog je prazan\n");
		return -1;
	}
	printf("\nNa stogu imamo: ");
	while (p != NULL) {
		printf("%d ", p->el);
		p = p->next;
	}
	printf("\n");
	return 0;
}

int citaj_iz_dat(Position p) {
	FILE *fp;
	char* temp = NULL;

	
	fp = fopen("postfix.txt", "r");
	if (!fp) {
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
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

	postfix_racunaj(temp, size,p);
	return 0;
}

int postfix_racunaj(char* temp, int size,Position p) {
	int el = 0, fja = 0, current = 0, brojac = 0;
	char ch = 0;

	do
	{

		fja = sscanf(temp, "%d %n", &el, &current);
		if (fja != 0 && fja != -1)
		{
			push(p, el);
			printf("\nDodajemo el %d\n", el);
			ispis(p->next);
		}
		else {

			fja = sscanf(temp, "%c %n", &ch, &current);
			operacije(p, ch);
			ispis(p->next);

		}

		temp += current;
		brojac += current;
	} while (brojac < size);
	return 0;
}

int operacije(Position p, char operator) {
	int a = 0, b = 0;
	pop(p, &b); pop(p, &a);
	int rez = 0;
	printf("\nRacunamo %d %c %d\n", a, operator, b);
	switch (operator)
	{
	case '+':
		rez = a + b;
		break;
	case '-':
		rez = a - b;
		break;
	case '*':
		rez = a * b;
		break;
	case '/':
		if (b != 0)
			rez = a / b;
		else {
			printf("Ne smije se djeliti s 0!\n");
			return -2;
		}
		break;
	case '%':
		rez = a % b;
		break;
	default:
		printf("To nije osnovni operator\n");
		return -1;
	}
	push(p, rez);
	return 0;
}

int push(Position p, int el) {

	Position q = Alokacija();
	if (q == NULL) {
		printf("Nema memorije\n");
		return -1;
	}
	q->el = el;
	q->next = p->next;
	p->next = q;
	return 0;

}
int pop(Position p, int *a) {
	if (p->next == NULL) {
		printf("Lista je bila prazna!\n");
		return -1;
	}
	Position temp = p->next;
	p->next = temp->next;
	*a = temp->el;
	free(temp);
	return 0;
}

Position Alokacija() {
	Position p;
	p = (Position)malloc(sizeof(cvor));
	if (p == NULL) {
		printf("Greska pri alokaciji\n");
		return NULL;
	}
	p->next = NULL;
	return p;
}

