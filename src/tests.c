#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_math.h"

START_TEST(fabsTest) {
  for (double number = -10; number <= 10; number += 0.1)
    ck_assert_double_eq_tol(s21_fabs(number), fabs(number), 1e-6);
  ck_assert_double_eq_tol(s21_fabs(-1e8), fabs(-1e8), 1e-6);
  ck_assert_double_eq_tol(s21_fabs(1e8), fabs(1e8), 1e-6);
  ck_assert_double_eq_tol(s21_fabs(1.23), fabs(1.23), 1e-6);

  ck_assert_double_eq(s21_fabs(s21_INFINITY), fabs(s21_INFINITY));
  ck_assert_double_eq(s21_fabs(-s21_INFINITY), fabs(-s21_INFINITY));
  ck_assert_double_nan(s21_fabs(s21_NAN));
  ck_assert_double_nan(s21_fabs(-s21_NAN));
  ck_assert_double_eq(s21_fabs(DBL_MAX), fabs(DBL_MAX));
  ck_assert_double_eq(s21_fabs(DBL_MIN), fabs(DBL_MIN));
}
END_TEST

START_TEST(absTest) {
  for (int i = -100; i <= 100; ++i) ck_assert_int_eq(s21_abs(i), abs(i));

  ck_assert_int_eq(s21_abs(-1), 1);
  ck_assert_int_eq(s21_abs(1), 1);
  ck_assert_int_eq(s21_abs(0), 0);
  ck_assert_int_eq(s21_abs(INT_MAX), abs(INT_MAX));
  ck_assert_int_eq(s21_abs(INT_MIN), abs(INT_MIN));
  ck_assert_int_eq(s21_abs((int)INFINITY), abs((int)INFINITY));
  ck_assert_int_eq(s21_abs((int)-INFINITY), abs((int)-INFINITY));
  ck_assert_int_eq(s21_abs((int)-NAN), abs((int)-NAN));
  ck_assert_int_eq(s21_abs((int)NAN), abs((int)NAN));
}
END_TEST

START_TEST(fmodTest) {
  for (double x = -5.5; x < 5.5; x += 0.3)
    for (double y = -6.6; y < 6.6; y += 0.3)
      ck_assert_double_eq_tol(s21_fmod(x, y), fmod(x, y), 1e-6);

  ck_assert_double_eq_tol(s21_fmod(-13.8, -1.5), fmod(-13.8, -1.5), 1e-6);
  ck_assert_double_eq_tol(s21_fmod(-13.8, 1.5), fmod(-13.8, 1.5), 1e-6);
  ck_assert_double_eq_tol(s21_fmod(13.8, -1.5), fmod(13.8, -1.5), 1e-6);
  ck_assert_double_eq_tol(s21_fmod(13.8, 1.5), fmod(13.8, 1.5), 1e-6);
  ck_assert_double_eq_tol(s21_fmod(13.6, 2.72), fmod(13.6, 2.72), 1e-6);
  ck_assert_double_eq_tol(s21_fmod(-13.6, 2.72), fmod(-13.6, 2.72), 1e-6);
  ck_assert_double_eq_tol(s21_fmod(-13.6, -2.72), fmod(-13.6, -2.72), 1e-6);
  ck_assert_double_eq_tol(s21_fmod(13.6, -2.72), fmod(13.6, -2.72), 1e-6);
  ck_assert_double_eq_tol(s21_fmod(1e10, 15), fmod(1e10, 15), 1e-6);

  ck_assert_double_eq_tol(s21_fmod(0, 3), fmod(0, 3), 1e-6);
  ck_assert_double_eq_tol(s21_fmod(0, -3), fmod(0, -3), 1e-6);
  ck_assert(isnan(s21_fmod(s21_INFINITY, 2)));
  ck_assert(isnan(s21_fmod(-s21_INFINITY, 2)));
  ck_assert(isnan(s21_fmod(s21_INFINITY, 0)));
  ck_assert(isnan(s21_fmod(-s21_INFINITY, 0)));
  ck_assert(isnan(s21_fmod(3, 0)));
  ck_assert(isnan(s21_fmod(-3, 0)));
  ck_assert(isnan(s21_fmod(s21_INFINITY, -s21_INFINITY)));
  ck_assert(isnan(s21_fmod(-s21_INFINITY, s21_INFINITY)));
  ck_assert_double_eq_tol(s21_fmod(3, s21_INFINITY), fmod(3, s21_INFINITY),
                          1e-6);
  ck_assert_double_eq_tol(s21_fmod(-3, s21_INFINITY), fmod(-3, s21_INFINITY),
                          1e-6);
  ck_assert(isnan(s21_fmod(s21_NAN, 3)));
  ck_assert(isnan(s21_fmod(s21_NAN, s21_NAN)));
  ck_assert(isnan(s21_fmod(3, s21_NAN)));
  ck_assert(isnan(s21_fmod(s21_INFINITY, s21_NAN)));
  ck_assert(isnan(s21_fmod(-s21_INFINITY, s21_NAN)));
  ck_assert(isnan(s21_fmod(s21_NAN, s21_INFINITY)));
  ck_assert(isnan(s21_fmod(s21_NAN, -s21_INFINITY)));
}
END_TEST

START_TEST(sinTest) {
  for (double angle = -10 * s21_PI; angle <= 10 * s21_PI; angle += s21_PI / 12)
    ck_assert_double_eq_tol(s21_sin(angle), sin(angle), 1e-6);

  ck_assert_double_eq_tol(s21_sin(1e9), sin(1e9), 1e-6);
  ck_assert_double_eq_tol(s21_sin(-1e9), sin(-1e9), 1e-6);
  ck_assert_double_eq_tol(s21_sin(35 * s21_PI / 3), sin(35 * s21_PI / 3), 1e-6);
  ck_assert(isnan(s21_sin(s21_NAN)));
  ck_assert(isnan(s21_sin(s21_INFINITY)));
  ck_assert(isnan(s21_sin(-s21_INFINITY)));
}
END_TEST

START_TEST(cosTest) {
  for (double angle = -10 * s21_PI; angle <= 10 * s21_PI; angle += s21_PI / 12)
    ck_assert_double_eq_tol(s21_cos(angle), cos(angle), 1e-6);

  ck_assert_double_eq_tol(s21_cos(1e9), cos(1e9), 1e-6);
  ck_assert_double_eq_tol(s21_cos(-1e9), cos(-1e9), 1e-6);
  ck_assert_double_eq_tol(s21_cos(35 * s21_PI / 3), cos(35 * s21_PI / 3), 1e-6);
  ck_assert(isnan(s21_cos(s21_NAN)));
  ck_assert(isnan(s21_cos(s21_INFINITY)));
  ck_assert(isnan(s21_cos(-s21_INFINITY)));
}
END_TEST

START_TEST(tanTest) {
  for (double angle = -10 * s21_PI + s21_PI / 8; angle <= 10 * s21_PI;
       angle += s21_PI / 12)
    ck_assert_ldouble_eq_tol(s21_tan(angle), tan(angle), 1e-6);

  ck_assert_ldouble_eq_tol(s21_tan(1e9), tan(1e9), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-1e9), tan(-1e9), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(35 * s21_PI / 3), tan(35 * s21_PI / 3),
                           1e-6);

  ck_assert(isnan(s21_tan(s21_NAN)));
  ck_assert(isnan(s21_tan(s21_INFINITY)));
  ck_assert(isnan(s21_tan(-s21_INFINITY)));
}
END_TEST

START_TEST(powTest) {
  for (double number = -3; number <= 3; number += 0.3) {
    for (double power = -3.5; power <= 3.5; power += 0.3) {
      long double s21_result = s21_pow(number, power);
      double result = pow(number, power);
      if (isnan(result))
        ck_assert_ldouble_nan(s21_result);
      else
        ck_assert_double_eq_tol(s21_result, result, 1e-6);
    }
  }

  ck_assert_double_eq_tol(s21_pow(1, -2), pow(1, -2), 1e-6);

  ck_assert_double_infinite(s21_pow(0.0, -3));
  ck_assert_double_infinite(s21_pow(-0.0, -3));
  ck_assert_double_infinite(s21_pow(0.0, -4));
  ck_assert_double_infinite(s21_pow(-0.0, -4));
  ck_assert_double_infinite(s21_pow(0.0, -4.6));
  ck_assert_double_infinite(s21_pow(-0.0, -4.6));
  ck_assert_double_eq_tol(s21_pow(0.0, s21_INFINITY), pow(0.0, s21_INFINITY),
                          1e-6);
  ck_assert_double_eq_tol(s21_pow(-0.0, s21_INFINITY), pow(-0.0, s21_INFINITY),
                          1e-6);
  ck_assert_double_eq_tol(s21_pow(0.0, 3), pow(0.0, 3), 1e-6);
  ck_assert_double_eq_tol(s21_pow(-0.0, 3), pow(-0.0, 3), 1e-6);
  ck_assert_double_eq_tol(s21_pow(0.0, 2.5), pow(0.0, 2.5), 1e-6);
  ck_assert_double_eq_tol(s21_pow(-0.0, 4), pow(-0.0, 4), 1e-6);
  ck_assert_double_eq_tol(s21_pow(-1, s21_INFINITY), pow(-1, s21_INFINITY),
                          1e-6);
  ck_assert_double_eq_tol(s21_pow(-1, -s21_INFINITY), pow(-1, -s21_INFINITY),
                          1e-6);
  ck_assert_double_eq_tol(s21_pow(1, s21_NAN), pow(1, s21_NAN), 1e-6);
  ck_assert_double_eq_tol(s21_pow(1, 1), pow(1, 1), 1e-6);
  ck_assert_double_eq_tol(s21_pow(1, -1), pow(1, -1), 1e-6);
  ck_assert_double_eq_tol(s21_pow(1, 1.5), pow(1, 1.5), 1e-6);
  ck_assert_double_eq_tol(s21_pow(1, -1.5), pow(1, -1.5), 1e-6);
  ck_assert_double_eq_tol(s21_pow(1, s21_INFINITY), pow(1, s21_INFINITY), 1e-6);
  ck_assert_double_eq_tol(s21_pow(1, -s21_INFINITY), pow(1, -s21_INFINITY),
                          1e-6);
  ck_assert_double_eq_tol(s21_pow(1, 0.7), pow(1, 0.7), 1e-6);
  ck_assert_double_eq_tol(s21_pow(1, -0.7), pow(1, -0.7), 1e-6);
  ck_assert_double_eq_tol(s21_pow(s21_NAN, 0.0), pow(s21_NAN, 0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(1, 0.0), pow(1, 0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(-1, 0.0), pow(-1, 0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(1.5, 0.0), pow(1.5, 0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(-1.5, 0.0), pow(-1.5, 0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(s21_INFINITY, 0.0), pow(s21_INFINITY, 0.0),
                          1e-6);
  ck_assert_double_eq_tol(s21_pow(-s21_INFINITY, 0.0), pow(-s21_INFINITY, 0.0),
                          1e-6);
  ck_assert_double_eq_tol(s21_pow(0.7, 0.0), pow(0.7, 0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(-0.7, 0.0), pow(-0.7, 0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(s21_NAN, -0.0), pow(s21_NAN, -0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(1, -0.0), pow(1, -0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(-1, -0.0), pow(-1, -0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(1.5, -0.0), pow(1.5, -0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(-1.5, -0.0), pow(-1.5, -0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(s21_INFINITY, -0.0), pow(s21_INFINITY, -0.0),
                          1e-6);
  ck_assert_double_eq_tol(s21_pow(-s21_INFINITY, -0.0),
                          pow(-s21_INFINITY, -0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(0.7, -0.0), pow(0.7, -0.0), 1e-6);
  ck_assert_double_eq_tol(s21_pow(-0.7, -0.0), pow(-0.7, -0.0), 1e-6);
  ck_assert(isnan(s21_pow(-3, 1.5)));
  ck_assert(isnan(s21_pow(-3.5, 1.5)));
  ck_assert(isnan(s21_pow(-3, -1.5)));
  ck_assert(isnan(s21_pow(-3.5, -1.5)));
  ck_assert_double_infinite(s21_pow(-0.7, -s21_INFINITY));
  ck_assert_double_infinite(s21_pow(0.7, -s21_INFINITY));
  ck_assert_double_eq_tol(s21_pow(13.9, -s21_INFINITY),
                          pow(13.9, -s21_INFINITY), 1e-6);
  ck_assert_double_eq_tol(s21_pow(-13.9, -s21_INFINITY),
                          pow(-13.9, -s21_INFINITY), 1e-6);
  ck_assert_double_eq_tol(s21_pow(0.8, s21_INFINITY), pow(0.8, s21_INFINITY),
                          1e-6);
  ck_assert_double_eq_tol(s21_pow(-0.8, s21_INFINITY), pow(-0.8, s21_INFINITY),
                          1e-6);
  ck_assert_double_infinite(s21_pow(35.6, s21_INFINITY));
  ck_assert_double_infinite(s21_pow(-35.6, s21_INFINITY));
  ck_assert_double_eq_tol(s21_pow(-s21_INFINITY, -19), pow(-s21_INFINITY, -19),
                          1e-6);
  ck_assert_double_eq_tol(s21_pow(-s21_INFINITY, -340.009),
                          pow(-s21_INFINITY, -340.009), 1e-6);
  ck_assert_double_eq_tol(s21_pow(-s21_INFINITY, -340),
                          pow(-s21_INFINITY, -340), 1e-6);
  ck_assert_double_infinite(s21_pow(-s21_INFINITY, 701));
  ck_assert_double_infinite(s21_pow(-s21_INFINITY, 345.01));
  ck_assert_double_infinite(s21_pow(-s21_INFINITY, 10000));
  ck_assert_double_eq_tol(s21_pow(s21_INFINITY, -13.5),
                          pow(s21_INFINITY, -13.5), 1e-6);
  ck_assert_double_eq_tol(s21_pow(s21_INFINITY, -0.005),
                          pow(s21_INFINITY, -0.005), 1e-6);
  ck_assert_double_eq_tol(s21_pow(s21_INFINITY, -10), pow(s21_INFINITY, -10),
                          1e-6);
  ck_assert_double_eq_tol(s21_pow(s21_INFINITY, -s21_INFINITY),
                          pow(s21_INFINITY, -s21_INFINITY), 1e-6);
  ck_assert_double_infinite(s21_pow(s21_INFINITY, 13.5));
  ck_assert_double_infinite(s21_pow(s21_INFINITY, 0.005));
  ck_assert_double_infinite(s21_pow(s21_INFINITY, 10));
  ck_assert_double_infinite(s21_pow(s21_INFINITY, s21_INFINITY));
}
END_TEST

////////////////////////////////////////  EXP START
////////////////////////////////////////  EXP START
////////////////////////////////////////  EXP START

START_TEST(exp_test_1) {
  for (double k = -5; k < 5; k += 0.001) {
    ck_assert_ldouble_eq_tol(s21_exp(k), exp(k), 1e-6);
  }
}
END_TEST

START_TEST(exp_test_2) {
  for (double k = -15; k < 15; k += 0.05)
    ck_assert_ldouble_eq_tol(s21_exp(k), exp(k), 1e-6);
}
END_TEST

START_TEST(exp_test_3) {
  for (int k = 0; k <= 24; k++)
    ck_assert_ldouble_eq_tol(s21_exp(k), exp(k), 1e-6);
}
END_TEST

START_TEST(exp_test_4) {
  char str1[100];
  char str2[100];
  // предполгаем что в 16 символах нет точки
  for (int k = 25; k <= 200; k++) {
    int zi = 16;
    sprintf(str1, "%LF", s21_exp(k));
    sprintf(str2, "%LF", expl(k));
    for (int i = 0; i < 17; i++)
      if (str2[i] == '.') {
        zi++;
        break;
      }  //если есть точка то для нужной точности ее нужно учесть
    str1[zi] = '\0';
    str2[zi] = '\0';
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(exp_test_5) {
  for (int k = -1000; k <= 0; k++)
    ck_assert_ldouble_eq_tol(s21_exp(k), exp(k), s21_eps);
}
END_TEST

START_TEST(exp_test_6) { ck_assert_double_nan(s21_exp(s21_NAN)); }
END_TEST

START_TEST(exp_test_7) { ck_assert_double_infinite(s21_exp(s21_INFINITY)); }
END_TEST

START_TEST(exp_test_8) {
  ck_assert_ldouble_eq_tol(expl(0), s21_exp(0), s21_eps);
  ck_assert_ldouble_eq_tol(expl(1), s21_exp(1), s21_eps);
}
END_TEST

START_TEST(exp_test_9) {
  ck_assert_ldouble_eq_tol(expl(-s21_INFINITY), s21_exp(-s21_INFINITY),
                           s21_eps);
}
END_TEST

START_TEST(exp_test_10) {
  ck_assert_double_infinite(expl(LDBL_MAX));
  ck_assert_double_infinite(s21_exp(LDBL_MAX));
}
END_TEST

START_TEST(exp_test_11) {
  ck_assert_ldouble_eq_tol(expl(LDBL_MIN), s21_exp(LDBL_MIN), s21_eps);
}
END_TEST

///////////////////////////////////////////END EXP
///////////////////////////////////////////END EXP
///////////////////////////////////////////END EXP

////////////////////////////////////////  ASIN START
////////////////////////////////////////  ASIN START
////////////////////////////////////////  ASIN START

START_TEST(asin_test_1) {
  for (double k = -1; k <= 1; k += 0.01)
    ck_assert_ldouble_eq_tol(s21_asin(k), asin(k), s21_eps);
}
END_TEST

START_TEST(asin_test_2) {
  for (double k = -1.0000001; k >= -100; k -= 1.01) {
    ck_assert_ldouble_nan(s21_asin(k));
  }
}
END_TEST

START_TEST(asin_test_3) {
  for (double k = 1.0000001; k <= 100; k += 0.01) {
    ck_assert_ldouble_nan(s21_asin(k));
  }
}
END_TEST

START_TEST(asin_test_4) {
  ck_assert_ldouble_nan(asin(-s21_INFINITY));
  ck_assert_ldouble_nan(s21_asin(-s21_INFINITY));

  ck_assert_ldouble_nan(asin(s21_INFINITY));
  ck_assert_ldouble_nan(s21_asin(s21_INFINITY));
}
END_TEST

START_TEST(asin_test_5) {
  ck_assert_ldouble_nan(asinl(LDBL_MAX));
  ck_assert_ldouble_nan(s21_asin(LDBL_MAX));

  ck_assert_ldouble_nan(asinl(LDBL_MAX));
  ck_assert_ldouble_nan(s21_asin(LDBL_MAX));
}
END_TEST

START_TEST(asin_test_6) {
  ck_assert_ldouble_nan(asin(s21_NAN));
  ck_assert_ldouble_nan(s21_asin(s21_NAN));

  ck_assert_ldouble_nan(asin(-s21_NAN));
  ck_assert_ldouble_nan(s21_asin(-s21_NAN));
}
END_TEST
////////////////////////////////////////  ASIN END
////////////////////////////////////////  ASIN END
////////////////////////////////////////  ASIN END

////////////////////////////////////////  ACOS START
////////////////////////////////////////  ACOS START
////////////////////////////////////////  ACOS START
START_TEST(acos_test_1) {
  for (double k = -1; k <= 1; k += 0.01)
    ck_assert_ldouble_eq_tol(s21_acos(k), acos(k), s21_eps);
}
END_TEST

START_TEST(acos_test_2) {
  for (double k = -1.0000001; k >= -10; k -= 1) {
    ck_assert_ldouble_nan(s21_acos(k));
  }
}
END_TEST

START_TEST(acos_test_3) {
  for (double k = 1.0000001; k <= 100; k += 0.01) {
    ck_assert_ldouble_nan(s21_acos(k));
  }
}
END_TEST

START_TEST(acos_test_4) {
  ck_assert_ldouble_nan(acos(-s21_INFINITY));
  ck_assert_ldouble_nan(s21_acos(-s21_INFINITY));

  ck_assert_ldouble_nan(acos(s21_INFINITY));
  ck_assert_ldouble_nan(s21_acos(s21_INFINITY));
}
END_TEST

START_TEST(acos_test_5) {
  ck_assert_ldouble_nan(acosl(LDBL_MAX));
  ck_assert_ldouble_nan(s21_acos(LDBL_MAX));

  ck_assert_ldouble_nan(acosl(LDBL_MAX));
  ck_assert_ldouble_nan(s21_acos(LDBL_MAX));
}
END_TEST

START_TEST(acos_test_6) {
  ck_assert_ldouble_nan(acos(s21_NAN));
  ck_assert_ldouble_nan(s21_acos(s21_NAN));

  ck_assert_ldouble_nan(acos(-s21_NAN));
  ck_assert_ldouble_nan(s21_acos(-s21_NAN));
}
END_TEST
////////////////////////////////////////  ACOS END
////////////////////////////////////////  ACOS END
////////////////////////////////////////  ACOS END

///////////////////ATAN START
///////////////////ATAN START
///////////////////ATAN START

START_TEST(atan_test_1) {
  for (double k = -15000000; k <= 15000000; k += 1000)
    ck_assert_ldouble_eq_tol(s21_atan(k), atan(k), s21_eps);
  ck_assert_ldouble_eq_tol(s21_atan(5.123456789123), atan(5.123456789123),
                           s21_eps);
  ck_assert_ldouble_eq_tol(s21_atan(0.00000004564897), atan(0.00000004564897),
                           s21_eps);
  ck_assert_ldouble_eq_tol(s21_atan(170000000000000.1), atan(170000000000000.1),
                           s21_eps);
  ck_assert_ldouble_eq_tol(s21_atan(0), atan(0), s21_eps);
  ck_assert_ldouble_eq_tol(s21_atan(-0), atan(-0), s21_eps);
  ck_assert_ldouble_eq_tol(atan(s21_PI), s21_atan(s21_PI), s21_eps);
  ck_assert_ldouble_eq_tol(atan(s21_E), s21_atan(s21_E), s21_eps);
}
END_TEST

START_TEST(atan_test_2) {
  ck_assert_ldouble_nan(atan(s21_NAN));
  ck_assert_ldouble_nan(s21_atan(s21_NAN));

  ck_assert_ldouble_nan(atan(-s21_NAN));
  ck_assert_ldouble_nan(s21_atan(-s21_NAN));
}
END_TEST

START_TEST(atan_test_3) {
  ck_assert_ldouble_eq_tol(s21_atan(-1), atan(-1), s21_eps);
  ck_assert_ldouble_eq_tol(s21_atan(1), atan(1), s21_eps);
}
END_TEST

START_TEST(atan_test_4) {
  ck_assert_ldouble_eq_tol(s21_atan(-s21_INFINITY), atan(-s21_INFINITY),
                           s21_eps);
  ck_assert_ldouble_eq_tol(s21_atan(s21_INFINITY), atan(s21_INFINITY), s21_eps);
}
END_TEST

START_TEST(atan_test_5) {
  ck_assert_ldouble_eq_tol(s21_atan(LDBL_MAX), atanl(LDBL_MAX), s21_eps);
  ck_assert_ldouble_eq_tol(s21_atan(LDBL_MIN), atanl(LDBL_MIN), s21_eps);
}
END_TEST

START_TEST(sqrt_test_1) {
  for (double k = 0; k < 30; k += 3) {
    double a = s21_sqrt(k);
    double b = sqrt(k);
    ck_assert_double_eq_tol(a, b, 1e-7);
  }
}
END_TEST

START_TEST(sqrt_test_2) {
  for (double k = 0; k < 1.1; k += 0.01) {
    double a = s21_sqrt(k);
    double b = sqrt(k);
    ck_assert_double_eq_tol(a, b, 1e-7);
  }
}
END_TEST

START_TEST(sqrt_test_3) {
  for (double k = 0; k < 20000; k += 3000.098) {
    double a = s21_sqrt(k);
    double b = sqrt(k);
    ck_assert_double_eq_tol(a, b, 1e-7);
  }
}
END_TEST

START_TEST(sqrt_test_4) {
  ck_assert_ldouble_eq(s21_sqrt(LDBL_MAX), sqrt(LDBL_MAX));
  ck_assert_ldouble_eq_tol(s21_sqrt(LDBL_MIN), sqrt(LDBL_MIN), 1e-7);
  ck_assert_ldouble_nan(s21_sqrt(-s21_INFINITY));
  ck_assert_ldouble_eq(s21_sqrt(s21_INFINITY), sqrt(s21_INFINITY));
  ck_assert_ldouble_nan(s21_sqrt(-s21_NAN));
  ck_assert_ldouble_nan(s21_sqrt(s21_NAN));
  ck_assert_ldouble_eq_tol(s21_sqrt(0.5), sqrt(0.5), 1e-7);
  ck_assert_ldouble_nan(s21_sqrt(-0.7));
  ck_assert_ldouble_eq_tol(s21_sqrt(1), sqrt(1), 1e-7);
  ck_assert_ldouble_eq_tol(s21_sqrt(1.1), sqrt(1.1), 1e-7);
  ck_assert_ldouble_eq_tol(s21_sqrt(0), sqrt(0), 1e-7);
  ck_assert_ldouble_eq_tol(s21_sqrt(-0), sqrt(-0), 1e-7);
  ck_assert_double_nan(s21_sqrt(-5));
  ck_assert_ldouble_eq_tol(s21_sqrt(7.12312309845), sqrt(7.12312309845), 1e-7);
  ck_assert_ldouble_eq_tol(s21_sqrt(0.00000004564897), sqrt(0.00000004564897),
                           1e-7);
  ck_assert_ldouble_eq_tol(s21_sqrt(0.0000000000007), sqrt(0.0000000000007),
                           1e-7);
  ck_assert_ldouble_eq_tol(s21_sqrt(190000000000000.1132),
                           sqrt(190000000000000.1123), 1e-8);
  ck_assert_double_eq_tol(s21_sqrt(1000), sqrt(1000), 1e-7);
  ck_assert_double_eq_tol(s21_sqrt(100012321392), sqrt(100012321392), 1e-7);
}
END_TEST

START_TEST(floor_test_1) {
  ck_assert_double_eq(floor(INFINITY), s21_floor(s21_INFINITY));
  ck_assert_double_eq(floor(-INFINITY), s21_floor(-s21_INFINITY));
  ck_assert_double_nan(s21_floor(s21_NAN));
  ck_assert_double_nan(s21_floor(-s21_NAN));
  ck_assert_double_eq(floor(-7.13141), s21_floor(-7.13141));
  ck_assert_double_eq(floor(-95.1), s21_floor(-95.1));
  ck_assert_double_eq(floor(101.91), s21_floor(101.91));
  ck_assert_double_eq(floor(10009.00123), s21_floor(10009.00123));
  ck_assert_double_eq(floor(-10009.555), s21_floor(-10009.555));
  ck_assert_double_eq(floor(-0.10009), s21_floor(-0.10009));
  ck_assert_double_eq(floor(-1e-23), s21_floor(-1e-23));
  ck_assert_double_eq(floor(190000000000000.1132),
                      s21_floor(190000000000000.1132));
}
END_TEST

START_TEST(floor_test_2) {
  ck_assert_ldouble_eq(s21_floor(0), floor(0));
  ck_assert_ldouble_eq(s21_floor(-0), floor(-0));
  ck_assert_ldouble_eq(s21_floor(-0.000001), floor(-0.000001));
  ck_assert_ldouble_eq(s21_floor(-89999990.23455), floor(-89999990.23455));
  ck_assert_ldouble_eq(s21_floor(-0.019), floor(-0.19));
  ck_assert_ldouble_eq(s21_floor(0.75), floor(0.75));
  ck_assert_ldouble_eq(s21_floor(-1.0000000000000000000093),
                       floor(-1.0000000000000000000093));
}
END_TEST

START_TEST(ceil_test_1) {
  ck_assert_double_eq(ceil(INFINITY), s21_ceil(s21_INFINITY));
  ck_assert_double_eq(ceil(-INFINITY), s21_ceil(-s21_INFINITY));
  ck_assert_double_nan(s21_ceil(s21_NAN));
  ck_assert_double_nan(s21_ceil(-s21_NAN));
  ck_assert_double_eq(ceil(-7.13141), s21_ceil(-7.13141));
  ck_assert_double_eq(ceil(-95.1), s21_ceil(-95.1));
  ck_assert_double_eq(ceil(101.91), s21_ceil(101.91));
  ck_assert_double_eq(ceil(10009.00123), s21_ceil(10009.00123));
  ck_assert_double_eq(ceil(-10009.555), s21_ceil(-10009.555));
  ck_assert_double_eq(ceil(-0.10009), s21_ceil(-0.10009));
  ck_assert_double_eq(ceil(-1e-23), s21_ceil(-1e-23));
  ck_assert_double_eq(ceil(190000000000000.1132),
                      s21_ceil(190000000000000.1132));
}
END_TEST

START_TEST(ceil_test_2) {
  ck_assert_ldouble_eq(s21_ceil(0), ceil(0));
  ck_assert_ldouble_eq(s21_ceil(-0), ceil(-0));
  ck_assert_ldouble_eq(s21_ceil(-0.000001), ceil(-0.000001));
  ck_assert_ldouble_eq(s21_ceil(-89999990.23455), ceil(-89999990.23455));
  ck_assert_ldouble_eq(s21_ceil(-0.019), ceil(-0.19));
  ck_assert_ldouble_eq(s21_ceil(0.75), ceil(0.75));
  ck_assert_ldouble_eq(s21_ceil(-1.0000000000000000000093),
                       ceil(-1.0000000000000000000093));
}
END_TEST

START_TEST(log_test_1) {
  for (double k = 1; k < 100; k += 11.223) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, 1e-7);
  }
}
END_TEST

START_TEST(log_test_2) {
  for (double k = 0.1; k < 4; k += 0.3) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, 1e-7);
  }
}
END_TEST

START_TEST(log_test_3) {
  for (double k = 0.1; k < 10000; k += 100) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, 1e-7);
  }
}
END_TEST

START_TEST(log_test_4) {
  for (double k = 0.000001; k < 1; k *= 11) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, 1e-7);
  }
}
END_TEST

START_TEST(log_test_5) {
  ck_assert_ldouble_eq(s21_log(LDBL_MAX), log(LDBL_MAX));
  ck_assert_ldouble_eq(s21_log(LDBL_MIN), log(LDBL_MIN));
  ck_assert_double_nan(s21_log(s21_NAN));
  ck_assert_double_eq_tol(log(0.001), s21_log(0.001), 1e-7);
  ck_assert_double_nan(s21_log(-6));
  ck_assert_double_eq(log(s21_INFINITY), s21_log(s21_INFINITY));
  ck_assert_double_nan(s21_log(-s21_INFINITY));
  ck_assert_double_eq(log(1), s21_log(1));
  ck_assert_double_eq_tol(log(exp(1)), s21_log(exp(1)), 1e-7);
  ck_assert_double_eq_tol(log(2), s21_log(2), 1e-7);
}
END_TEST

Suite *suite() {
  Suite *s = suite_create("tests");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, fabsTest);
  tcase_add_test(tc, absTest);
  tcase_add_test(tc, fmodTest);
  tcase_add_test(tc, sinTest);
  tcase_add_test(tc, cosTest);
  tcase_add_test(tc, tanTest);
  tcase_add_test(tc, powTest);

  tcase_add_test(tc, asin_test_1);
  tcase_add_test(tc, asin_test_2);
  tcase_add_test(tc, asin_test_3);
  tcase_add_test(tc, asin_test_4);
  tcase_add_test(tc, asin_test_5);
  tcase_add_test(tc, asin_test_6);

  tcase_add_test(tc, acos_test_1);
  tcase_add_test(tc, acos_test_2);
  tcase_add_test(tc, acos_test_3);
  tcase_add_test(tc, acos_test_4);
  tcase_add_test(tc, acos_test_5);
  tcase_add_test(tc, acos_test_6);

  tcase_add_test(tc, atan_test_1);
  tcase_add_test(tc, atan_test_2);
  tcase_add_test(tc, atan_test_3);
  tcase_add_test(tc, atan_test_4);
  tcase_add_test(tc, atan_test_5);

  tcase_add_test(tc, exp_test_1);
  tcase_add_test(tc, exp_test_2);
  tcase_add_test(tc, exp_test_3);
  tcase_add_test(tc, exp_test_4);
  tcase_add_test(tc, exp_test_5);
  tcase_add_test(tc, exp_test_6);
  tcase_add_test(tc, exp_test_7);
  tcase_add_test(tc, exp_test_8);
  tcase_add_test(tc, exp_test_9);
  tcase_add_test(tc, exp_test_10);
  tcase_add_test(tc, exp_test_11);

  tcase_add_test(tc, sqrt_test_1);
  tcase_add_test(tc, sqrt_test_2);
  tcase_add_test(tc, sqrt_test_3);
  tcase_add_test(tc, sqrt_test_4);
  tcase_add_test(tc, floor_test_1);
  tcase_add_test(tc, floor_test_2);
  tcase_add_test(tc, ceil_test_1);
  tcase_add_test(tc, ceil_test_2);
  tcase_add_test(tc, log_test_1);
  tcase_add_test(tc, log_test_2);
  tcase_add_test(tc, log_test_3);
  tcase_add_test(tc, log_test_4);
  tcase_add_test(tc, log_test_5);

  suite_add_tcase(s, tc);

  return s;
}

int main() {
  int nf;
  Suite *s = suite();
  SRunner *sr;

  sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}

// int main() {

//   for (long double k = 0; k <= 26; k++) {
//     printf("RES: %f k:%.0Lf \n", exp(k), k);
//   }

//     return 0;
// }
