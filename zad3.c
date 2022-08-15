#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

typedef struct{
	int num;
	int n;
	int m;
	double **v;
} inp;

void*a(void*in){
	inp g ;
	g.num = (inp*)in->num;
	g.n = (inp*)in->n;
	g.m = (inp*)in->m;
	g.v = (inp*)in->v;
	free(in);
	double res[g.n];
	for(int i=0;i<g.n;i++){
		if(i%THREAD_COUNT==g.num){
			double sum =0;
			for(int j =0;j<g.m;j++){
				sum = sum + g.v[i][j]*g.v[i][j];
			}
			res[i] = sqrt(sum);
		}
		else{
			res[i] = 0.;
		}
	}
	return (void*)res;
}



int main(){
	int n,m;
	//scanf("%d %d", &n, &m);
	scanf("%d", &n);
	scanf("%d", &m);
	//printf("%d %d\n", n, m);
	double vect[n][m];
	for(int i =0; i < n;i++){
		for(int j=0;j<m;j++){
			scanf("%lf", &vect[i][j]);
		}
	}
	char filename[100];
	scanf("%s", filename);
	/*printf("%s\n", filename);
	for(int i =0; i < n;i++){
		for(int j=0;j<m;j++){
			printf("%lf ", vect[i][j]);
		}
		printf("\n");
	}*/
	pthread_t th[THREAD_COUNT];
	for(int i = 0;i < n/THREAD_COUNT; i++){
		inp *arg = malloc(sizeof(inp));
		arg->num = i;
		arg->n =n;
		arg->m =m;
		arg->v = vect;
		pthread_create(&th[i], NULL, a, arg);
	}
	for(int i = 0;i < n/THREAD_COUNT; i++)
	
	return 0;

}
