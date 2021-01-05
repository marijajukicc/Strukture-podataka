/*11. Napisati kod koji za zadane podatke studenata (matièni broj, ime i prezime) pravi hash tablicu sa zasebnim redovima.
Tablica ima 11 mjesta, a funkcija za preslikavanje kljuè raèuna da se zbraja ASCII vrijednost prvih pet slova prezimena i zatim raèuna
ostatak cjelobrojnog dijeljenja te vrijednosti s velièinom tablice. Studenti s istim kljuèem se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
Kada se tablica izgradi treba ispisati cijelu tablicu (naglasiti na kojem kljuèu se nalaze koji podaci) te ponuditi moguænost da se za odreðenog studenta
(prezime i ime) ispiše njegov matièni broj*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 31
#define SIZE 11

typedef struct Student* Position;
typedef struct Hash* HashPointer;

typedef struct Student {
	int id_no;
	char name[MAX];
	char surname[MAX];
	Position next;
}student;

typedef struct Hash {
	int size;
	Position* members;
}hash;

HashPointer createHashTable();
int studentsFromFile(HashPointer);
int createKey(char*);
int insertStudent(int, char*, char*,int, HashPointer);
int printTable(HashPointer);
int printTheStudent(HashPointer);

int main() {
	HashPointer table = createHashTable();

	if (!table) {
		return -1;
	}
	studentsFromFile(table);
	printTable(table);
	printTheStudent(table);
	return 0;
}
HashPointer createHashTable() {
	HashPointer newEl = (HashPointer)malloc(sizeof(hash));

	if (!newEl) {
		perror("Error in allocating hash table");
		return NULL;
	}
	newEl->size = SIZE;
	newEl->members = (Position*)malloc(sizeof(student) * SIZE);

	if (!newEl->members) {
		perror("Error in allocating members inside of the hash table");
		return NULL;
	}

	for (int i = 0; i < SIZE; i++) {
		newEl->members[i] = (Position)malloc(sizeof(student));
		newEl->members[i]->next = NULL;
	}
	return newEl;
}

int studentsFromFile(HashPointer table) {
	FILE* fp;
	int key = 0, mbg = 0;
	char name[MAX], surname[MAX];

	fp = fopen("studenti.txt", "r");
	if (!fp) {
		perror("Error in opening the file\n");
		return -1;
	}
	while (!feof(fp)) {
		fscanf(fp, "%d %s %s", &mbg, name, surname);
		key = createKey(surname);
		if (insertStudent(mbg, name, surname,key, table))
			printf("Couldn't put student in the table\n");
	}
	fclose(fp);
	return 0;
}

int createKey(char* surname) {
	int sum = 0;

	for (int i = 0; i < 5; i++)
		sum += surname[i];

	return sum % SIZE;
}

int insertStudent(int mbr, char* name, char* surname,int key, HashPointer table) {
	Position current = table->members[key];
	Position newEl = (Position)malloc(sizeof(student));

	if (!newEl) {
		perror("Error in allocating newEl member");
		return 1;
	}
	newEl->id_no = mbr;
	strcpy(newEl->name, name);
	strcpy(newEl->surname, surname);

	while (current->next != NULL && (strcmp(surname, current->next->surname) > 0 || (strcmp(surname, current->next->surname) == 0 && strcmp(name, current->next->name) > 0)))
		current = current->next;

	newEl->next = current->next;
	current->next = newEl;
	return 0;

}
int printTable(HashPointer table) {
	for (int i = 0; i < SIZE; i++) {
		Position student = table->members[i]->next;
		printf("%d. key: \n", i + 1);
		if (!student)
			puts("There is no student with this key");
		while (student) {
			printf("Identification no.%d , Name : %s , Surname : %s \n", student->id_no, student->name, student->surname);
			student = student->next;
		}
	}
	puts("---------------------------------------------------------------");
	return 0;
}

int printTheStudent(HashPointer table) {
	char name[MAX], surname[MAX];
	int found = 0;

	printf("\nPlease,enter name and surname of person you are checking id number: ");
	scanf("%s %s", name, surname);
	Position isFound = table->members[createKey(surname)];
	if (isFound!=NULL) {
		while (isFound) {
			if (strcmp(isFound->surname, surname) == 0 && strcmp(isFound->name, name) == 0) {
				printf("Identification number for '%s %s' is no. %d\n", name, surname, isFound->id_no);
				found = 1;
			}
			isFound = isFound->next;
		}
	}
	if (!found) {
		printf("Person '%s %s' isn't in the table\n",name,surname);
	}
	return 0;
}

