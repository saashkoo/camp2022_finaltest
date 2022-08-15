#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned long long int serial;
	double weight;
	double price;
	char marka[101];
} Laptop;

int i_rand(int min, int max){
	return min+rand()%(max-min+1);
}

char * randstr(){
	int lenght = i_rand(8, 12);
	char *a = malloc(sizeof(char)*14);
	a[0] = i_rand('A','Z');
	int i = 1;
	for(;i < lenght;i++){
		if(i_rand(0, 25)){
			a[i] = i_rand('a','z');
		}
		else{
			a[i] = ' ';
		}
	}
	a[i] = '\0';
	return a;

}


Laptop rd_laptop(){
	static unsigned uid = 0;
	char * a = randstr();
	double weiight = i_rand(25, 10000)/1000.;
	double pricee = i_rand(1000, 500000)/100.;
	Laptop l = {.serial = uid, .weight = weiight, .price = pricee};
	strcpy(l.marka, a);
	uid++;
	free(a);
	return l;
}

void printl(Laptop l){
	printf("Serial: %.4llu Weight: %2.3lf Price: %4.2lf Poduced by: %s\n", l.serial, l.weight, l.price, l.marka);
}

double totalLaptopWeight(Laptop * a){
	double sum = 0.;
	if (a == NULL){return -1.0;}
	for(int i =0; a[i].weight > 0.024; i++){
		sum =sum + a[i].weight;
	}
	return sum;
}

Laptop * minPriceItem(Laptop* a){
	if (a == NULL){return NULL;}
	int min = 0;
	for(int i =1; a[i].weight > 0.024; i++){
		if(a[i].price < a[min].price){
			min =i;
		}
	}
	return a+min;

}

int main(){
	Laptop *ls = malloc(sizeof(Laptop)*(LAPTOPS_COUNT+1));
	srand(clock());
	for(int i =0; i < LAPTOPS_COUNT; i++){
		ls[i] = rd_laptop();
	}
	ls[LAPTOPS_COUNT].weight = 0.;
	for(int i =0; i < LAPTOPS_COUNT; i++){
		printl(ls[i]);
	}
	
	printf("%lf\n", totalLaptopWeight(ls));
	printf("\n");
	printl(*(minPriceItem(ls)));
	printf("%lu\n", sizeof(double));
	free(ls);
	return 0;
}
