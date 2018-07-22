/* Copyright (c) 2018 Niklas Rosenstein
 *
 * last modified: 2018-05-13
 */

#pragma once

#include <complex.h>


// Synonyms for the complex functions declared in <complex.h>
complex nr_complex(const float a, b) { return CMPLX(a, b); }
complex nr_complex_add(const complex a, b) { return cadd(a, b); }
complex nr_complex_sub(const complex a, b) { return csub(a, b); }
complex nr_complex_mult(const complex a, b) { return cmult(a, b); }
complex nr_complex_mult(const complex a; float b) { return complex(a.real * b, a.imag * b); }
complex nr_complex_mult(const complex a; float b, c) { return complex(a.real * b, a.imag * c); }
complex nr_complex_mult_real(const complex a; float b) { return cmultreal(a, b); }
complex nr_complex_mult_imag(const complex a; float b) { return cmultimag(a, b); }
complex nr_complex_div(const complex a, b) { return a * conj(b); }
complex nr_complex_conj(const complex a) { return conj(a); }
float nr_complex_abs(const complex a) { return cabs(a); }
complex nr_complex_exp(const complex a) { return cexp(a); }

/**
 * Calculates the argument of the complex number *c*.
 *
 * @param c: The complex number.
 * @return: The argument of the complex number.
 */
float nr_complex_arg(const complex c) {
  return atan2(c.imag, c.real);
}

/**
 * Calculate the complex exponentiation of two complex numbers. Based
 * on the formula described at MathWorld [1].
 *
 * [1]: http://mathworld.wolfram.com/ComplexExponentiation.html
 *
 * @param a: The base of the exponentiation.
 * @param b: The exponent for the exponentiation.
 * @return: The result of the exponentiation.
 */
complex nr_complex_pow(const complex a, b) {
  float a_squared_length = a.real * a.real + a.imag * a.imag;
  float a_arg = nr_complex_arg(a);
  float inner = b.real * a_arg + 0.5 * b.imag * log(a_squared_length);
  float scalar = pow(a_squared_length, b.real * 0.5) * exp(-b.imag * a_arg);
  return complex(scalar * cos(inner), scalar * sin(inner));
}

/**
 * Represents a bicomplex number.
 */
struct nr_bicomplex {
  complex w, z;
}

/**
 * Bicomplex number constructor.
 */
nr_bicomplex nr_bicomplex(const float a, b, c, d) {
  return nr_bicomplex(complex(a, b), complex(c, d));
}

/**
 * Calculate the conjugate of a bicomplex number.
 */
nr_bicomplex nr_bicomplex_conj(const nr_bicomplex c) {
  return nr_bicomplex(c.w, nr_complex_mult(c.z, -1));
}

/**
 * Add two bicomplex numbers.
 */
nr_bicomplex nr_bicomplex_add(const nr_bicomplex a, b) {
  return nr_bicomplex(nr_complex_add(a.w, b.w), nr_complex_add(a.z, b.z));
}

/**
 * Subtract two bicomplex numbers.
 */
nr_bicomplex nr_bicomplex_sub(const nr_bicomplex a, b) {
  return nr_bicomplex(nr_complex_sub(a.w, b.w), nr_complex_sub(a.z, b.z));
}

/**
 * Calculate the product of two bicomplex numbers.
 */
// @{
nr_bicomplex nr_bicomplex_mult(const complex u, v, w, z) {
  return nr_bicomplex(
    nr_complex_sub(nr_complex_mult(u, v), nr_complex_mult(v, z)),
    nr_complex_add(nr_complex_mult(u, z), nr_complex_mult(v, w)));
}

nr_bicomplex nr_bicomplex_mult(const nr_bicomplex a, b) {
  return nr_bicomplex_mult(a.w, a.z, b.w, b.z);
}
// @}

/**
 * Calculate the norm of a bicommplex number, resulting in
 * a complex number.
 */
nr_bicomplex nr_bicomplex_norm(const nr_bicomplex c) {
  return nr_bicomplex(nr_complex_add(
    nr_complex_mult(c.w, c.w), nr_complex_mult(c.z, c.z)), complex(0, 0));
}

/**
 * Returns the absolute value of a bicomplex number.
 */
float nr_bicomplex_abs(const nr_bicomplex c) {
  return cabs(nr_bicomplex_norm(c).w);
}
