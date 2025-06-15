// Copyright Tomescu Ana-Maria 324CAa 2023-2024

#include <stdlib.h>
#include "utils.h"

struct matrix_t {
	int lines;
	int columns;
	int **data;
	int sum;
};

typedef struct matrix_t matrix;

/**
 * @brief Alloc a new matrix
 *
 * @param lines number of lines
 * @param columns number of columns
 * @return a dynamic alloc'ed matrix
 */
matrix *alloc_matrix(int lines, int columns);

/**
 * @brief Resize a matrix
 *
 * @param m matrix to resize
 * @param l_count new number of lines
 * @param c_count new number of columns
 * @param l array of indexes of lines
 * @param c array of indexes of columns
 * @return a new matrix with the desired size
 */
matrix *resize_matrix(matrix *m, int l_count, int c_count, int *l, int *c);

/**
 * @brief Performs matrix addition.
 *
 * @param m1 first matrix
 * @param m2 second matrix
 * @return a new matrix representing m1 + m2
 */
matrix *add_matrix(matrix *m1, matrix *m2);

/**
 * @brief Performs matrix subtraction.
 *
 * @param m1 first matrix
 * @param m2 second matrix
 * @return a new matrix representing m1 - m2
 */
matrix *sub_matrix(matrix *m1, matrix *m2);

/**
 * @brief Performs matrix multiplication.
 *
 * @param m1 first matrix
 * @param m2 second matrix
 * @return a new matrix representing m1 * m2
 */
matrix *mul_matrix(matrix *m1, matrix *m2);

/**
 * @brief Performs matrix multiplication using Strassen algorithm.
 *
 * @param a first matrix
 * @param b second matrix
 * @return a new matrix representing a * b
 */
matrix *mul_matrix_strassen(matrix *a, matrix *b);

/**
 * @brief Computes the sum of all elements of m.
 * The result is stored in m->sum.
 *
 * @param m the matrix
 */
void compute_matrix_sum(matrix *m);

/**
 * @brief Frees all the memory used by a matrix
 *
 * @param m the matrix
 */
void free_matrix(matrix *m);
