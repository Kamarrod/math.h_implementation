#include "s21_math.h"

long double s21_sin(double x) {
  long double result = s21_NAN;
  if (!(x == s21_INFINITY || x == -s21_INFINITY || x != x)) {
    int sign = 1;
    if (x < 0) {
      x = -x;
      sign = -1;
    }
    x = s21_fmod(x, 2 * s21_PI);
    if (x > s21_PI) sign *= -1;
    x = s21_fmod(x, s21_PI);
    if (x > s21_PI / 2) x = s21_PI - x;

    long double step = x;
    result = x;
    int stepSign = -1;
    for (int n = 3; s21_fabs(step) > s21_eps; n += 2) {
      step *= x * x / n / (n - 1);
      result += stepSign * step;
      stepSign *= -1;
    }
    result *= sign;
  }

  return result;
}

long double s21_cos(double x) {
  long double result = s21_NAN;
  if (!(x == s21_INFINITY || x == -s21_INFINITY || x != x)) {
    if (x < 0) x = -x;
    x = s21_fmod(x, 2 * s21_PI);
    if (x > s21_PI) x = 2 * s21_PI - x;
    int sign = 1;
    if (x > s21_PI / 2) {
      x = s21_PI - x;
      sign = -1;
    }

    long double step = 1;
    result = 1;
    int stepSign = -1;
    for (int n = 2; s21_fabs(step) > s21_eps; n += 2) {
      step *= x * x / n / (n - 1);
      result += stepSign * step;
      stepSign *= -1;
    }
    result *= sign;
  }

  return result;
}

long double s21_tan(double x) {
  long double result = s21_NAN;
  if (!(x == s21_INFINITY || x == -s21_INFINITY || x != x)) {
    long double sin = s21_sin(x);
    long double cos = s21_cos(x);
    if (!s21_isNan(cos) && !s21_isNan(sin)) result = sin / cos;
  }
  return result;
}

int s21_isPositiveZero(double number) { return 1.0 / number == +s21_INFINITY; }

int s21_isNegativeZero(double number) { return 1.0 / number == -s21_INFINITY; }

int s21_isNan(double number) { return number != number; }

int s21_isFinite(double number) {
  return number != s21_INFINITY && number != -s21_INFINITY &&
         !s21_isNan(number);
}

int s21_isEven(double number) { return s21_fmod(number, 2) == 0; }

int s21_isOdd(double number) {
  return number < 0 ? s21_fmod(number, 2) == -1 : s21_fmod(number, 2) == 1;
}

int s21_isInteger(double number) { return s21_fmod(number, 1) == 0; }

long double s21_pow(double base, double exp) {
  long double result;
  if ((s21_isPositiveZero(base) && exp < 0 && s21_isOdd(exp)) ||
      (base == 0 && s21_isFinite(exp) && exp < 0 &&
       (s21_isEven(exp) || !s21_isInteger(exp))) ||
      (base == 0 && exp == -s21_INFINITY) ||
      (s21_fabs(base) < 1 && exp == -s21_INFINITY) ||
      (s21_fabs(base) > 1 && exp == s21_INFINITY) ||
      (base == -s21_INFINITY && exp > 0 &&
       (!s21_isInteger(exp) || s21_isEven(exp))) ||
      (base == s21_INFINITY && exp > 0))
    result = s21_INFINITY;
  else if ((s21_isNegativeZero(base) && exp < 0 && s21_isOdd(exp)) ||
           (base == -s21_INFINITY && exp > 0 && s21_isOdd(exp)))
    result = -s21_INFINITY;
  else if ((s21_isPositiveZero(base) && exp > 0 && s21_isOdd(exp)) ||
           (base == 0 && exp > 0 && (!s21_isInteger(exp) || s21_isEven(exp))) ||
           (s21_fabs(base) > 1 && exp == -s21_INFINITY) ||
           (s21_fabs(base) < 1 && exp == s21_INFINITY) ||
           (base == -s21_INFINITY && exp < 0 &&
            (!s21_isInteger(exp) || s21_isEven(exp))) ||
           (base == s21_INFINITY && exp < 0))
    result = 0.0;
  else if ((s21_isNegativeZero(base) && exp > 0 && s21_isOdd(exp)) ||
           (base == -s21_INFINITY && exp < 0 && s21_isOdd(exp)))
    result = -0.0;
  else if ((base == -1 && (exp == s21_INFINITY || exp == -s21_INFINITY)) ||
           base == 1 || exp == 0)
    result = 1;
  else if (s21_isFinite(base) && base < 0 && s21_isFinite(exp) &&
           !s21_isInteger(exp))
    result = s21_NAN;
  else if (!s21_isNan(exp) && !s21_isNan(base))
    result = s21_exp(exp * s21_log(base));
  else
    result = s21_NAN;
  return result;
}

long double s21_fmod(double x, double y) {
  long double result;
  if (((x == s21_INFINITY || x == -s21_INFINITY) && y == y) ||
      (x == x && y == 0)) {
    result = s21_NAN;
  } else if ((y == s21_INFINITY || y == -s21_INFINITY) && x != s21_INFINITY &&
             x != -s21_INFINITY) {
    result = x;
  } else if (!(x != x || y != y)) {
    long max = x / y > 0 ? s21_floor(x / y) : s21_ceil(x / y);
    result = x - y * max;
  } else {
    result = s21_NAN;
  }
  return result;
}

long double s21_fabs(double x) {
  long double result;
  if (x == s21_INFINITY || x == -s21_INFINITY)
    result = s21_INFINITY;
  else if (s21_isNan(x))
    result = s21_NAN;
	else if(s21_isNegativeZero(x))
		result = 0.0;
  else
    result = x >= 0 ? x : -x;
  return result;
}

int s21_abs(int x) { return x > 0 ? x : -x; }

long double s21_atan(double x) {
  int sign_change = 0, invertation = 0, iters = 0;
  long double res;
  if (x < 0.) {
    x = -x;
    sign_change = 1;
  }
  if (x > 1.) {
    x = 1. / x;
    invertation = 1;
  }
  while (x > M_PI12) {
    x = (x * SQRT3 - 1) / (x + SQRT3);
    iters++;
  }
  res =
      x * (0.55913709 / (1.4087812 + x * x) + 0.60310579 - 0.05160454 * x * x);
  while (iters > 0) {
    res += M_PI6;
    iters--;
  }
  if (invertation) res = M_PI2 - res;
  if (sign_change) res = -res;
  return res;
}

long double s21_asin(double x) {
  long double res;
  if (x < -1. || x > 1.) {
    res = s21_NAN;
  } else if (x == -1.)
    res = -M_PI2;
  else if (x == 1.)
    res = M_PI2;
  else {
    x /= s21_sqrt(1. - x * x);
    res = s21_atan(x);
  }
  return res;
}

long double s21_acos(double x) {
  long double res = s21_asin(x);
  res = M_PI2 - res;
  return res;
}

long double s21_exp(double x) {
  long double res = 1;
  if (x < -19)
    res = 0;
  else if (x == s21_INFINITY) {
    res = s21_INFINITY;
  } else {
    long double add = 1, i = 1;
    while (s21_fabs(add) > 1e-7) {
      add *= x / i;
      res += add;
      i++;

      if (res > DBL_MAX) {
        res = s21_INFINITY;
        break;
      }
    }
  }
  return res;
}

// long double s21_exp(double x) {
//   long double res = 1;
//   if (x < -19)
//     res = 0;
//   else if (x == s21_INFINITY) {
//     res = s21_INFINITY;
//   } else {
//     if(x >=2) {
//       while(x>=2){
//         x=x-2;
//         res=res * (long double) e2;
//       }
//       res*=s21_exp(x);
//     } else {
//       long double add = 1, i = 1;
//       while (s21_fabs(add) > 1e-7) {
//         add *= x / i;
//         res += add;
//         i++;

//         if (res > DBL_MAX) {
//           res = s21_INFINITY;
//           break;
//         }
//       }
//     }

//   }
//   return res;
// }


long double s21_ceil(double x) {
  long double result = x;
  if (!(x == s21_INFINITY || x == -s21_INFINITY || x != x)) {
    long long integer = (ll)x;
    if (integer == x || x < 0) {
      result = integer;
    } else {
      result = (ll)x + 1;
    }
  }
  return (long double)result;
}

long double s21_floor(double x) {
  long double result = x;
  if (!(x == s21_INFINITY || x == -s21_INFINITY || x != x)) {
    long long integer = (ll)x;
    if (integer == x || x > 0) {
      result = integer;
    } else {
      result = (ll)x - 1;
    }
  }
  return (long double)result;
}

long double s21_sqrt(double x) {
  long double result = s21_NAN;
  int flag = 0;
  if (x != x || x == s21_INFINITY || x < 0) flag = 1;
  double left = 1 < x ? 1 : x;
  double right = 1 > x ? 1 : x;

  while (flag != 1 && 100 * left * left < x) left *= 10;
  while (flag != 1 && 0.01 * right * right > x) right *= 0.1;

  for (int i = 0; i < 1e6 && flag != 1; i++) {
    double mid = (left + right) / 2;
    if (mid * mid == x || s21_fabs(mid * mid - x) < 1e-12) {
      i = 1e6 + 1;
    } else {
      if (mid * mid > x)
        right = mid;
      else
        left = mid;
    }
    result = mid;
  }
  return x == s21_INFINITY ? s21_INFINITY : result;
}

long double GetExponentialForm(double x, int *b) {
  long double a = x;
  if (x < 1) {
    while (a <= 1) {
      a *= 10.0;
      *b = *b - 1;
    }
  } else
    while (a >= 10) {
      a /= 10.0;
      *b = *b + 1;
    }
  return a;
}

long double s21_log(double x) {
  int b = 0;
  long double result = s21_NAN;
  int flag = 0;
  if ((x <= 0 || x == s21_INFINITY || x != x)) flag = 1;
  if (x == 1) {
    result = 0.0;
    flag = 1;
  }
  if (flag != 1) {
    long double a = GetExponentialForm(x, &b);
    long double prevA = (a / 10) - 1;
    result = (a / 10) - 1;
    for (int i = 2; i < 371; i++) {
      prevA *= (a / 10) - 1;
      if (i % 2 == 1) {
        result += prevA / i;
      } else {
        result += -prevA / i;
      }
    }
    result -= (b + 1) * ln0_1;
  }
  return x == 0 ? -s21_INFINITY : x == s21_INFINITY ? s21_INFINITY : result;
}


// int main() {

//   for (double k = 0; k <= 26; k++) {
//     printf("k:%.0f  MY: %Lf ORIG: %f \n", k , s21_exp(k), exp(k));
//   }

//     return 0;
// }
