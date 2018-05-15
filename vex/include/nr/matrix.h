/* Copyright (c) 2018 Niklas Rosenstein
 *
 * last modified: 2018-05-12
 */

#pragma once


/**
 * Represents an N by M matrix.
 */
struct nr_matrix {
  int rows = 0, cols = 0;
  float values[] = { };

  /**
   * Read the matrix value at position *i* and *j*. If the indices are
   * outside the matrices bounds, returns 0.
   */
  float at(int i, j) {
    return values[i * cols + j];
  }

  /**
   * Set the matrix value at position *i* and *j* to *v*.
   * If the indices are outside the matrices bounds, nothing happens.
   */
  void write(int i, j; float v) {
    if (i >= 0 && i < rows && j >= 0 && j < cols) {
      values[i * cols + j] = v;
    }
  }

  /**
   * Resets all values to 0.
   */
  void reset() {
    for (int i = 0; i < len(values); ++i) {
      values[i] = 0.0;
    }
  }

  /**
   * Resets the matrix to a N by M matrix and fills all values with 0.
   */
  void reset(int n, m) {
    rows = n;
    cols = m;
    resize(values, n * m);
    this->reset();
  }

  /**
   * Resets the matrix to a rectangular N by N identity matrix.
   */
  void loadident(int n) {
    rows = cols = n;
    resize(values, n*n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        values[i * n + j] = (i == j ? 1.0 : 0.0);
      }
    }
  }

  /**
   * Returns 1 if the matrix is empty (no columns and/or rows).
   */
  int empty() {
    return rows == 0 || cols == 0;
  }

  /**
   * Add this matrix with another matrix. The matrices must be of the
   * same size, otherwise an empty matrix will be returned.
   */
  nr_matrix add(nr_matrix b) {
    nr_matrix res;
    if (rows == b.rows && cols == b.cols) {
      res->reset(rows, cols);
      for (int i = 0; i < rows * cols; ++i) {
        res.values[i] = values[i] + b.values[i];
      }
    }
    else {
      res->reset(0, 0);
    }
    return res;
  }

  /**
   * Subtract this matrix with another matrix. The matrices must be of the
   * same size, otherwise an empty matrix will be returned.
   */
  nr_matrix sub(nr_matrix b) {
    nr_matrix res;
    if (rows == b.rows && cols == b.cols) {
      for (int i = 0; i < rows * cols; ++i) {
        res.values[i] = values[i] - b.values[i];
      }
    }
    else {
      res->reset(0, 0);
    }
    return res;
  }

  /**
   * Performs and (A x B) x (B x C) matrix multiplication. Returns a (A x C)
   * matrix. If B is inconsistent, an empty matrix will be returned instead.
   */
  nr_matrix mul(nr_matrix b) {
    nr_matrix result;
    if (cols == b.rows) {
      result->reset(rows, b.cols);
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < b.cols; ++j) {
          float sum = 0.0;
          for (int k = 0; k < cols; ++k) {
            sum += values[i * cols + k] * b.values[k * cols + j];
          }
          result.values[i * cols + j] = sum;
        }
      }
    }
    else {
      result->reset(0, 0);
    }
    return result;
  }

  /**
   * Return the transposed version of this matrix.
   */
  nr_matrix transpose() {
    nr_matrix res;
    res->reset(cols, rows);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        res.values[j * rows + i] = values[i * cols + j];
      }
    }
    return res;
  }

  /**
   * Converts the matrix to a string representation in row major order.
   */
  string tostring() {
    string result = sprintf("nr_matrix(rows=%d, cols=%d, values=[", rows, cols);
    for (int i = 0; i < rows; ++i) {
      string row = "[";
      for (int j = 0; j < cols; ++j) {
        row += sprintf((j == cols-1) ? "%f" : "%f, ", values[i * cols + j]);
      }
      result = concat(result, row, (i == rows-1) ? "]" : "], ");
    }
    return result + "])";
  }

}

/**
 * Square identity matrix constructor.
 */
nr_matrix nr_matrix(int n) {
  nr_matrix res;
  res->loadident(n);
  return res;
}

/**
 * Zero N by M matrix constructor.
 */
nr_matrix nr_matrix(int n, m) {
  nr_matrix res;
  res->reset(n, m);
  return res;
}
