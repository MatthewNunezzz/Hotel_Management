#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int room_num;
    int status;
    char username[50];
    char last_name[50];
    char email[50];
    char address[255];
    char telephone_num[20];
    char check_in_date[11];
    char check_out_date[11];
    int days;
}room;

void book_room(room *hotel){
    int num;
    printf("Which room would you like to book? ");
    scanf("%d", &num);
    if(hotel[(num - 1)].status == 1)
        printf("Room is already booked\n");
    else if(hotel[(num - 1)].status == 0){
        hotel[(num - 1)].status = 1;
        printf("Enter username: ");
        scanf("%s",&hotel[(num - 1)].username);
        printf("Enter last name: ");
        scanf("%s",&hotel[(num - 1)].last_name);
        printf("Enter email: ");
        scanf("%s",&hotel[(num - 1)].email);
        printf("Enter home address: ");
        scanf("%s",&hotel[(num - 1)].address);
        printf("Enter telephone number: ");
        scanf("%s",&hotel[(num - 1)].telephone_num);
        printf("You may only book 7 months in advance.\n");
        printf("Enter check in date(MM/DD/YYYY): ");
        scanf("%s",&hotel[(num - 1)].check_in_date);
        printf("Enter check out date(MM/DD/YYYY): ");
        scanf("%s",&hotel[(num - 1)].check_out_date);

        //The goal is to find the number of days between the check-in and check-out date

        //Because a user may only book 7 seven months in advance, a calendar of the next 7 months will be created
        //This calendar is made as a multidimensional array with 8 rows(months) and 31 columns(days)
        int calendar[8][31];

        //This multidimensional array will then be filled with ones to represent each day
        //Because a few months only contain 30 days, these months/rows will only contain 30 ones
        //We will fill the empty spaces with zeroes
        for(int i=0; i < (sizeof(calendar)/sizeof(calendar[0])); i++){
            for(int j=0; j < (sizeof(calendar[0])/sizeof(calendar[0][0])); j++){
                if((i == 1) && (j == 30))
                    calendar[i][j] = 0;
                else if((i == 4) && (j == 30))
                    calendar[i][j] = 0;
                else if((i == 6) && (j == 30))
                    calendar[i][j] = 0;
                else
                    calendar[i][j] = 1;
            }
        }

        //The months are extracted from the check-in/check-out date strings
        char check_in_month_str[3] = {hotel[(num - 1)].check_in_date[0],hotel[(num - 1)].check_in_date[1]};
        char check_out_month_str[3] = {hotel[(num - 1)].check_out_date[0], hotel[(num - 1)].check_out_date[1]};

        //The month strings are then converted into integers
        int check_in_month_int = atoi(check_in_month_str);
        int check_out_month_int = atoi(check_out_month_str);

        //An array is created to map the next eight months with their respective row numbers in the multidimensional array/calendar
        int months[8] = {5,6,7,8,9,10,11,12};
        int begin_row_num, begin_col_num, end_row_num, end_col_num;

        for(int i=0; i < (sizeof(months)/sizeof(months[0]));i++){
            if(check_in_month_int == months[i])
                begin_row_num = i;
            if(check_out_month_int == months[i])
                end_row_num = i;
        }

        //The days are extracted from the check-in/check-out date strings
        char check_in_day_str[3] = {hotel[(num-1)].check_in_date[3],hotel[(num-1)].check_in_date[4]};
        char check_out_day_str[3] = {hotel[(num-1)].check_out_date[3], hotel[(num-1)].check_out_date[4]};

        //The days strings are then converted into integers
        int check_in_day_int = atoi(check_in_day_str);
        int check_out_day_int = atoi(check_out_day_str);

        //The days are then subtracted by 1 to accurately represent their position in the multidimensional array/calendar
        begin_col_num = check_in_day_int - 1;
        end_col_num = check_out_day_int - 1;


        int days = 0;
        //A for loop is used to find the number of days between the check-in and check-out date
        //This is done by simply adding up all the ones in between the check-in and check-out date
        for(int row_num = begin_row_num; row_num <= end_row_num ; row_num++){
            //In the case that the check-in and check-out dates are in the same month
            if(begin_row_num == end_row_num){
                for(int col_num = begin_col_num; col_num <= end_col_num; col_num++){
                    days += calendar[row_num][col_num];
                }
            }
            //These next three conditional statements represent the case that the check-in and check-out dates occur in different months
            else if(row_num == begin_row_num){
                for(int col_num = begin_col_num; col_num < (sizeof(calendar[0])/sizeof(calendar[0][0])); col_num++){
                    days += calendar[row_num][col_num];
                }
            }
            else if(row_num == end_row_num){
                for(int col_num = 0; col_num <= end_col_num; col_num++){
                    days += calendar[row_num][col_num];
                }
            }
            else{
                for(int col_num = 0; col_num < (sizeof(calendar[0])/sizeof(calendar[0][0])); col_num++){
                    days += calendar[row_num][col_num];
                }
            }
        }
        hotel[(num-1)].days = days;
    }
    else{
        printf("Please pick a room from 1 to 10\n");
    }
}

void view(room *hotel){
    int num;
    printf("Room Number? ");
    scanf("%d", &num);
    if(hotel[(num - 1)].status == 0)
        printf("This room is vacant\n");
    else if(hotel[(num - 1)].status == 1){
        printf("Customer Details: \n");
        printf("Username: %s\n", hotel[(num - 1)].username);
        printf("Last Name: %s\n", hotel[(num - 1)].last_name);
        printf("Email: %s\n", hotel[(num - 1)].email);
        printf("Address: %s\n", hotel[(num - 1)].address);
        printf("Telephone: %s\n", hotel[(num - 1)].telephone_num);
    }
    else
        printf("Room Doesn't Exist\n");
}

void edit(room *hotel){
    int num;
    printf("Room Number? ");
    scanf("%d", &num);
    if(hotel[(num - 1)].status == 0)
        printf("This room is vacant\n");
    else if(hotel[(num - 1)].status == 1){
        hotel[(num - 1)].status = 1;
        printf("Re-enter username: ");
        scanf("%s",&hotel[(num - 1)].username);
        printf("Re-enter last name: ");
        scanf("%s",&hotel[(num - 1)].last_name);
        printf("Re-enter email: ");
        scanf("%s",&hotel[(num - 1)].email);
        printf("Re-enter home address: ");
        scanf("%s",&hotel[(num - 1)].address);
        printf("Re-enter telephone number: ");
        scanf("%s",&hotel[(num - 1)].telephone_num);
    }
    else{
        printf("Room Doesn't Exist\n");
    }
}

void check_out(room *hotel){
    int num;
    printf("Room Number? ");
    scanf("%d", &num);
    if(hotel[(num - 1)].status == 0)
        printf("This room is vacant\n");
    else if(hotel[(num - 1)].status == 1){
        hotel[(num - 1)].status = 0;

        int bill = 50 * hotel[num - 1].days;
        printf("Bill: $%d.00\n", bill);
    }
}

void print_report(room *hotel,int size){

    FILE *f = fopen("hotel.txt","a");
    if (f != NULL){
        fprintf(f,"Room#\t\tCheck-in date\t\tNumber of days\t\t Status\n");
        for(int i; i < size; i++){
            fprintf(f,"%d\t\t",hotel[i].room_num);
            if(hotel[i].status == 1){
                fprintf(f,"%s\t\t\t",hotel[i].check_in_date);
                fprintf(f,"%d\t\t\t\t",hotel[i].days);
                fprintf(f,"Booked\n");
            }
            else
                fprintf(f,"\t\t\t\t\t\t\t\tVacant\n");
        }
        fclose(f);
        f = NULL;
    }
}

int main()
{
    room hotel[10];
    int size = (sizeof(hotel)/sizeof(hotel[0]));

    for(int i=0; i < size; i++){
        hotel[i].room_num = (i + 1);
        hotel[i].status = 0;
    }

    printf("Hello and Welcome!\nTo book a room enter b or B\n");
    printf("To view customer details enter v or V\n");
    printf("To edit customer details enter e or E\n");
    printf("To check out enter c or C\n");
    printf("To print a report enter r or R\n");
    printf("To exit program enter t or T\n");

    char trans_type;

    while(1){
        printf("\nTransaction Type? ");
        scanf(" %c", &trans_type);
        if((trans_type == 'b') || (trans_type == 'B')){
            book_room(hotel);
        }
        else if((trans_type == 'v') || (trans_type == 'V')){
            view(hotel);
        }
        else if((trans_type == 'e') || (trans_type == 'E')){
            edit(hotel);
        }
        else if((trans_type == 'c') || (trans_type == 'C')){
            check_out(hotel);
        }
        else if((trans_type == 'r') || (trans_type == 'R')){
            print_report(hotel, size);
        }
        else if((trans_type == 't') || (trans_type == 'T')){
            break;
        }
        else{
            printf("Invalid User Input\n");
        }
    }

    return 0;
}
