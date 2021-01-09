//
// Created by Braian on 11/12/2020.
//

#ifndef MYFINANCE_ACCOUNTS_H
#define MYFINANCE_ACCOUNTS_H

#endif //MYFINANCE_ACCOUNTS_H

//MENUS
void accountsMenu(int type);
void filteredAccountsMenu(int type);

//LISTING
void listAccounts(int accountType);
void listFilteredValEqual(int accountType);
void listFilteredValGreater(int accountType);
void listFilteredValLess(int accountType);
void listFilteredDesc(int accountType);
void listFilteredPaid(int accountType);
void listFilteredNotPaid(int accountType);
void listFilteredOverdue(int accountType);

//INITIATE
void initiateMovements();

//CRUD MOVEMENTS
void removeMov(int pos);
void insertMov(float value, char *desc, int type, int vYear, int vMonth, int vDay, char paid, int pYear, int pMonth, int pDay);  
int insertManyMovs(float value, char *desc, int type, int vYear, int vMonth, int vDay, char paid, int months, int pYear, int pMonth, int pDay); //recursive

//MANIPULATE
void paidAccountOnDate(int type, int pos, int pYear, int pMonth, int pDay);
void payAccountToday(int type, int pos);
void reversingPayment(int type, int pos);
void updateDesc(int type);

//UTILS
int hasAccounts(int accountType, int ctrl); //recursive

//USER INTERACTIONS
void newAccount(int type, int more);
void pay(int type);
void reversing(int type);
void del(int type);


//DATA PERSISTENCE
int readFiles();
int writeFiles();

//DYNAMIC FUNCTIONS
void updateDynFloat(float *, float);
