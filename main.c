#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define STRINGS_COUNT   500
#define MAX_STRING_SIZE 500
#define NAME 256

void PrintStrings(char strings[][MAX_STRING_SIZE], int K) {
	for (int i = 0; i <=K; i++) {
		//printf("%d \t", i);
		if (strlen(strings[i]) < MAX_STRING_SIZE) {
			printf("%s", strings[i]);
		}
		else {
			for (int j = 0; j < MAX_STRING_SIZE; j++) {
				printf("%c", strings[i][j]);
			}
		}
	}

}
int test_str_1(char  str_1[MAX_STRING_SIZE], char  str_2[MAX_STRING_SIZE]) {
	int kol_pr = 0;
	/*if ((str_1[0] > str_2[0])) {
		k = 1;
	}
	return(k);*/
	for (int i = 0; i < MAX_STRING_SIZE - kol_pr; i++) {
		//for (int i = 0; i < 2; i++) {
		if (str_1[i] == '\0') {
			return(0);
		}
		else if (str_2[i] == '\0') {
			return(1);
		}
		else if (str_1[i] > str_2[i]) {
			return(1);
		}
		else if (str_1[i] < str_2[i]) {
			return(0);
		}
		kol_pr++;


	}
	return(0);
}
int test_str_3(char  str_1[MAX_STRING_SIZE], char  str_2[MAX_STRING_SIZE]) {
	int kol_pr = 0;
	int max_1 = strlen(str_1), max_2 = strlen(str_2);
	if (max_1 > MAX_STRING_SIZE) {
		max_1 = MAX_STRING_SIZE;
	}
	if (max_2 > MAX_STRING_SIZE) {
		max_2 = MAX_STRING_SIZE;
	}

	if (max_1 > max_2) {
		return(1);
	}
	else if (max_1 == max_2) {
		return(test_str_1(str_1, str_2));
	}
	else {
		return(0);
	}



}
void SortStrings(char strings[][MAX_STRING_SIZE], int (*compareStringsFunction)(char*, char*)) {

	// быстрая сортировка двумерного массива строк
	int k = 0;
	char  temp = 0;
	int f = 1;
	do {
		f = 0;
		for (int i = 1; i < STRINGS_COUNT; i++) {
			//k = test_str(strings[i - 1], strings[i]);
			k = compareStringsFunction(strings[i - 1], strings[i]);
			if (k == 1) {
				for (int j = 0; j < MAX_STRING_SIZE; j++) {
					temp = strings[i - 1][j]; // 
					strings[i - 1][j] = strings[i][j];
					strings[i][j] = temp;
				}
				f = 1;

			}
		}

	} while (f == 1);

}
int main() {
	setlocale(LC_ALL, "Rus");
	unsigned char name[NAME];
	long long f_len;
	printf("Ведите имя файла:");
	gets_s(name, 255);
	//scanf_s("%s", name);
	//printf("%s\n", name);
	FILE* f;
	fopen_s(&f, name, "rt");
	fseek(f, 0, SEEK_END);
	f_len = ftell(f);
	
	char mass[STRINGS_COUNT][MAX_STRING_SIZE];
	char* text;
	
	text = (char*)malloc(f_len + 1);
	fseek(f, 0, SEEK_SET);
	int st=fread(text, 1, f_len, f);
	text[st] = '\0';//массив 
	fclose(f);
	
	
	int poz_in_str = 0;
	int i = 0;
	for (int j = 0; j < st; j++) {
		if ((text[j] != '\n')&&(text[j] != '\0')) {
			mass[i][poz_in_str] = text[j];
			poz_in_str++;
		}
		else{
			if (text[j] != '\0') {
				
				mass[i][poz_in_str++] = '\n';
				
				mass[i][poz_in_str] = '\0';
				
				i++;
				poz_in_str = 0;
			}
		    //mass[i][poz_in_str++] = '\n';
			//
			//mass[i][poz_in_str] = '\0';
			////printf("%s", mass[i]);
			//i++;
			//poz_in_str = 0;

		}
	}
	printf("%d", poz_in_str);
	if ((poz_in_str!=0)&&(mass[i][poz_in_str-1] != '\n')) {

		mass[i][poz_in_str++] = '\n';
		mass[i][poz_in_str] = '\0';
		
	}

	
	SortStrings(mass, test_str_3);
	PrintStrings(mass, i);
}