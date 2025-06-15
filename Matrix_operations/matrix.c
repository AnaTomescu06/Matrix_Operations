// Copyright Tomescu Ana-Maria 324CAa 2023-2024

#include "matrix.h"

matrix *alloc_matrix(int lines, int columns)
{
	matrix *m = (matrix *)malloc(sizeof(matrix));
	m->lines = lines;
	m->columns = columns;
	m->data = alloc_2d_array(lines, columns);
	return m;
}

matrix *resize_matrix(matrix *m, int l_count, int c_count, int *l, int *c)
{
	matrix *new_m = alloc_matrix(l_count, c_count);
	for (int i = 0; i < l_count; i++) {
		int new_line = l[i];
		for (int j = 0; j < c_count; j++) {
			int new_column = c[j];
			new_m->data[i][j] = m->data[new_line][new_column];
		}
	}
	return new_m;
}

matrix *add_matrix(matrix *m1, matrix *m2)
{
	matrix *new_m = alloc_matrix(m1->lines, m1->columns);
	for (int i = 0; i < m1->lines; i++)
		for (int j = 0; j < m1->columns; j++)
			new_m->data[i][j] = apply_modulo(m1->data[i][j] + m2->data[i][j]);
	return new_m;
}

matrix *sub_matrix(matrix *m1, matrix *m2)
{
	matrix *new_m = alloc_matrix(m1->lines, m1->columns);
	for (int i = 0; i < m1->lines; i++)
		for (int j = 0; j < m1->columns; j++)
			new_m->data[i][j] = apply_modulo(m1->data[i][j] - m2->data[i][j]);
	return new_m;
}

matrix *mul_matrix(matrix *m1, matrix *m2)
{
	matrix *r = alloc_matrix(m1->lines, m2->columns);

	for (int i = 0; i < m1->lines; i++) {
		for (int j = 0; j < m2->columns; j++) {
			r->data[i][j] = 0;
			for (int k = 0; k < m1->columns; k++) {
				int mul = m1->data[i][k] * m2->data[k][j];
				r->data[i][j] = apply_modulo(r->data[i][j] + mul);
			}
		}
	}
	return r;
}

matrix *mul_matrix_strassen(matrix *a, matrix *b)
{
	int size = a->lines;
	matrix *c = alloc_matrix(size, size);

	// Stop condition
	if (size == 1) {
		c->data[0][0] = apply_modulo(a->data[0][0] * b->data[0][0]);
		return c;
	}

	// Divide m1 and m2 into 8 matrixes (A, B)
	int *l1 = alloc_1d_array(size / 2);
	int *l2 = alloc_1d_array(size / 2);
	for (int i = 0; i < size / 2; i++) {
		l1[i] = i;
		l2[i] = i + size / 2;
	}
	matrix *a1 = resize_matrix(a, size / 2, size / 2, l1, l1);
	matrix *a2 = resize_matrix(a, size / 2, size / 2, l1, l2);
	matrix *a3 = resize_matrix(a, size / 2, size / 2, l2, l1);
	matrix *a4 = resize_matrix(a, size / 2, size / 2, l2, l2);
	matrix *b1 = resize_matrix(b, size / 2, size / 2, l1, l1);
	matrix *b2 = resize_matrix(b, size / 2, size / 2, l1, l2);
	matrix *b3 = resize_matrix(b, size / 2, size / 2, l2, l1);
	matrix *b4 = resize_matrix(b, size / 2, size / 2, l2, l2);

	// Compute components of M
	matrix *s1 = add_matrix(a1, a4);	// A1 + A4
	matrix *s2 = add_matrix(b1, b4);	// B1 + B4
	matrix *s3 = add_matrix(a3, a4);	// A3 + A4
	matrix *s4 = sub_matrix(b2, b4);	// B2 - B4
	matrix *s5 = sub_matrix(b3, b1);	// B3 - B1
	matrix *s6 = add_matrix(a1, a2);	// A1 + A2
	matrix *s7 = sub_matrix(a3, a1);	// A3 - A1
	matrix *s8 = add_matrix(b1, b2);	// B1 + B2
	matrix *s9 = sub_matrix(a2, a4);	// A2 - A4
	matrix *s10 = add_matrix(b3, b4);	// B3 + B4

	// Compute M
	matrix *m1 = mul_matrix_strassen(s1, s2);
	matrix *m2 = mul_matrix_strassen(s3, b1);
	matrix *m3 = mul_matrix_strassen(a1, s4);
	matrix *m4 = mul_matrix_strassen(a4, s5);
	matrix *m5 = mul_matrix_strassen(s6, b4);
	matrix *m6 = mul_matrix_strassen(s7, s8);
	matrix *m7 = mul_matrix_strassen(s9, s10);

	// Compute C
	matrix *m14 = add_matrix(m1, m4);
	matrix *m57 = sub_matrix(m5, m7);
	matrix *m12 = sub_matrix(m1, m2);
	matrix *m36 = add_matrix(m3, m6);
	matrix *c1 = sub_matrix(m14, m57);
	matrix *c2 = add_matrix(m3, m5);
	matrix *c3 = add_matrix(m2, m4);
	matrix *c4 = add_matrix(m12, m36);

	for (int i = 0; i < size / 2; i++) {
		for (int j = 0; j < size / 2; j++) {
			c->data[i][j] = c1->data[i][j];
			c->data[i][j + size / 2] = c2->data[i][j];
			c->data[i + size / 2][j] = c3->data[i][j];
			c->data[i + size / 2][j + size / 2] = c4->data[i][j];
		}
	}

	// Free memory
	free_1d_array(l1); free_1d_array(l2);
	free_matrix(a1); free_matrix(a2); free_matrix(a3); free_matrix(a4);
	free_matrix(b1); free_matrix(b2); free_matrix(b3); free_matrix(b4);
	free_matrix(m1); free_matrix(m2); free_matrix(m3); free_matrix(m4);
	free_matrix(m5); free_matrix(m6); free_matrix(m7);
	free_matrix(c1); free_matrix(c2); free_matrix(c3); free_matrix(c4);
	free_matrix(m12); free_matrix(m14); free_matrix(m36); free_matrix(m57);
	free_matrix(s1); free_matrix(s2); free_matrix(s3); free_matrix(s4);
	free_matrix(s5); free_matrix(s6); free_matrix(s7); free_matrix(s8);
	free_matrix(s9); free_matrix(s10);

	return c;
}

void compute_matrix_sum(matrix *m)
{
	m->sum = 0;
	for (int i = 0; i < m->lines; i++)
		for (int j = 0; j < m->columns; j++)
			m->sum = apply_modulo(m->sum + m->data[i][j]);
}

void free_matrix(matrix *m)
{
	free_2d_array(m->data, m->lines);
	free(m);
}
