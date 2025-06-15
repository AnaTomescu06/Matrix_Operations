// Copyright Tomescu Ana-Maria 324CAa 2023-2024

#include "matrix.h"

struct matrix_pool_t {
	int size;
	int count;
	matrix **v;
};

typedef struct matrix_pool_t matrix_pool;

/**
 * @brief Initializes an empty matrix pool with 1 free space.
 *
 * @return the newly created matrix pool
 */
matrix_pool *init_matrix_pool(void);

/**
 * @brief Inserts a new matrix into the pool.
 * If the pool is full, it extends it by doubling it's size.
 *
 * @param pool the pool
 * @param m the matrix to add to the pool
 */
void insert_matrix(matrix_pool *pool, matrix *m);

/**
 * @brief Removes a matrix from the pool.
 * If the pool gets half empty, it frees half the memory.
 * The remaining matrixes are shifted to the left. No gaps will exist.
 *
 * @param pool the pool
 * @param index matrix to remove
 */
void remove_matrix(matrix_pool *pool, int index);
