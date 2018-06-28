#include <stdio.h>

int main(void)
{
	int n;
	scanf("%d", &n);
	
	long int seq[n];
	for (int i=0; i<n; i++)
		scanf("%ld", &seq[i]);
		
	int m;
	scanf("%d", &m);
	
	for (int i=0; i<m; i++)
	{
		int consulta;
		scanf("%d", &consulta);
		if (consulta>0 && consulta<=n)
			printf("valor @ %d = %ld\n", consulta, seq[consulta-1]);
		else
			printf("valor @ %d = -\n", consulta);
	}
}
