#include <stdio.h>
#include <stdlib.h>

typedef struct nod nod;
struct nod
{
	nod *leg;
	int inf;
};
void adaugNod(nod** p, nod**u, int inf)
{
		nod *aux = (nod*)malloc(sizeof(nod*));
		aux->inf = inf;
		aux->leg = NULL;
		(*u)->leg = aux;
		*u = aux;

}
int main()
{
	int x;

	nod*p = (nod*)malloc(sizeof(nod));
	nod*u = (nod*)malloc(sizeof(nod));
	p->inf = 1;
	p->leg = NULL;
	u = p;
	int i;
	for ( i = 2; i < 10; i++)
	{
		int y;
		printf("Introduceti informatica dorita:");
		scanf("%d", &y);
		adaugNod(&p, &u, y);
	}
	nod* p2 = p;
	while (p2 != NULL)
	{
		printf("%d ", p2->inf);
		p2 = p2->leg;
	}
	printf("P2=%d", p2);
	while (p != NULL)
	{
		p2 = p;
		printf("p=%d ", p);
		p = p->leg;
		printf("p2=%d ", p);
		free(p2);
	}




	printf("Programul a finalizat");
	scanf("%d", &x);
	printf("%d", x);
    return 0;
}
