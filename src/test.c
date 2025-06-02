#include <check.h>
#include <math.h>

#include "s21_math.h"

Suite *suite_s21_test();

int main() {
  Suite *s;
  SRunner *sr;

  s = suite_s21_test();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}

START_TEST(test_s21_abs) {
  ck_assert_double_eq(s21_abs(0), abs(0));
  ck_assert_double_eq(s21_abs(1), abs(1));
  ck_assert_double_eq(s21_abs(-1), abs(-1));
}
END_TEST
START_TEST(test_s21_fabs) {
  for (double i = -1000.0; i <= 1000.0; i += 0.01)
    ck_assert_double_eq_tol(s21_fabs(i), fabs(i), EPS_6);
  ck_assert_double_nan(s21_fabs(S21_nan));
  ck_assert_double_eq(s21_fabs(+0.0), fabs(+0.0));
  ck_assert_double_eq(s21_fabs(-0.0), fabs(-0.0));
  ck_assert_double_eq(s21_fabs(S21_inf), fabs(S21_inf));
  ck_assert_double_eq(s21_fabs(-S21_inf), fabs(-S21_inf));
}
END_TEST
START_TEST(test_s21_ceil) {
  ck_assert_ldouble_nan(s21_ceil(S21_nan));
  ck_assert_double_eq(s21_ceil(-S21_inf), ceil(-S21_inf));
  ck_assert_double_eq(s21_ceil(+S21_inf), ceil(+S21_inf));
  ck_assert_double_eq_tol(s21_ceil(+0.0), ceil(+0.0), EPS_6);
  ck_assert_double_eq_tol(s21_ceil(-0.0), ceil(-0.0), EPS_6);
  ck_assert_double_eq_tol(s21_ceil(5.5), ceil(5.5), EPS_6);
  ck_assert_double_eq_tol(s21_ceil(-5.5), ceil(-5.5), EPS_6);
  ck_assert_double_eq_tol(s21_ceil(-0.45), ceil(-0.45), EPS_6);
  ck_assert_double_eq_tol(s21_ceil(0.45), ceil(0.45), EPS_6);
  ck_assert_double_eq_tol(s21_ceil(1.00000000001), ceil(1.00000000001), EPS_6);
  ck_assert_double_eq_tol(s21_ceil(11231231241141414.00000000001),
                          ceil(11231231241141414.00000000001), EPS_6);
  ck_assert_double_eq_tol(s21_ceil(DBL_MAX), ceil(DBL_MAX), EPS_6);
  ck_assert_double_eq_tol(s21_ceil(-DBL_MAX), ceil(-DBL_MAX), EPS_6);
}
END_TEST
START_TEST(test_s21_floor) {
  ck_assert_double_eq(s21_floor(-S21_inf), floor(-S21_inf));
  ck_assert_double_eq(s21_floor(+S21_inf), floor(+S21_inf));
  ck_assert_ldouble_nan(s21_floor(S21_nan));
  ck_assert_double_eq_tol(s21_floor(-2.2), floor(-2.2), EPS_6);
  ck_assert_double_eq_tol(s21_floor(2.2), floor(2.2), EPS_6);
  ck_assert_double_eq_tol(s21_floor(+0.0), floor(+0.0), EPS_6);
  ck_assert_double_eq_tol(s21_floor(0.0), floor(0.0), EPS_6);
  ck_assert_double_eq_tol(s21_floor(-0.0), floor(-0.0), EPS_6);
  ck_assert_double_eq_tol(s21_floor(1.00000000001), floor(1.00000000001),
                          EPS_6);
  ck_assert_double_eq_tol(s21_floor(2123123124), floorl(2123123124), EPS_6);
}
END_TEST
START_TEST(test_s21_fmod) {
  ck_assert_double_eq(s21_fmod(-0.7, -S21_inf), fmod(-0.7, -S21_inf));
  ck_assert_double_eq(s21_fmod(-0.7, +S21_inf), fmod(-0.7, +S21_inf));
  ck_assert_double_eq(s21_fmod(0.7, -S21_inf), fmod(0.7, -S21_inf));
  ck_assert_double_eq(s21_fmod(0.7, +S21_inf), fmod(0.7, +S21_inf));
  ck_assert_ldouble_nan(s21_fmod(+S21_inf, 0.7));
  ck_assert_ldouble_nan(s21_fmod(-S21_inf, 0.7));
  ck_assert_ldouble_nan(s21_fmod(+S21_inf, -0.7));
  ck_assert_ldouble_nan(s21_fmod(-S21_inf, -0.7));
  ck_assert_ldouble_nan(s21_fmod(S21_nan, -0.7));
  ck_assert_ldouble_nan(s21_fmod(0.7, S21_nan));
  ck_assert_ldouble_nan(s21_fmod(0.7, 0.0));
  ck_assert_ldouble_nan(s21_fmod(-0.7, 0.0));
  ck_assert_double_eq(s21_fmod(0.7, 0.2), fmod(0.7, 0.2));
  ck_assert_double_eq(s21_fmod(0.7, -0.2), fmod(0.7, -0.2));
  ck_assert_double_eq(s21_fmod(-0.7, -0.2), fmod(-0.7, -0.2));
  ck_assert_double_eq(s21_fmod(-0.7, 0.2), fmod(-0.7, 0.2));
  ck_assert_double_eq(s21_fmod(5.5, 2.0), fmod(5.5, 2.0));
  ck_assert_double_eq(s21_fmod(2.0, 5.5), fmod(2.0, 5.5));
  ck_assert_double_eq(s21_fmod(2.0, -5.5), fmod(2.0, -5.5));
  ck_assert_double_eq(s21_fmod(+0, 5.5), fmod(+0, 5.5));
  ck_assert_double_eq(s21_fmod(-0, 5.5), fmod(-0, 5.5));
}
END_TEST
START_TEST(test_s21_pow) {
  ck_assert_double_eq(s21_pow(+0.0, 2.2), pow(+0.0, 2.2));
  ck_assert_double_eq(s21_pow(-S21_inf, 5.1), pow(-S21_inf, 5.1));
  ck_assert_double_eq(s21_pow(+0.0, 2.0), pow(+0.0, 2.0));
  ck_assert_double_eq(s21_pow(+0.0, -2.2), pow(+0.0, -2.2));
  ck_assert_double_eq(s21_pow(+0.0, -2.0), pow(+0.0, -2.0));
  ck_assert_double_eq(s21_pow(-0.0, 2.2), pow(-0.0, 2.2));
  ck_assert_double_eq(s21_pow(-0.0, -2.0), pow(-0.0, -2.0));
  ck_assert_double_eq(s21_pow(-0.0, -2.2), pow(-0.0, -2.2));
  ck_assert_double_eq(s21_pow(-0.0, 2.0), pow(-0.0, 2.0));
  ck_assert_double_eq(s21_pow(0.7, -S21_inf), pow(0.7, -S21_inf));
  ck_assert_double_eq(s21_pow(0.7, +S21_inf), pow(0.7, +S21_inf));
  ck_assert_double_eq(s21_pow(-0.7, -S21_inf), pow(0.7, -S21_inf));
  ck_assert_double_eq(s21_pow(-1.7, -S21_inf), pow(-1.7, -S21_inf));
  ck_assert_double_eq(s21_pow(1.7, -S21_inf), pow(1.7, -S21_inf));
  ck_assert_double_eq(s21_pow(-0.7, +S21_inf), pow(0.7, +S21_inf));
  ck_assert_double_eq(s21_pow(-1.7, +S21_inf), pow(-1.7, +S21_inf));
  ck_assert_double_eq(s21_pow(1.7, +S21_inf), pow(1.7, +S21_inf));
  ck_assert_double_eq(s21_pow(-S21_inf, -2.0), pow(-S21_inf, -2.0));
  ck_assert_double_eq(s21_pow(-S21_inf, -2.2), pow(-S21_inf, -2.2));
  ck_assert_double_eq(s21_pow(-S21_inf, 4.0), pow(-S21_inf, 4.0));
  ck_assert_double_eq(s21_pow(-0.0, -5.0), pow(-0.0, -5.0));
  ck_assert_double_eq(s21_pow(-S21_inf, 5.0), pow(-S21_inf, 5.0));
  ck_assert_double_eq(s21_pow(-S21_inf, 5.0), pow(-S21_inf, 5.0));
  ck_assert_double_eq(s21_pow(-S21_inf, -S21_inf), pow(-S21_inf, -S21_inf));
  ck_assert_double_eq(s21_pow(-S21_inf, S21_inf), pow(-S21_inf, S21_inf));
  ck_assert_double_eq(s21_pow(S21_inf, -S21_inf), pow(S21_inf, -S21_inf));
  ck_assert_double_eq(s21_pow(S21_inf, S21_inf), pow(S21_inf, S21_inf));
  ck_assert_double_eq(s21_pow(S21_nan, 0.0), pow(S21_nan, 0.0));

  ck_assert_double_eq_tol(s21_pow(2.0, 4.0), pow(2.0, 4.0), EPS_6);
  ck_assert_double_eq_tol(s21_pow(-0.0, 5.0), pow(-0.0, 5.0), EPS_6);
  ck_assert_double_eq_tol(s21_pow(-S21_inf, -5.0), pow(-S21_inf, -5.0), EPS_6);
  ck_assert_double_eq_tol(s21_pow(-1, S21_inf), pow(-1, S21_inf), EPS_6);
  ck_assert_double_eq_tol(s21_pow(-1, -S21_inf), pow(-1, -S21_inf), EPS_6);
  ck_assert_double_eq_tol(s21_pow(1, -S21_inf), pow(1, -S21_inf), EPS_6);
  ck_assert_double_eq_tol(s21_pow(1, S21_inf), pow(1, S21_inf), EPS_6);
  ck_assert_double_eq_tol(s21_pow(1, 0.0), pow(1, 0.0), EPS_6);
  ck_assert_double_eq_tol(s21_pow(1, 6.0), pow(1, 6.0), EPS_6);
  ck_assert_double_eq_tol(s21_pow(13.3, 0.0), pow(13.3, 0.0), EPS_6);
  ck_assert_double_eq_tol(s21_pow(0.0, 0.0), pow(0.0, 0.0), EPS_6);
  ck_assert_double_eq_tol(s21_pow(S21_inf, 0.0), pow(S21_inf, 0.0), EPS_6);
  ck_assert_double_eq_tol(s21_pow(-S21_inf, 0.0), pow(-S21_inf, 0.0), EPS_6);

  ck_assert_double_nan(s21_pow(-2.2, -2.2));
  ck_assert_double_nan(s21_pow(-2.2, 0.2));
  ck_assert_double_nan(s21_pow(S21_nan, 0.2));
  ck_assert_double_nan(s21_pow(S21_nan, 5));
  ck_assert_double_nan(s21_pow(-2.8, S21_nan));
  ck_assert_double_nan(s21_pow(4, S21_nan));
  ck_assert_double_nan(s21_pow(S21_nan, S21_nan));
  ck_assert_double_nan(s21_pow(S21_nan, S21_inf));
  ck_assert_double_nan(s21_pow(S21_nan, -S21_inf));
  ck_assert_double_nan(s21_pow(-S21_inf, S21_nan));
  ck_assert_double_nan(s21_pow(S21_inf, S21_nan));
  ck_assert_double_nan(s21_pow(0.0, S21_nan));

  ck_assert_double_eq(s21_pow(DBL_MAX, 5.0), pow(DBL_MAX, 5.0));
  ck_assert_double_eq(s21_pow(-DBL_MAX, 5.0), pow(-DBL_MAX, 5.0));
  ck_assert_double_eq(s21_pow(5.0, -DBL_MAX), pow(5.0, -DBL_MAX));
  ck_assert_double_eq(s21_pow(5.0, DBL_MAX), pow(5.0, DBL_MAX));
  ck_assert_double_eq(s21_pow(-DBL_MAX, 0), pow(-DBL_MAX, 0));
  ck_assert_double_eq(s21_pow(DBL_MAX, 0), pow(DBL_MAX, 0));
  ck_assert_double_eq(s21_pow(0, -DBL_MAX), pow(0, -DBL_MAX));
  ck_assert_double_eq(s21_pow(0, DBL_MAX), pow(0, DBL_MAX));
  ck_assert_double_eq(s21_pow(-DBL_MAX, 1), pow(-DBL_MAX, 1));
  ck_assert_double_eq(s21_pow(DBL_MAX, 1), pow(DBL_MAX, 1));
  ck_assert_double_eq(s21_pow(1, -DBL_MAX), pow(1, -DBL_MAX));
  ck_assert_double_eq(s21_pow(1, DBL_MAX), pow(1, DBL_MAX));
  ck_assert_double_eq(s21_pow(-DBL_MAX, -DBL_MAX), pow(-DBL_MAX, -DBL_MAX));
  ck_assert_double_eq(s21_pow(DBL_MAX, DBL_MAX), pow(DBL_MAX, DBL_MAX));
  ck_assert_double_eq(s21_pow(DBL_MAX, -DBL_MAX), pow(DBL_MAX, -DBL_MAX));
  ck_assert_double_eq(s21_pow(-DBL_MAX, DBL_MAX), pow(-DBL_MAX, DBL_MAX));
}
END_TEST
START_TEST(test_s21_sqrt) {
  ck_assert_double_eq_tol(s21_sqrt(0.0), sqrt(0.0), EPS_6);
  ck_assert_double_eq_tol(s21_sqrt(-0.0), sqrt(-0.0), EPS_6);
  ck_assert_double_eq_tol(s21_sqrt(9), sqrt(9), EPS_6);
  ck_assert_ldouble_nan(s21_sqrt(-9));
}
END_TEST
START_TEST(test_s21_exp) {
  ck_assert_ldouble_nan(s21_exp(S21_nan));
  ck_assert_double_eq(s21_exp(-S21_inf), exp(-S21_inf));
  ck_assert_double_eq(s21_exp(+S21_inf), exp(+S21_inf));
  ck_assert_double_eq(s21_exp(0.0), exp(0.0));
  ck_assert_double_eq(s21_exp(-0.0), exp(-0.0));
  ck_assert_double_eq_tol(s21_exp(5.5), exp(5.5), EPS_6);
  ck_assert_double_eq_tol(s21_exp(-5.5), exp(-5.5), EPS_6);
  ck_assert_double_eq_tol(s21_exp(-0.45), exp(-0.45), EPS_6);
  ck_assert_double_eq_tol(s21_exp(0.45), exp(0.45), EPS_6);
  ck_assert_double_eq(s21_exp(DBL_MAX), exp(DBL_MAX));
  ck_assert_double_eq_tol(s21_exp(-DBL_MAX), exp(-DBL_MAX), EPS_6);
}
END_TEST
START_TEST(test_s21_log) {
  ck_assert_double_eq(s21_log(0.0), log(0.0));
  ck_assert_double_eq(s21_log(-0.0), log(-0.0));
  ck_assert_double_eq(s21_log(1), log(1));
  ck_assert_double_eq_tol(s21_log(9), log(9), EPS_6);
  ck_assert_ldouble_nan(s21_log(-9));
  ck_assert_ldouble_nan(s21_log(S21_nan));
  ck_assert_double_eq(s21_log(S21_inf), log(S21_inf));
  ck_assert_ldouble_nan(s21_log(-S21_inf));
}
END_TEST
START_TEST(test_s21_sin) {
  ck_assert_double_eq_tol(s21_sin(0.0), sin(0.0), EPS_6);
  ck_assert_double_eq_tol(s21_sin(-0.0), sin(-0.0), EPS_6);
  ck_assert_double_eq_tol(s21_sin(9), sin(9), EPS_6);
  ck_assert_double_eq_tol(s21_sin(-9), sin(-9), EPS_6);
  ck_assert_ldouble_nan(s21_sin(S21_nan));
  ck_assert_ldouble_nan(s21_sin(S21_inf));
  ck_assert_ldouble_nan(s21_sin(-S21_inf));
}
END_TEST
START_TEST(test_s21_cos) {
  ck_assert_double_eq_tol(cos(0), s21_cos(0), 1e-6);  // погрешность 1e-6
  ck_assert_double_eq_tol(cos(1), s21_cos(1), 1e-6);
  ck_assert_double_eq_tol(cos(3 * S21_PI / 18), s21_cos(3 * S21_PI / 18),
                          1e-6);  // угл 30 градусов
  ck_assert_double_eq_tol(cos(6 * S21_PI / 360), s21_cos(6 * S21_PI / 360),
                          1e-6);  // угл 1 градус
  ck_assert_double_eq_tol(cos(-S21_PI / 360), s21_cos(-S21_PI / 360), 1e-6);
  ck_assert_double_eq_tol(cos(S21_PI / 6), s21_cos(S21_PI / 6),
                          1e-6);  // угл 30 градусов
  ck_assert_double_eq_tol(cos(S21_PI * 2), s21_cos(S21_PI * 2),
                          1e-6);  // cos(2P) = 0
  ck_assert_double_eq_tol(cos(1e-6), s21_cos(1e-6),
                          1e-6);  // очень маленькие значения
  ck_assert_double_eq_tol(cos(-1e-6), s21_cos(-1e-6), 1e-6);
  ck_assert_double_nan(s21_cos(S21_inf));
  ck_assert_double_nan(s21_cos(-S21_inf));
  ck_assert_double_nan(s21_cos(S21_nan));
  for (double i = -100; i <= 100; i += 0.001) {
    ck_assert_ldouble_eq_tol(cos(i), s21_cos(i), 1e-6);
  }  // цикл проверяет результаты функций для широкого диапазона значений -100
     // до
     //  100 с шагом 0.001.
  ck_assert_double_eq_tol(cos(-2435.6578), s21_cos(-2435.6578),
                          1e-6);  // при максимальных значениях
  ck_assert_double_eq_tol(cos(38456.9174678), s21_cos(38456.9174678), 1e-6);
}
END_TEST
START_TEST(test_s21_tan) {
  ck_assert_double_eq_tol(s21_tan(0.0), tan(0.0), EPS_6);
  ck_assert_double_eq_tol(s21_tan(-0.0), tan(-0.0), EPS_6);
  ck_assert_double_eq_tol(s21_tan(9), tan(9), EPS_6);
  ck_assert_double_eq_tol(s21_tan(-9), tan(-9), EPS_6);
  ck_assert_ldouble_nan(s21_tan(S21_inf));
  ck_assert_ldouble_nan(s21_tan(-S21_inf));
}
END_TEST
START_TEST(test_s21_asin) {
  ck_assert_double_eq_tol(asin(0), s21_asin(0), 1e-6);
  ck_assert_double_eq_tol(asin(1), s21_asin(1), 1e-6);
  ck_assert_double_eq_tol(asin(0.475), s21_asin(0.475), 1e-6);
  ck_assert_double_eq_tol(asin(-0.475), s21_asin(-0.475), 1e-6);
  ck_assert_double_eq_tol(asin(-0.9999999), s21_asin(-0.9999999), 1e-6);
  ck_assert_double_eq_tol(asin(0.9999999), s21_asin(0.9999999), 1e-6);
  ck_assert_double_eq_tol(asin(1e-6), s21_asin(1e-6), 1e-6);
  ck_assert_double_eq_tol(asin(-1e-6), s21_asin(-1e-6), 1e-6);
  ck_assert_double_nan(s21_asin(7));
  ck_assert_double_nan(s21_asin(-7));
  ck_assert_double_nan(s21_asin(S21_inf));
  ck_assert_double_nan(s21_asin(-S21_inf));
  ck_assert_double_nan(s21_asin(S21_nan));
  ck_assert_double_eq_tol(asin(0.7071067811865475244),
                          s21_asin(0.7071067811865475244), 1e-6);
  ck_assert_double_eq_tol(asin(-0.7071067811865475244),
                          s21_asin(-0.7071067811865475244), 1e-6);
  for (double i = -1; i <= 1; i += 0.1) {
    ck_assert_ldouble_eq_tol(asin(i), s21_asin(i), 1e-6);
  }
}
END_TEST
START_TEST(test_s21_acos) {
  ck_assert_double_eq_tol(acos(0), s21_acos(0), 1e-6);
  ck_assert_double_eq_tol(acos(1), s21_acos(1), 1e-6);
  ck_assert_double_eq_tol(acos(0.475), s21_acos(0.475), 1e-6);
  ck_assert_double_eq_tol(acos(-0.475), s21_acos(-0.475), 1e-6);
  ck_assert_double_eq_tol(acos(-0.9999999), s21_acos(-0.9999999), 1e-6);
  ck_assert_double_eq_tol(acos(0.9999999), s21_acos(0.9999999), 1e-6);
  ck_assert_double_eq_tol(acos(1e-6), s21_acos(1e-6), 1e-6);
  ck_assert_double_eq_tol(acos(-1e-6), s21_acos(-1e-6), 1e-6);
  ck_assert_double_nan(s21_acos(7));
  ck_assert_double_nan(s21_acos(-7));
  ck_assert_double_nan(s21_acos(S21_inf));
  ck_assert_double_nan(s21_acos(-S21_inf));
  ck_assert_double_nan(s21_acos(S21_nan));
  ck_assert_double_eq_tol(acos(0.7071067811865475244),
                          s21_acos(0.7071067811865475244), 1e-6);
  ck_assert_double_eq_tol(acos(-0.7071067811865475244),
                          s21_acos(-0.7071067811865475244), 1e-6);
  for (double i = -1; i <= 1; i += 0.1) {
    ck_assert_ldouble_eq_tol(acos(i), s21_acos(i), 1e-6);
  }
}
END_TEST
START_TEST(test_s21_atan) {
  ck_assert_double_eq_tol(atan(0), s21_atan(0), 1e-6);
  ck_assert_double_eq_tol(atan(1), s21_atan(1), 1e-6);
  ck_assert_double_eq_tol(atan(-1), s21_atan(-1), 1e-6);
  ck_assert_double_eq_tol(atan(S21_PI / 2), s21_atan(S21_PI / 2), 1e-6);
  ck_assert_double_eq_tol(atan(-S21_PI / 2), s21_atan(-S21_PI / 2), 1e-6);
  ck_assert_double_eq_tol(atan(475), s21_atan(475), 1e-6);
  ck_assert_double_eq_tol(atan(-475), s21_atan(-475), 1e-6);
  ck_assert_double_eq_tol(atan(475.758), s21_atan(475.758), 1e-6);
  ck_assert_double_eq_tol(atan(-475.758), s21_atan(-475.758), 1e-6);
  ck_assert_double_eq_tol(atan(0.475), s21_atan(0.475), 1e-6);
  ck_assert_double_eq_tol(atan(-0.475), s21_atan(-0.475), 1e-6);
  ck_assert_double_eq_tol(atan(1e-6), s21_atan(1e-6), 1e-6);
  ck_assert_double_eq_tol(atan(-1e-6), s21_atan(-1e-6), 1e-6);
  ck_assert_double_eq_tol(atan(S21_inf), s21_atan(S21_inf), 1e-6);
  ck_assert_double_eq_tol(atan(-S21_inf), s21_atan(-S21_inf), 1e-6);
  ck_assert_double_nan(s21_atan(S21_nan));
}
END_TEST

Suite *suite_s21_test() {
  Suite *s = suite_create("s21_test");

  TCase *is_abs = tcase_create("s21_abs");
  tcase_add_test(is_abs, test_s21_abs);
  suite_add_tcase(s, is_abs);

  TCase *is_fabs = tcase_create("s21_fabs");
  tcase_add_test(is_fabs, test_s21_fabs);
  suite_add_tcase(s, is_fabs);

  TCase *is_ceil = tcase_create("s21_ceil");
  tcase_add_test(is_ceil, test_s21_ceil);
  suite_add_tcase(s, is_ceil);

  TCase *is_floor = tcase_create("s21_floor");
  tcase_add_test(is_floor, test_s21_floor);
  suite_add_tcase(s, is_floor);

  TCase *is_fmod = tcase_create("s21_fmod");
  tcase_add_test(is_fmod, test_s21_fmod);
  suite_add_tcase(s, is_fmod);

  TCase *is_pow = tcase_create("s21_pow");
  tcase_add_test(is_pow, test_s21_pow);
  suite_add_tcase(s, is_pow);

  TCase *is_sqrt = tcase_create("s21_sqrt");
  tcase_add_test(is_sqrt, test_s21_sqrt);
  suite_add_tcase(s, is_sqrt);

  TCase *is_exp = tcase_create("s21_exp");
  tcase_add_test(is_exp, test_s21_exp);
  suite_add_tcase(s, is_exp);

  TCase *is_log = tcase_create("s21_log");
  tcase_add_test(is_log, test_s21_log);
  suite_add_tcase(s, is_log);

  TCase *is_sin = tcase_create("s21_sin");
  tcase_add_test(is_sin, test_s21_sin);
  suite_add_tcase(s, is_sin);

  TCase *is_cos = tcase_create("s21_cos");
  tcase_add_test(is_cos, test_s21_cos);
  suite_add_tcase(s, is_cos);

  TCase *is_tan = tcase_create("s21_tan");
  tcase_add_test(is_tan, test_s21_tan);
  suite_add_tcase(s, is_tan);

  TCase *is_asin = tcase_create("s21_asin");
  tcase_add_test(is_asin, test_s21_asin);
  suite_add_tcase(s, is_asin);

  TCase *is_acos = tcase_create("s21_acos");
  tcase_add_test(is_acos, test_s21_acos);
  suite_add_tcase(s, is_acos);

  TCase *is_atan = tcase_create("s21_atan");
  tcase_add_test(is_atan, test_s21_atan);
  suite_add_tcase(s, is_atan);

  return s;
}