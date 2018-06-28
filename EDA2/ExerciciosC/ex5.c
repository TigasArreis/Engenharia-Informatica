#include <stdio.h>
#include <stdlib.h>

typedef struct coordenadas
{
	int x;
	int y;
}coord;

coord *newCoord()
{
	coord *nova = malloc(sizeof(coord));
	nova->x = 0;
	nova->y = 0;
	return nova;
}

char **setZona(int n)
{
	char **a = (char **)malloc(n*sizeof(char *));
	for (int i=0; i<n; i++)
		a[i] = (char *)malloc(n*sizeof(char));
			
	return a;
}

void isoladas(char **z, int n, int *m)
{
	for (int j=0; j<n; j++)
		for (int k=0; k<n; k++)
			if (*(*(z+j)+k) == 'X')
				*m+=1;
}

int main(void)
{
	int dim, nIsol = 0;
	scanf("%d", &dim);
	
	char **zona = setZona(dim);
	
	for (int i=0; i<dim; i++)
		scanf("%s", zona[i]);

    for(int j=0;j<dim;j++)
    {
        for (int k=0;k<dim;k++)
            printf("%c",*(*(zona+j)+k));
        printf("\n");
    }
    
    isoladas(zona, dim, &nIsol);
    printf("%d", nIsol);
}
