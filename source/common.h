//
// Created by Braian on 11/12/2020.
//

#ifndef MYFINANCE_COMMON_H
#define MYFINANCE_COMMON_H

#endif //MYFINANCE_COMMON_H

//MENU
void menu();

//INITIATE
void iniciateDate();

//UTIL
void limpa();
void pause();
void clearBuffer();

//SWAPPING
void swapChar(char *ptr1, char *ptr2);
void swapInt(int *ptr1, int *ptr2);
void swapFloat(float *ptr1, float *ptr2);

//DATE FUNCTIONS
int getSystemYear();
int getSystemMonth();
int getSystemDay();
void increaseDay(int *vYear, int *vMonth, int *vDay);
void increaseMonth(int *vYear, int *vMonth);
int leapYear(int *vYear);
int dateOverdue(int year, int month, int day);

//STRING FUNCTIONS
int strLength(char *str);
void subStr(char *out, char *in, int posIni, int length);
int strCompare(char *str1, char *str2);
int containsStr(char *haystack, char *needle);
