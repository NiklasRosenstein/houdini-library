/* Copyright (c) 2018 Niklas Rosenstein
 *
 * last modified: 2018-05-12
 */

#include <nr/array.h>

/**
 * Returns an array of the points connected to the point *p*.
 *
 * @param geometry: The geometry to search.
 * @param p: The point number.
 * @return: An array of point numbers.
 */
int[] nr_geometry_connected_points(int geometry, ptnum) {
  int result[];
  int prims[] = pointprims(geoself(), ptnum);
  for (int i = 0; i < len(prims); ++i) {
    int points[] = primpoints(geoself(), prims[i]);
    int index = nr_array_indexof(points, ptnum);
    if (index >= 0 && len(points) >= 2) {
      nr_array_unique_append(result, points[(index-1)%len(points)]);
    }
    if (len(points) >= 3) {
      nr_array_unique_append(result, points[(index+1)%len(points)]);
    }
  }
  return result;
}
