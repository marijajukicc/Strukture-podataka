#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
	char ime[20];
	char prezime[20];
	int bod;
}student;


int countstud(int* brstud,char* filename) {
	

	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("ERROR IN OPENING FILE \n");
		return -1;
	}
	while (!feof(fp))
	{
		if (fgetc(fp) == '\n')
		{
			(*brstud)++;
		}

	}
	fclose(fp);
	return 0;
}

int aloc(int *brSt, student **s) {
	*s = (student**)malloc((*brSt) * sizeof(student));
	return 0;
}

int readFromFile(student *s, int *brSt,char* filename)
{

	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("ERROR IN OPENING FILE \n");
		return -1;
	}
	for (int i = 0; i < *brSt; i++)
	{

		fscanf(fp, "%s %s %d", s[i].ime, s[i].prezime, &s[i].bod);

	}
	
	fclose(fp);


	return 0;
}
int Ispis(student* s, int br)
{
	int i,max_bod = 0;


	for (i = 0; i < br; i++) {
		max_bod += s[i].bod;
	}

	printf("\nMaksimalno je %d bodova\n\n", max_bod);

	for (i = 0; i < br; i++) {
		printf("Ime: %s\nPrezime: %s\nApsolutni broj bodova: %d\nRelativni broj bodova: %f\n\n\n", s[i].ime, s[i].prezime, s[i].bod, (float)(s[i].bod) / max_bod * 100);
	}
	return 0;
}


int main()
{
	int brojStudenata = 0;
	student *s;
	char filename[50];
	puts("Unesite ime filea");
	scanf("%s", filename);

	countstud(&brojStudenata,filename);
	aloc(&brojStudenata,&s);
	readFromFile(s, &brojStudenata,filename);
	Ispis(s, brojStudenata);
	
	return 0;
}
