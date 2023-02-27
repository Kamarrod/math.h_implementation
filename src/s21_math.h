#ifndef S21_MATH_H
#define S21_MATH_H

#include <float.h>
#include <stdio.h>

#define s21_PI 3.14159265358979323846
#define s21_E 2.71828182845904523536
#define ull unsigned long long
#define ll long long
#define s21_eps 1e-6

#define M_PI12 (s21_PI / 12.)
#define M_PI6 (s21_PI / 6.)
#define M_PI2 (s21_PI / 2.)
#define SQRT3 ((double)1.732050807569)

#define s21_INFINITY 1.0 / 0.0
#define s21_NAN -0.0 / 0.0
#define ln0_1 -2.30258509299

long double s21_sin(double x);
long double s21_cos(double x);
long double s21_fabs(double x);
long double s21_tan(double x);
long double s21_fmod(double x, double y);
int s21_abs(int x);
long double s21_pow(double base, double exp);
long double s21_atan(double x);
long double s21_asin(double x);
long double s21_acos(double x);
long double s21_tan(double x);
long double s21_exp(double x);
long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_sqrt(double x);
long double s21_log(double x);

int s21_isPositiveZero(double number);
int s21_isNegativeZero(double number);
int s21_isNan(double number);
int s21_isFinite(double number);
int s21_isEven(double number);
int s21_isOdd(double number);
int s21_isInteger(double number);

#endif  // S21_MATH_H