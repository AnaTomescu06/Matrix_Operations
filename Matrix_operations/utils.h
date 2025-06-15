// Copyright Tomescu Ana-Maria 324CAa 2023-2024

/**
 * @brief Alloc a 1d array of integers.
 *
 * @param count the size of the array
 * @return the newly created array
 */
int *alloc_1d_array(int count);

/**
 * @brief Alloc a 2d array of integers.
 *
 * @param lines the number of lines
 * @param columns the number of columns
 * @return the newly created array
 */
int **alloc_2d_array(int lines, int columns);

/**
 * @brief Reads integers from stdin and stores them in a 1d array.
 *
 * @param arr the array where the integers will be stored
 * @param count the number of integers to read
 */
void read_1d_array(int *arr, int count);

/**
 * @brief Reads integers from stdin and stores them in a 2d array.
 *
 * @param arr the array where the integers will be stored
 * @param lines the number of lines to read
 * @param columns the number of columns to read
 */
void read_2d_array(int **arr, int lines, int columns);

/**
 * @brief Free the memory used by a 1d array
 */
void free_1d_array(int *arr);

/**
 * @brief Free the memory used by a 2d array
 */
void free_2d_array(int **arr, int lines);

/**
 * @brief Prints 1d array to stdout.
*/
void print_1d_array(int *arr, int count);

/**
 * @brief Prints 2d array to stdout.
*/
void print_2d_array(int **arr, int lines, int columns);

/**
 * @brief Applies modulo 10007 to number.
*/
int apply_modulo(int n);
