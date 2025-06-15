// Copyright Tomescu Ana-Maria 324CAa 2023-2024

#include <stdlib.h>
#include <stdio.h>
#include "matrix_pool.h"

matrix_pool *init_matrix_pool(void)
{
	matrix_pool *pool = (matrix_pool *)malloc(sizeof(matrix_pool));
	pool->count = 0;
	pool->size = 1;
	pool->v = (matrix **)malloc(pool->size * sizeof(matrix *));

	return pool;
}

void check_pool_size(matrix_pool *pool)
{
	int new_size = -1;

	if (pool->count == pool->size) { // Limit reached
		new_size = pool->size * 2;
		pool->size = new_size;
	} else if (pool->count < pool->size / 2) {	// Half empty
		new_size = pool->size / 2;
		pool->size = new_size;
	}

	if (new_size != -1)
		pool->v = (matrix **)realloc(pool->v, new_size * sizeof(matrix *));
}

void insert_matrix(matrix_pool *pool, matrix *m)
{
	check_pool_size(pool);
	pool->v[pool->count++] = m;
}

void remove_matrix(matrix_pool *pool, int index)
{
	for (int i = index; i < pool->count - 1; i++)
		pool->v[i] = pool->v[i + 1];
	pool->count--;

	check_pool_size(pool);
}
