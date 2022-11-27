#define _CRT_SECURE_NO_WARNINGS
#define MAX 10
#define MAX_EXERCISES 13
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CourseInfo
{
	int courseNum;
	int grade;
} COURSE_INFO;

void firstMessage();
int getNumOfCourses(char sem);
void sortCourses(COURSE_INFO data[], int size);
void printCourses(COURSE_INFO data[], int size);
int intersect(COURSE_INFO dataA[], int sizeA,
	COURSE_INFO dataB[], int sizeB, int interCourse[]);
int unite(COURSE_INFO dataA[], int sizeA,
	COURSE_INFO dataB[], int sizeB, int uniteCourse[]);
void changeGrades(int data[], int size);
void printCNum(int data[], int size);
COURSE_INFO findMinGrade(COURSE_INFO data[], int size);
int findFailPass(int grades[], int size);
int reorderGrades(int grades[], int size, int limit);
void swap(COURSE_INFO* data1, COURSE_INFO* data2);
void swap1(int* a, int* b);

void main()
{
	int A_numOfCourses, B_numOfCourses, i, intereSect_SIZE, Unite_SIZE, numOfExercises, ExercisesArr[MAX_EXERCISES], fpINDEX, limit, GradesUnderLimit;
	COURSE_INFO semA_courses[MAX], semB_courses[MAX], interSect[2 * MAX], Unite[2 * MAX], minGrade;

	firstMessage();
	A_numOfCourses = getNumOfCourses('A');
	for (i = 0; i < A_numOfCourses; i++)
	{
		printf("enter course number and grade: ");
		scanf("%d %d", &semA_courses[i].courseNum, &semA_courses[i].grade);
	}
	B_numOfCourses = getNumOfCourses('B');
	for (i = 0; i < B_numOfCourses; i++)
	{
		printf("enter course number and grade: ");
		scanf("%d %d", &semB_courses[i].courseNum, &semB_courses[i].grade);
	}
	sortCourses(semA_courses, A_numOfCourses);
	sortCourses(semB_courses, B_numOfCourses);

	printf("\n\nSorted courses of semester A: ");
	printCourses(semA_courses, A_numOfCourses);

	printf("\n\nSorted courses of semester B: ");
	printCourses(semB_courses, B_numOfCourses);

	intereSect_SIZE = intersect(semA_courses, A_numOfCourses, semB_courses, B_numOfCourses, interSect);
	Unite_SIZE = unite(semA_courses, A_numOfCourses, semB_courses, B_numOfCourses, Unite);
	printf("courses taken in semester A or semester B: ");
	printCNum(Unite, Unite_SIZE);
	printf("\ncourses taken in semester A and semester B: ");
	printCNum(interSect, intereSect_SIZE);

	minGrade = findMinGrade(semA_courses, A_numOfCourses);
	printf("\n\nMinimum grade in semester A is: %d in course #%d", minGrade.grade, minGrade.courseNum);

	printf("\nHow many exercises were given in course #%d? ", minGrade.courseNum);
	scanf("%d", &numOfExercises);
	printf("Enter exercises grades: ");
	for (i = 0; i < numOfExercises; i++)
		scanf("%d", &ExercisesArr[i]);
	changeGrades(ExercisesArr, numOfExercises);
	printf("Exercise grades: ");
	printCNum(ExercisesArr, numOfExercises);

	fpINDEX = findFailPass(ExercisesArr, numOfExercises);
	printf("\nIndex of Fail-Pass is: %d", fpINDEX);

	printf("\nPlease enter a limit grade: ");
	scanf("%d", &limit);
	GradesUnderLimit = reorderGrades(ExercisesArr, numOfExercises, limit);
	printf("\nAfter reordering grades, the grades smaller than %d are: ", limit);
	printCNum(ExercisesArr, GradesUnderLimit);
}

void firstMessage()
{
	printf("Welcome student!!\n"
		"and bye bye Pizzeria");
}
int getNumOfCourses(char sem)
{
	int num;
	printf("\nPlease enter number of courses in semester %c: ", sem);
	scanf("%d", &num);
	return num;
}
void sortCourses(COURSE_INFO data[], int size)
{
	int i, j;
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - 1 - i; j++)
		{
			if (data[j].courseNum > data[j + 1].courseNum)
				swap(&data[j], &data[j + 1]);
		}
	}
}
void printCourses(COURSE_INFO data[], int size)
{
	int i;
	printf("\nCourse# Grade\n====== =====\n");
	for (i = 0; i < size; i++)
		printf("%d	%d\n", data[i].courseNum, data[i].grade);
}
int intersect(COURSE_INFO dataA[], int sizeA,
	COURSE_INFO dataB[], int sizeB, int interCourse[])
{
	int k = 0, i = 0, j = 0;
	while (i < sizeA && j < sizeB)
	{
		if (dataA[i].courseNum < dataB[j].courseNum)
			i++;
		else if (dataA[i].courseNum > dataB[j].courseNum)
			j++;
		else
		{
			interCourse[k++] = dataA[i].courseNum;
			i++;
			j++;
		}
	}
	return k;
}
int unite(COURSE_INFO dataA[], int sizeA,
	COURSE_INFO dataB[], int sizeB, int uniteCourse[])
{
	int k = 0, i = 0, j = 0;
	while (i < sizeA && j < sizeB)
	{
		if (dataA[i].courseNum < dataB[j].courseNum)
			uniteCourse[k++] = dataA[i++].courseNum;
		if (dataA[i].courseNum > dataB[j].courseNum)
			uniteCourse[k++] = dataB[j++].courseNum;
		if (dataA[i].courseNum == dataB[j].courseNum)
		{
			uniteCourse[k++] = dataA[i].courseNum;
			i++;
			j++;
		}
	}
	while (i < sizeA)
		uniteCourse[k++] = dataA[i++].courseNum;
	while (j < sizeB)
		uniteCourse[k++] = dataB[j++].courseNum;

	return k;
}
void changeGrades(int data[], int size)
{
	data[0] = 30;
	data[size - 1] = 100;
}
void printCNum(int data[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", data[i]);
}
COURSE_INFO findMinGrade(COURSE_INFO data[], int size)
{
	int i, minGrade = data[0].grade;
	COURSE_INFO minCourseGrade;
	for (i = 1; i < size; i++)
	{
		if (data[i].grade < minGrade)
		{
			minGrade = data[i].grade;
			minCourseGrade = data[i];
		}
	}
	return minCourseGrade;
}
int findFailPass(int grades[], int size)
{
	int reqIND, i;
	for (i = 1; i < size; i++)
	{
		if (grades[i - 1] < 60 && grades[i] >= 60)
			return i - 1;
	}
}
int reorderGrades(int grades[], int size, int limit)
{
	int i, j;
	i = 0, j = size - 1;
	while (i <= j)
	{
		while (grades[i] < limit)
			i++;
		while (grades[j] >= limit)
			j--;
		if (i <= j)
			swap1(&grades[i], &grades[j]);
	}
}
void swap(COURSE_INFO* data1, COURSE_INFO* data2)
{
	COURSE_INFO temp;
	temp = *data1;
	*data1 = *data2;
	*data2 = temp;
}
void swap1(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}