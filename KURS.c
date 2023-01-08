#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define n_col 3

int** alloc_array(int n_row);
void destroy(int** arr, int n_row);
int fileselection();
void tableoutput(int** arr, int n_row);
int resulttabble(int** arr, int* sum, int n_row);
int sorting(int** arr, int n_row);
int win(int** arr, int vybor_w_l, int n_row);
int lose(int** arr, int vybor_w_l, int n_row);
int search(int** arr, int n_row, int vyborsrch, int ochki);
int editdata(int** arr);

int main() {
	system("chcp 1251");
	system("cls");
	int n_row = fileselection(); // для подсчета кол-ва строк в массиве
	int** arr = alloc_array(n_row); //чтение файла и выделение памяти
	int* sum = 0; //подсчет суммы очков
	sum = (int*)malloc(n_row * sizeof(int));
	int c = 0; //выбор пункта
	int vybor_w_l = 0;
	int vyborsrch = 0;
	int ochki = 0;
	printf("Чтение файла успешно\n\n");
	while (c != 7) {
		puts("Выберите пункт из представленного списка:");
		puts("1) Вывод исходной таблицы");
		puts("2) Вывод результирующей таблицы");
		puts("3) Сортировка команд");
		puts("4) Вывод победителя/проигравшей команды");
		puts("5) Поиск");
		puts("6) Изменение очков");
		puts("7) Выход");
		scanf("%d", &c);
		system("cls");
		switch (c) {
		case 1: {
			tableoutput(arr, n_row);
			getchar(); getchar();
			system("cls");
			break;
		}
		case 2: {
			resulttabble(arr, sum, n_row);
			getchar(); getchar();
			system("cls");
			break;
		}
		case 3: {
			printf("Введите выбор сортировки:\n1) По возрастанию\n2) По рейтингу\n");
			sorting(arr, n_row);
			printf("Команды отсортированы. Для просмотра снова введите 1 или 2\n");
			getchar(); getchar();
			system("cls");
			break;
		}
		case 4: {
			printf("Вывести команду:\n1)Победителя\n2)Проигравшую\n");
			scanf("%d", &vybor_w_l);
			printf("\t\t\t\tПобедитель\n\n");
			printf("|Команда|   |Место в таблице|   |Перебежки|   |Свечи|   |Общее число очков|\n");
			printf("|-------|---|---------------|---|---------|---|-----|---|-----------------|\n");
			if (vybor_w_l == 1) win(arr, vybor_w_l, n_row);
			if (vybor_w_l == 2) lose(arr, vybor_w_l, n_row);
			getchar(); getchar();
			system("cls");
			break;
		}
		case 5: {
			printf("Введите число очков, меньше/больше которых хотите вывести команды: ");
			scanf("%d", &ochki);
			printf("1) Больше\n2) Меньше\n");
			scanf("%d", &vyborsrch);
			printf("|Номер команды|\t |   Пробежки  |  |    Свечи    |\n");
			search(arr, n_row, vyborsrch, ochki);
			getchar(); getchar();
			system("cls");
			break;
		}
		case 6: {
			printf("Введите номер строки и столбца через пробел (Допустимая размерность 12 x 2): ");
			editdata(arr);
			getchar(); getchar();
			system("cls");
			break;
		}
		case 7: {
			printf("Завершение программы");
			exit(EXIT_SUCCESS);
			break;
		}
		}
	}
	destroy(arr, n_row);
	return 1;
}
//Выделение памяти под массив и запись данных из файла
int** alloc_array(int n_row) {
	FILE* pog;
	pog = fopen("lapta.txt", "r");
	int** arr = (int**)malloc(n_row * sizeof(int*));
	for (int i = 0; i < n_row; i++) {
		arr[i] = (int*)malloc(n_col * sizeof(int));
	}
	for (int i = 0; i < n_row; i++) {
		for (int j = 0; j < n_col; j++) {
			fscanf(pog, "%d", &arr[i][j]);
		}
	}
	return arr;
}
//Освобождение памяти
void destroy(int** arr, int n_row) {
	for (int i = 0; i < n_row; i++) {
		free(arr[i]);
	}
	free(arr);
}

// Чтение файла и подсчет кол-ва строк
int fileselection() {
	int n_row = 0;
	FILE* pog;
	pog = fopen("lapta.txt", "r");
	while (!feof(pog)) { // Пока файл не закончился 
		if (fgetc(pog) == '\n') // Пока есть картеки переноса строки 
			n_row += 1; // Прибавляем плюс один к количеству команд 
	}
	return n_row;
}

//Вывод исходной таблицы
void tableoutput(int** arr, int n_row) {
	puts("\t\t\t\t\tТаблица результатов вида спорта 'ЛАПТА'\n");
	printf("\t   | Пробежки |\t |   Свечи  |\n");
	for (int i = 0; i < n_row; i++) {
		printf("-----------|----------|--|----------|\n");
		printf("Команда %2d", arr[i][0]);
		for (int j = 1; j < n_col; j++) {
			printf(" |%10d| ", arr[i][j]); //Вывод очков команды
		}
		printf("\n");
	}
}
// Вывод результатирующей таблицы
int resulttabble(int** arr, int* sum, int n_row) {
	printf("\t     |Общее число очков|  |Среднее значение|\n");
	for (int i = 0; i < n_row; i++) {
		float average = 0.0; // Среднее значение каждой команды
		printf("-------------|-----------------|--|----------------|\n");
		printf("Команда %2d", arr[i][0]);
		for (int j = 1; j < n_col; j++) {
			sum[i] = arr[i][1] * 2;
			sum[i] += arr[i][2];
			average += arr[i][j];
		}
		printf("   |%17d| ", sum[i]);
		printf(" |%16.3f| ", average / 2);
		printf("\n");
	}
	return sum;
}
// Сортировка
int sorting(int** arr, int n_row) {
	int i, j = 1, pass, B, vyborsort = 0;
	scanf("%d", &vyborsort);
	pass = 0;
		while (pass <= n_row - 1) {
			i = 0;
			for (i = 0; i <= n_row - 2; i++) {
				j = 1;
				if (((vyborsort == 1) && (arr[i][j] > arr[i + 1][j])) || ((vyborsort == 2) && ((arr[i][j] < arr[i + 1][j])))) {
					for (j = 0; j <= n_col - 1; j++) {
						B = arr[i][j];
						arr[i][j] = arr[i + 1][j];
						arr[i + 1][j] = B;
					}
				}
			}
			pass++;
			B = 0;
		}
}
//Вывод выигравшей команды
int win(int** arr, int vybor_w_l, int n_row) {
	int index, per = 0, svechi = 0, kom = 0, max = -1;
	for (int i = 0; i < n_row; ++i) {
		for (int j = 1; j < n_col; ++j) {
			if (max < arr[i][j] * 2 + arr[i][j + 1] && max != arr[i][j] * 2 + arr[i][j + 1]) {
				max = arr[i][j] * 2 + arr[i][j + 1];
				index = i + 1;
				per = arr[i][j];
				svechi = arr[i][j + 1];
				kom = arr[i][0];
			}
		}
	}
	printf("|%7d|   |%15d|   |%9d|   |%5d|   |%17d|\n", kom, index, per, svechi, max);
	return max;
}
//Вывод проигравшей команды
int lose(int** arr, int vybor_w_l, int n_row) {
	int index, per = 0, svechi = 0, kom = 0, min = 9999;
	for (int i = 0; i < n_row; ++i) {
		for (int j = 1; j < n_col; ++j) {
			if (min > arr[i][j] * 2 + arr[i][j] && min != arr[i][j] * 2 + arr[i][j]) {
				min = arr[i][j] * 2 + arr[i][j + 1];
				index = i + 1;
				per = arr[i][j];
				svechi = arr[i][j + 1];
				kom = arr[i][0];
			}
		}
	}
	printf("|%7d|   |%15d|   |%9d|   |%5d|   |%17d|\n", kom, index, per, svechi, min);
	return min;
}
//Поиск команд по числу очков больше/меньше заданного
int search(int** arr, int n_row, int vyborsrch, int ochki) {
	for (int i = 0; i < n_row; i++) {
		printf("|-------------|--|-------------|--|-------------|\n");
		for (int j = 0; j < n_col; j++) {
			if (((vyborsrch == 1) && (arr[i][1] * 2 + arr[i][2] > ochki)) || ((vyborsrch == 2) && ((arr[i][1] * 2 + arr[i][2] < ochki && arr[i][1] * 2 < ochki && arr[i][1] * 2 != ochki && arr[i][2] < ochki)))) {
				printf("|%13d|  ", arr[i][j]);
			}
		}
		printf("\n");
	}
	return 1;
}

//Изменение данных в таблице
int editdata(int** arr) {
	int i = 0, j = 0, ochki;
	for (int k = 0; k < 1; k++) {
		scanf("%d %d", &i, &j);
		if (i > 12 || j > 2 || j == 0) {
			printf("Введенная размерность недопустима!\n");
			getchar(); getchar();
			system("cls");
			break;
		}
		printf("Введите очки:");
		scanf("%i", &ochki);
		arr[i][j] = ochki;
		printf("Очки изменены. Выберите пункт 1 или 2 для просмотра изменений");
	}
	return ochki;
}