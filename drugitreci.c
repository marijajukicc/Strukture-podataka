/*Definirati strukturu osoba (ime, prezime, godina ro�enja) i napisati program koji:
	- dinami�ki dodaje novi element na po�etak liste,
	- ispisuje listu,
	- dinami�ki dodaje novi element na kraj liste,
	- pronalazi element u listi (po prezimenu),
	- bri�e odre�eni element iz liste,
	- dinami�ki dodaje novi element iza odre�enog elementa,
	- dinami�ki dodaje novi element ispred odre�enog elementa,
	- sortira listu po prezimenima osoba,
	- upisuje listu u datoteku,
	- �ita listu iz datoteke.
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

void Insert(Position);
void Print(Position);
Position FindLast(Position);
Position Find(Position);
Position FindPrev(Position);
void Delete(Position);
void Sort(Position);
void ReadFromFile(Position);
void WriteToFile(Position);


int main()
{
	osoba head, *q;
	char izbor = 0;

	head.Next = NULL;
	while (izbor != 'K' && izbor != 'k')
	{
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

		scanf(" %c", &izbor);

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
			else
				Insert(q);
			break;
		case '6':
			q = FindPrev(&head);
			if (NULL == q)
				printf("\n Osoba ne postoji u listi!");
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
			break;
		default:
			printf("\nKrivi unos!!!\n");
		}
	}
	return 0;
}

void Insert(Position P)
{
	Position temp;

	temp = (Position)malloc(sizeof(osoba));
	printf("\nUnesite podatke o osobi: ");
	scanf(" %s %s %d", temp->name, temp->surname, &temp->bY);

	temp->Next = P->Next;
	P->Next = temp;
}

void Print(Position P)
{
	if (NULL == P)
		printf("\nLista je prazna!!\n");
	else
	{
		printf("\nU listi se nalaze:");
		while (P != NULL)
		{
			printf("\n\t %s %s %d", P->name, P->surname, P->bY);
			P = P->Next;
		}
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

void Delete(Position P)
{
	Position prev;

	prev = FindPrev(P);

	if (NULL != prev)
	{
		P = prev->Next;
		prev->Next = P->Next;
		printf("\n Osoba %s %s %d je obrisana!", P->name, P->surname, P->bY);
		free(P);
	}
	else
		printf("\n Osoba ne postoji u listi!");
}

void Sort(Position P)
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

}

void ReadFromFile(Position P)
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
	}
}

void WriteToFile(Position P)
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
	}
}