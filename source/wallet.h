//
// Created by Braian on 11/12/2020.
//

#ifndef MYFINANCE_WALET_H
#define MYFINANCE_WALET_H

#endif //MYFINANCE_WALET_H

//MENUS
void walletMenu();
void printWalletHeader();

//INITIATE
void iniciateWallet();

//MANIPULATE
int updateValor(float valor);
int setValor(float valor);

//USER INTERACTION
void IncrementWallet();
void decrementWallet();

//DATA PERSISTANCE
int saveWallet();
int getWallet();


