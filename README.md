# s21_math

Реализация собственной версии математической библиотеки math.h.

## Information

Математические операции на языке Си представляют собой группу функций в стандартной библиотеке языка программирования Си, реализующих основные математические функции. Все функции так или иначе используют числа с плавающей запятой. Различные стандарты C предоставляют различные, хотя и обратно совместимые, наборы функций. Любые функции, которые работают с углами, используют радианы в качестве единицы измерения угла.  

### Обзор некоторых функций "math.h"

| No. | Function | Description |
| --- | -------- | ----------- |
| 1 | `int abs(int x)` | вычисляет абсолютное значение целого числа |
| 2 | `long double acos(double x)` | вычисляет арккосинус |
| 3 | `long double asin(double x)` | вычисляет арксинус |
| 4 | `long double atan(double x)` | вычисляет арктангенс |
| 5 | `long double ceil(double x)` | возвращает ближайшее целое число, не меньшее заданного значения |
| 6 | `long double cos(double x)` | вычисляет косинус |
| 7 | `long double exp(double x)` | возвращает значение e, возведенное в заданную степень |
| 8 | `long double fabs(double x)` | вычисляет абсолютное значение числа с плавающей точкой |
| 9 | `long double floor(double x)` | возвращает ближайшее целое число, не превышающее заданное значение |
| 10 | `long double fmod(double x, double y)` | остаток операции деления с плавающей точкой |
| 11 | `long double log(double x)` | вычисляет натуральный логарифм |
| 12 | `long double pow(double base, double exp)` | возводит число в заданную степень |
| 13 | `long double sin(double x)` | вычисляет синус |
| 14 | `long double sqrt(double x)` | вычисляет квадратный корень |
| 15 | `long double tan(double x)` | вычисляет тангенс |  


## Реализация функций библиотеки math.h

Необходимо реализовать функции библиотеки math.h (только те, что непосредственно описаны выше):

- Библиотека должна быть разработана на языке Си стандарта C11 с использованием компиятора gcc 
- Код библиотеки должен находиться в папке src в ветке develop  
- Не использовать устаревшие и выведенные из употребления конструкции языка и библиотечные функции. Обращать внимания на пометки legacy и obsolete в официальной документации по языку и используемым библиотекам. Ориентироваться на стандарт POSIX.1-2017
- При написании кода необходимо придерживаться Google Style
- Оформить решение как статическую библиотеку с названием *s21_math.a* (с заголовочным файлом s21_math.h)
- Библиотека должна быть разработана в соответствии с принципами структурного программирования, должно быть исключено дублирование кода
- Перед каждой функцией использовать префикс s21_
- Подготовить полное покрытие unit-тестами функций библиотеки c помощью библиотеки Check
- Unit-тесты должны проверять результаты работы вашей реализации путём сравнения ее с реализацией стандартной библиотеки math.h
- Unit-тесты должны покрывать не менее 80% каждой функции
- В цели gcov_report должен формироваться отчёт gcov в виде html страницы. Для этого unit-тесты должны запускаться с флагами gcov  
- Предусмотреть Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_math.a, gcov_report)  
- Запрещено копирование реализации и использование стандартной библиотеки math.h везде, кроме unit-тестов  
- Необходимо соблюсти логику работы стандартной библиотеки (в части проверок, работы с памятью и поведения в нештатных ситуациях - здесь помогут тесты)
- Общая проверяемая точность - 16 значащих цифр
- Проверяемая точность дробной части - максимум 6 знаков после запятой.
