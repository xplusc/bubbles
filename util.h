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
 int util_Sign(int);
 
 /**
  * Return <x> bound by <lower> and <upper>.
  */
 double util_Clamp(double, double, double);
 
 /**
  * Return a random floating point number between <lower> and
  * <upper>.
  */
 double util_RandRange(double, double);
 
 #endif // UTIL_H
