#include "s21_math.h"

int s21_abs(int x) {
  if (x < 0) x *= -1;
  return x;
}

bool is_inf(long double x) { return x == (1.0 / 0.0) || x == (-1.0 / 0.0); }
long double s21_atan(double x) {
  long double result = 0;
  if (x > -1. && x < 1.) {
    for (int i = 0; i < 1000; i++) {
      result += s21_pow(-1, i) * s21_pow(x, 1 + (2 * i)) / (1 + (2 * i));
    }
  } else {
    for (int i = 0; i < 2000; i++) {
      result += (s21_pow(-1, i) * s21_pow(x, -1 - (2 * i))) / (1 + 2 * i);
    }
    result = S21_PI * (s21_sqrt(x * x)) / (2 * x) - result;
  }
  if (is_inf(x)) {
    if (x > 0) {
      result = S21_PI / 2;
    } else {
      result = -S21_PI / 2;
    }
  }
  if (x == 1.0) {
    result = S21_PI / 4;
  } else if (x == -1.0) {
    result = (S21_PI / 4) * -1;
  } else if (x == 0.0) {
    result = 0.0;
  } else if (x != x) {
    result = S21_nan;
  }
  return result;
}

long double s21_asin(double x) {
  long double result = 0;
  if (!(s21_fabs(x - 0.7071067811865475244) < EPS_10)) {
    if (!(s21_fabs(x + 0.7071067811865475244) < EPS_10)) {
      if (x < 1. && x > -1.) {
        result = s21_atan(x / (s21_sqrt(1 - x * x)));
      } else if (x == 1)
        result = S21_PI / 2;
      else if (x == -1)
        result = -1 * S21_PI / 2;
      else
        result = S21_nan;
    } else
      result = (-1 * S21_PI / 4);
  } else
    result = S21_PI / 4;
  return result;
}

long double s21_acos(double x) {
  long double result = 0;
  if (!(s21_fabs(x - 0.7071067811865475244) < EPS_10)) {
    if (!(s21_fabs(x + 0.7071067811865475244) < EPS_10)) {
      if (x > 0. && x < 1.) {
        result = s21_atan((s21_sqrt(1 - x * x)) / x);
      } else if (x > -1. && x < 0) {
        result = S21_PI + s21_atan(s21_sqrt(1 - x * x) / x);
      } else if (x == 1)
        result = 0;
      else if (x == -1)
        result = S21_PI;
      else if (x == 0)
        result = S21_PI / 2;
      else
        result = S21_nan;
    } else
      result = (3 * S21_PI / 4);
  } else
    result = S21_PI / 4;
  return result;
}

long double s21_fmod(double x, double y) {
  long double res = 0.0;
  int sign = 1;
  if (x < 0.0) {
    sign = -1;
    x = s21_fabs(x);
  }
  if (y < 0.0) y = s21_fabs(y);
  if (y == 0.0 || s21_fabs(x) == S21_inf || x != x || y != y)
    res = S21_nan;
  else if (x == y || (s21_fabs(x) == 0.0 && y != 0.0 && y != S21_nan))
    res = 0;
  else if (x < y || (s21_fabs(y) == S21_inf && s21_fabs(x) != S21_inf))
    res = x;
  else {
    long long int mod = x / y;
    res = (long double)x - (mod * (long double)y);
  }
  return res * sign;
}

long double s21_pow(double x, double y) {
  long double result = 1;
  if ((x == -1 && s21_fabs(y) == S21_inf) || x == 1 || s21_fabs(y) == 0.0)
    result = 1;
  else if (y == 1)
    result = x;
  else {
    if (s21_fabs(x) >= DBL_MAX) x = sign(x) * S21_inf;
    if (s21_fabs(y) >= DBL_MAX) y = sign(y) * S21_inf;
    if ((x == -0.0 && y < 0.0 && is_odd_int(y)) ||
        (x == -S21_inf && y > 0.0 && is_odd_int(y))) {
      result = -S21_inf;
    } else if ((s21_fabs(x) < 1 && y == -S21_inf) ||
               (s21_fabs(x) > 1 && y == +S21_inf) ||
               (x == +0.0 && y < 0.0 && is_odd_int(y)) ||
               ((s21_fabs(x) == 0.0) && y < 0.0 && !is_odd_int(y)) ||
               (y > 0.0 && !is_odd_int(y) && x == -S21_inf) ||
               (y > 0.0 && x == +S21_inf)) {
      result = +S21_inf;
    } else if (((x == +0.0 && y > 0.0 && is_odd_int(y)) ||
                ((s21_fabs(x) == 0.0) && y > 0.0 && !is_odd_int(y)) ||
                (s21_fabs(x) > 1 && y == -S21_inf) ||
                (s21_fabs(x) < 1 && y == +S21_inf) ||
                (x == -S21_inf && y < 0.0 && !is_odd_int(y)) ||
                (x == +S21_inf && y < 0.0))) {
      result = +0.0;
    } else if (is_odd_int(y) &&
               ((x == -0.0 && y > 0.0) || (x == -S21_inf && y < 0.0))) {
      result = -0.0;
    } else if ((x < 0.0 && (s21_fabs(y) != S21_inf) && ((int)y != y)) ||
               (x != x && y != 0) || (y != y && x != 1)) {
      result = S21_nan;
    } else {
      if (x < 0.0f) {
        x = s21_fabs(x);
        if (is_odd_int(y)) result = -1;
      }
      result *= s21_exp(y * s21_log(x));
    }
  }
  return result;
}

long double s21_sin(double x) {
  if (x > 0 && x > 2 * S21_PI) {
    double temp = x / (2 * S21_PI);
    x = x - (int)temp * 2 * S21_PI;
  } else if (x < 0 && x < -2 * S21_PI) {
    double temp = x / (2 * S21_PI);
    x = x - (int)temp * 2 * S21_PI;
  }
  long double sum = 0.0;
  long double y = (long double)x;
  long double t = y;
  int p = 0;
  while (s21_fabs(t) > EPS_6 / 10 && p < 10000) {
    sum += t;
    p++;
    t *= -y * y / (2.0 * p + 1.0) / (2.0 * p);
  }
  if (x != x || x == S21_inf) {
    sum = S21_nan;
  }
  return sum;
}

long double s21_sqrt(double x) { return s21_pow(x, 0.5); }

long double s21_tan(double x) { return s21_sin(x) / s21_cos(x); }

long double s21_ceil(double x) {
  long double result = x;
  if (x == S21_inf)
    result = S21_inf;
  else if (x == -S21_inf)
    result = -S21_inf;
  else if (x == S21_nan)
    result = S21_nan;
  else if (x != DBL_MAX && x != -DBL_MAX) {
    if ((x >= 0) && ((x - (long int)x) > 0)) result = (long int)x + 1;
    if ((x < 0) && ((x - (long int)x) < 0)) result = (long int)x;
  }
  return result;
}

long double s21_cos(double x) {
  long double result;
  if (x == S21_inf || x == -S21_inf || x == S21_nan)
    result = S21_nan;
  else {
    while (x > S21_PI || x < -S21_PI) {
      if (x > S21_PI)
        x -= 2 * S21_PI;
      else
        x += 2 * S21_PI;
    }
    result = 1;
    long double number, numerator = 1;
    long int i = 1;
    do {
      numerator *= -1 * x * x;
      number = numerator / s21_factorial(2 * i);
      result += number;
      ++i;
    } while (s21_fabs(number) > 1E-7);
  }
  return result;
}

long double s21_exp(double x) {
  long double result;
  if (x == S21_inf || x == DBL_MAX)
    result = S21_inf;
  else if (x == -S21_inf || x == -DBL_MAX)
    result = 0;
  else if (x == S21_nan)
    result = S21_nan;
  else {
    result = 1;
    long double number = 1;
    int i = 1;
    do {
      number *= s21_fabs(x) / i;
      result += number;
      i++;
      if (result > DBL_MAX) {
        result = S21_inf;
        break;
      }
    } while (number > 1E-10);
    if (x < 0) result = 1 / result;
  }
  return result;
}

long int s21_factorial(int number) {
  long int result = 1;
  if (number)
    for (long int i = 1; i <= number; ++i) result *= i;
  return result;
}

long double s21_fabs(double x) {
  long double result = x;
  if (x < 0) result = -1 * x;
  return result;
}

long double s21_floor(double x) {
  long double result = x;
  if (x == S21_inf)
    result = S21_inf;
  else if (x == -S21_inf)
    result = -S21_inf;
  else if (x == S21_nan)
    result = S21_nan;
  else if (x != DBL_MAX && x != -DBL_MAX) {
    if ((x >= 0) && ((x - (long int)x) > 0)) result = (long int)x;
    if ((x < 0) && ((x - (long int)x) < 0)) result = (long int)x - 1;
  }
  return result;
}

long double s21_log(double x) {
  int amount_of_e_in_x = 0;
  double result = 0;
  double previousResult = 0;
  if (x == S21_inf)
    result = S21_inf;
  else if (x == 0)
    result = -S21_inf;
  else if (x < 0)
    result = S21_nan;
  else if (x == 1)
    result = 0;
  else {
    for (; x >= s21_e; x /= s21_e, amount_of_e_in_x++) continue;
    for (int i = 0; i < 100; i++) {
      previousResult = result;
      result = previousResult + 2 * (x - s21_exp(previousResult)) /
                                    (x + s21_exp(previousResult));
    }
  }
  return amount_of_e_in_x + result;
}

int sign(double x) {
  int res = 0;
  res = (x > 0) ? 1 : -1;
  return res;
}

int is_odd_int(double y) { return ((int)y == y && (int)y % 2 != 0) ? 1 : 0; }
