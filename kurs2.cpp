#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <locale.h>
#include <string.h>

#define INF 99999

int** createMatrix(int size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)calloc(size, sizeof(int));
    }
    return matrix;
}

void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void printMatrix(int** matrix, int size) {
    printf("\n=== МАТРИЦА СМЕЖНОСТИ ГРАФА ===\n\n");

    printf("    ");
    for (int j = 0; j < size; j++) {
        printf(" V%d ", j);
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("V%d: ", i);
        for (int j = 0; j < size; j++) {
            if (i == j) {
                printf("  0 ");
            }
            else if (matrix[i][j] == 0) {
                printf("  . ");
            }
            else {
                printf("%3d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int** generateRandomGraph(int size, int includeNegative, int isDirected) {
    int** matrix = createMatrix(size);

    srand(time(NULL));

    if (isDirected) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i != j) {
                    if (rand() % 100 < 50) {
                        if (includeNegative) {
                            matrix[i][j] = (rand() % 121) - 20;
                        }
                        else {
                            matrix[i][j] = rand() % 100 + 1;
                        }
                    }
                }
            }
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (rand() % 100 < 50) {
                    int weight;
                    if (includeNegative) {
                        weight = (rand() % 121) - 20;
                    }
                    else {
                        weight = rand() % 100 + 1;
                    }
                    matrix[i][j] = weight;
                    matrix[j][i] = weight;
                }
            }
        }
    }

    return matrix;
}

int** inputGraphFromKeyboard(int size, int isDirected) {
    int** matrix = createMatrix(size);

    printf("\nВведите веса ребер (0 - если ребра нет):\n");

    if (isDirected) {
        printf("(Ориентированный граф - ребра могут быть направленными)\n");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    matrix[i][j] = 0;
                    continue;
                }

                printf("Вес ребра V%d -> V%d: ", i, j);
                scanf("%d", &matrix[i][j]);
            }
        }
    }
    else {
        printf("(Неориентированный граф - ребра симметричные)\n");
        for (int i = 0; i < size; i++) {
            for (int j = i; j < size; j++) {
                if (i == j) {
                    matrix[i][j] = 0;
                    continue;
                }

                printf("Вес ребра V%d <-> V%d: ", i, j);
                int weight;
                scanf("%d", &weight);
                matrix[i][j] = weight;
                matrix[j][i] = weight;
            }
        }
    }

    return matrix;
}

int** loadGraphFromFile(const char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("\nОшибка: не удалось открыть файл '%s'\n", filename);
        return NULL;
    }

    if (fscanf(file, "%d", size) != 1) {
        printf("Ошибка: неверный формат файла\n");
        fclose(file);
        return NULL;
    }

    if (*size <= 0) {
        printf("Ошибка: некорректный размер графа\n");
        fclose(file);
        return NULL;
    }

    int** matrix = createMatrix(*size);

    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                printf("Ошибка: недостаточно данных в файле\n");
                freeMatrix(matrix, *size);
                fclose(file);
                return NULL;
            }
        }
    }

    fclose(file);
    printf("\nГраф успешно загружен из файла '%s'\n", filename);
    return matrix;
}

void saveGraphToFile(int** matrix, int size, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("\nОшибка: не удалось создать файл '%s'\n", filename);
        return;
    }

    fprintf(file, "%d\n", size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("\nГраф успешно сохранен в файл '%s'\n", filename);
}

void bellmanFord(int** matrix, int size, int start) {
    int* distance = (int*)malloc(size * sizeof(int));
    int hasNegativeCycle = 0;

    for (int i = 0; i < size; i++) {
        distance[i] = INF;
    }
    distance[start] = 0;

    printf("\n=== ВЫПОЛНЕНИЕ АЛГОРИТМА ===\n");

    for (int iteration = 1; iteration <= size - 1; iteration++) {
        int changes = 0;

        for (int from = 0; from < size; from++) {
            for (int to = 0; to < size; to++) {
                if (matrix[from][to] != 0) {
                    if (distance[from] != INF &&
                        distance[from] + matrix[from][to] < distance[to]) {
                        distance[to] = distance[from] + matrix[from][to];
                        changes = 1;
                    }
                }
            }
        }

        if (changes == 0) {
            break;
        }
    }

    for (int from = 0; from < size; from++) {
        for (int to = 0; to < size; to++) {
            if (matrix[from][to] != 0) {
                if (distance[from] != INF &&
                    distance[from] + matrix[from][to] < distance[to]) {
                    hasNegativeCycle = 1;
                    break;
                }
            }
        }
        if (hasNegativeCycle) break;
    }

    printf("\n=== РЕЗУЛЬТАТЫ ===\n");
    printf("Стартовая вершина: %d\n\n", start);

    if (hasNegativeCycle) {
        printf("Граф содержит отрицательный цикл!\n");
        printf("Кратчайшие пути не существуют!\n\n");
    }

    for (int i = 0; i < size; i++) {
        printf("До вершины %d: ", i);
        if (distance[i] == INF) {
            printf("нет пути\n");
        }
        else if (i == start) {
            printf("0 (стартовая вершина)\n");
        }
        else {
            printf("%d\n", distance[i]);
        }
    }

    FILE* file = fopen("result.txt", "w");
    if (file) {
        fprintf(file, "РЕЗУЛЬТАТЫ АЛГОРИТМА ФОРДА-БЕЛЛМАНА\n");
        fprintf(file, "Стартовая вершина: %d\n\n", start);

        if (hasNegativeCycle) {
            fprintf(file, "ВНИМАНИЕ: Граф содержит отрицательный цикл!\n");
            fprintf(file, "Кратчайшие пути не существуют!\n\n");
        }

        for (int i = 0; i < size; i++) {
            if (distance[i] == INF) {
                fprintf(file, "Вершина %d: недостижима\n", i);
            }
            else if (i == start) {
                fprintf(file, "Вершина %d (стартовая): 0\n", i);
            }
            else {
                fprintf(file, "Вершина %d: %d\n", i, distance[i]);
            }
        }

        fclose(file);
        printf("\nРезультаты сохранены в файл 'result.txt'\n");
    }

    free(distance);
}

int getNumber(const char* prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
            return value;
        }
        printf("Ошибка! Введите число от %d до %d\n", min, max);
        while (getchar() != '\n');
    }
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

int getGraphType() {
    int choice;
    while (1) {
        printf("\nВыберите тип графа:\n");
        printf("1. Ориентированный граф (направленные ребра)\n");
        printf("2. Неориентированный граф (симметричные ребра)\n");
        printf("Выберите вариант (1-2): ");

        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
            printf("Ошибка! Пожалуйста, выберите 1 или 2\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        return choice;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int** matrix = NULL;
    int size = 0;
    int choice;

    printf("        КУРСОВАЯ РАБОТА\n");
    printf("  по теме: АЛГОРИТМ ФОРДА-БЕЛЛМАНА\n");
    printf("  Выполнил студент группы 24ВВВ1:\n");
    printf("                                  Хмельков М.А.\n");
    printf("===============================================\n\n");

    while (1) {
        printf("\nМЕНЮ:\n");
        printf("1. Создать/загрузить граф\n");
        printf("2. Показать текущий граф\n");
        printf("3. Выполнить алгоритм Форда-Беллмана\n");
        printf("4. Сохранить граф в файл\n");
        printf("5. Выйти из программы\n");
        printf("Выберите вариант (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
        case 1: {
            printf("\n=== ВЫБЕРИТЕ СПОСОБ СОЗДАНИЯ ГРАФА ===\n");
            printf("1. Автоматическая генерация (случайный граф)\n");
            printf("2. Ручной ввод с клавиатуры\n");
            printf("3. Загрузка из файла\n");
            printf("4. Вернуться в главное меню\n");
            printf("Выберите вариант (1-4): ");

            int graphChoice;
            scanf("%d", &graphChoice);
            clearInputBuffer();

            if (matrix != NULL) {
                freeMatrix(matrix, size);
                matrix = NULL;
            }

            switch (graphChoice) {
            case 1: {
                size = getNumber("\nВведите количество вершин (2-7): ", 2, 7);

                int graphType = getGraphType();
                int isDirected = (graphType == 1);

                printf("\nВключить отрицательные веса?\n");
                printf("1. Да\n");
                printf("2. Нет\n");
                printf("Выберите (1-2): ");
                int weightChoice;
                scanf("%d", &weightChoice);
                clearInputBuffer();

                matrix = generateRandomGraph(size, weightChoice == 1, isDirected);
                printf("\nСлучайный граф успешно создан!\n");
                if (isDirected) {
                    printf("Тип: ориентированный граф\n");
                }
                else {
                    printf("Тип: неориентированный граф\n");
                }
                break;
            }

            case 2: {
                size = getNumber("\nВведите количество вершин (2-7): ", 2, 7);

                int graphType = getGraphType();
                int isDirected = (graphType == 1);

                matrix = inputGraphFromKeyboard(size, isDirected);
                printf("\nГраф успешно введен!\n");
                if (isDirected) {
                    printf("Тип: ориентированный граф\n");
                }
                else {
                    printf("Тип: неориентированный граф\n");
                }
                break;
            }

            case 3: {
                char filename[100];
                printf("\nВведите имя файла: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;

                matrix = loadGraphFromFile(filename, &size);
                break;
            }

            case 4:
                break;

            default:
                printf("Неверный выбор!\n");
            }
            break;
        }

        case 2: {
            if (matrix == NULL) {
                printf("\nГраф не создан! Сначала создайте или загрузите граф.\n");
            }
            else {
                printMatrix(matrix, size);
            }
            break;
        }

        case 3: {
            if (matrix == NULL) {
                printf("\nГраф не создан! Сначала создайте или загрузите граф.\n");
            }
            else {
                printf("\nВведите номер стартовой вершины (0-%d): ", size - 1);
                int start;
                scanf("%d", &start);
                clearInputBuffer();

                if (start < 0 || start >= size) {
                    printf("Ошибка! Стартовая вершина должна быть от 0 до %d\n", size - 1);
                }
                else {
                    bellmanFord(matrix, size, start);
                }
            }
            break;
        }

        case 4: { 
            if (matrix == NULL) {
                printf("\nГраф не создан! Нечего сохранять.\n");
            }
            else {
                char filename[100];
                printf("\nВведите имя файла для сохранения (по умолчанию graph.txt): ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;

                if (strlen(filename) == 0) {
                    strcpy(filename, "graph.txt");
                }

                saveGraphToFile(matrix, size, filename);
            }
            break;
        }

        case 5: {
            printf("\nПрограмма завершена. (0__0)\n");

            if (matrix != NULL) {
                freeMatrix(matrix, size);
            }
            return 0;
        }

        default:
            printf("Неверный выбор! Пожалуйста, выберите 1-5.\n");
        }
    }

    return 0;
}