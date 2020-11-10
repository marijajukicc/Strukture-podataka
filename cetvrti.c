#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>


typedef struct Polinom * Polozaj;

typedef struct Polinom
{
	int koef;
	int eksp;
	Polozaj next;
}polinom;

int sortirano_citanje(Polozaj);
int ispis(Polozaj);
int suma(Polozaj, Polozaj, Polozaj);
int mnozenje(Polozaj, Polozaj, Polozaj);


int main(){

	polinom p, q, sum, umnozak;
	int i=0, j=0;
	p.next = NULL;
	q.next = NULL;
	sum.next = NULL;
	umnozak.next = NULL;

	//ucitavanje 2 polinoma
	//while uvjet kako bi izbjegli pokretanje programa koji ima pogresno otvorene fileove i tek pokrenuli s ispravno otvorenim fileovima
	while (i!=1) {
		i=sortirano_citanje(&p);
	}
	while (j!=1) {
		j=sortirano_citanje(&q);

	}
	
	//ispis 2 upisanih polinoma
	printf("\n P = ");
	ispis(p.next);
	printf("\n Q = ");
	ispis(q.next);

	//zbrajanje 2 upisanih polinoma i ispis sume
	suma(p.next, q.next, &sum);
	printf("\n P + Q = ");
	ispis(sum.next);

	//mnozenje 2 upisanih polinoma i ispis umnoska
	mnozenje(p.next, q.next, &umnozak);
	printf("\n P * Q = ");
	ispis(umnozak.next);


	return 0;
}

int sortirano_citanje(Polozaj p)
{
	char ime[50];
	FILE *fp;
	Polozaj new_el,p_p;

	printf("Ime datoteke:\t");
	scanf(" %s", ime);

	fp=fopen(ime, "r");
	if (!fp) {
		printf("\n %s se ne moze otvoriti.", ime);
		return -1;
	}
	else {
		while (!feof(fp)){

				
				new_el = (Polozaj)malloc(sizeof(polinom));
				fscanf(fp, " %d %d", &new_el->koef, &new_el->eksp);
			
			//ako sam upisala koef 0, da mi nepotrebno ne zauzima memoriju, maknit cu ga
			if (new_el->koef == 0)
				free(new_el);
			else
			{
				p_p = p;

				//sve dok ili ne dodem do kraja liste  ili ako su vec upisani exp manji od trenutnog se micem kroz listu
				while (NULL !=p_p->next && p_p->next->eksp < new_el->eksp)
					p_p = p_p->next;


				//ako imaju isti eksponent,njihovi koeficijenti se pribroje jedan drugome i oslobodim u memoriji mjesto novoupisanog
				if (p_p->next != NULL && p_p->next->eksp == new_el->eksp)
				{
					p_p->next->koef += new_el->koef;
					free(new_el);
					//ako mi novoupisani clan ponisti prethodni jer imaju isti eksponent i suprotan br(-5,5), oslobadam memoriju ta 2 clana
					if (p_p->next->koef == 0)
					{
						new_el = p_p->next;
						p_p->next = new_el->next;
						free(new_el);
					}
				}
				else //ako nemaju isti exp a novi clan ima manji onda se taj novi clan upisuje na mjesto clana koji je trenutno sljedeci veci od novog
				{
					new_el->next = p_p->next;
					p_p->next=new_el;
				}
			}
		}
		
	}
	fclose(fp);
	return 1;
}

int ispis(Polozaj P){

	while (P!= NULL)
	{
		printf("%dx^%d", P->koef, P->eksp);
		P = P->next;
		if (P != NULL) {
			printf(" + ");
		}	
	}
	printf("\n");
	return 0;
}

int suma(Polozaj p, Polozaj q, Polozaj suma){

	Polozaj temp;

	//while ce se izvrsavati dok ne dodemo do kraja nekog od 2 polinoma
	while (p !=NULL && q !=NULL)
	{
		temp = (Polozaj)malloc(sizeof(polinom));
		//Ako broj ima svog para s istom potencijom onda se njihovi koeficijenti zbroje a eksponent ostaje isti (x+x=2x) te idemo na sljedece clanove oba polinoma
		if (p->eksp == q->eksp)
		{
			temp->eksp = p->eksp;
			temp->koef = p->koef + q->koef;
			p = p->next;
			q = q->next;
		}
		//Zbog pravilnog redoslijeda pri ispisu, provjeravam koji je manji kako bi sto manji element bio sto vise s lijeve strane(x+x^2+...) ako nema svog para s istom potencijom i pomicemo na sljedeceg clana tog polinoma
		else if (p->eksp > q->eksp)
		{
			temp->eksp = q->eksp;
			temp->koef = q->koef;
			q = q->next;
		}
		else if(p->eksp < q->eksp)
		{
			temp->eksp = p->eksp;
			temp->koef = p->koef;
			p = p->next;
		}
		temp->next = suma->next;
		suma->next = temp;
		suma = suma->next;
	}
	//Gornji while se prekinio jer je jedan polinom kraci i dosao je do kraja te cemo s novim whileom preostale elemente onog duzeg spremiti u sveukupnu sumu
	while (p!=NULL || q !=NULL)
	{
		temp= (Polozaj)malloc(sizeof(polinom));
		if (p !=NULL)
		{
			temp->eksp = p->eksp;
			temp->koef = p->koef;
			p = p->next;
		}
		else if (q !=NULL)
		{
			temp->eksp = q->koef;
			temp->koef = q->koef;
			q = q->next;
		}
		
		temp->next = suma->next;
		suma->next = temp;
		suma = suma->next;
	}
	return 0;
}

int mnozenje(Polozaj p, Polozaj q, Polozaj umnozak)
{
	Polozaj tmp, q_q,umozak_umnozak;

	for(p;p != NULL; p=p->next)
	{
		//Potrebna pomocna varijabla q_q kako bi se sljedeci p uvijek pomnozilo sa svakim q
		q_q = q;
		for (q_q;q_q != NULL;q_q=q_q->next)
		{
			tmp = (Polozaj)malloc(sizeof(polinom));
			//mnozenje polinoma= zbrojimo eksp a koeficijente pomnozimo
			tmp->eksp = p->eksp + q_q->eksp;
			tmp->koef = p->koef * q_q->koef;

			umozak_umnozak = umnozak;

			while (umozak_umnozak->next != NULL && umozak_umnozak->next->eksp < tmp->eksp)
				umozak_umnozak = umozak_umnozak->next;

			if (umozak_umnozak->next != NULL && umozak_umnozak->next->eksp == tmp->eksp)
			{
				umozak_umnozak->next->koef += tmp->koef;
				free(tmp);
			}
			else
			{
				tmp->next = umozak_umnozak->next;
				umozak_umnozak->next = tmp;
			}
		}
	}

	return 0;
}