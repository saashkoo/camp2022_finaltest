#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

int count_bits(unsigned int m){
	int sum = 0;
	for(int i =0; i< 32; i++){
		if(!!(m & (1<<i))){
			sum++;
		}
	}
	return sum;
}

unsigned int *file_input(char * filename, int *size){
	FILE * f = fopen(filename, "r");
	if(NULL == f){
		perror("Error opening file");
		return NULL;
	}
	errno = 0;//making sure errno is 0 (Success)
	unsigned * res = malloc(1000*sizeof(unsigned));
	int c = 1;
	int e;
	do{
		if(c % 1000){res = realloc(res, c);}
		e = fscanf(f, "%u", &res[c-1]);
		c++;
	}while(e != EOF);
	if(errno != 0){
		perror("Error reading file");
		return NULL;
	}
	*size = c-2;
	int ee = fclose(f);
	if(EOF == ee){
		perror("error closing file"); return NULL;
	}
	return res;
}

void * ex(void *a){
	int s;
	//printf("t:%p\n", a);
	char * jj = (char*)a;
	//printf("tt:%s\n", jj);
	int *tsum = malloc(sizeof(int));
	*tsum = 0;
	unsigned int * nums;
	nums = file_input(jj, &s);
	if(NULL == nums){exit(-1);}
	for(int j =0; j<s;j++){
		*tsum = *tsum + count_bits(nums[j]);
	}
	printf("%s:%d\n",jj, *tsum);
	return (void*)tsum;
}


int main(int argc, char * argv[]){
	pthread_t threads[argc-1];
	int sum = 0; 
	int *res;
	for(int i = 1;i < argc;i++){
	//printf("mm:%d\n", argv[i][2]);
	//printf("m:%p\n",(void*)argv[i] );
		pthread_create(&threads[i], NULL, ex, (void*)argv[i]);
		//printf("%d\n", *res);
	}
	for(int i = 1;i < argc;i++){
		pthread_join(threads[i], (void**)&res);
		sum = sum+*res;
	}
	printf("final sum:%d\n", sum);
	return 0;


}
