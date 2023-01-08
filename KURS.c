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
	int n_row = fileselection(); // ��� �������� ���-�� ����� � �������
	int** arr = alloc_array(n_row); //������ ����� � ��������� ������
	int* sum = 0; //������� ����� �����
	sum = (int*)malloc(n_row * sizeof(int));
	int c = 0; //����� ������
	int vybor_w_l = 0;
	int vyborsrch = 0;
	int ochki = 0;
	printf("������ ����� �������\n\n");
	while (c != 7) {
		puts("�������� ����� �� ��������������� ������:");
		puts("1) ����� �������� �������");
		puts("2) ����� �������������� �������");
		puts("3) ���������� ������");
		puts("4) ����� ����������/����������� �������");
		puts("5) �����");
		puts("6) ��������� �����");
		puts("7) �����");
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
			printf("������� ����� ����������:\n1) �� �����������\n2) �� ��������\n");
			sorting(arr, n_row);
			printf("������� �������������. ��� ��������� ����� ������� 1 ��� 2\n");
			getchar(); getchar();
			system("cls");
			break;
		}
		case 4: {
			printf("������� �������:\n1)����������\n2)�����������\n");
			scanf("%d", &vybor_w_l);
			printf("\t\t\t\t����������\n\n");
			printf("|�������|   |����� � �������|   |���������|   |�����|   |����� ����� �����|\n");
			printf("|-------|---|---------------|---|---------|---|-----|---|-----------------|\n");
			if (vybor_w_l == 1) win(arr, vybor_w_l, n_row);
			if (vybor_w_l == 2) lose(arr, vybor_w_l, n_row);
			getchar(); getchar();
			system("cls");
			break;
		}
		case 5: {
			printf("������� ����� �����, ������/������ ������� ������ ������� �������: ");
			scanf("%d", &ochki);
			printf("1) ������\n2) ������\n");
			scanf("%d", &vyborsrch);
			printf("|����� �������|\t |   ��������  |  |    �����    |\n");
			search(arr, n_row, vyborsrch, ochki);
			getchar(); getchar();
			system("cls");
			break;
		}
		case 6: {
			printf("������� ����� ������ � ������� ����� ������ (���������� ����������� 12 x 2): ");
			editdata(arr);
			getchar(); getchar();
			system("cls");
			break;
		}
		case 7: {
			printf("���������� ���������");
			exit(EXIT_SUCCESS);
			break;
		}
		}
	}
	destroy(arr, n_row);
	return 1;
}
//��������� ������ ��� ������ � ������ ������ �� �����
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
//������������ ������
void destroy(int** arr, int n_row) {
	for (int i = 0; i < n_row; i++) {
		free(arr[i]);
	}
	free(arr);
}

// ������ ����� � ������� ���-�� �����
int fileselection() {
	int n_row = 0;
	FILE* pog;
	pog = fopen("lapta.txt", "r");
	while (!feof(pog)) { // ���� ���� �� ���������� 
		if (fgetc(pog) == '\n') // ���� ���� ������� �������� ������ 
			n_row += 1; // ���������� ���� ���� � ���������� ������ 
	}
	return n_row;
}

//����� �������� �������
void tableoutput(int** arr, int n_row) {
	puts("\t\t\t\t\t������� ����������� ���� ������ '�����'\n");
	printf("\t   | �������� |\t |   �����  |\n");
	for (int i = 0; i < n_row; i++) {
		printf("-----------|----------|--|----------|\n");
		printf("������� %2d", arr[i][0]);
		for (int j = 1; j < n_col; j++) {
			printf(" |%10d| ", arr[i][j]); //����� ����� �������
		}
		printf("\n");
	}
}
// ����� ���������������� �������
int resulttabble(int** arr, int* sum, int n_row) {
	printf("\t     |����� ����� �����|  |������� ��������|\n");
	for (int i = 0; i < n_row; i++) {
		float average = 0.0; // ������� �������� ������ �������
		printf("-------------|-----------------|--|----------------|\n");
		printf("������� %2d", arr[i][0]);
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
// ����������
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
//����� ���������� �������
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
//����� ����������� �������
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
//����� ������ �� ����� ����� ������/������ ���������
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

//��������� ������ � �������
int editdata(int** arr) {
	int i = 0, j = 0, ochki;
	for (int k = 0; k < 1; k++) {
		scanf("%d %d", &i, &j);
		if (i > 12 || j > 2 || j == 0) {
			printf("��������� ����������� �����������!\n");
			getchar(); getchar();
			system("cls");
			break;
		}
		printf("������� ����:");
		scanf("%i", &ochki);
		arr[i][j] = ochki;
		printf("���� ��������. �������� ����� 1 ��� 2 ��� ��������� ���������");
	}
	return ochki;
}