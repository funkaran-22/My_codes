#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FREQ 10000000
#define SAMP_FREQ (FREQ * 5)

int main(int argc, char *argv[]){
	double value[255] = {};
	
	FILE *fp;
	
	double discr_freq = ((double)FREQ/(double)SAMP_FREQ);
	
	int i;
	for(i=0; i<255; i++){
		value[i] = sin(2*M_PI*i*discr_freq);
	}
	
	fp = fopen("file.txt", "w");
	
	for(i = 0; i < 255; i++){
		fprintf(fp, "%f\n", value[i]);
	}
	
	fclose(fp);
		
	return 0;
}