#ifndef S21_MATH_H
#define S21_MATH_H

#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define S21_inf 1.0 / 0.0
#define S21_nan 0.0 / 0.0
#define S21_PI 3.14159265358979323846L
#define s21_e 2.71828182845904523536028747135266250L
#define EPS_10 1e-10
#define EPS_6 1e-06

bool is_inf(long double x);
int s21_abs(int x);              
long double s21_acos(double x);  
long double s21_asin(double x);  
long double s21_atan(double x);  

long double s21_ceil(double x);   
long double s21_cos(double x);    
long double s21_exp(double x);    
long double s21_fabs(double x);   
long double s21_floor(double x);  
long int s21_factorial(int number);

long double s21_fmod(double x, double y);      
long double s21_log(double x);                 
long double s21_pow(double base, double exp);  
long double s21_sin(double x);                 
long double s21_sqrt(double x);                
long double s21_tan(double x);                 

int sign(double x);
int is_odd_int(double y);

#endif