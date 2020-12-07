/*6. Napisati program koji pomoæu vezanih listi simulira rad:
a) stoga,
b) reda.
Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10 -100.*/

#define CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct Cvor* Pozicija;
typedef struct Cvor{
	int el;
	Pozicija next;
}cvor;

int Stavi_na_stog(Pozicija);
int First_out(Pozicija);
int Stavi_u_red(Pozicija);
int Ispis(Pozicija);
Pozicija Alokacija(Pozicija);

int main() {
	cvor p, q;
	p.next = NULL;
	q.next = NULL;
	srand(time(NULL));
	for(int i=0;i<10;i++)
		Stavi_na_stog(&p);
	printf("Stog je: "); Ispis(p.next);
	First_out(&p);
	printf("Nakon sto maknemo prvog: "); Ispis(p.next);
	for (int i = 0; i < 10; i++)
		Stavi_u_red(&q);
	printf("Red je: "); Ispis(q.next);
	First_out(&q);
	printf("Prvi se maknuo iz reda: "); Ispis(q.next);
	Stavi_u_red(&q);
	printf("Dosao je novi el na kraj: "); Ispis(q.next);
	return 0;
}

int Ispis(Pozicija p) {
	if (p == NULL) {
		printf("Lista je prazna\n");
		return -1;
	}
	while (p != NULL) {
		printf("%d  ", p->el);
		p = p->next;
	}
	printf("\n\n");
	return 0;
}

Pozicija Alokacija() {
	Pozicija p;
	p = (Pozicija)malloc(sizeof(cvor));
	if (p == NULL) {
		printf("Greska pri alokaciji\n");
		return NULL;
	}
	p->next = NULL;
	return p;
}

int Stavi_na_stog(Pozicija p) {
	Pozicija q=Alokacija();
	if (q == NULL) {
		printf("Nema memorije\n");
		return -1;
	}
	q->el = rand() % 91 + 10;
	q->next = p->next;
	p->next = q;
	return 0;

}

int First_out(Pozicija p) {
	if (p->next == NULL) {
		printf("Lista je bila prazna!\n");
		return -1;
	}
	Pozicija temp = p->next;
	p->next = temp->next;
	free(temp);
	return 0;	
}

int Stavi_u_red(Pozicija p) {
	while (p->next != NULL)
		p = p->next;
	if (Stavi_na_stog(p) == -1)
		return -1;
	return 0;
}