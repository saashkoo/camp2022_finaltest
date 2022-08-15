#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

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

int main(int argc, char* argv[]){
	int ssum = 0;
	//printf("%d\n", count_bits(1));
	pid_t cpid[argc-1];
	pid_t w;
	int status, ttnum;

	for(int i = 1; i < argc; i++){
	//printf("I:%d argc:%d\n", i, argc);
		cpid[i] = fork();
		if (cpid[i] == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
		}
		if (cpid[i] == 0) {/* Code executed by child */
		int s;
		int tsum = 0;
		unsigned int * nums;
		nums = file_input(argv[i], &s);
		if(NULL == nums){exit(-1);}
		for(int j =0; j<s;j++){
			tsum = tsum + count_bits(nums[j]);
			//printf("tsum:%d, s:%d\n", tsum, s);
		}
		free(nums);
		FILE * r = fopen("w.data", "w+");
		if(NULL == r){
			perror("Error opening data file");
			exit(-1);
		}
		int e = fprintf(r,"%d", tsum);
		if(e < 1){perror("error writing data"); exit(-1);}
		int ee = fclose(r);
		if(ee == EOF){perror("error closing data file"); exit(-1);}
		exit(0);
		
		} else {/* Code executed by parent */
			w = waitpid(cpid[i], &status, 0);
			if (w == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		}
		FILE * r = fopen("w.data", "r");
		if(NULL == r){
			perror("Error opening data file");
			continue;
		}
		int e = fscanf(r,"%d", &ttnum);
		if(e < 1){perror("error reading data file");continue;}
		int ee = fclose(r);
		if(ee == EOF){perror("error closing data file");continue;}
		ssum = ssum + ttnum;
		printf("%s:%d\n",argv[i], ttnum);
	}
	printf("final sum:%d\n", ssum);
	return 0;

}
