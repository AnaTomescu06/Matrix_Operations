// Copyright Tomescu Ana-Maria 324CAa 2023-2024

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int *alloc_1d_array(int count)
{
	int *v = (int *)malloc(count * sizeof(int));
	return v;
}

int **alloc_2d_array(int lines, int columns)
{
	int **v = (int **)malloc(lines * sizeof(int *));
	for (int i = 0; i < lines; i++)
		v[i] = alloc_1d_array(columns);
	return v;
}

void read_1d_array(int *arr, int count)
{
	for (int i = 0; i < count; i++)
		scanf("%d", &arr[i]);
}

void read_2d_array(int **arr, int lines, int columns)
{
	for (int i = 0; i < lines; i++)
		read_1d_array(arr[i], columns);
}

void free_1d_array(int *arr)
{
	free(arr);
}

void free_2d_array(int **arr, int lines)
{
	for (int i = 0; i < lines; i++)
		free_1d_array(arr[i]);
	free(arr);
}

void print_1d_array(int *arr, int count)
{
	for (int i = 0; i < count; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void print_2d_array(int **arr, int lines, int columns)
{
	for (int i = 0; i < lines; i++)
		print_1d_array(arr[i], columns);
}

int apply_modulo(int n)
{
	n = n % 10007;
	if (n < 0)
		n += 10007;
	return n;
}
