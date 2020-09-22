#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define STRINGS_COUNT   500
#define MAX_STRING_SIZE 500
#define NAME 256

void PrintStrings(char** strings, int K) {
	for (int i = 0; i <K; i++) {
		//printf("%d\t", i);
			printf("%s\n", strings[i]);
		
	}

}
int test_str_1(char* str_1, char* str_2) {
	int kol_pr = 0;
	int max_len = max(strlen(str_1), strlen(str_2))+1;
	for (int i = 0; i < max_len - kol_pr; i++) {
		
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
int test_str_3(char*  str_1, char*  str_2) {
	int kol_pr = 0;
	int max_1 = strlen(str_1);
	int max_2 = strlen(str_2);

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
void SortStrings(char** strings, int z) {

	// быстрая сортировка двумерного массива строк
	int k = 0;
	char*  temp ;
	int f = 1;
	int max_1 = 0;
	int max_2 = 0;
	do {
		f = 0;
		for (int i = 1; i < z; i++) {
			max_1 = strlen(strings[i - 1]);
			max_2 = strlen(strings[i]);
			//k = test_str(strings[i - 1], strings[i]);
			k = test_str_3(strings[i - 1], strings[i]);
			if (k == 1) {
				temp = strings[i - 1]; // 
				strings[i - 1] = strings[i];
				strings[i] = temp;
				
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
	fseek(f, 0, SEEK_SET);
	//fclose(f);
	char* estr;
	char* text;
	char* buf;
	char** text_2, temp ;
	int str_len = 0;
	int i = 0;
	text = (char*)malloc(f_len + 1);
	text_2 = (char**)malloc(sizeof(buf)*100 );

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
		//printf("%d  %s",str_len, buf);
		if (buf[str_len-1]=='\n') {
			buf[str_len-1] = '\0';
		}
		i++;
		/*if (i > 1) {
			text_2= (char**)realloc(text_2, sizeof(buf) * i);
			if (text_2 == NULL)
			{
				printf("ошибка выделения памяти \n");
				exit(1);
			}
			
			
		}*/
		text_2[i - 1] = buf;
		
	}

	
	fclose(f);

	SortStrings(text_2,  i);
	PrintStrings(text_2, i);

}
