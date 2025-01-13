//Το προγραμμα δημιουργηθηκε με τη χρηση του VS Code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

//Structs
typedef struct date {
    int dd;
    int mm;
    int yyyy;
} Date;

typedef struct transaction {
    char transaction_id[35];
    Date transaction_date;
    float transaction_amount;
    char transaction_executor[21];
    char transaction_receiver[21];
} Transaction;

typedef struct user {
    char username[21];
    char password[21];
    char name[21];
    char surname[21];
    char card_id[17];
    char card_owner[41];
    char card_cvv[4];
    int next_transaction_number;
    float wallet;
    Transaction latest_transactions[5];
    int number_of_transactions; 
    // ^ Number of transactions that this user was involved
} User;

struct ebanking_system {
    Transaction system_latest_transactions[20]; // Last 20 Transactions for all the System  
    User system_users[50]; // Allow up to 50 users in the system
    int amount_of_users; // Must be initialized as zero (amount of currently registered users)
    int number_of_transactions; // Must be initialized as zero (number of current transactions executed)
} eBankingSystem;

struct public_transactions {
 char transaction_name[23];
 char transaction_provider[21];
 char transaction_code[4];
 int transaction_cost;
};

//Function Prototypes
void main_menu_func(); //DIKIA MOY
void homepage_menu();
void customer_registration();
int valid_password(char password[21]);
int valid_cvv(char card_cvv[4]);
void erase_user_data(int p); //DIKIA MOY
void customer_dashboard_menu();
void customer_login();
int get_username_position(char username[21]);
void initialize_available_transactions();
void view_available_transactions();
void execute_transaction(int user_position);
int get_provider_position(char provider_code[4]);
Date generate_date();
char *generate_transaction_id(Date t_date, char executor[21], int transaction_number);
void change_my_password(int user_position);
void add_transaction_to_user(int user_position, Transaction t);
void add_transaction_to_system(Transaction t);
void admin_login();
void admin_dashboard_menu();
void print_transaction(Transaction t);
void view_last_transactions();
void search_user_menu();
void find_user();
void print_cipher(char password[21]);

//GLOBALS
char sCAR[] = "CAR", sIDC[] = "IDC", sPPT[] = "PPT", sTFF[] = "TFF", sEGC[] = "EGC", sTMR[] = "TMR";
struct public_transactions *g_availableTransactions;
int f_u = -1, r_u = -1, f_s = -1, r_s = -1, admin_next_trans = 0;

int main(int argc, char const *argv[]){
    struct public_transactions availableTransactions[6];
    g_availableTransactions = availableTransactions;

    eBankingSystem.amount_of_users = 0;
    eBankingSystem.number_of_transactions = 0;

    main_menu_func();

    return 0;
}

void main_menu_func(){
    int ep;

    do{
        do{     //MENU
            homepage_menu();
            printf("\nChoice: ");
            scanf(" %d", &ep);
            if (!(ep == 0 || ep == 1 || ep == 2 || ep == 3)){
                printf("Option does not exist. Please try again.\n");
                //idea gia sleep(), clear kai emfanish to menu ksana meta
            }   
        } while (!(ep == 0 || ep == 1 || ep == 2 || ep == 3));

        switch (ep){
        case 1:
            if (eBankingSystem.amount_of_users < 50){
                customer_registration();
                eBankingSystem.amount_of_users++;
            }
            else{
                printf("The banking system is full and can't handle any other new customer");
            }
            
            break;

        case 2:
            customer_login();

            break;

        case 3:
            admin_login();

            break;
        
        default:
            return; //Pisw sth main

            break;
        }
        
    }while(ep != 0);
}

void homepage_menu(){
    printf("-DS Bank Menu-\n\n");
    printf("0. Exit\n");
    printf("1. Customer Registration\n");
    printf("2. Customer Login\n");
    printf("3. Admin Login\n");
}

void customer_registration(){
    char password[21], verify_password[21];
    int lives = 3, flag = 0, pl_sp = 0, isValid;

    system("cls");
    printf("-Customer Registration-\n\n");

    do{     //ELEGXOS EGGUROTHTAS TOY USERNAME
        printf("Username: ");
        scanf(" %s", &eBankingSystem.system_users[eBankingSystem.amount_of_users].username);

        //AN TO USERNAME EINAI KAPOIO AP TA DESMEUMENA ONOMATA SYNALLAGWN
        if ((strcmp(eBankingSystem.system_users[eBankingSystem.amount_of_users].username, sCAR) == 0) || (strcmp(eBankingSystem.system_users[eBankingSystem.amount_of_users].username, sIDC) == 0) || (strcmp(eBankingSystem.system_users[eBankingSystem.amount_of_users].username, sPPT) == 0) || (strcmp(eBankingSystem.system_users[eBankingSystem.amount_of_users].username, sTFF) == 0) || (strcmp(eBankingSystem.system_users[eBankingSystem.amount_of_users].username, sEGC) == 0) || (strcmp(eBankingSystem.system_users[eBankingSystem.amount_of_users].username, sTMR) == 0)){
            printf("You can't use this as a username. Please choose a different username\n");
            continue;
        }
        
        //AN TO USERNAME POU 8ELEI NA BALEI YPARXEI HDH
        for (int i = 0; i <= eBankingSystem.amount_of_users; i++){
            if(strcmp(eBankingSystem.system_users[eBankingSystem.amount_of_users].username, eBankingSystem.system_users[i].username) == 0){
                if (eBankingSystem.amount_of_users != i){
                    flag = 1;
                    printf("This username is already taken. Please choose a different username\n");
                }
                             
            }
        }
    }while((strcmp(eBankingSystem.system_users[eBankingSystem.amount_of_users].username, sCAR) == 0) || (strcmp(eBankingSystem.system_users[eBankingSystem.amount_of_users].username, sIDC) == 0) || (strcmp(eBankingSystem.system_users[eBankingSystem.amount_of_users].username, sPPT) == 0) || (strcmp(eBankingSystem.system_users[eBankingSystem.amount_of_users].username, sTFF) == 0) || (strcmp(eBankingSystem.system_users[eBankingSystem.amount_of_users].username, sEGC) == 0) || (strcmp(eBankingSystem.system_users[eBankingSystem.amount_of_users].username, sTMR) == 0) || (flag == 1));
    
    printf("*Note: the password must contain at least 7 characters, one <<!>> or <<?>> and a number.\n");
    do{     //ELEGXOS EGGYROTHTAS TOU PASSWORD
        
        printf("Password: ");
        scanf(" %s", &password);

        isValid = valid_password(password);

        if (isValid == 0){
            lives--;
            printf(" Please enter another password.\nYou have %d more attempts\n\n", lives);
        }            
    } while ((isValid == 0) && (lives > 0));

    if (lives == 0){
        printf("You have surpassed your available attempts.\nPress Enter to return to the main menu\n");
        fflush(stdin);
        getc(stdin);
        erase_user_data(eBankingSystem.amount_of_users);
        system("cls");
        return;
    }

    lives = 3;
    
    do{    //ELEGXOS GIA TA 2 PASSWORDS NA EINAI ISA
        printf("Verify Password: ");
        scanf(" %s", &verify_password);
        if (strcmp(password, verify_password) != 0){
            lives--;
            printf("The two passwords doesn't match. Please try again, you have %d more attempts\n\n", lives);
        }
    } while(strcmp(password, verify_password) != 0 && lives > 0);
    
    if (lives == 0){
        printf("You have surpassed your available attempts.\nPress Enter to return to the main menu\n");
        fflush(stdin);
        getc(stdin);
        erase_user_data(eBankingSystem.amount_of_users);
        system("cls");
        return;
    }
        
    strcpy(eBankingSystem.system_users[eBankingSystem.amount_of_users].password, password);

    lives = 3;

    system("cls");
    printf("-Customer Registration-\n\n");
    printf("Account credentials entered successfully\nNow it's time to fill out your personal information\n");
    printf("Enter your name: ");
    scanf(" %s", &eBankingSystem.system_users[eBankingSystem.amount_of_users].name);
    printf("Enter your surname: ");
    scanf(" %s", &eBankingSystem.system_users[eBankingSystem.amount_of_users].surname);
    strcpy(eBankingSystem.system_users[eBankingSystem.amount_of_users].card_owner, eBankingSystem.system_users[eBankingSystem.amount_of_users].name);
    strcat(eBankingSystem.system_users[eBankingSystem.amount_of_users].card_owner, eBankingSystem.system_users[eBankingSystem.amount_of_users].surname);

    do{     //ELEGXOS EGGYROTHTAS TOY CARD NUMBER
        printf("Enter Card ID: ");
        scanf(" %s", &eBankingSystem.system_users[eBankingSystem.amount_of_users].card_id);
        //AN EXEI SWSTO MHKOS
        if (strlen(eBankingSystem.system_users[eBankingSystem.amount_of_users].card_id) != 16){
            lives--;
            printf("The card number must be 16 digits long.\nYou have %d more attempts\n\n", lives);
            continue;
        }

        flag = 0;

        //AN EXEI KAPOION XARAKTHRA MESA
        for (int i = 0; i < 16; i++){
            if (!isdigit(eBankingSystem.system_users[eBankingSystem.amount_of_users].card_id[i])){
                lives--;
                printf("The card number must not contain any characters.\nYou have %d more attempts\n\n", lives);
                flag = 1;
                break;
            }
            
        }
        

    } while ((strlen(eBankingSystem.system_users[eBankingSystem.amount_of_users].card_id) != 16 || (flag == 1)) && lives > 0);

    if (lives == 0){
        printf("You have surpassed your available attempts.\nPress Enter to return to the main menu\n");
        fflush(stdin);
        getc(stdin);
        erase_user_data(eBankingSystem.amount_of_users);
        system("cls");
        return;
    }

    lives = 3;

    do{     //ELEGXOS EGGYROTHTAS TOU CVV
        printf("Enter CVV / CVC: ");
        scanf(" %s", &eBankingSystem.system_users[eBankingSystem.amount_of_users].card_cvv);
        
        isValid = valid_cvv(eBankingSystem.system_users[eBankingSystem.amount_of_users].card_cvv);

        if (isValid == 0){
            lives--;
            printf("Please enter another CVV / CVC.\nYou have %d more attempts\n\n", lives);
        }

    } while ((isValid == 0) && lives > 0);

    if (lives == 0){
        printf("You have surpassed your available attempts.\nPress Enter to return to the main menu\n");
        fflush(stdin);
        getc(stdin);
        erase_user_data(eBankingSystem.amount_of_users);
        system("cls");
        return;
    }
    
    system("cls");
    printf("\nThe registration process was successful Mr./Ms. %s.\nYou have been credited 300$ as a welcome gift from the DS Bank.\n", eBankingSystem.system_users[eBankingSystem.amount_of_users].name);
    Sleep(5000);
    system("cls");

    eBankingSystem.system_users[eBankingSystem.amount_of_users].wallet = 300;
    eBankingSystem.system_users[eBankingSystem.amount_of_users].number_of_transactions = 0;
}

int valid_password(char password[21]){
    int pl_sp = 0, pl_n = 0;

    //AN TO PASSWORD EXEI TOYLAXISTON ENAN SPECIAL CHARACTER
    for (int i = 0; i < strlen(password); i++){
        if (password[i] == '!' || password[i] == '?'){
            pl_sp++;
            //break;
            continue;
        }
        if (isdigit(password[i])){
            pl_n++;
        }
        
    }

    //AN TO PASSWORD EINAI TOULAXISTON 7 XARAKTHRES
    if (strlen(password) < 7){
        printf("The password must be at least 7 characters long.");
        return 0;
    }
    else{
        if (pl_sp == 0){
            printf("No special character found.");
            return 0;
        }
        else{
            if (pl_n == 0){
                printf("No number found.");
                return 0;    
            }
            else{
                return 1;
            }
        } 
    }

}

int valid_cvv(char card_cvv[4]){
    int flag = 0;

    //AN EXEI MESA KAPOIO XARAKTHRA
    for (int i = 0; i < 3; i++){
        if (!isdigit(card_cvv[i])){
            flag = 1;
        }
    }
    //printf("\n%d\n", flag);
    if (strlen(card_cvv) != 3){
        printf("The CVV / CVC must be 3 digits long. ");
        return 0;       
    }
    else{
        if (flag == 1){
            printf("The CVV / CVC must not contain any characters. ");
            //printf("\nmphke\n");
            return 0;
        }
        else{
            return 1;
        }
    }

}

void erase_user_data(int p){
    eBankingSystem.system_users[p].name[0] = '\0';
    eBankingSystem.system_users[p].username[0] = '\0';
    eBankingSystem.system_users[p].surname[0] = '\0';
    eBankingSystem.system_users[p].password[0] = '\0';
    eBankingSystem.system_users[p].card_owner[0] = '\0';
    eBankingSystem.system_users[p].card_cvv[0] = '\0';
    eBankingSystem.system_users[p].card_id[0] = '\0';
    eBankingSystem.amount_of_users -= 1;
}

void customer_dashboard_menu(){
    printf("-Customer Dashboard Menu-\n\n");
    printf("0. Logout\n");
    printf("1. View Available Transactions\n");
    printf("2. Execute Transaction\n");
    printf("3. Change My Password\n");
}

void customer_login(){
    char username[21], password[21];
    int flag = 0, p, lives = 5;

    system("cls");
    printf("-Customer Login-\n\n");

    do{     //ELGXOS USERNAME K PASSWORD POU EDWSE
        printf("Enter your username: ");
        scanf(" %s", &username);
        
        p = get_username_position(username);

        if (p == -1){
            lives--;
            printf("Account with this username does not exist. Please try again, you have %d more attempts\n", lives);
            continue;
        }
        
        
        printf("Enter your password: ");
        scanf(" %s", &password);

        if (strcmp(eBankingSystem.system_users[p].password, password) != 0){
            lives--;
            printf("Wrong password. Please try again, you have %d more attempts\n", lives);
        }
        
    }while ((strcmp(eBankingSystem.system_users[p].password, password) != 0 /*|| flag == 0*/) && lives > 0);
    
    if (lives == 0){
        printf("\nYou have surpassed your available attempts.\nPress any key to return to the main menu\n");
        fflush(stdin);
        getc(stdin);
        system("cls");
        return;
    }
    
    system("cls");
    printf("Successful Login");
    Sleep(4000);
    system("cls");

    int ep;

    do{
        do{     //CUSTOMER DASHBOARD MENU
            printf("Name: %s   Balance: %.2f\n", eBankingSystem.system_users[p].username, eBankingSystem.system_users[p].wallet);
            customer_dashboard_menu();
            printf("\nChoice: ");
            scanf(" %d", &ep);
            if (!(ep == 0 || ep == 1 || ep == 2 || ep == 3)){
                printf("Option does not exist. Please try again.\n");
                //idea gia sleep(), clear kai emfanish to menu ksana meta
            }   
        } while (!(ep == 0 || ep == 1 || ep == 2 || ep == 3));

        initialize_available_transactions();

        switch (ep){
        case 1:
            view_available_transactions();
            
            break;

        case 2:
            execute_transaction(p);

            break;

        case 3:
            change_my_password(p);
            break;
        
        default:
            break;
        }
        
    }while(ep != 0);
    
    system("cls");

    return;
}


int get_username_position(char username[21]){
    int pi = -1;
    // EPISTROFH THS 8ESHS KAPOIOU USER ME BASH TO USERNAME
    for (int i = 0; i <= eBankingSystem.amount_of_users; i++){
        if (strcmp(username, eBankingSystem.system_users[i].username) == 0){
            pi = i;
            return pi;
        }
    }

    if (pi = -1){
        return pi;
    }
    
}

void initialize_available_transactions(){
    //ARXIKOPOIHSH OLWN TWN DHMOSIWN SYNALLAGWN
    strcpy(g_availableTransactions[0].transaction_name, "Car License");
    strcpy(g_availableTransactions[0].transaction_provider, "Transport Ministry");
    strcpy(g_availableTransactions[0].transaction_code, "CAR");
    g_availableTransactions[0].transaction_cost = 5;

    strcpy(g_availableTransactions[1].transaction_name, "Identity Card");
    strcpy(g_availableTransactions[1].transaction_provider, "Greek Police");
    strcpy(g_availableTransactions[1].transaction_code, "IDC");
    g_availableTransactions[1].transaction_cost = 15;

    strcpy(g_availableTransactions[2].transaction_name, "Passport");
    strcpy(g_availableTransactions[2].transaction_provider, "Greek Police");
    strcpy(g_availableTransactions[2].transaction_code, "PPT");
    g_availableTransactions[2].transaction_cost = 80;

    strcpy(g_availableTransactions[3].transaction_name, "Traffic Fees");
    strcpy(g_availableTransactions[3].transaction_provider, "Transport Ministry");
    strcpy(g_availableTransactions[3].transaction_code, "TFF");
    g_availableTransactions[3].transaction_cost = 240;

    strcpy(g_availableTransactions[4].transaction_name, "Exhaust Gas Card");
    strcpy(g_availableTransactions[4].transaction_provider, "Transport Ministry");
    strcpy(g_availableTransactions[4].transaction_code, "EGC");
    g_availableTransactions[4].transaction_cost = 10;

    strcpy(g_availableTransactions[5].transaction_name, "Trademark Registration");
    strcpy(g_availableTransactions[5].transaction_provider, "Development Ministry");
    strcpy(g_availableTransactions[5].transaction_code, "TMR");
    g_availableTransactions[5].transaction_cost = 100;
}

void view_available_transactions(){
    system("cls");
    //EMFANISH TWN DHMOSIWN SYNALLAGWN OMORFA SE PINAKAKI
    printf("Name of Transaction\tProvider\t\tCode\tCost\n");
    for (int i = 0; i < 6; i++){
        printf("%-23s\t%-22s\t%-4s\t%-d\n", g_availableTransactions[i].transaction_name, g_availableTransactions[i].transaction_provider, g_availableTransactions[i].transaction_code, g_availableTransactions[i].transaction_cost);
    }
    printf("\n\nPress Enter to return to the Customer Dashboard");
    fflush(stdin);
    getc(stdin);
    system("cls");
}

void execute_transaction(int user_position){
    Transaction trans;
    int lives = 3, flag = 0, p;
    char password[21];

    system("cls");
    printf("-Transaction Menu-\n\n");

    do{     //ELGXOS GIA TON RECEIVER POU EDWSE
        printf("Please type the username of an existing user or a Public Transaction Code: ");
        scanf(" %s", &trans.transaction_receiver);
        p = get_provider_position(trans.transaction_receiver);
        if (p == -1){

            p = get_username_position(trans.transaction_receiver);
            while (p == user_position){
                printf("You can't tranfer money to yourself!\nPlease type another username: ");
                scanf(" %s", &trans.transaction_receiver);
                p = get_username_position(trans.transaction_receiver);
            }
            
            if(p == -1){
                lives--;
                printf("Couldn't find any username or public transaction matching your input. Please try again, you have %d more attempts\n", lives);
            }
            else{
                flag = 1;
            }
        }
        
    } while ((p == -1) && (lives > 0));
    
    if (lives == 0){
        printf("\nYou have surpassed your available attempts.\nPress Enter to return to the Customer Dashboard\n");
        fflush(stdin);
        getc(stdin);
        system("cls");
        return;
    }

    system("cls");
    printf("-Transaction Menu-\n\n");
    printf("Transaction receiver succesfully found");
    Sleep(3000);
    system("cls");
    printf("-Transaction Menu-\n\n");
    printf("Enter the amount ($) you want to pay: ");

    lives = 3;

    if (flag == 1){     //XRHSTHS
        do{
            scanf(" %f", &trans.transaction_amount);
            if (trans.transaction_amount <= 0){
                lives--;
                printf("The transfer amount must be a positive number\nPlease enter again the desired amount you want to transfer. You have %d more lives\n", lives);
            }
            else if (trans.transaction_amount > eBankingSystem.system_users[user_position].wallet){
                lives--;
                printf("You can't transfer that amount of money because it's bigger than what you have in your wallet\nPlease enter again the desired amount you want to transfer. You have %d more lives\n", lives);
            }

            printf("Enter your password for payment verification: ");
            scanf(" %s", &password);

            if (strcmp(eBankingSystem.system_users[user_position].password, password) != 0){
                printf("Wrong password. You will be returned to Customer Dashboard");
                Sleep(2000);
                system("cls");
                return;
            }
            
        } while ((trans.transaction_amount <= 0 || trans.transaction_amount > eBankingSystem.system_users[user_position].wallet) && (lives > 0));

        if (lives == 0){
            printf("\nYou have surpassed your available attempts.\nPress Enter to return to the Customer Dashboard\n");
            fflush(stdin);
            getc(stdin);
            system("cls");
            return;
        }
        // OLES OI ENERGEIES GIA NA GINEI TO TRANSACTION KAI NA KATAGRAFH STO SYSTHMA
        strcpy(trans.transaction_executor, eBankingSystem.system_users[user_position].username);
        eBankingSystem.system_users[user_position].next_transaction_number = eBankingSystem.system_users[user_position].number_of_transactions;
        eBankingSystem.system_users[user_position].number_of_transactions++;
        eBankingSystem.number_of_transactions++;
        trans.transaction_date = generate_date();
        char *pTr_id = generate_transaction_id(trans.transaction_date, trans.transaction_executor, eBankingSystem.system_users[user_position].next_transaction_number);
        for (int i = 0; i < 35; i++){
            trans.transaction_id[i] = *(pTr_id+i);
        }
        eBankingSystem.system_users[user_position].wallet -= trans.transaction_amount;
        eBankingSystem.system_users[p].wallet += trans.transaction_amount;
        add_transaction_to_user(user_position, trans);
        add_transaction_to_system(trans);

        printf("Payment was successful!");
        Sleep(2500);
        system("cls");
        
    }
    else{      //DHMOSIOS
        
        do{
            scanf(" %f", &trans.transaction_amount);

            if (trans.transaction_amount <= 0){
                lives--;
                printf("The transfer amount must be a positive number. Please enter again the desired amount you want to transfer. You have %d more lives\n", lives);
            }
            else if(trans.transaction_amount != g_availableTransactions[p].transaction_cost){
                lives--;
                printf("The amount you want to pay must equal the cost of the transaction you chose (%d$). Please try again, you have %d more lives\n", g_availableTransactions[p].transaction_cost, lives);
            }
            else{
                if (eBankingSystem.system_users[user_position].wallet < g_availableTransactions[p].transaction_cost){
                    printf("You can't pay that amount of money because it's bigger than what you have in your wallet\nSince you don't have the money to pay this public service you'll be returned to the Customer Dashboard\n");
                    Sleep(3000);
                    return;
                }
            }
            
        } while (((trans.transaction_amount <= 0) || (trans.transaction_amount != g_availableTransactions[p].transaction_cost)) && lives > 0);
        
        if (lives == 0){
            printf("\nYou have surpassed your available attempts.\nPress Enter to return to the Customer Dashboard\n");
            fflush(stdin);
            getc(stdin);
            system("cls");
            return;
        }

        printf("Enter your password for payment verification: ");
        scanf(" %s", &password);

        if (strcmp(eBankingSystem.system_users[user_position].password, password) != 0){
            printf("Wrong password. You will be returned to Customer Dashboard");
            Sleep(2000);
            system("cls");
            return;
        }
        // OLES OI ENERGEIES GIA NA GINEI TO TRANSACTION KAI NA KATAGRAFH STO SYSTHMA
        strcpy(trans.transaction_executor, eBankingSystem.system_users[user_position].username);
        eBankingSystem.system_users[user_position].next_transaction_number = eBankingSystem.system_users[user_position].number_of_transactions;
        eBankingSystem.system_users[user_position].number_of_transactions++;
        eBankingSystem.number_of_transactions++;
        trans.transaction_date = generate_date();
        char *pTr_id = generate_transaction_id(trans.transaction_date, trans.transaction_executor, eBankingSystem.system_users[user_position].next_transaction_number);
        for (int i = 0; i < 35; i++){
            trans.transaction_id[i] = *(pTr_id+i);
        }
        eBankingSystem.system_users[user_position].wallet -= trans.transaction_amount;
        add_transaction_to_user(user_position, trans);
        add_transaction_to_system(trans);


        printf("Payment was successful!");
        Sleep(2500);
        system("cls");
    }
    
}

int get_provider_position(char provider_code[4]){
    // EPISTROFH THS 8ESHS KAPOIOU DHMOSIOU ME BASH TON RECEIVER POU EDWSE O USER
    for (int i = 0; i < 6; i++){
        if (strcmp(provider_code, g_availableTransactions[i].transaction_code) == 0){
            return i;
        }
    }

    return -1;
}

Date generate_date(){
    //KANEI AUTO POU LEEI
    Date d;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    d.dd = tm.tm_mday;
    d.mm = tm.tm_mon + 1;
    d.yyyy = tm.tm_year + 1900;

    return d;
}

char *generate_transaction_id(Date t_date, char executor[21], int transaction_number){
    //EPISHS KANEI AUTO POU LEEI
    char tr_id[35], dd[3], mm[3], yyyy[5], sTransaction_number[5];
    char *s_ptr = tr_id;

    sprintf(dd, "%d", t_date.dd);
    sprintf(mm, "%d", t_date.mm);
    sprintf(yyyy, "%d", t_date.yyyy);
    sprintf(sTransaction_number, "%d", transaction_number);

    strcpy(tr_id, executor);
    strcat(tr_id, "_");
    if(strlen(dd)==1){
        strcat(tr_id, "0");
        strcat(tr_id, dd);
    }
    else{
        strcat(tr_id, dd);
    }
    
    if (strlen(mm)==1){
        strcat(tr_id, "0");
        strcat(tr_id, mm);
    }
    else{
        strcat(tr_id, mm);
    }
    
    strcat(tr_id, yyyy);
    strcat(tr_id, "_");
    
    if (strlen(sTransaction_number) == 1){
        strcat(tr_id, "000");
        strcat(tr_id, sTransaction_number);
    }
    else if (strlen(sTransaction_number) == 2){
        strcat(tr_id, "00");
        strcat(tr_id, sTransaction_number);
    }
    else if (strlen(sTransaction_number) == 3){
        strcat(tr_id, "0");
        strcat(tr_id, sTransaction_number);
    }
    else{
        strcat(tr_id, sTransaction_number);
    }
    
    return s_ptr;
}

void add_transaction_to_user(int user_position, Transaction t){
    //int f = -1, r = -1;

    if (r_u == 4){     //Full
        for (int i = 1; i < 5; i++){
            eBankingSystem.system_users[user_position].latest_transactions[i-1].transaction_id[0] = '\0';
            eBankingSystem.system_users[user_position].latest_transactions[i-1].transaction_executor[0] = '\0';
            eBankingSystem.system_users[user_position].latest_transactions[i-1].transaction_receiver[0] = '\0';
            strcpy(eBankingSystem.system_users[user_position].latest_transactions[i-1].transaction_id, eBankingSystem.system_users[user_position].latest_transactions[i].transaction_id);
            eBankingSystem.system_users[user_position].latest_transactions[i-1].transaction_date = eBankingSystem.system_users[user_position].latest_transactions[i].transaction_date;
            eBankingSystem.system_users[user_position].latest_transactions[i-1].transaction_amount = eBankingSystem.system_users[user_position].latest_transactions[i].transaction_amount;
            strcpy(eBankingSystem.system_users[user_position].latest_transactions[i-1].transaction_executor, eBankingSystem.system_users[user_position].latest_transactions[i].transaction_executor);
            strcpy(eBankingSystem.system_users[user_position].latest_transactions[i-1].transaction_receiver, eBankingSystem.system_users[user_position].latest_transactions[i].transaction_receiver);
        }
        eBankingSystem.system_users[user_position].latest_transactions[4].transaction_id[0] = '\0';
        eBankingSystem.system_users[user_position].latest_transactions[4].transaction_executor[0] = '\0';
        eBankingSystem.system_users[user_position].latest_transactions[4].transaction_receiver[0] = '\0';
        strcpy(eBankingSystem.system_users[user_position].latest_transactions[4].transaction_id, t.transaction_id);
        eBankingSystem.system_users[user_position].latest_transactions[4].transaction_date = t.transaction_date;
        eBankingSystem.system_users[user_position].latest_transactions[4].transaction_amount = t.transaction_amount;
        strcpy(eBankingSystem.system_users[user_position].latest_transactions[4].transaction_executor, t.transaction_executor);
        strcpy(eBankingSystem.system_users[user_position].latest_transactions[4].transaction_receiver, t.transaction_receiver);
    }
    else if (f_u == -1 && r_u == -1){     //adeia
        f_u = 0;
        r_u = 0;
        strcpy(eBankingSystem.system_users[user_position].latest_transactions[r_u].transaction_id, t.transaction_id);
        eBankingSystem.system_users[user_position].latest_transactions[r_u].transaction_date = t.transaction_date;
        eBankingSystem.system_users[user_position].latest_transactions[r_u].transaction_amount = t.transaction_amount;
        strcpy(eBankingSystem.system_users[user_position].latest_transactions[r_u].transaction_executor, t.transaction_executor);
        strcpy(eBankingSystem.system_users[user_position].latest_transactions[r_u].transaction_receiver, t.transaction_receiver);
    }
    else{   //oute adeia oute gemath
        r_u += 1;
        strcpy(eBankingSystem.system_users[user_position].latest_transactions[r_u].transaction_id, t.transaction_id);
        eBankingSystem.system_users[user_position].latest_transactions[r_u].transaction_date = t.transaction_date;
        eBankingSystem.system_users[user_position].latest_transactions[r_u].transaction_amount = t.transaction_amount;
        strcpy(eBankingSystem.system_users[user_position].latest_transactions[r_u].transaction_executor, t.transaction_executor);
        strcpy(eBankingSystem.system_users[user_position].latest_transactions[r_u].transaction_receiver, t.transaction_receiver);
    }
    
    
}

void add_transaction_to_system(Transaction t){
    //int f = -1, r = -1;

    if (r_s == 19){     //Full
        for (int i = 1; i < 20; i++){
            eBankingSystem.system_latest_transactions[i-1].transaction_id[0] = '\0';
            eBankingSystem.system_latest_transactions[i-1].transaction_executor[0] = '\0';
            eBankingSystem.system_latest_transactions[i-1].transaction_receiver[0] = '\0';
            strcpy(eBankingSystem.system_latest_transactions[i-1].transaction_id, eBankingSystem.system_latest_transactions[i].transaction_id);
            eBankingSystem.system_latest_transactions[i-1].transaction_date = eBankingSystem.system_latest_transactions[i].transaction_date;
            eBankingSystem.system_latest_transactions[i-1].transaction_amount = eBankingSystem.system_latest_transactions[i].transaction_amount;
            strcpy(eBankingSystem.system_latest_transactions[i-1].transaction_executor, eBankingSystem.system_latest_transactions[i].transaction_executor);
            strcpy(eBankingSystem.system_latest_transactions[i-1].transaction_receiver, eBankingSystem.system_latest_transactions[i].transaction_receiver);
        }
        strcpy(eBankingSystem.system_latest_transactions[19].transaction_id,t.transaction_id);
        eBankingSystem.system_latest_transactions[19].transaction_date = t.transaction_date;
        eBankingSystem.system_latest_transactions[19].transaction_amount = t.transaction_amount;
        strcpy(eBankingSystem.system_latest_transactions[19].transaction_executor, t.transaction_executor);
        strcpy(eBankingSystem.system_latest_transactions[19].transaction_receiver, t.transaction_receiver);
    }
    else if (f_s == -1 && r_s == -1){     //adeia
        f_s = 0;
        r_s = 0;
        strcpy(eBankingSystem.system_latest_transactions[r_s].transaction_id, t.transaction_id);
        eBankingSystem.system_latest_transactions[r_s].transaction_date = t.transaction_date;
        eBankingSystem.system_latest_transactions[r_s].transaction_amount = t.transaction_amount;
        strcpy(eBankingSystem.system_latest_transactions[r_s].transaction_executor, t.transaction_executor);
        strcpy(eBankingSystem.system_latest_transactions[r_s].transaction_receiver, t.transaction_receiver);
    }
    else{   //oute adeia oute gemath
        r_s += 1;
        strcpy(eBankingSystem.system_latest_transactions[r_s].transaction_id, t.transaction_id);
        eBankingSystem.system_latest_transactions[r_s].transaction_date = t.transaction_date;
        eBankingSystem.system_latest_transactions[r_s].transaction_amount = t.transaction_amount;
        strcpy(eBankingSystem.system_latest_transactions[r_s].transaction_executor, t.transaction_executor);
        strcpy(eBankingSystem.system_latest_transactions[r_s].transaction_receiver, t.transaction_receiver);
    }
}

void change_my_password(int user_position){                
    char new_password[21],verify_password[21];
    int isValid;

    system("cls");
    printf("-Password Change-\n\n");
    printf("*Note: the password must contain at least 7 characters, one <<!>> or <<?>> and a number.\n");       
    do{ //ELEGXOS GIA TO AN EINAI VALID OPWS KAI STO REGISTRATION
        printf("Enter the new password: ");                
        scanf(" %s", &new_password);
        isValid=valid_password(new_password);
        if (isValid == 0){
            printf("Invalid password, Try again.\n");
        }         
    }while(isValid == 0);

    do{    //ELEGXOS GIA TA 2 PASSWORDS NA EINAI ISA
        printf("Verify your new password: ");
        scanf(" %s", &verify_password);
        if (strcmp(new_password, verify_password) != 0){
            printf("The two passwords doesn't match. Please try again\n");
        }
    } while(strcmp(new_password, verify_password) != 0);
    
    printf("Enter your last password to verify the change: ");
    scanf(" %s", &verify_password);
    if (strcmp(verify_password, eBankingSystem.system_users[user_position].password) == 0){     //EDWSE SWSTO PROHGOUMENO PASSWORD
        printf("Password change was successful.");
        strcpy(eBankingSystem.system_users[user_position].password, new_password);
        Sleep(2500);
        system("cls");
    }
    else{       //DEN EDWSE SWSTO PROHGOUMENO PASSWORD
        printf("Wrong password, you will return to the Customer Dashboard");
        Sleep(2500);
        system("cls");
        return;
    }
}

void admin_dashboard_menu(){
    printf("-Admin Dashboard Menu-\n\n");
    printf("0. Logout\n");
    printf("1. View Last Transactions\n");
    printf("2. Find User\n");
    printf("3. View Stats\n");
}

void admin_login(){
    char username[21], password[21];
    int flag = 0, p, lives = 5;

    system("cls");
    printf("-Admin Login-\n\n");

    do{ //ELGXOS GIA TO USERNAME NA EINAI SWSTO
        printf("Enter username: ");
        scanf(" %s", &username);

        if (strcmp(username, "admin") != 0){
            lives--;
            printf("Wrong username, try again. You have %d more attempts\n", lives);
        }
        
    }while(strcmp(username, "admin") != 0 && lives > 0);

    if (lives == 0){
        printf("\nYou have surpassed your available attempts.\nPress Enter to return to the main menu\n");
        fflush(stdin);
        getc(stdin);
        system("cls");
        return;
    }
        
    do{ //ELEGXOS GIA TO PASSWORD NA EINAI SWSTO
        printf("Enter password: ");
        scanf(" %s", &password);

        if (strcmp(password, "admin123") != 0){
            lives--;
            printf("Wrong password, try again. You have %d more attempts\n", lives);
        }
        
    }while ((strcmp(password, "admin123") != 0) && lives > 0);
    
    if (lives == 0){
        printf("\nYou have surpassed your available attempts.\nPress Enter to return to the main menu\n");
        fflush(stdin);
        getc(stdin);
        system("cls");
        return;
    }
    
    system("cls");
    printf("Successful Login");
    Sleep(4000);
    system("cls");

    int ep;

    do{
        do{// ADMIN DASHBOARD MENU
            admin_dashboard_menu();
            printf("\nChoice: ");
            scanf(" %d", &ep);
            if (!(ep == 0 || ep == 1 || ep == 2 || ep == 3)){
                printf("Option does not exist. Please try again.\n");
                //idea gia sleep(), clear kai emfanish to menu ksana meta
            }   
        } while (!(ep == 0 || ep == 1 || ep == 2 || ep == 3));

        switch (ep){
        case 1:
            view_last_transactions();
            
            break;

        case 2:
            find_user();

            break;

        case 3:
            //view_stats;

            break;
        
        default:
            break;
        }
        
    }while(ep != 0);
    
    system("cls");

    return;
}

void print_transaction(Transaction t){
    //EKTUPWNEI TA TRANSACTIONS OPWS PREPEI GIA THN EPILOGH STO MENU TOU ADMIN
    printf("[%s] (%d/%d/%d) %s -> %s (%.2f euros)\n", t.transaction_id, t.transaction_date.dd, t.transaction_date.mm, t.transaction_date.yyyy, t.transaction_executor, t.transaction_receiver, t.transaction_amount);
}

void view_last_transactions(){
    system("cls");
    printf("-Latest Transactions-\n\n");

    //EPANALHPSH GIA NA EKTUPO8OUN OLA TA TRANSACTIONS POU EXOUN GINEI
    
    for (int i = 0; i < eBankingSystem.number_of_transactions; i++){
        print_transaction(eBankingSystem.system_latest_transactions[i]);
    }
    
    printf("\nPress Enter to return to the menu");
    fflush(stdin);
    getc(stdin);
    system("cls");

}

void search_user_menu(){
    printf("-User Actions-\n\n");
    printf("A. Add Amount\n");
    printf("B. Customer Info\n");
    printf("*Give any other character to return to the Admin Dashboard\n");
}

void find_user(){
    Transaction trans;
    char username[21];
    int p;

    system("cls");
    //ELGXOS GIA TO AN YPARXEI TO USERNAME POU DINEI
    printf("Enter username: ");
    scanf(" %s", &username);
        
    p = get_username_position(username);

    if(p == -1){
        printf("User not found. You will return back to the menu");
        Sleep(2500);
        system("cls");
        return;
    }
    char ep;

    system("cls");
    do{
        do{ // SEARCH USER MENU
            search_user_menu();
            printf("\nChoice: ");
            scanf(" %c", &ep);
            if (!(ep == 'A' || ep == 'B')){
                system("cls");
                return;
            }   
        } while (!(ep == 'A' || ep == 'B'));

        switch (ep){
        case 'A': // ADD AMOUNT
            system("cls");

            do{
                printf("Enter the amount you want to add: ");
                scanf(" %f", &trans.transaction_amount);
                if (trans.transaction_amount <=0){
                    printf("Must be a positive number\n");
                }
            }while(trans.transaction_amount <=0);

            strcpy(trans.transaction_executor, "admin");
            strcpy(trans.transaction_receiver, username);
            eBankingSystem.number_of_transactions++;
            trans.transaction_date = generate_date();
            char *pTr_id = generate_transaction_id(trans.transaction_date, trans.transaction_executor, admin_next_trans);
            for (int i = 0; i < 35; i++){
                trans.transaction_id[i] = *(pTr_id+i);
            }
            admin_next_trans++;
            add_transaction_to_system(trans);
            eBankingSystem.system_users[p].wallet += trans.transaction_amount;

            printf("Amount added.");
            Sleep(2500);
            system("cls");
            
            break;

        case 'B': // CUSTOMER INFO
            system("cls");
            printf("-Customer Info-\n");
            printf("User: %s\n\n", eBankingSystem.system_users[p].username);
            printf("Name: %s\n", eBankingSystem.system_users[p].name);
            printf("Surname: %s\n", eBankingSystem.system_users[p].surname);
            printf("Password (encrypted): ");
            print_cipher(eBankingSystem.system_users[p].password);
            printf("\nWallet Balance: %.2f\n", eBankingSystem.system_users[p].wallet);
            printf("Card Details:\n\t");
            printf("Card Number: %s\n\t", eBankingSystem.system_users[p].card_id);
            printf("Card Name: %s\n\t", eBankingSystem.system_users[p].card_owner);
            printf("CVV/CVC: %s\n", eBankingSystem.system_users[p].card_cvv);
            printf("Number of Transactions: %d\n\n", eBankingSystem.system_users[p].number_of_transactions);

            printf("Press Enter to go back");
            fflush(stdin);
            getc(stdin);
            system("cls");

            break;
        }
        
    }while(1);
}

void print_cipher(char password[21]){
    //EKTUPOSH TOU KWDIKOU TOU XRHSTH KRYPTOGRAFIMENO
    for (int i = 0; i < strlen(password); i++){
        printf("%c", password[i]+5);
    }
    
}
