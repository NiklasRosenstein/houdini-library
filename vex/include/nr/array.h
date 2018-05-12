/* Copyright (c) 2018 Niklas Rosenstein
 *
 * last modified: 2018-05-12
 */

/**
 * Returns the index of first occurence of the value *v* in the array *a*.
 * If the value does not exist in the array, returns -1.
 *
 * @param a: The array to search the value in.
 * @param v: The value to search for.
 * @return: The index of the value or -1.
 */
int nr_array_indexof(int a[]; int v) {
  for (int i = 0; i < len(a); ++i) {
    if (a[i] == v) return i;
  }
  return -1;
}

/**
 * Appends the value *v* to the array *a* only if the value does not already
 * occur in the array.
 *
 * @param a: The array to append the value to.
 * @param v: The value to append to the array.
 * @return: 1 if the value was appended, 0 otherwise.
 */
int nr_array_unique_append(int a[]; int v) {
  if (nr_array_indexof(a, v) == -1) {
    append(a, v);
    return 1;
  }
  return 0;
}
