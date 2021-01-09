#include <stdio.h>
#include "common.h"
#include "wallet.h"
#include "accounts.h"

int main() {
    
    iniciateDate();
    iniciateWallet();
	initiateMovements();

    menu();

    saveWallet();
    writeFiles();

    return 0;
}

