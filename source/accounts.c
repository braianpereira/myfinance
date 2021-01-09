//
// Created by Braian on 11/12/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "accounts.h"
#include "common.h"
#include "wallet.h"

// Data storage for accounts
float *movValue;
char movDesc[255][255];
int movType[255];
int movVencYear[255];
int movVencMonth[255];
int movVencDay[255];
int movPayYear[255];
int movPayMonth[255];
int movPayDay[255];
char movPaid[255];
int movement;

void accountsMenu(int type){
    int option = 0;
    char conta[38];

    if(type == 1)
        strcpy(conta,"##         CONTAS A PAGAR          ##");
    else
        strcpy(conta,"##        CONTAS A RECEBER         ##");

    do {
        limpa();
        printWalletHeader();
        printf("#####################################\n");
        printf("%s\n", conta);
        printf("#####################################\n");
        printf("##                                 ##\n");
        printf("## 1 - Listar contas               ##\n");
        printf("## 2 - Filtrar contas              ##\n");
        printf("## 3 - Lancar uma conta            ##\n");
        printf("## 4 - Lancar varias contas        ##\n");
        printf("## 5 - Pagar conta                 ##\n");
        printf("## 6 - Estornar conta              ##\n");
        printf("## 7 - Remover conta               ##\n");
        printf("## 8 - Alterar descricao           ##\n");
        printf("## 9 - Voltar                      ##\n");
        printf("##                                 ##\n");
        printf("#####################################\n");
        printf("#####################################\n");

        scanf(" %d",&option);

        switch (option) {
            case 1: listAccounts(type); pause(); break;
            case 2: filteredAccountsMenu(type); break;
            case 3: newAccount(type, 0); break;
            case 4: newAccount(type, 1); break;
            case 5: pay(type); break;
            case 6: reversing(type); break;
            case 7: del(type); break;
            case 8: updateDesc(type); break;
        }
    } while (option != 9);
}

void filteredAccountsMenu(int type){
    int option = 0;
    char conta[38];

    if(type == 1)
        strcpy(conta,"##     CONTAS A PAGAR - FILTRO     ##");
    else
        strcpy(conta,"##    CONTAS A RECEBER - FILTRO    ##");

    do {
        limpa();
        printWalletHeader();
        printf("#####################################\n");
        printf("%s\n", conta);
        printf("#####################################\n");
        printf("##                                 ##\n");
        printf("## 1 - Valor igual a               ##\n");
        printf("## 2 - Valor maior ou igual que    ##\n");
        printf("## 3 - Valor menor ou igual que    ##\n");
        printf("## 4 - Descricao contem            ##\n");
        printf("## 5 - Pagas                       ##\n");
        printf("## 6 - Nao pagas                   ##\n");
        printf("## 7 - Atrasadas                   ##\n");
        printf("## 8 - Voltar                      ##\n");
        printf("##                                 ##\n");
        printf("#####################################\n");
        printf("#####################################\n");

        scanf(" %d",&option);

        switch (option) {
            case 1: listFilteredValEqual(type); pause(); break;
            case 2: listFilteredValGreater(type); pause(); break;
            case 3: listFilteredValLess(type); pause(); break;
            case 4: listFilteredDesc(type); pause(); break;
            case 5: listFilteredPaid(type); pause(); break;
            case 6: listFilteredNotPaid(type); pause(); break;
            case 7: listFilteredOverdue(type); pause(); break;
        }
    } while (option != 8);
}

void initiateMovements(){
    movement = 0;

    readFiles();

    if(movement>0){
        return;
    }


    for (int i = 0; i < 255; ++i) {
        movDesc[i][0] = '\0';
        movType[i] = 0;
        movVencYear[i] = 0;
        movVencMonth[i] = 0;
        movVencDay[i] = 0;
        movPayYear[i] = 0;
        movPayMonth[i] = 0;
        movPayDay[i] = 0;
    }

    movPaid[0] = '\0';
    movement = 1;
}

void removeMov(int pos){
    for (int i = pos; i < movement; ++i) {

        swapFloat((movValue+i),(movValue+i+1));
        strcpy(movDesc[i], movDesc[i+1]);
        swapInt(&movType[i], &movType[i+1]);
        swapInt(&movVencYear[i], &movVencYear[i+1]);
        swapInt(&movVencMonth[i], &movVencMonth[i+1]);
        swapInt(&movVencDay[i], &movVencDay[i+1]);
        swapInt(&movPayYear[i], &movPayYear[i+1]);
        swapInt(&movPayMonth[i], &movPayMonth[i+1]);
        swapInt(&movPayDay[i], &movPayDay[i+1]);
        swapChar(movPaid+i, movPaid+i+1);
    }

    movement--;

    movValue = (float *) realloc (movValue, movement * sizeof(float));
}

void insertMov(float value, char *desc, int type, int vYear, int vMonth, int vDay, char paid, int pYear, int pMonth, int pDay){

    updateDynFloat(movValue, value);

    strcpy(movDesc[movement-1], desc);
    movType[movement-1] = type;
    movVencYear[movement-1] = vYear;
    movVencMonth[movement-1] = vMonth;
    movVencDay[movement-1] = vDay;

    if(paid == 'S'){
        movPayYear[movement-1] = pYear;
        movPayMonth[movement-1] = pMonth;
        movPayDay[movement-1] = pDay;

        if(type == 1)
            updateValor(-value);
        else
            updateValor(value);
    }
    swapChar(movPaid+movement-1, &paid);

    movement++;
}

int insertManyMovs(float value, char *desc, int type, int vYear, int vMonth, int vDay, char paid, int months, int pYear, int pMonth, int pDay){
    if(months > 0){
        insertMov(value, desc, type, vYear, vMonth, vDay, paid, pYear, pMonth, pDay);
        increaseMonth(&vYear, &vMonth);

        return insertManyMovs(value, desc, type, vYear, vMonth, vDay, paid, months-1, pYear, pMonth, pDay);
    } else
        return 0;
}

void paidAccountOnDate(int type, int pos, int pYear, int pMonth, int pDay){
    movPaid[pos] = 'S';
    movPayYear[pos] = pYear;
    movPayMonth[pos] = pMonth;
    movPayDay[pos] = pDay;

    if (type == 1)
        updateValor(-*(movValue+pos));
    else
        updateValor(*(movValue+pos));
}

void payAccountToday(int type, int pos){
    paidAccountOnDate(type, pos, getSystemYear(), getSystemMonth(), getSystemDay());
}

void reversingPayment(int type, int pos){
    movPaid[pos] = 'N';
    movPayYear[pos] = 0;
    movPayMonth[pos] = 0;
    movPayDay[pos] = 0;

    if(type == 1)
        updateValor(*(movValue+pos));
    else
        updateValor(-*(movValue+pos));
}

void listAccounts(int accountType){
    float total = 0;
    
    limpa();
    
    if (hasAccounts(accountType, 0)){
        
        printf("Codigo |     Valor     |  Data venc  | Pago |  Data pag  | Descricao \n");
        
        for (int i = 0; i < movement; ++i) {
            if(movType[i] == accountType) {
                printf(" %03d   |R$ %12.2f| %02d/%02d/%d  |  %c   | %02d/%02d/%04d | %s",
                       i, *(movValue+i),movVencDay[i], movVencMonth[i], movVencYear[i], movPaid[i],
                       movPayDay[i], movPayMonth[i], movPayYear[i], movDesc[i]);
                total += *(movValue+i);
            }
        }
        
        printf("\nTotal  |R$ %12.2f|", total);
        
    }else{
        printf("Sem contas para listar!");
    }
}

void listFilteredValEqual(int accountType){
    float value, total = 0;

    printf("Informe o valor para filtrar: ");
    scanf("%f", &value);

    limpa();

    if (hasAccounts(accountType, 0)){

        printf("Codigo |     Valor     |  Data venc  | Pago |  Data pag  | Descricao \n");

        for (int i = 0; i < movement; ++i) {
            if(movType[i] == accountType && *(movValue+i) == value) {
                printf(" %03d   |R$ %12.2f| %02d/%02d/%d  |  %c   | %02d/%02d/%04d | %s",
                       i, *(movValue+i),movVencDay[i], movVencMonth[i], movVencYear[i], movPaid[i],
                       movPayDay[i], movPayMonth[i], movPayYear[i], movDesc[i]);
                total += *(movValue+i);
            }
        }

        printf("\nTotal  |R$ %12.2f|", total);
        
    }else{
        printf("Sem contas para listar!");
    }
}

void listFilteredValGreater(int accountType){
    float value, total = 0;

    printf("Informe o valor para filtrar: ");
    scanf("%f", &value);

    limpa();

    if (hasAccounts(accountType, 0)){

        printf("Codigo |     Valor     |  Data venc  | Pago |  Data pag  | Descricao \n");

        for (int i = 0; i < movement; ++i) {
            if(movType[i] == accountType && *(movValue+i) >= value) {
                printf(" %03d   |R$ %12.2f| %02d/%02d/%d  |  %c   | %02d/%02d/%04d | %s",
                       i, *(movValue+i),movVencDay[i], movVencMonth[i], movVencYear[i], movPaid[i],
                       movPayDay[i], movPayMonth[i], movPayYear[i], movDesc[i]);
                total += *(movValue+i);
            }
        }

        printf("\nTotal  |R$ %12.2f|", total);
        
    }else{
        printf("Sem contas para listar!");
    }
}

void listFilteredValLess(int accountType){
    float value, total = 0;

    printf("Informe o valor para filtrar: ");
    scanf("%f", &value);

    limpa();

    if (hasAccounts(accountType, 0)){

        printf("Codigo |     Valor     |  Data venc  | Pago |  Data pag  | Descricao \n");

        for (int i = 0; i < movement; ++i) {
            if(movType[i] == accountType && *(movValue+i) <= value) {
                printf(" %03d   |R$ %12.2f| %02d/%02d/%d  |  %c   | %02d/%02d/%04d | %s",
                       i, *(movValue+i),movVencDay[i], movVencMonth[i], movVencYear[i], movPaid[i],
                       movPayDay[i], movPayMonth[i], movPayYear[i], movDesc[i]);
                total += *(movValue+i);
            }
        }

        printf("\nTotal  |R$ %12.2f|", total);
        
    }else{
        printf("Sem contas para listar!");
    }
}

void listFilteredDesc(int accountType){
    char word[255];
    float total = 0;

    printf("Informe a palavra para filtrar: ");
    clearBuffer();
    scanf("%s", word);

    limpa();

    if (hasAccounts(accountType, 0)){

        printf("Codigo |     Valor     |  Data venc  | Pago |  Data pag  | Descricao \n");

        for (int i = 0; i < movement; ++i) {
            if(movType[i] == accountType && containsStr(movDesc[i], word)) {
                printf(" %03d   |R$ %12.2f| %02d/%02d/%d  |  %c   | %02d/%02d/%04d | %s",
                       i, *(movValue+i),movVencDay[i], movVencMonth[i], movVencYear[i], movPaid[i],
                       movPayDay[i], movPayMonth[i], movPayYear[i], movDesc[i]);
                total += *(movValue+i);
            }
        }

        printf("\nTotal  |R$ %12.2f|", total);
    }else{
        printf("Sem contas para listar!");
    }
}

void listFilteredPaid(int accountType){
    float total = 0;

    limpa();

    if (hasAccounts(accountType, 0)){

        printf("Codigo |     Valor     |  Data venc  | Pago |  Data pag  | Descricao \n");

        for (int i = 0; i < movement; ++i) {
            if(movType[i] == accountType && movPaid[i] == 'S') {
                printf(" %03d   |R$ %12.2f| %02d/%02d/%d  |  %c   | %02d/%02d/%04d | %s",
                       i, *(movValue+i),movVencDay[i], movVencMonth[i], movVencYear[i], movPaid[i],
                       movPayDay[i], movPayMonth[i], movPayYear[i], movDesc[i]);
                total += *(movValue+i);
            }
        }

        printf("\nTotal  |R$ %12.2f|", total);
    }else{
        printf("Sem contas para listar!");
    }
}

void listFilteredNotPaid(int accountType){
    float total = 0;

    limpa();

    if (hasAccounts(accountType, 0)){

        printf("Codigo |     Valor     |  Data venc  | Pago |  Data pag  | Descricao \n");

        for (int i = 0; i < movement; ++i) {
            if(movType[i] == accountType && movPaid[i] == 'N') {
                printf(" %03d   |R$ %12.2f| %02d/%02d/%d  |  %c   | %02d/%02d/%04d | %s",
                       i, *(movValue+i),movVencDay[i], movVencMonth[i], movVencYear[i], movPaid[i],
                       movPayDay[i], movPayMonth[i], movPayYear[i], movDesc[i]);
                total += *(movValue+i);
            }
        }

        printf("\nTotal  |R$ %12.2f|", total);
        
    }else{
        printf("Sem contas para listar!");
    }
}

void listFilteredOverdue(int accountType){
    float total = 0;

    limpa();

    if (hasAccounts(accountType, 0)){

        printf("Codigo |     Valor     |  Data venc  | Pago |  Data pag  | Descricao \n");

        for (int i = 0; i < movement; ++i) {
            if(movType[i] == accountType && dateOverdue(movVencYear[i], movVencMonth[i], movVencDay[i])) {
                printf(" %03d   |R$ %12.2f| %02d/%02d/%d  |  %c   | %02d/%02d/%04d | %s",
                       i, *(movValue+i),movVencDay[i], movVencMonth[i], movVencYear[i], movPaid[i],
                       movPayDay[i], movPayMonth[i], movPayYear[i], movDesc[i]);
                total += *(movValue+i);
            }
        }

        printf("\nTotal  |R$ %12.2f|", total);

    }else{
        printf("Sem contas para listar!");
    }
}

void newAccount(int type, int more){
    float value;
    int vYear, vMonth, vDay, pYear = 0, pMonth = 0, pDay = 0, months;
    char paid = 'N', desc[255], op;

    printf("Informe o valor: ");
    scanf("%f", &value);

    printf("Data venc hoje (S/N)? ");
    clearBuffer();
    scanf("%c",&op);

    if(op == 'S' || op == 's'){
        vDay = getSystemDay();
        vMonth = getSystemMonth();
        vYear = getSystemYear();
    } else {
        printf("Informe o dia de venc: ");
        scanf("%d", &vDay);

        printf("Informe o mes de venc: ");
        scanf("%d", &vMonth);

        printf("Informe o ano de venc: ");
        scanf("%d", &vYear);

    }

    printf("Ja esta pago (S/N)?");
    clearBuffer();
    scanf("%c",&paid);

    if(paid == 'S' || paid == 's'){
        paid = 'S';

        printf("Data pag hoje (S/N)? ");
        clearBuffer();
        scanf("%c",&op);

        if (op == 'S' || op == 's'){
            pDay = getSystemDay();
            pMonth = getSystemMonth();
            pYear = getSystemYear();
        } else {
            printf("Informe o dia de pag: ");
            scanf("%d", &pDay);

            printf("Informe o mes de pag: ");
            scanf("%d", &pMonth);

            printf("Informe o ano de pag: ");
            scanf("%d", &pYear);
        }


    } else {
        paid = 'N';
    }

    printf("Informe uma descricao para o movimento: ");
    clearBuffer();
    scanf("%[^\n]",desc);
    strcat(desc,"\n");

    if(more == 0)
        insertMov(value, desc, type, vYear, vMonth, vDay, paid, pYear, pMonth, pDay);
    else {
        printf("Quantos meses(atual incluso): ");
        scanf("%d",&months);

        insertManyMovs(value, desc, type, vYear, vMonth, vDay, paid, months, pYear, pMonth, pDay);
    }

    printf("\nConta inserida com sucesso!");
    pause();
}

void pay(int type){
    char op;
    int cod, pDay, pMonth, pYear;

    listAccounts(type);

    printf("\nInforme o codigo da conta para pagar: ");
    scanf("%d", &cod);

    printf("Data de pagamento no dia de hoje (S/N)? ");
    clearBuffer();
    scanf("%c", &op);

    if(op == 'S' || op == 's'){
        payAccountToday(type, cod);
    } else {
        printf("Informe o dia de pag: ");
        scanf("%d", &pDay);

        printf("Informe o mes de pag: ");
        scanf("%d", &pMonth);

        printf("Informe o ano de pag: ");
        scanf("%d", &pYear);

        paidAccountOnDate(type, cod, pYear, pMonth, pDay);
    }

    printf("\n Conta paga com sucesso!");
    pause();

}

void reversing(int type){
    int cod;

    listAccounts(1);

    printf("\nInforme o codigo da conta para estornar: ");
    scanf("%d", &cod);

    reversingPayment(type, cod);

    printf("\nEstornado com sucesso!");
    pause();
}

void del(int type){
    int cod;
    char op;

    listAccounts(type);

    printf("\nInforme o codigo da conta para remover: ");
    scanf("%d", &cod);

    if(movPaid[cod] == 'S'){
        printf("\nConta esta paga, para remover eh preciso estornar!");
        printf("\nEstornar conta agora (S/N)? ");
        clearBuffer();
        scanf("%c", &op);

        if(op == 'S' || op == 's')
            reversingPayment(type, cod);
        else {
            printf("\nProcesso cancelado!");
            pause();
            return;
        }
    }
    removeMov(cod);

    printf("\nRemovida com sucesso!");
    pause();
}

int hasAccounts(int accountType, int ctrl){
    if(ctrl < movement-1)
        return (movType[ctrl] == accountType) + hasAccounts(accountType, ctrl+1);
    else
        return 0;
}

void updateDesc(int type){
    int cod;
    char desc[255];

    listAccounts(type);

    printf("\nInforme a codigo da conta para alterar a descricao: ");
    scanf("%d",&cod);

    printf("\nInforme a nova descricao: ");
    clearBuffer();
    scanf("%[^\n]", desc);

    strcpy(movDesc[cod], desc);

    printf("\nDescricao alterada com sucesso!");

    pause();
}

int readFiles(){
    FILE *fp;
    int linha, iResult;
    char *cResult;

    //movValues
    linha = 1;

    fp = fopen("./db/movValue.txt", "r");
    if(fp==NULL){
        return 0;
    }

    movValue = (float *) malloc(linha * sizeof(float));
    while( (iResult = fscanf(fp, "%f\n", (movValue+linha-1))) != EOF){

        linha++;

        movValue = (float *) realloc(movValue, linha * sizeof(float));
    }

    fclose(fp);

    //movDesc
    linha = 0;

    fp = fopen("./db/movDesc.txt", "r");
    if(fp==NULL){
        return 0;
    }
    while( (cResult = fgets(movDesc[linha], 255, fp)) != NULL ){
        linha++;
    }

    fclose(fp);

    
    //movType
    linha = 0;

    fp = fopen("./db/movType.txt", "r");
    if(fp==NULL){
        return 0;
    }
    while( (iResult = fscanf(fp, "%i\n", &movType[linha])) != EOF ){
        linha++;
    }

    fclose(fp);

    //movVencYear
    linha = 0;

    fp = fopen("./db/movVencYear.txt", "r");
    if(fp==NULL){
        return 0;
    }
    while( (iResult = fscanf(fp, "%i\n", &movVencYear[linha])) != EOF ){
        linha++;
    }

    fclose(fp);

    //movVencMonth
    linha = 0;

    fp = fopen("./db/VencMonth.txt", "r");
    if(fp==NULL){
        return 0;
    }
    while( (iResult = fscanf(fp, "%i\n", &movVencMonth[linha])) != EOF ){
        linha++;
    }

    fclose(fp);

    //movVencDay
    linha = 0;

    fp = fopen("./db/movVencDay.txt", "r");
    if(fp==NULL){
        return 0;
    }
    while( (iResult = fscanf(fp, "%i\n", &movVencDay[linha])) != EOF ){
        linha++;
    }

    fclose(fp);

    //movPayYear
    linha = 0;

    fp = fopen("./db/movPayYear.txt", "r");
    if(fp==NULL){
        return 0;
    }
    while( (iResult = fscanf(fp, "%i\n", &movPayYear[linha])) != EOF ){
        linha++;
    }

    fclose(fp);

    //movPayMonth
    linha = 0;

    fp = fopen("./db/movPayMonth.txt", "r");
    if(fp==NULL){
        return 0;
    }
    while( (iResult = fscanf(fp, "%i\n", &movPayMonth[linha])) != EOF ){
        linha++;
    }

    fclose(fp);

    //movPayDay
    linha = 0;

    fp = fopen("./db/movPayDay.txt", "r");
    if(fp==NULL){
        return 0;
    }
    while( (iResult = fscanf(fp, "%i\n", &movPayDay[linha])) != EOF ){
        linha++;
    }

    fclose(fp);

    //movPaid
    linha = 0;

    fp = fopen("./db/movPaid.txt", "r");
    if(fp==NULL){
        return 0;
    }
    while( (movPaid[linha] = fgetc(fp)) != EOF ){
        linha++;
    }

    linha++;

    movement = linha;

    return 1;
}


int writeFiles(){
    FILE *fp;

    //movValues
    fp = fopen("./db/movValue.txt", "w");
    if(fp==NULL){
        return 0;
    }

    for (int i = 0; i < movement; ++i){
        fprintf(fp, "%f\n", *(movValue+i));
    }

    fclose(fp);

    //movDesc
    fp = fopen("./db/movDesc.txt", "w");
    if(fp==NULL){
        return 0;
    }

    for (int i = 0; i < movement; ++i){
        fputs(movDesc[i], fp);
    }

    fclose(fp);

    
    //movType
    fp = fopen("./db/movType.txt", "w");
    if(fp==NULL){
        return 0;
    }
    for (int i = 0; i < movement; ++i){
         fprintf(fp, "%i\n", movType[i]);
    }

    fclose(fp);

    //movVencYear
    fp = fopen("./db/movVencYear.txt", "w");
    if(fp==NULL){
        return 0;
    }
    for (int i = 0; i < movement; ++i){
         fprintf(fp, "%i\n", movVencYear[i]);
    }

    fclose(fp);

    //movVencMonth
    fp = fopen("./db/VencMonth.txt", "w");
    if(fp==NULL){
        return 0;
    }
    for (int i = 0; i < movement; ++i){
         fprintf(fp, "%i\n", movVencMonth[i]);
    }

    fclose(fp);

    //movVencDay
    fp = fopen("./db/movVencDay.txt", "w");
    if(fp==NULL){
        return 0;
    }
    for (int i = 0; i < movement; ++i){
         fprintf(fp, "%i\n", movVencDay[i]);
    }

    fclose(fp);

    //movPayYear
    fp = fopen("./db/movPayYear.txt", "w");
    if(fp==NULL){
        return 0;
    }
    for (int i = 0; i < movement; ++i){
         fprintf(fp, "%i\n", movPayYear[i]);
    }

    fclose(fp);

    //movPayMonth
    fp = fopen("./db/movPayMonth.txt", "w");
    if(fp==NULL){
        return 0;
    }
    for (int i = 0; i < movement; ++i){
         fprintf(fp, "%i\n", movPayMonth[i]);
    }

    fclose(fp);

    //movPayDay
    fp = fopen("./db/movPayDay.txt", "w");
    if(fp==NULL){
        return 0;
    }
    for (int i = 0; i < movement; ++i){
         fprintf(fp, "%i\n", movPayDay[i]);
    }

    fclose(fp);

    //movPaid
    fp = fopen("./db/movPaid.txt", "w");
    if(fp==NULL){
        return 0;
    }
    for (int i = 0; i < movement; ++i){
         fputc(movPaid[i], fp);
    }

    fclose(fp);

    return 1;
}

void updateDynFloat(float *dynArr, float value){

    dynArr = (float *) realloc(dynArr, movement * sizeof(float));

    *(dynArr+movement-1) = value;
}

