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


/**
 * Calculates the area of the triangle composed of the specified
 * points *a*, *b* and *c*.
 */
float nr_geometry_triangle_area(vector a, b, c) {
  float A = length(a - b);
  float B = length(b - c);
  float C = length(c - a);
  float s = (A + B + C);
  return sqrt(s * (s - A) * (s - B) * (s - C));
}


/**
 * Calculates the local one ring area of the point *p*.
 */
float nr_geometry_local_one_ring_area(int geo, p) {
  float area = 0.0;
  foreach (int prim; pointprims(geo, p)) {
    int pts[] = primpoints(geo, prim);
    area += nr_geometry_triangle_area(
        point(geo, 'P', pts[0]),
        point(geo, 'P', pts[1]),
        point(geo, 'P', pts[2]));
  }
  return area;
}
