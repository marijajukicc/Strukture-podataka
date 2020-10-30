/*Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
	- dinamièki dodaje novi element na poèetak liste,
	- ispisuje listu,
	- dinamièki dodaje novi element na kraj liste,
	- pronalazi element u listi (po prezimenu),
	- briše odreðeni element iz liste,
	- dinamièki dodaje novi element iza odreðenog elementa,
	- dinamièki dodaje novi element ispred odreðenog elementa,
	- sortira listu po prezimenima osoba,
	- upisuje listu u datoteku,
	- èita listu iz datoteke.
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct osoba;
typedef struct osoba *Position;
typedef struct osoba {
	char name[256];
	char surname[256];
	int bY;
	Position Next;
}osoba;

int Insert(Position);
int Print(Position);
Position FindLast(Position);
Position Find(Position);
Position FindPrev(Position);
int Delete(Position);
int Sort(Position);
int ReadFromFile(Position);
int WriteToFile(Position);
int Menu();
int Izbor(int);

int main()
{
	osoba head, *q;
	char izbor = 0;

	head.Next = NULL;
	while (izbor != 'K' && izbor != 'k'){
		Menu();
		scanf(" %c", &izbor);
		Izbor(izbor);
	}	
	return 0;
}

int Menu(){
	printf("\nUnesi:");
	printf("\n\t0 -> unos elementa na pocetak");
	printf("\n\t1 -> ispis niza");
	printf("\n\t2 -> unos elementa na kraj");
	printf("\n\t3 -> trazenje elementa u listi po prezimenu");
	printf("\n\t4 -> brisanje");
	printf("\n\t5 -> dodavanje iza elementa");
	printf("\n\t6 -> dodavanje ispred elementa");
	printf("\n\t7 -> sortiranje liste po prezimenu");
	printf("\n\t8 -> citanje iz datoteke");
	printf("\n\t9 -> upisivanje liste u datoteku");
	printf("\n\tk -> kraj\n\n\t");
	return 0;
}
	
int izbor(int izbor){
	switch (izbor)
		{
		case '0':
			Insert(&head);
			break;
		case '1':
			Print(head.Next);
			break;
		case '2':
			q = FindLast(&head);
			Insert(q);
			break;
		case '3':
			q = Find(head.Next);
			if (NULL == q)
				printf("\n Osoba ne postoji u listi!");
			else
				printf("\n\tOsoba je: %s %s, %d", q->name, q->surname, q->bY);
			break;
		case '4':
			Delete(&head);
			break;
		case '5':
			q = Find(head.Next);
			if (NULL == q)
				printf("\n Osoba ne postoji u listi!");
				return -1;
			else
				Insert(q);
			break;
		case '6':
			q = FindPrev(&head);
			if (NULL == q)
				printf("\n Osoba ne postoji u listi!");
				return -2;
			else
				Insert(q);
			break;
		case '7':
			Sort(&head);
			break;
		case '8':
			ReadFromFile(&head);
			break;
		case '9':
			WriteToFile(head.Next);
			break;
		case 'k':
		case 'K':
			printf("\nKraj programa!!!\n");
			return 0;
			break;
		default:
			printf("\nKrivi unos!!!\n");
			return -1;
		}
	}
}

int Insert(Position P)
{
	Position temp;

	temp = (Position)malloc(sizeof(osoba));
	printf("\nUnesite podatke o osobi: ");
	scanf(" %s %s %d", temp->name, temp->surname, &temp->bY);

	temp->Next = P->Next;
	P->Next = temp;
	return 0;
}

int Print(Position P)
{
	if (NULL == P)
		printf("\nLista je prazna!!\n");
		return -1;
	else
	{
		printf("\nU listi se nalaze:");
		while (P != NULL)
		{
			printf("\n\t %s %s %d", P->name, P->surname, P->bY);
			P = P->Next;
		}
		return 0;
	}


}

Position FindLast(Position P)
{
	while (NULL != P->Next)
		P = P->Next;
	return P;
}


Position Find(Position P)
{
	char lastName[10];


	printf("\nUnesi prezime osobe koju zelis pronaci: ");
	scanf(" %s", lastName);

	while (P != NULL && strcmp(P->surname, lastName) != 0)
		P = P->Next;

	return P;
}

Position FindPrev(Position P)
{
	char lastName[10];

	if (NULL == P->Next)
		P = NULL;
	else
	{
		printf("\nUnesi prezime osobe koju zelis pronaci: ");
		scanf(" %s", lastName);


		while (strcmp(P->Next->surname, lastName) != 0 && P->Next->Next != NULL)
			P = P->Next;

		if (strcmp(P->Next->surname, lastName) != 0)
			P = NULL;
	}

	return P;
}

int Delete(Position P)
{
	Position prev;

	prev = FindPrev(P);

	if (NULL != prev)
	{
		P = prev->Next;
		prev->Next = P->Next;
		printf("\n Osoba %s %s %d je obrisana!", P->name, P->surname, P->bY);
		free(P);
		return 0;
	}
	else
		printf("\n Osoba ne postoji u listi!");
		return 1;
}

int  Sort(Position P)
{
	Position i, j, prev_j, temp, end;

	end = NULL;

	i = P;

	while (i->Next != end)
	{
		prev_j = i;
		j = i->Next;
		while (j->Next != end)
		{
			if (strcmp(j->surname, j->Next->surname) > 0)
			{
				temp = j->Next;
				prev_j->Next = temp;
				j->Next = temp->Next;
				temp->Next = j;

				j = temp;
			}

			prev_j = j;
			j = j->Next;
		}
		end = j;
	}
	return 0;

}

int ReadFromFile(Position P)
{
	// ova funkcija dodaje elemente iz datoteke nakon pokazivaca na osobu koji posaljemo

	FILE *dat;
	char imeDat[10];
	Position temp;

	printf("\nUnesi ime datoteke iz koje zelis procitati listu:");
	scanf(" %s", imeDat);

	dat = fopen(imeDat, "r");

	if (NULL == dat)
		printf("\n Ne postoji datoteke s tim imenom");
		return -1;
	else
	{
		while (feof(dat) == 0)
		{
			temp = (Position)malloc(sizeof(osoba));

			fscanf(dat, " %s %s %d", temp->name, temp->surname, &temp->bY);

			temp->Next = P->Next;
			P->Next = temp;
			P = temp;
		}

		fclose(dat);
		return 0;
	}
}

int WriteToFile(Position P)
{
	// ova funkcija dodaje elemente iz datoteke nakon pokazivaca na osobu koji posaljemo

	FILE *dat;
	char imeDat[10];

	printf("\nUnesi ime datoteke u koju zelis spremiti listu:");
	scanf(" %s", imeDat);

	dat = fopen(imeDat, "w");

	if (NULL == dat)
		perror("\n Greska u otvaranju datoteke");
	else
	{
		while (P != NULL)
		{
			fprintf(dat, "\n %s %s %d", P->name, P->surname, P->bY);
			P = P->Next;
		}

		fclose(dat);
		return 0;
	}
}
