+++
title = "Conversions"
+++

## Spherical to cartesian coordinates

The formula that you want to use depends on the target coordinate system
and the orientation you choose for the sphere. To get an earth-like
orientation with poles along the Y-axis in Houdini's right-handed coordinate
system:

```c
vector sphericalToCartesian(float lon, lat, rad) {
  return rad * set(
    -cos(lat) * cos(lon),
    sin(lat),
    cos(lat) * sin(lon)
  );
}
```

![](https://i.imgur.com/0sccqS6.png)

*Airport locations loaded from https://openflights.org/data.html*
