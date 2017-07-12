# Conversions

## Table of Contents

  * [Spherical to cartesian coordinates](#spherical-to-cartesian-coordinates)

## Spherical to cartesian coordinates

```c
vector sphericalToCartesian(float lat, lon, rad) {
  return rad * set(
    cos(lat) * cos(lon),
    cos(lat) * sin(lon),
    sin(lat)
  );
}
```
