/* Copyright (c) 2018 Niklas Rosenstein
 *
 * last modified: 2018-05-12
 */

/**
 * Calculates the angle between two vectors in radians.
 */
float nr_vector_angle(vector a, b) {
  return acos(dot(a, b) / (length(a) * length(b)));
}
