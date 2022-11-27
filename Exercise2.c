#define _CRT_SECURE_NO_WARNINGS
#define SIZE 2
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int id;
	int* stud_grades;
	int exams;
}student_init_data;

typedef struct {
	int id;
	double stud_avg;
}student_processed_data;

typedef struct {
	student_processed_data* aboveAvg;
	student_processed_data* belowAvg;
	int aboveAvg_size, belowAvg_size;
	double Total_Avg;
}statistics;

void Init_Array(student_init_data* arr_stud, int size);
int* Input_Data(int num_of_exams);
double Student_Average(int* stud_arr, int size);
double Total_Average(double* avg_stud_arr, int size);
void Classification(student_init_data* arr, int size, statistics* ptr);
void Print_Tab(statistics object);
void Free_Memory(statistics stat, student_init_data* arr, int size);

void main()
{
	int i;
	student_init_data stud_arr[SIZE];
	statistics stat;

	Init_Array(stud_arr, SIZE);
	for (i = 0; i < SIZE; i++) {
		printf("\nStudent %d, id: %d\n", i + 1, stud_arr[i].id);
		stud_arr[i].stud_grades = Input_Data(stud_arr[i].exams);
	}
	Classification(stud_arr, SIZE, &stat);

	Print_Tab(stat);
	Free_Memory(stat, stud_arr, SIZE);
}

void Init_Array(student_init_data* arr_stud, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("Student #%d\n", i + 1);
		printf("Enter ID: ");
		scanf("%d", &(arr_stud[i].id));
		printf("Enter numbers of tests: ");
		scanf("%d", &(arr_stud[i].exams));
		printf("\n");
	}
}
int* Input_Data(int num_of_exams) {
	int* grades_arr, i;
	grades_arr = malloc(num_of_exams * sizeof(int));
	for (i = 0; i < num_of_exams; i++) {
		printf("Enter your grade of exam %d: ", i + 1);
		scanf("%d", &(grades_arr[i]));
	}
	return grades_arr;
}
double Student_Average(int* stud_arr, int size) {
	double avg = 0;
	int i;
	for (i = 0; i < size; i++)
		avg += stud_arr[i];

	return (avg / (double)size);
}
double Total_Average(double* avg_stud_arr, int size) {
	double avg = 0;
	int i;
	for (i = 0; i < size; i++)
		avg += avg_stud_arr[i];

	return (avg / (double)size);
}
void Classification(student_init_data* arr, int size, statistics* ptr) {
	int i, k1, k2;
	k1 = k2 = 0;
	ptr->aboveAvg_size = 0;
	ptr->belowAvg_size = 0;
	double* avg_arr = malloc(size * sizeof(double));
	for (i = 0; i < size; i++)
		avg_arr[i] = Student_Average(arr[i].stud_grades, arr[i].exams);
	
	ptr->Total_Avg = Total_Average(avg_arr, size);
	for (i = 0; i < size; i++)
	{
		if (avg_arr[i] >= ptr->Total_Avg)
			ptr->aboveAvg_size++;
		else
			ptr->belowAvg_size++;
	}
	ptr->aboveAvg = malloc(ptr->aboveAvg_size * sizeof(student_processed_data));
	ptr->belowAvg = malloc(ptr->belowAvg_size * sizeof(student_processed_data));
	for (i = 0; i < size; i++)
	{
		if (Student_Average(arr[i].stud_grades, arr[i].exams) >= ptr->Total_Avg)
		{
			ptr->aboveAvg[k1].id = arr[i].id;
			ptr->aboveAvg[k1].stud_avg = Student_Average(arr[i].stud_grades, arr[i].exams);
			k1++;
		}
		else
		{
			ptr->belowAvg[k2].id = arr[i].id;
			ptr->belowAvg[k2].stud_avg = Student_Average(arr[i].stud_grades, arr[i].exams);
			k2++;
		}
	}
	free(avg_arr);
}
void Print_Tab(statistics object) {
	int i;
	printf("\nThe average is: %lf", object.Total_Avg);

	printf("\nThe students that above the totalAverage: ");
	for (i = 0; i < object.aboveAvg_size; i++) {
		printf("\nStudent ID: %d and his Average: %lf", object.aboveAvg[i].id, object.aboveAvg[i].stud_avg);
	}

	printf("\nThe students that below the totalAverage: ");
	for (i = 0; i < object.belowAvg_size; i++) {
		printf("\nStudent ID: %d and his Average: %lf", object.belowAvg[i].id, object.belowAvg[i].stud_avg);
	}
}
void Free_Memory(statistics stat, student_init_data* arr, int size) {
	int i;
	free(stat.aboveAvg);
	free(stat.belowAvg);
	for (i = 0; i < size; i++)
		free(arr[i].stud_grades);

	printf("\n\nMemory Free!");
}