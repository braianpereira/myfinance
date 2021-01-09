//
// Created by Braian on 11/12/2020.
//
#include <stdio.h>
#include "wallet.h"
#include "common.h"
#include "accounts.h"

// Wallet value storage
float WALLET = 0.0;

void walletMenu() {

    int option = 0;

    do {
        limpa();
        printWalletHeader();
        printf("#####################################\n");
        printf("##                                 ##\n");
        printf("## 1 - Inicializar carteira        ##\n");
        printf("## 2 - Adicionar valor             ##\n");
        printf("## 3 - Remover valor               ##\n");
        printf("## 4 - Voltar                      ##\n");
        printf("##                                 ##\n");
        printf("#####################################\n");
        printf("#####################################\n");

        scanf(" %d",&option);

        switch (option) {
            case 1: iniciateWallet(); break;
            case 2: IncrementWallet(); break;
            case 3: decrementWallet(); break;
        }

    } while (option != 4);

}

int updateValor(float valor) {

    WALLET += valor;

    return 0;
}

int setValor(float valor) {

    WALLET = valor;

    return 0;
}

void iniciateWallet() {
    float valor;
    int option;

    getWallet();

    if(WALLET != 0){
        return;
    }

    limpa();

    printf("#############################################################\n");
    printf("#############################################################\n");
    printf("##                                                         ##\n");
    printf("## Ao inicializar todos os movimentos serao descartados!!! ##\n");
    printf("##                                                         ##\n");
    printf("## Se tem certeza digite 1 ou 0 para sair                  ##\n");
    printf("##                                                         ##\n");
    printf("#############################################################\n");
    printf("#############################################################\n");

    scanf("%d", &option);

    if( option == 1){
        printf("Informe o valor atual para a carteira:");
        scanf("%f", &valor);
    }

    setValor(valor);
}

void IncrementWallet() {
    float value;

    printf("Informe o valor: ");
    scanf("%f", &value);

    insertMov(value, "Adicionado pela carteira", 2, getSystemYear(), getSystemMonth(), getSystemDay(), 'S', getSystemYear(), getSystemMonth(), getSystemDay());

}

void decrementWallet() {
    float value;

    printf("Informe o valor: ");
    scanf("%f", &value);

    insertMov(value, "Removido pela carteira", 1, getSystemYear(), getSystemMonth(), getSystemDay(), 'S', getSystemYear(), getSystemMonth(), getSystemDay());
}

void printWalletHeader(){
    printf("#####################################\n");
    printf("## VALOR NA CARTEIRA: R$ %.2f \n",WALLET);
}


int saveWallet(){
    FILE *fp;

    fp = fopen("./db/WALLET.txt", "w");
    if(fp == NULL){
        return 0;
    }

    fprintf(fp, "%f\n", WALLET);

    fclose(fp);

    return 1;
}

int getWallet(){
    FILE *fp;

    fp = fopen("./db/WALLET.txt", "r");
    if(fp == NULL){
        return 0;
    }

    fscanf(fp, "%f\n", &WALLET);

    fclose(fp);

    return 1;
}