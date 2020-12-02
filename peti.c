/*5. Za dvije sortirane liste L1 i L2(mogu se proèitati iz datoteke ili unijeti ruèno, bitno je
	samo da su sortirane), napisati program koji stvara novu vezanu listu tako da raèuna :
a) L1 unija L2,
b) L1 presjek L2.
Liste osim pokazivaèa na slijedeæu strukturu imaju i jedan cjelobrojni element, po
kojem su sortirane.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Cvor *Pozicija;

typedef struct Cvor {
	int el;
	Pozicija next;
}cvor;

int sortirani_unos(Pozicija);
Pozicija alociranje(int);
int presjek_(Pozicija, Pozicija, Pozicija);
int unija(Pozicija, Pozicija, Pozicija);
int ispis(Pozicija);
int unos_na_pocetak(Pozicija,Pozicija);
int unos_na_kraj(Pozicija,Pozicija);
int main() {
	cvor p, q,rez,presjek;
	p.next = NULL;
	q.next = NULL;
	rez.next = NULL;
	presjek.next = NULL;
	int i = 0;

	while (i != 1) 
		i = sortirani_unos(&p);
	i = 0;
	while (i != 1)
		i = sortirani_unos(&q);


	printf("\n\nP = ");
	ispis(p.next);
	printf("\nQ = ");
	ispis(q.next);

	unija(p.next, q.next, &rez);
	printf("\n P + Q = ");
	ispis(rez.next);

	presjek_(p.next, q.next, &presjek);
	printf("\n P * Q = ");
	ispis(presjek.next);
	return 0;
}

int sortirani_unos(Pozicija p) {
	char ime[200];
	FILE *fp;
	Pozicija new_el, current;

	printf("\nUnesite ime datoteke za citanje el skupa: ");
	scanf(" %s", ime);

	fp = fopen(ime, "r");
	if (!fp) {
		printf("\nGreska!Datoteka %s nije otvorena.", ime);
		return -1;
	}
	else {
		while (!feof(fp)) {

			new_el = (Pozicija)malloc(sizeof(cvor));
			fscanf(fp, " %d", &new_el->el);

			current = p;
			while (NULL != current->next && current->next->el < new_el->el)
				current = current->next;

			if (current->next != NULL && current->next->el == new_el->el)
			{
				current->next->el = new_el->el;
				free(new_el);
			}
			else
			{
				new_el->next = current->next;
				current->next = new_el;
			}
		}
	}
	fclose(fp);
	return 1;

}

int ispis(Pozicija P) {

	while (P != NULL)
	{
		printf("%d ", P->el);
		P = P->next;
	}
	printf("\n");
	return 0;
}

int unija(Pozicija p, Pozicija q, Pozicija rez) {
	Pozicija temp=NULL;
	while (p != NULL && q != NULL) {
		temp = (Pozicija)malloc(sizeof(cvor));
		if (p->el == q->el) {
			temp = alociranje(p->el);
			p = p->next;
			q = q->next;
		}
		else if (q->el < p->el) {
			temp = alociranje(q->el);
			q = q->next;
		}
		else if (p->el < q->el) {
			temp = alociranje(p->el);
			p = p->next;
		}
		temp->next = rez->next;
		rez->next = temp;
		rez = rez->next;
	}
	while (p != NULL || q != NULL)
	{
		
		if (p != NULL)
		{
			temp = alociranje(p->el);
			p = p->next;
		}
		else if (q != NULL)
		{
			temp = alociranje(q->el);
			q = q->next;
		}

		temp->next = rez->next;
		rez->next = temp;
		rez = rez->next;
	}
	return 0;
}

Pozicija alociranje(int El)
{
	Pozicija p;

	p = (Pozicija)malloc(sizeof(cvor));

	if (p == NULL) {
		printf("Alociranje nije uspjelo\n");
		return NULL;
	}

	p->el = El;
	p->next = NULL;

	return p;
}

int presjek_(Pozicija p, Pozicija q, Pozicija presjek) {
	Pozicija tmp;

	while(p != NULL && q != NULL)
	{
		
		if (p->el == q->el) {
			tmp = alociranje(p->el);
			p = p->next;
			q = q->next;
			unos_na_kraj(presjek, tmp);
		}
		if (p !=NULL && q!=NULL  && p->el < q->el) {
			p = p->next;
		}
		if (p !=NULL && q != NULL && p->el > q->el) {
			q = q->next;
		}
		
	}
	return 0;
}

int unos_na_pocetak(Pozicija p,Pozicija q) {
	q->next = p->next;
	p->next = q;
	return 0;
}

int unos_na_kraj(Pozicija p, Pozicija q)
{
	while (p->next != NULL) {
		p = p->next;
	}
	unos_na_pocetak(p, q);
	return 0;
}