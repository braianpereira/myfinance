//
// Created by Braian on 11/12/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"
#include "wallet.h"
#include "accounts.h"

int systemDay;
int systemMonth;
int systemYear;

void menu(){

    int option = 0;

    do {
        limpa();
        printWalletHeader();
        printf("#####################################\n");
        printf("##              MENU               ##\n");
        printf("#####################################\n");
        printf("##                                 ##\n");
        printf("## 1 - Gerenciar carteira          ##\n");
        printf("## 2 - Gerenciar contas a pagar    ##\n");
        printf("## 3 - Gerenciar contas a receber  ##\n");
        printf("## 4 - Sair                        ##\n");
        printf("##                                 ##\n");
        printf("#####################################\n");
        printf("#####################################\n");

        scanf(" %d",&option);

        switch (option) {
            case 1: walletMenu(); break;
            case 2: accountsMenu(1); break;
            case 3: accountsMenu(2); break;
        }
    } while (option != 4);
}

void limpa() {
    system("cls");
}

void pause(){
    fflush(stdin);
    getchar();
}

void clearBuffer(){
    scanf("%*[^\n]"); scanf("%*c");
}

void iniciateDate(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    systemDay = tm.tm_mday;
    systemMonth = tm.tm_mon + 1;
    systemYear = tm.tm_year + 1900;
}

void swapChar(char *ptr1, char *ptr2){
    char temp;

    temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void swapInt(int *ptr1, int *ptr2){
    int temp;

    temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void swapFloat(float *ptr1, float *ptr2){
    float temp;

    temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

int getSystemYear(){
    return systemYear;
}

int getSystemMonth(){
    return systemMonth;
}

int getSystemDay(){
    return systemDay;
}

void increaseDay(int *vYear, int *vMonth, int *vDay){
    *(vDay) += 1;

    if (*vDay > 31) {
        if (*vMonth == 1 ||
            *vMonth == 3 ||
            *vMonth == 5 ||
            *vMonth == 7 ||
            *vMonth == 8 ||
            *vMonth == 10 ||
            *vMonth == 12 ) {
            increaseMonth(vYear, vMonth);
            *vDay = 1;
        }
    } else if(*vDay > 30){
        if (*vMonth == 4 ||
            *vMonth == 6 ||
            *vMonth == 9 ||
            *vMonth == 11){
            increaseMonth(vYear, vMonth);
            *vDay = 1;
        }
    } else {
        if ((leapYear(vYear) && *vDay > 29) || (!leapYear(vYear) && *vDay > 28)){
                increaseMonth(vYear, vMonth);
                *vDay = 1;
        }
    }
}

void increaseMonth(int *vYear, int *vMonth){
    if(*vMonth == 12){
        *(vYear) += 1;
        *vMonth = 1;
    } else
        *(vMonth) += 1;
}

int leapYear(int *year){
    if ((*year%4==0 && *year%100!=0) || (*year%400==0))
        return 1;
    else
        return 0;
}
/*
 * Return if a date is orverdued compared with system date
 */
int dateOverdue(int year, int month, int day){
    if(year < getSystemYear())
        return 1;
    else if (year == getSystemYear() && month < getSystemMonth())
        return 1;
    else if (year == getSystemYear() && month == getSystemMonth() && day < getSystemDay())
        return 1;
    else
        return 0;
}

int strLength(char *str){
    int size = 0;

    for (size = 0; *(str+size) |= '\0' ; ++size);

    return size;
}

void subStr(char *out, char *in, int posIni, int length){
    int cont = 0;

    for (int i = posIni; i < posIni+length; ++i) {
        *(out+cont) = *(in+i);
        cont++;
    }
    *(out+cont) = '\0';
}

/*
 * Usage str2 MUST be of minor or equal space allocation e.g. str1[20] and str2[10]
 * return 0 if not equal 1 if it's equal
 */
int strCompare(char *str1, char *str2){
    for (int i = 0; i <= strLength(str2); ++i) {
        if(*(str1+i) != *(str2+i))
            return 0;
    }
    return 1;
}


int containsStr(char *haystack, char *needle){
    char subS[255];

    int haystackSize = strLength(haystack);
    int needleSize = strLength(needle);

    for (int i = 0; i < haystackSize; ++i) {
        subStr(subS, haystack,i, needleSize);

        if (strCompare(subS, needle))
            return 1;
    }

    return 0;
}