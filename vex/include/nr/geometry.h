/* Copyright (c) 2018 Niklas Rosenstein
 *
 * last modified: 2018-05-12
 */

#include <assert.h>
#include <nr/array.h>


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
 *
 * @param geo: The geometry.
 * @param p: The point number to compute the local one ring area of.
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


/**
 * Returns an array of the points connected to the point *p*.
 * If the *sorted* argument is true, the returned array of points
 * represents the one-ring of the point in correct walking order.
 *
 * @param geometry: The geometry to search.
 * @param p: The point number.
 * @param sorted: Whether the returned array is sorted to obtain
 *    the proper one-ring point order.
 * @return: An array of point numbers.
 */
int[] nr_geometry_connected_points(int geo, ptnum) {
  int result[];
  int prims[] = pointprims(geo, ptnum);
  for (int i = 0; i < len(prims); ++i) {
    int points[] = primpoints(geo, prims[i]);
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
 * Calculates the cartesian coordinates from spherical coordinates.
 *
 * @param lon: Longitute in radians.
 * @param lat: Latitude in radians.
 * @param rad: The radius of the sphere.
 */
float nr_geometry_spherical_to_cartesian(float lon, lat, rad) {
  return rad * set(
    -cos(lat) * cos(lon),
    sin(lat),
    cos(lat) * sin(lon)
  );
}
