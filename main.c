# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <conio.h>
# include <process.h>
# include <time.h> // for date handling

//structure for storing  auction item details
typedef struct{
    int item_id;             // Unique ID for the auction item
    char item_name[20];        // Name of the item (string, max 19 chars + '\0')
    float base_price;          // Starting/base price of the item
    float highest_bid;         // Highest bid placed so far on the item
    char highest_bidder[20];   // Name of the highest bidder (string)
    char date_add[11];         // Date when the item was added (YYYY-MM-DD format, so 10 chars + '\0')
} auction_item;
    
// password  of 8 characters for login and register 
void getpassword(char password[]){
    int i=0;          
         char chr;    // Variable to store each character entered
   
    while(1){ // Infinite loop to read characters one by one
        chr=getch();
        if (chr==13){     // If Enter key is pressed (ASCII 13)
            password[i] = '\0';  // Null-terminate the password string
            break;
        }
        else if (chr==8){       // If Backspace key is pressed (ASCII 8)
            printf("\b \b");    // Erase the last '*' printed on screen
            i--;                // Move back one index in password array to delete last char
        
           
        }
    
        else if (i<8){   // If Backspace key is pressed (ASCII 8)
            printf("\b \b");    // Erase the last '*' printed on screen
            i--;                // Move back one index in password array to delete last char
        

    
        }
    }
    }

    // module to register for auction  by saving username and password to login.txt
void create_account(){
char username[10],password[8];
//  temprory username and password
char stored_user[10],stored_pass[8];
int found=0;
// opening file login.txt
FILE *fp=fopen("login.txt","r");
printf ("username:");
scanf ("%s",username);
if (fp!=NULL){// If file opened successfully
        // Read each username and password from the file until end
   while (fscanf(fp,"%s %s",stored_user,stored_pass)==2){
    // checking if username alraedy exists
    if (strcmp(username,stored_user)==0){
       
        found=1;          // Mark that username exists
           break;        // Exit loop early
 
   
    }
   }
fclose(fp);
}
if (found==1){
            printf ("username already exist");              // Notify user
              return ;                                // Stop function because username is taken

}
// saving user credentials 
fp=fopen("login.txt","a");
if (fp!=NULL){
printf ("password:");     // Prompt user to enter password
        getpassword(password);                      // Call your function to securely get password input
          fprintf (fp,"%s %s\n",username,password);      // Write username and password into file on a new line

}
fclose (fp);
}

// module to login for user by checking if  already registered username and password in login.txt
int userlogin(){
char username[10],password[8];
int found=0;
char fileuser[20],filepass[21];
int pcnt=0;
while (pcnt<3){ // check if user has already  entered wrong  password 3 times 
FILE *fp=fopen("login.txt","r");
if (fp!=NULL){

    printf ("username:");
    scanf ("%s",username);
printf ("password");
getpassword(password);  // Get masked password input using your getpassword()


while (fscanf(fp,"%s %s",fileuser,filepass)==2){
                    // Check if entered username and password matches this record

if (strcmp(username,fileuser)==0 && strcmp( password,filepass)==0){
        found=1;  //Mark login success
                break;          // Exit reading file loop

    }}
   

fclose (fp);
if (found==1){
printf ("\nlogin successful\n");
return 1;}
else {
pcnt++;
// showing the incorrect password to console
printf ("password you entered %s\n",password);
if (pcnt<3)
printf ("login failed\n");// Inform user that login failed
                else
                    printf("you have exhausted your attempts\n"); // Max attempts reached

}
}}

}

// module  for admin to login using a secret admin password
 int admin_access( ){
    char username[10],password[8],admin_password[10];
// temproary username and password
char fileuser[20],filepass[21];
const char * secret_password="@admin#"; // admin secret password
printf ("admin username");
scanf ("%s",username);
printf ("password");
getpassword(password);
FILE *fp=fopen ("login.txt","r");   // Open login file to check credentials
int found=0;

while (fscanf(fp, "%s %s", fileuser, filepass) == 2) {
     // Compare with each username-password pair in file
        if (strcmp(username, fileuser) == 0 && strcmp(password, filepass) == 0) {

            found = 1;  // Mark found if matches
            break;
        }
    }
    fclose(fp);
    if (found){
        printf ("\nenter admin secret password");
        getpassword(admin_password);  // Get secret admin password masked
        // checking for correct admin password
        if (strcmp(admin_password,secret_password)==0){
            printf ("\nadmin login successful"); // Check secret password
                      return 1;                    // Success
            
        }
        else {
            printf ("incorrect admin secret password\n");
            return 0;// Secret password wrong
        }
    }else {
        printf ("incorrect admin username or password");
        return 0;  // Username or password wrong
    }
 }

// module to add items auction
void add_auction_item(){
    auction_item  item,temp_item;
    FILE * fp=fopen("data.txt","a+");
  
    if (fp!=NULL){
        // storing date when item is added
      time_t t=time(NULL);
      struct tm tm=*localtime(&t); 
              sprintf(item.date_add, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

int check_duplicate=1;
// check if item id already exist i.e, duplicate id
while(check_duplicate){
check_duplicate=0;
printf ("\nitem id:\n");
scanf ("%d",&item.item_id);
rewind(fp);
// Read all existing items to check for duplicates
while (fscanf(fp,"%d %s %f %f %s %s",&temp_item.item_id,temp_item.item_name,&temp_item.base_price,&temp_item.highest_bid,temp_item.highest_bidder,temp_item.date_add)==6 )
if (temp_item.item_id==item.item_id){
    printf ("\nitem id already exist!! try another!!!\n");
    check_duplicate=1;
    break;
}
}
  // Prompt for item name; uses scanf format to read line with spaces
printf ("\nITEM name:");
getchar();
scanf ("%[^\n]s",item.item_name);
printf ("base price:");
scanf ("%f",&item.base_price);
 // Set initial highest bid to base price
item.highest_bid=item.base_price;

        // No highest bidder initially
strcpy(item.highest_bidder,"none");
      // Write new item to file
fprintf (fp,"%d %s %f %f %s %s \n",item.item_id,item.item_name,item.base_price,item.highest_bid,item.highest_bidder,item.date_add);
    
}
fclose (fp);
}

// module for users to place bids on auction items
void submit_bids(){
    auction_item item; // Structure to hold item details during file read

    
    int item_id;            // ID of the item the user wants to bid on
    float current_bid;          // New bid value from the user
    char current_bidder[20];    // Name of the current bidder
   
    
    int id_found=0;   // Flag to track if item ID exists
    FILE *fp=fopen("data.txt","r");    // Open the original data file for reading
    FILE *temp = fopen("temp.txt", "w");   // Open a temp file to write updated re
  
   if (fp!=NULL && temp!=NULL){
    // Prompt the user to enter the item ID they want to bid on
printf ("enter item id you want to place bid on:");
scanf ("%d",&item_id);
 // Read all items from the file one by one
while (fscanf (fp,"%d %s %f %f %s %s\n",&item.item_id,item.item_name,&item.base_price,&item.highest_bid,item.highest_bidder,item.date_add)==6){
    // check if id is present fo placing bid
    if (item_id==item.item_id){
id_found=1; // Mark that the ID was found

// Display current highest bid details
        printf ("current highest bid for item %s is %f by %s on %s\n",item.item_name,item.highest_bid,item.highest_bidder,item.date_add);
       
       
                // Prompt user to enter their new bid printf ("enter your  bid:");
        scanf ("%f",&current_bid);
       // Check if the new bid is higher than the current highest
if (current_bid>item.highest_bid){
        printf (" name of current bidder ");
        getchar();
        scanf ("%[^\n]",current_bidder);
        // Update highest bid and bidder
  item.highest_bid=  current_bid;
  strcpy(item.highest_bidder,current_bidder);
    }
    else 
    {
                            // If the bid is too low
printf ("your bid is less than the previous bid");    }  }
            // Write the (updated or original) item back to temp file
   
fprintf (temp,"%d %s %f %f %s %s\n",item.item_id,item.item_name,item.base_price,item.highest_bid,item.highest_bidder,item.date_add);   }
fclose (fp);
fclose (temp);
        // Replace old data file with the updated temp file

remove("data.txt");
    rename("temp.txt", "data.txt");
            // If no matching ID was found

if (!id_found)
printf ("item id not found");
    }   
}

// module for admin to announce winners of auction
void display_winner() {
    auction_item item;
    FILE *fp = fopen("data.txt", "r");

    if (fp == NULL) {
        printf("Error opening data file.\n");
        return;
    }
        // Print header for winners list

    printf("\n\t\t--- Auction Winners ---\n");
    printf("%-10s %-20s %-10s %-15s\n", "Item ID", "Item Name", "Bid", "Winner");
    // Read each item from the file

    while (fscanf(fp, "%d %s %f %f %s %s", &item.item_id, item.item_name, &item.base_price, &item.highest_bid, item.highest_bidder,item.date_add) == 6) {
        // Show only if item is bid on
        if (strcmp(item.highest_bidder, "n") != 0) {
            printf("%-10d %-20s %-10.2f %-15s\n", item.item_id, item.item_name, item.highest_bid, item.highest_bidder);
        } else {
            // if no auction on item than write no bids
            printf("%-10d %-20s %-10.2f %-15s\n", item.item_id, item.item_name, item.highest_bid, "No Bids");
        }
    }

    fclose(fp);
}

//   module for admin to generate report of auction on basis of particular date 
void generating_report(){
    auction_item item;
   
    char date[11];            // User input date (YYYY-MM-DD)
    int total_item = 0;       // Counter for total items added on the date
    int total_bids = 0;       // Counter for total bids placed on the date
   
    FILE *fp1=fopen("data.txt","r"); // File containing auction data
    FILE *fp2 = fopen("report.txt", "w"); // File to write the report

    if (fp1!=NULL && fp2!=NULL){
                // Get the date from the user for which the report is to be generated

        printf ("enter date (YYYY-MM-DD):");
        scanf ("%s",date);
        // report genertaing format
        fprintf(fp2, "Daily Auction Report - Date: %s\n", date);
    fprintf(fp2, ".............................................................\n");
    fprintf(fp2, "%-10s %-20s %-10s %-10s %-15s\n", 
            "Item ID", "Item Name", "Base Price", "Bid", "Bidder");
    fprintf(fp2, "............................................................\n");

        while (fscanf(fp1, "%d %s %f %f %s %s",  &item.item_id,  item.item_name,  &item.base_price, &item.highest_bid, item.highest_bidder, item.date_add) == 6) {
// comparing the date input if present in file
        if (strcmp(item.date_add, date) == 0) {
            total_item++;
                // Count bids if bidder is not "none"

            if (strcmp(item.highest_bidder, "none") != 0) {
                total_bids++;
            }
                // Write item details to the report

            fprintf(fp2, "%-10d %-20s %-10.2f %-10.2f %-15s\n", 
                    item.item_id, item.item_name, item.base_price, 
                    item.highest_bid, item.highest_bidder);
        }
    } 
    // final stats of items on particular date
    fprintf(fp2, "\nTotal number of Items Added: %d\n", total_item);
    fprintf(fp2, "Total  number of Bids Placed: %d\n", total_bids);

    fclose(fp1);
    fclose(fp2);

    printf("Daily report generated in 'report.txt'\n");

    }
}

// user menu
void menu_user() {
    int choice;
    do {
        printf("\n--- User Menu ---\n");
        printf("1. Add Item\n2. Place Bid\n3. Logout\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            // user will be allowed  to perform these functions if loggedin
            case 1: add_auction_item();                // Function to add a new auction item

             break;
            case 2: submit_bids(); // to place bids
            break;
            case 3: printf("Logged out.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 3);
}

// admin menu
void menu_admin() {
    int choice;
    do {
        //
        printf("\n--- Admin Menu ---\n");
        printf("1. Announce Winner\n2. Generate Report\n3. Logout\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            // admin will be allowed to perform these functions if admin loggedin
            case 1: display_winner(); break; // display winner
            case 2: generating_report(); break; // generate report
            case 3: printf("Logged out.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 3);
}

void main_menumodule() {
    int choice;// variable to enter user menu 
    int  is_loggedin = 0;// flag to indicate successfull login
   
    while (1) {// infinte loop for continious menu display
        printf("\n.....Main Menu.....\n");
        printf("1. Register\n2. Login\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            // register a new user
            case 1: create_account(); break;
            case 2:// sub-menu to login-admin or user
                printf("1. User Login\n2. Admin Login\nEnter choice: ");
                scanf("%d", &choice);
                if (choice == 1) {
                    // user login flow
                    is_loggedin = userlogin();

                    if (is_loggedin) menu_user();
                } else if (choice == 2) {
                    // admin login flow
                    is_loggedin = admin_access();
                    if (is_loggedin) menu_admin();
                } else {
                    printf("Invalid login type.\n");
                }
                break;
            case 3: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
}



int main (){
main_menumodule();

    return 0;
}


