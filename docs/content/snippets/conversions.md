+++
title = "Conversions"
+++

## Distance independent particle size

Calculate the size of a particle independent from its distance so that it
always appears in the size of a particle at distance = 1.


```c
// Calculates the angle of the camera given its focal length and diameter
// of the apperture.
float cam_angle(float f, D) {
    return 2 * atan(D / (f * 2));
}

// Calculates the logarithm of any base using the Change-of-base formula.
float log(float base, val) {
    return log(val) / log(base);
}

// Input parameters, replace per your needs.
float focal_length = 50;
float apperture = 41.04;
vector camera_pos = {0, 0, 0};
float size = 0.005;  // Particle size at distance 1

float phi = cam_angle(focal_length, apperture);
float distance = length(@P - camera_pos);
@pscale = sin(phi/2) * distance * size;
```

<p align="center"><img src="../../static/pov-distance-independent-particle-size.png"/></p>
