#define _POSIX_C_SOURCE >= 200809L || _XOPEN_SOURCE >= 700
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	FILE* fp;
	char *strbutton; 
	char *strswitch;
	char t1, t2;
	char sw0, sw1, sw2, sw3;
	size_t numbytes=6;
	int x=0;
	int pom=0;
	float pwm = 0;
	int taster_novo, taster_staro=0;
	long int period = 20000L;
	
	while(1)
	{
		fp=fopen("/dev/switch", "r");
		if(fp == NULL){
				puts("Problem pri otvaranju /dev/switch");
		return -1;}
		strswitch = (char *)malloc(numbytes+1);
		getline(&strswitch, &numbytes, fp);
		if(fclose(fp)){
					puts("Problem pri zatvaranju /dev/switch");
		return -1;}
		sw0 = strswitch[5] - 48;
		sw1 = strswitch[4] - 48;
		sw2 = strswitch[3] - 48;
		sw3 = strswitch[2] - 48;
		free(strswitch);
		
		pom = sw0 + sw1*2 + sw3*4;
		x=pom*0.05;
		
	
			
		fp=fopen("/dev/button", "r");
			if(fp == NULL){
				puts("Problem pri otvaranju /dev/button");
			return -1;}	
				
		strbutton = (char *)malloc(numbytes+1);
		getline(&strbutton, &numbytes, fp);
		
			if(fclose(fp)){
				puts("Problem pri zatvaranju /dev/button");
			return -1;}
			
			t1 = strbutton[5] - 48;
			t2 = strbutton[4] - 48;
			free(strbutton);	
			
			taster_novo=0;	
			
			if(t1 == 0 && t2 == 1) taster_novo=1;
			if(t1 == 1 && t2 == 0) taster_novo=2;

			if(taster_novo != taster_staro && taster_novo!=0)
			{
				if(taster_novo == 1)
				{
					if(pwm+x > 1)
						pwm = 1;
				else pwm+=x;}
				
				if(taster_novo == 2)
				{
					if(pwm-x < 0)
						pwm = 0;
				else pwm-=x;}
				
				usleep(1);
			}
			taster_staro = taster_novo;
			printf("%f\n", pwm);
			
			if(sw3 == 0) {
				fp = fopen("/dev/led", "w");
				if(fp == NULL){
					puts("Problem pri otvaranju /dev/led");
					return -1;
				}
				fputs("0x00\n", fp);
				if(fclose(fp)){
					printf("Problem pri zatvaranju /dev/led\n");
					return -1;
				}
			} else{
					fp = fopen("/dev/led", "w");
					if(fp == NULL){
					puts("Problem pri otvaranju /dev/led");
					return -1;}
				
					fputs("0x0F\n", fp);
					if(fclose(fp)){
						printf("Problem pri zatvaranju /dev/led\n");
						return -1;}
					
					
					usleep(pwm*period);
					
					
					fp = fopen("/dev/led", "w");
					if(fp == NULL){
					puts("Problem pri otvaranju /dev/led");
					return -1;}
				
					fputs("0x00\n", fp);
					if(fclose(fp)){
						printf("Problem pri zatvaranju /dev/led\n");
						return -1;}
			}
				usleep((1-pwm)*period);
			}
		}
					
					
			

				
			
			
			
			




		