#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sys\stat.h>// для проверки наличия файла 
//#define STRINGS_COUNT   500
//#define MAX_STRING_SIZE 500
#define NAME 256

// построчная печать
void PrintStrings(char** strings, int K) {
	for (int i = 0; i <K; i++) {
		
			printf("%s\n", strings[i]);
		
	}

}
// если строки одинаковые по длине , проверить по величине 
int test_str_1(char* str_1, char* str_2) { 
	int kol_pr = 0;
	int max_len = max(strlen(str_1), strlen(str_2))+1;
	for (int i = 0; i < max_len - kol_pr; i++) {
		
		if (str_1[i] == '\0') {
			return(-1);
		}
		else if (str_2[i] == '\0') {
			return(1);
		}
		else if (str_1[i] > str_2[i]) {
			return(1);
		}
		else if (str_1[i] < str_2[i]) {
			return(-1);
		}
		kol_pr++;


	}
	return(0);
}
// по длине строки 

int test_str_3( char* str1, char* str2) {
	
	
	int max_1 = strlen(str1);
	int max_2 = strlen(str2);
	
	
	if (max_1 > max_2) {
		return(1);
	}
	else if (max_1 == max_2) {
		return(test_str_1(str1,str2));
	}
	else {
		return(-1);
	}



}

// быстрая сортировка двумерного массива строк
void qsort_t(char* strings[],int b, int e)
{
	int l = b, r = e;
	char* temp;
    char* piv =strings [(l + r) / 2];// Опорным элементом для примера возьмём средний
	while (l <= r)
	{
		while (test_str_3(strings[l] , piv)<0) {

			l++;
		}
			
		while (test_str_3(strings[r], piv)>0) {
			r--;
		}
		if (l <= r) {
			temp = strings[l]; 
			strings[l] = strings[r];
			strings[r] = temp;
			l++;
			r--;
		}
	}
	if (b < r) {
		qsort_t(strings, b, r);
	}
	if (e > l) {
		qsort_t(strings, l, e);
	}
}   


// чтение файла 
void read_file(char* name) {
    printf("имя файла:%s\n", name);
	long long f_len;
	
	
	FILE* f;
	fopen_s(&f, name, "rt");
	fseek(f, 0, SEEK_END);
	f_len = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	char* estr; // на строку 
	char* text; // буфер для чтения строки 
	char* buf; // буфер для раделения 
	char** text_2;
	int str_len = 0;
	
	int i = 0;
	text = (char*)malloc(f_len + 1);
	text_2 = (char**)malloc(sizeof(buf) );

	while (1)
	{
		// Чтение одной строки  из файла
		estr = fgets(text, f_len, f);

		//Проверка на конец файла или ошибку чтения
		if (estr == NULL)
		{
			// Проверяем, что именно произошло: кончился файл
			// или это ошибка чтения
			if (feof(f) != 0)
			{
				//Если файл закончился, выводим сообщение о завершении 
				//чтения и выходим из бесконечного цикла
				
				break;
			}
			else
			{
				//Если при чтении произошла ошибка, выводим сообщение 
				//об ошибке и выходим из бесконечного цикла
				printf("\nОшибка чтения из файла\n");
				exit(1);
			}
		}
		//Если файл не закончился, и не было ошибки чтения 
		//выводим считанную строку  на экран
		str_len = strlen(text);
		buf = (char*)malloc(str_len+1);
		
	
		strcpy_s(buf, str_len+1, text);
		
		if (buf[str_len-1]=='\n') {
			buf[str_len-1] = '\0';
		}
		i++;
		if (i > 1) {
			text_2= (char**)realloc(text_2, sizeof(buf) * i);
			if (text_2 == NULL)
			{
				printf("ошибка выделения памяти \n");
				exit(1);
			}
			
			
		}
		text_2[i - 1] = buf;
		
	}

	
	fclose(f);

	qsort_t(text_2, 0, i - 1); 
	PrintStrings(text_2, i);
	for (int d = 0; d < i; d++) {
		free(text_2[d]);
	}
	free(text_2);
	free(text);
	
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "Rus");
	unsigned char name[NAME];
	struct stat buff; // структура для получения данных файла 
	if (argv[1]!='\0') {// проверяем заполнина ли командная строка 
		strcpy_s(name, NAME, argv[1]);
	}
	else {
		if (stat("filenames.txt", &buff)==-1)// проверка наличия файла, если нет , то ввод с экрана 
		{
			printf("Ведите имя файла:");
	        gets_s(name, 255);

		}
		else { // иначе читать 
			int f_len = 256;
			
			char* estr; // для чтения строки из файла  
			char text[256]; // для чтения имени файла 
			int str_len = 0;
			FILE* f;
			fopen_s(&f, "filenames.txt", "rt");
			while (1)
			{
				// Чтение одной строки  из файла
				estr = fgets(text, f_len, f);

				//Проверка на конец файла или ошибку чтения
				if (estr == NULL)
				{
					// Проверяем, что именно произошло: кончился файл
					// или это ошибка чтения
					if (feof(f) != 0)
					{
						//Если файл закончился, выводим сообщение о завершении 
						//чтения и выходим из бесконечного цикла

						break;
					}
					else
					{
						//Если при чтении произошла ошибка, выводим сообщение 
						//об ошибке и выходим из бесконечного цикла
						printf("\nОшибка чтения из файла\n");
						exit(1);
					}
				}
				//Если файл не закончился, и не было ошибки чтения 
				//выводим считанную строку  на экран
				str_len = strlen(text);
				


				if (text[str_len - 1] == '\n') {
					text[str_len - 1] = '\0';
				}
				read_file(text);
			}

			fclose(f);
			exit(0);
		}
		

	}
	read_file(name);
	

}
