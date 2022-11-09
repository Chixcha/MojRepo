#include <stdio.h>
#include <unistd.h>

int main(int arc, char** argv)
{
	FILE* fp;
	char *str;
	char tval1,tval2;
	size_t numbytes=6;
	float percentage;
	long int period = 20000L;
	if(argc == 2)
			sscanf(argv[1],"%f",&percentage);
	else{
			printf("Pogresan broj argumenata\n");
			return -1;
	}
	while(1)
	{
		fp = fopen("/dev/button", "r");
		if(fp == NULL){
				puts("Problem pri otvaranju /dev/button");
				return -1;}
				
		//ocitaj vrednosti tastera i smesti ih u prethodno alocirani niz		
		str = (char *)malloc(numbytes+1);
		getline(&str, &numbytes, fp);
		
		if(fclose(fp)){
				puts("Problem pri zatvaranju /dev/button");
				return -1;}
				
		//konvertuj ASCII u brojeve
		tval1 = str[2] - 48;
		tval2 = str[3] - 48;
		
		if(tval1 = 0 && tval2 = 1 && percentage<=0.9){
			
		percentage+=0.1;}
		
		if(tval = 1 && tval2 = 0 && percentage>=0.1){
			
		percentage-=0.1;}
	
					
					
		fp = fopen("/dev/led", "w");
		if(fp == NULL){
				printf("Problem pri otvaranju /dev/led\n");
				return -1;
		}
		
			//pali diode
			fputs("0x0f\n", fp);
			if(fclose(fp)){
				printf("Problem pri zatvaranju /dev/led\n");
				return -1;
			}
			//pwm impuls odredjen preko usleep funkcije i zadatog argumenta percentage
			usleep(percentage*period);
			
			
			fp = fopen("/dev/led", "w");
			if(fp == NULL){
					printf("Problem pri otvaranju /dev/led\n");
			return -1;}
			
			//ugasi diode
			fputs("0x00\n", fp);
			if(fclose(fp)){
					printf("Problem pri zatvaranju /dev/led\n");
					return -1;}
			//pwm pauza oredjena preko usleep funkcije i zadatog argumenta percentage
			usleep((1-percentage)*period);
			
	}
			
}		
		
		
		
		
		
		