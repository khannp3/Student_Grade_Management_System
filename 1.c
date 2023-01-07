#include <stdio.h>
#include <stdlib.h>
#include "Q.h"

char *my_strcat(const char * const str1, const char * const str2){

	char *z = NULL;

	int total_len = strlen(str1)+ strlen(str2); //total length is str1+str2

	z = calloc(total_len , sizeof(char));

	for (int j = 0; j < strlen(str1); j++){ //loops through str1 array
		z[j] = str1[j];  //takes index from str1
	}

	for (int j = strlen(str1), w = 0; w < strlen(str2); j++, w++){ //loops through str2 array
		z[j] = str2[w]; //takes index from str2
	}

	z[total_len] = '\0';

	return z;
}
