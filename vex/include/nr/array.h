/* Copyright (c) 2018 Niklas Rosenstein
 *
 * last modified: 2018-05-13
 */

/**
 * Returns the index of first occurence of the value *v* in the array *a*.
 * If the value does not exist in the array, returns -1.
 *
 * @param a: The array to search the value in.
 * @param v: The value to search for.
 * @return: The index of the value or -1.
 */
#define DEFINE_NR_ARRAY_INDEXOF(TYPE) \
int nr_array_indexof(TYPE a[]; TYPE v) { \
  for (int i = 0; i < len(a); ++i) { \
    if (a[i] == v) return i; \
  } \
  return -1; \
}

DEFINE_NR_ARRAY_INDEXOF(int)
DEFINE_NR_ARRAY_INDEXOF(string)


/**
 * Appends the value *v* to the array *a* only if the value does not already
 * occur in the array.
 *
 * @param a: The array to append the value to.
 * @param v: The value to append to the array.
 * @return: 1 if the value was appended, 0 otherwise.
 */
#define DEFINE_NR_ARRAY_UNIQUE_APPEND(TYPE) \
int nr_array_unique_append(TYPE a[]; TYPE v) { \
  if (nr_array_indexof(a, v) == -1) { \
    append(a, v); \
    return 1; \
  } \
  return 0; \
}

DEFINE_NR_ARRAY_UNIQUE_APPEND(int)
DEFINE_NR_ARRAY_UNIQUE_APPEND(string)


/**
 * Returns the common elements of the two arrays *a* and *b*.
 */
#define DEFINE_NR_ARRAY_COMMON_ELEMENTS(TYPE) \
TYPE[] nr_array_common_elements(TYPE a[], b[]) { \
  TYPE result[]; \
  for (int i = 0; i < len(a); ++i) { \
    if (nr_array_indexof(b, a[i]) != -1) { \
      append(result, a[i]); \
    } \
  } \
  return result; \
}

DEFINE_NR_ARRAY_COMMON_ELEMENTS(int)
DEFINE_NR_ARRAY_COMMON_ELEMENTS(string)


/**
 * Returns the insert index for *v* into the sorted array *a*.
 * Using the returned index to insert the value will keep the
 * array in its sorted state.
 *
 * The function is stable in that if the value *v* equals a
 * value that is already in the array, the returned index is
 * the index of that value.
 *
 * @param a: The array where the value would be inserted into.
 * @param v: The value that would be inserted.
 * @param num: The number of elements from the beginning of the
 *    array to search through. If omitted, defaults to the actual
 *    size of the array.
 */
#define DEFINE_NR_ARRAY_SORTED_INSERT_INDEX(TYPE) \
int nr_array_sorted_insert_index(TYPE a[]; TYPE v; int num) { \
  int left = 0, right = num - 1; \
  while (left <= right) { \
    int pivot = (left + right) / 2; \
    if (a[pivot] < v) { \
      if (left == right) return pivot + 1; \
      left = pivot + 1; \
    } \
    else if (a[pivot] > v) { \
      if (left == right) return pivot -1; \
      right = pivot - 1; \
    } \
    else { \
      return pivot; \
    } \
  } \
  return left; \
} \
int nr_array_sorted_insert_index(TYPE a[]; TYPE v) { \
  return nr_array_sorted_insert_index(a, v, len(a)); \
}

DEFINE_NR_ARRAY_SORTED_INSERT_INDEX(int)
DEFINE_NR_ARRAY_SORTED_INSERT_INDEX(string)


/**
 * Returns the index of *v* in the sorted array *a*. Returns -1
 * if the elemnt does not appear in the array.
 *
 * @param a: The sorted array to search through.
 * @param v: The value to search for.
 * @param num: The number of elements from the beginning of the
 *    array to search through. If omitted, defaults to the actual
 *    size of the array.
 */
#define DEFINE_NR_ARRAY_SORTED_INDEXOF(TYPE) \
int nr_array_sorted_indexof(TYPE a[]; TYPE v; int num) { \
  int left = 0, right = num - 1; \
  while (left <= right) { \
    int pivot = (left + right) / 2; \
    if (a[pivot] < v) { \
      left = pivot + 1; \
    } \
    else if (a[pivot] > v) { \
      right = pivot - 1; \
    } \
    else { \
      return pivot; \
    } \
  } \
  return -1; \
}\
int nr_array_sorted_indexof(TYPE a[]; TYPE v) { \
  return nr_array_sorted_indexof(a, v, len(a)); \
} \

DEFINE_NR_ARRAY_SORTED_INDEXOF(int)
DEFINE_NR_ARRAY_SORTED_INDEXOF(string)


/**
 * Create an array with indices that, when applied on the same input array
 * to shuffle the elements, results in a sorted array.
 *
 * @param a: The array to sort implicitly.
 * @return: An array that serves as a translation map to reorder the array
 *    *a* so it becomes sorted.
 */
#define DEFINE_NR_ARRAY_QUICKSORT_INDICES(TYPE) \
void _nr_array_quicksort_indices(int indices[]; TYPE a[]; int left_, right_) { \
  int low[], high[]; \
  append(low, left_); \
  append(high, right_); \
  while (len(low) > 0) { \
    int left = pop(low); \
    int right = pop(high); \
    if (left >= right) continue; \
    TYPE pivot = a[indices[right]]; \
    int i = left - 1; \
    for (int j = left; j < right; ++j) { \
      if (a[indices[j]] < pivot) { \
        i++; \
        int temp = indices[i]; \
        indices[i] = indices[j]; \
        indices[j] = temp; \
      } \
    } \
    i++; \
    int temp = indices[i]; \
    indices[i] = indices[right]; \
    indices[right] = temp; \
    append(low, left); \
    append(high, i-1); \
    append(low, i+1); \
    append(high, right); \
  } \
} \
int[] nr_array_quicksort_indices(TYPE a[]) { \
  int indices[]; resize(indices, len(a)); \
  for (int i = 0; i < len(a); ++i) indices[i] = i; \
  _nr_array_quicksort_indices(indices, a, 0, len(a)-1); \
  return indices; \
}

DEFINE_NR_ARRAY_QUICKSORT_INDICES(int)
DEFINE_NR_ARRAY_QUICKSORT_INDICES(float)
DEFINE_NR_ARRAY_QUICKSORT_INDICES(string)
