/*
#include <iostream>
#include<math.h>
#include<windows.h>
#include<time.h>
#include<locale>

intmain()
{
	setlocale(LC_ALL, "Russian");

	int M[10] = { 0,1,2,3,4,5,6,7,8,9 };
	intMaxM = -10000;
	intMinM = 10000;

	for (inti = 0; i < 10; i++) {
		if (M[i] > MaxM) {
			MaxM = M[i];
		}
	}

	for (int j = 0; j < 10; j++) {
		if (M[j] < MinM) {
			MinM = M[j];
		}
	}

	intSumm = MaxM - MinM;
	printf("Разница максимального и минимального элементов массива M %d", Summ);
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale>

intmain() {
	setlocale(LC_ALL, "Russian");
	constint size = 10;
	int M[size];

	srand((unsignedint)time(NULL));

	for (inti = 0; i < size; ++i) {
		M[i] = rand() % 100;
	}


	printf("Массивслучайныхчисел: ");
	for (inti = 0; i < size; ++i) {
		printf("%d ", M[i]);
	}
	printf("\n");

	return 0;
}

#include"stdafx.h"
#include<locale>
#include<stdio.h>
#include<stdlib.h>

intmain() {
	setlocale(LC_ALL, "Russian");
	intsize;

	printf("Введите размер массива: ");
	scanf("%d", &size);


	int* M = (int*)malloc(size * sizeof(int));

	printf("Введите %d чисел:\n", size);
	for (inti = 0; i < size; i++) {
		scanf("%d", &M[i]);
	}

	printf("Введённыймассив: ");
	for (inti = 0; i < size; i++) {
		printf("%d ", M[i]);
	}
	printf("\n");

	free(M);
	return 0;
}

#include"stdafx.h"
#include<stdio.h>
#include<locale>
intmain() {
	setlocale(LC_ALL, "Russian");
	int M[3][3];

	printf("Введите 9 чисел (3 строки по 3 числа):\n");
	for (inti = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d", &M[i][j]);
		}
	}

	printf("Суммыпостолбцам:\n");
	for (int j = 0; j < 3; j++) {
		int sum = 0;
		for (inti = 0; i < 3; i++) {
			sum += M[i][j];
		}
		printf("Столбец %d: %d\n", j + 1, sum);
	}

	return 0;
}

#include"stdafx.h"
#include<stdio.h>
#include<string.h>
#include<locale.h>

#define MAX_NAME_LENGTH 50
#define STUDENT_COUNT 5

struct student {
	char surname[MAX_NAME_LENGTH];
	char name[MAX_NAME_LENGTH];
};

intmain() {

	setlocale(LC_ALL, "");

	struct student students[STUDENT_COUNT] = {
			{"Pytyutin", "Sergey"},
			{"Khmelkov", "Maxim"},
			{"Sokolov", "Oleg"},
			{"Cherenkov", "Danil"},
			{"Belov", "Pavel"}
	};

	charsearch_surname[MAX_NAME_LENGTH];
	charsearch_name[MAX_NAME_LENGTH];

	printf("Введитефамилию: ");
	scanf("%49s", search_surname);

	printf("Введитеимя: ");
	scanf("%49s", search_name);

	int found = 0;

	for (inti = 0; i < STUDENT_COUNT; i++) {

		if (strcmp(students[i].surname, search_surname) == 0 &&
			strcmp(students[i].name, search_name) == 0) {
			printf("Найден студент: Фамилия: %s, Имя: %s\n",
				students[i].surname, students[i].name);
			found = 1;
			break;
		}
	}

	if (!found) {
		printf("Студент с заданными параметрами не найден.\n");
	}

	return 0;
}

#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include<malloc.h>
intmain() {
	setlocale(LC_ALL, "Russian");

	int n;
	printf("Введите размер квадратного массива: ");
	while (scanf("%d", &n) != 1 || n <= 0) {
		printf("Ошибка: введите положительное целое число: ");
		while (getchar() != '\n');
	}


	int** M;
	if (M == NULL) {
		printf("Ошибка выделения памяти\n");
		return 1;
	}
	M = newint * [n];
	for (inti = 0; i < n; i++) {
		M[i] = newint[n];
	}


	srand((unsignedint)time(NULL));


	printf("Сгенерированныймассив:\n");
	for (inti = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			M[i][j] = rand() % 51 - 10;
			printf("%4d ", M[i][j]);
		}
		printf("\n");
	}


	intcount_non_positive = 0;
	for (inti = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (M[i][j] <= 0) {
				count_non_positive++;
			}
		}
	}

	printf("Количество неположительных элементов (<= 0): %d\n", count_non_positive);


	for (inti = 0; i < n; i++) free(M[i]);
	free(M);

	return 0;
}

#include<iostream>
#include<cstring>

int main() {
	setlocale(LC_ALL, "");

	constint count = 5;
	structStudent{
	char surname[50];
	char name[50];
	};

	Student students[count] = {
			{"Pytyutin", "Sergey"},
			{"Khmelkov", "Maksim"},
			{"Sokolov", "Oleg"},
			{"Maksimov", "Kirill"},
			{"Belov", "Pavel"}

	};

	std::cout << "Всестуденты:\n";
	for (int i = 0; i < count; i++) {
		std::cout << students[i].surname << " " << students[i].name << "\n";
	}

	charsearch[50];
	std::cout << "\nВведите текст для поиска: ";
	std::cin >> search;

	std::cout << "Результаты:\n";

	bool found = false;

	for (int i = 0; i < count; i++) {
		if (strstr(students[i].surname, search) || strstr(students[i].name, search)) {
			std::cout << students[i].surname << " " << students[i].name << "\n";
			found = true;
		}
	}

	if (!found) {
		std::cout << "Нетсовпадений\n";
	}

	return 0;
}
*/