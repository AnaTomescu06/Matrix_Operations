// Copyright Tomescu Ana-Maria 324CAa 2023-2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_pool.h"
#include "utils.h"

void load_matrix_cmd(matrix_pool *pool)
{
	int lines, columns;
	scanf("%d %d", &lines, &columns);

	matrix *m = alloc_matrix(lines, columns);
	read_2d_array(m->data, lines, columns);

	insert_matrix(pool, m);
}

void print_dimensions_cmd(matrix_pool *pool)
{
	int index;
	scanf("%d", &index);

	if (index >= pool->count || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	matrix *m = pool->v[index];
	printf("%d %d\n", m->lines, m->columns);
}

void print_matrix_cmd(matrix_pool *pool)
{
	int index;
	scanf("%d", &index);

	if (index >= pool->count || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	matrix *m = pool->v[index];
	print_2d_array(m->data, m->lines, m->columns);
}

void resize_matrix_cmd(matrix_pool *pool)
{
	int index;
	scanf("%d", &index);

	int l_count, c_count;

	// Read new lines
	scanf("%d", &l_count);
	int *lines = alloc_1d_array(l_count);
	read_1d_array(lines, l_count);

	// Read new columns
	scanf("%d", &c_count);
	int *columns = alloc_1d_array(c_count);
	read_1d_array(columns, c_count);

	if (index >= pool->count || index < 0) {
		printf("No matrix with the given index\n");
		free_1d_array(lines);
		free_1d_array(columns);
		return;
	}

	matrix *m = pool->v[index];
	matrix *new_m = resize_matrix(m, l_count, c_count, lines, columns);

	// Free unused memory
	free_matrix(m);
	free_1d_array(lines);
	free_1d_array(columns);

	// Store result
	pool->v[index] = new_m;
}

void multiply_matrix_cmd(matrix_pool *pool)
{
	int index1, index2;
	scanf("%d %d", &index1, &index2);

	if (index1 >= pool->count ||
		index2 >= pool->count ||
		index1 < 0 || index2 < 0
	) {
		printf("No matrix with the given index\n");
		return;
	}
	matrix *m1 = pool->v[index1];
	matrix *m2 = pool->v[index2];

	if (m1->columns != m2->lines) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	matrix *r = mul_matrix(m1, m2);
	insert_matrix(pool, r);
}

int matrix_cmp_fn(const void *p1, const void *p2)
{
	matrix *m1 = *(matrix **)p1;
	matrix *m2 = *(matrix **)p2;

	return m1->sum - m2->sum;
}

void sort_pool_cmd(matrix_pool *pool)
{
	// Compute sums
	for (int i = 0; i < pool->count; i++)
		compute_matrix_sum(pool->v[i]);

	qsort(pool->v, pool->count, sizeof(matrix *), matrix_cmp_fn);
}

void transpose_matrix_cmd(matrix_pool *pool)
{
	int index;
	scanf("%d", &index);

	if (index >= pool->count || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	matrix *m = pool->v[index];

	// Alloc space for transposed matrix
	int new_lines = m->columns;
	int new_columns = m->lines;
	int **new_data = alloc_2d_array(new_lines, new_columns);

	// Copy data
	for (int i = 0; i < m->lines; i++)
		for (int j = 0; j < m->columns; j++)
			new_data[j][i] = m->data[i][j];

	// Free unused memory
	free_2d_array(m->data, m->lines);

	// Store new properties
	m->lines = new_lines;
	m->columns = new_columns;
	m->data = new_data;
}

void log_power_cmd(matrix_pool *pool)
{
	int index, power;
	scanf("%d %d", &index, &power);

	if (index >= pool->count || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	if (power < 0) {
		printf("Power should be positive\n");
		return;
	}
	matrix *m = pool->v[index];
	if (m->lines != m->columns) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	int size = m->lines;

	// Create identity matrix
	matrix *aux = alloc_matrix(size, size);
	for (int i = 0; i < size; i++) {
		memset(aux->data[i], 0, size * sizeof(int));
		aux->data[i][i] = 1;
	}

	while (power > 1) {
		if (power % 2 == 1) {
			// aux = m * aux
			matrix *aux2 = mul_matrix(m, aux);
			free_matrix(aux);
			aux = aux2;
		}
		// m = m * m
		matrix *aux2 = mul_matrix(m, m);
		free_matrix(m);
		m = aux2;
		power /= 2;
	}
	// m = m * aux
	matrix *aux2 = mul_matrix(m, aux);
	free_matrix(m);
	free_matrix(aux);
	pool->v[index] = aux2;
}

void free_matrix_cmd(matrix_pool *pool)
{
	int index;
	scanf("%d", &index);

	if (index >= pool->count || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	matrix *m = pool->v[index];
	free_matrix(m);
	remove_matrix(pool, index);
}

void free_all_cmd(matrix_pool *pool)
{
	for (int i = 0; i < pool->count; i++)
		free_matrix(pool->v[i]);
	free(pool->v);
	free(pool);
}

void strassen_cmd(matrix_pool *pool)
{
	int index1, index2;
	scanf("%d %d", &index1, &index2);

	if (index1 >= pool->count ||
		index2 >= pool->count ||
		index1 < 0 || index2 < 0
	) {
		printf("No matrix with the given index\n");
		return;
	}
	matrix *m1 = pool->v[index1];
	matrix *m2 = pool->v[index2];

	if (m1->columns != m2->lines) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	matrix *result = mul_matrix_strassen(m1, m2);
	insert_matrix(pool, result);
}

int main(void)
{
	int running = 1;

	matrix_pool *pool = init_matrix_pool();

	while (running) {
		char command;
		scanf("%c", &command);
		switch (command) {
		case 'L':
			load_matrix_cmd(pool);
			break;
		case 'D':
			print_dimensions_cmd(pool);
			break;
		case 'P':
			print_matrix_cmd(pool);
			break;
		case 'C':
			resize_matrix_cmd(pool);
			break;
		case 'M':
			multiply_matrix_cmd(pool);
			break;
		case 'O':
			sort_pool_cmd(pool);
			break;
		case 'T':
			transpose_matrix_cmd(pool);
			break;
		case 'R':
			log_power_cmd(pool);
			break;
		case 'F':
			free_matrix_cmd(pool);
			break;
		case 'S':
			strassen_cmd(pool);
			break;
		case 'Q':
			free_all_cmd(pool);
			running = 0;
			break;
		default:
			if (command != '\n')
				printf("Unrecognized command\n");
			break;
		}
	}
	return 0;
}
