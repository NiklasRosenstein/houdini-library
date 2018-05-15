/* Copyright (c) 2018 Niklas Rosenstein
 *
 * last modified: 2018-05-13
 */

#pragma once


/**
 * Represents a sparse N by M matrix.
 */
struct nr_sparse_matrix {
  int rows = 0, cols = 0;
  int indices[];
  float values[];

  float _at(int cell_index) {
    int lin_index = nr_array_sorted_indexof(indices, cell_index);
    if (lin_index >= 0) {
      return values[lin_index];
    }
    return 0.0;
  }

  void _write(int cell_index; float v) {
    int lin_index = nr_array_sorted_insert_index(indices, cell_index);
    int have_value = (indices[lin_index] == cell_index);
    int is_zero = abs(v) <= 0.0;  // TODO: Epsilon?
    if (!have_value && !is_zero) {
      insert(indices, lin_index, cell_index);
      insert(values, lin_index, v);
    }
    else if (have_value) {
      if (is_zero) {
        // TODO: Heuristic: Don't pop the value until some number of pops
        //       should have happened and then completely rebuild the array
        //       instead of popping values (as it requires shifting).
        pop(indices, lin_index);
        pop(values, lin_index);
      }
      else {
        values[lin_index] = v;
      }
    }
  }

  /**
   * Read a value from the sparse matrix.
   */
  float at(int i, j) {
    if (i >= 0 && i < rows && j >= 0 && j < cols) {
      return this->_at(i * cols + j);
    }
    return 0.0;
  }

  /**
   * Write a value to the matrix. This function keeps the matrix in
   * a consistent state (sorted index table).
   */
  void write(int i, j; float v) {
    if (i >= 0 && i < rows && j >= 0 && j < cols) {
      this->_write(i * cols + j, v);
    }
  }

  /**
   * Resets all values to 0.
   */
  void reset() {
    resize(indices, 0);
    resize(values, 0);
  }

  /**
   * Resets the matrix to a sparse N x M matrix.
   */
  void reset(int n, m) {
    rows = n;
    cols = m;
    this->reset();
  }

  /**
   * Loads the sparse identity matrix of size N x N.
   */
  void loadident(int n) {
    rows = cols = n;
    resize(indices, n);
    resize(values, n);
    for (int i = 0; i < n; ++i) {
      indices[i] = i * cols + i;
      values[i] = 1.0;
    }
  }

  /**
   * Returns 1 if the matrix is empty (has no colums and/or rows).
   */
  int empty() {
    return rows == 0 || cols == 0;
  }

  /**
   * Add this matrix with another matrix.
   */
  nr_sparse_matrix add(nr_sparse_matrix b) {
    nr_sparse_matrix res;
    if (rows == b.rows && cols == b.cols) {
      res = this;
      int sorted_cells = len(res.indices);
      for (int i = 0; i < len(b.indices); ++i) {
        int lin_idx = nr_array_sorted_indexof(res.indices, b.indices[i], sorted_cells);
        if (lin_idx >= 0) {
          res.values[lin_idx] += b.values[i];
        }
        else {
          append(res.indices, b.indices[i]);
          append(res.values, b.values[i]);
        }
      }
      int i[] = nr_array_quicksort_indices(res.indices);
      res.indices = reorder(res.indices, i);
      res.values = reorder(res.values, i);
    }
    else {
      res->reset(0, 0);
    }
    return res;
  }


  /**
   * Subtract this matrix with another matrix.
   */
  nr_sparse_matrix sub(nr_sparse_matrix b) {
    nr_sparse_matrix res;
    if (rows == b.rows && cols == b.cols) {
      res = this;
      int sorted_cells = len(res.indices);
      for (int i = 0; i < len(b.indices); ++i) {
        int lin_idx = nr_array_sorted_indexof(res.indices, b.indices[i], sorted_cells);
        if (lin_idx >= 0) {
          res.values[lin_idx] -= b.values[i];
        }
        else {
          append(res.indices, b.indices[i]);
          append(res.values, b.values[i]);
        }
      }
      int i[] = nr_array_quicksort_indices(res.indices);
      res.indices = reorder(res.indices, i);
      res.values = reorder(res.values, i);
    }
    else {
      res->reset(0, 0);
    }
    return res;
  }

}

/**
 * Returns the sparse identity matrix of size N x N.
 */
nr_sparse_matrix nr_sparse_matrix(int n) {
  nr_sparse_matrix res;
  res->loadident(n);
  return res;
}

/**
 * Returns the sparse zero matrix of size N x M.
 */
nr_sparse_matrix nr_sparse_matrix(int n, m) {
  nr_sparse_matrix res;
  res->reset(n, m);
  return res;
}
