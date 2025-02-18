/**
 * This file contains utility functions.
 */
 
 #ifndef UTIL_H
 #define UTIL_H
 
 /**
  * Return  1 if <x> is positive
  *         0 if <x> is zero
  *        -1 if <x> is negative
  */
 int util_sign(int);
 
 /**
  * Return <x> bound by <lower> and <upper>.
  */
 double util_clamp(double, double, double);
 
 #endif // UTIL_H
