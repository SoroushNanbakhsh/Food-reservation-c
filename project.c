#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct __Clients__
{
    char name[21];
    char family_name[21];
    char username[21];
    char password[21];
    long long int national_id_code;
    char birthday[11];
    char gender[7];
    char type[8];
    int approve; // 0.Not approved 1.Approved
    unsigned long long int wallet;
} client;

typedef struct __Self__
{
    unsigned int id;
    char name[21];
    char address[21];
    unsigned int capacity;
    int self_type; // 1.male 2.female
    int Meal_time; // 1.nahar 2.sham
    char open_time[6];
    char close_time[6];
} self;

typedef struct __Food__
{
    unsigned int id;
    char name[21];
    int type; // 1.main-food 2.dessert
    unsigned long long int price;
} food;

typedef struct __Plan__
{
    char date[11];
    unsigned int self_id;
    char type[7];
    int food_id;
    int amount;
    unsigned long long int cost;
} plan;

typedef struct __Reserve__
{
    char client_username[21];
    unsigned int self_id;
    char date[11];
    char meal[7];
    unsigned int food_id;
} reserve;

typedef struct __Poll__
{
    char question[150];

    char A_text[50];
    unsigned int A;

    char B_text[50];
    unsigned int B;

    char C_text[50];
    unsigned int C;

    char D_text[50];
    unsigned int D;

    char date[11];
} poll;

typedef struct __Payment__
{
    char subject[50];
    char client_username[21];
    char date[11];
    char time[6];
} payment;

typedef struct __PersonFunction__
{
    char client_username[21];
    char subject[50];
    char date[11];
    char time[6];
} function;

int file_number = 1;
int reserve_file_number = 1;
int plan_file_number = 1;
int poll_file_number = 1;

int date_year;
int date_month;
int date_day;

int date_hour;
int date_minute;

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//colors
void red()
{
    printf("\033[0;31m");
}
void green()
{
    printf("\033[0;32m");
}
void yellow()
{
    printf("\033[0;33m");
}
void blue()
{
    printf("\033[0;34m");
}
void purple()
{
    printf("\033[0;35m");
}
void cyan()
{
    printf("\033[0;36m");
}
void white()
{
    printf("\033[0;37m");
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int check_UsernameAndPassword(char* username, char* password, client *logined_client);
int login_window(client *logined_client);
void register_window(client *Logined_client);
int first_window(void);
int menu(client *logined_client);
void change_password(client *logined_client);
void approve(void);
void change_student_password(void);
void remove_student(void);
void deactivate(void);
void define_self(void);
void define_food(void);
void define_meal_plan(void);
void charge_student_account(void);
void food_log(void);
void person_function(void);
void add_news(void);
void add_poll(void);
void RESERVE(client *logined_client);
void take_food(client *logined_client);
void charge_account(client *logined_client);
void send_charge(void);
void reserved_plan(client* logined_client);
void cancel_reserve(client *logined_client);
void daily_reserve(client *logined_client);
void change_self(client *logined_client);
void payment_log(client *logined_client);
void eated_food_log(void);
void check_news(void);
void vote(void);
void change_date_time(void);

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void change_date_time(void)
{
    purple();
    puts("----------------------------------------------------------------------------");
    printf("\n\n\n\n\n\n");

    cyan();

    char date[11];
    printf("Set date : ");
    scanf("%s", date);

    if(date[4] != '-')
    {
        puts("Invalid");
        return;
    }
    else if(date[7] != '-')
    {
        puts("Invalid");
        return;
    }

    sscanf(date, "%d-%d-%d", &date_year, &date_month, &date_day);

    char time[6];

    printf("\nSet time : ");
    scanf("%s", time);

    if(time[2] != ':')
    {
        puts("Invalid");
        return;
    }

    sscanf(time, "%d:%d", &date_hour, &date_minute);

    if(date_hour < 0 || date_hour > 24)
    {
        puts("invalid");
        return;
    }
    else if(date_minute < 0 || date_minute > 59)
    {
        puts("invalid");
        return;
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void vote(void)
{
    FILE *poll1Ptr;
    FILE *poll2Ptr;

    if(poll_file_number == 1)
    {
        poll1Ptr = fopen("Polls1.dat", "ab+");
        poll2Ptr = fopen("polls2.dat", "wb+");
        rewind(poll1Ptr);
        poll_file_number = 2;
    }
    else
    {
        poll1Ptr = fopen("Polls2.dat", "ab+");
        poll2Ptr = fopen("polls1.dat", "wb+");
        rewind(poll2Ptr);
        poll_file_number = 1;
    }

    if(poll1Ptr == NULL || poll2Ptr == NULL)
    {
        puts("File could not be opened.");

        fclose(poll1Ptr);
        fclose(poll2Ptr);

        return;
    }
    else
    {
        poll poll1;
        poll poll2;

        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");
        cyan();

        int poll_date_year;
        int poll_date_month;
        int poll_date_day;

        sscanf(poll1.date, "%d-%d-%d", &poll_date_year, &poll_date_month, &poll_date_day);

        while(!feof(poll1Ptr))
        {
            fread(&poll1, sizeof(poll), 1, poll1Ptr);

            if(date_year < poll_date_year || date_year == poll_date_year && date_month < poll_date_month || date_year == poll_date_year && date_month == poll_date_month && date_day <= poll_date_day)
            {
                printf("T | %s\n", poll1.question);

                green();
                printf("A | %s", poll1.A_text);
                printf("B | %s", poll1.B_text);
                printf("C | %s", poll1.C_text);
                printf("D | %s", poll1.D_text);
            }
        }

        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");

        cyan();

        printf("Select from A-D : ");
        char select;
        scanf(" %c", &select);

        if(!(select >= 'a' && select <= 'z' || select >= 'A' && select <= 'Z'))
        {
            puts("invalid");

            fclose(poll1Ptr);
            fclose(poll2Ptr);

            return;
        }
        else
        {
            poll2.A = poll1.A;
            poll2.B = poll1.B;
            poll2.C = poll1.C;
            poll2.D = poll1.D;

            strcpy(poll2.A_text, poll1.A_text);
            strcpy(poll2.B_text, poll1.B_text);
            strcpy(poll2.C_text, poll1.C_text);
            strcpy(poll2.D_text, poll1.D_text);

            strcpy(poll2.date, poll1.date);
            strcpy(poll2.question, poll1.question);

            rewind(poll1Ptr);
            fread(&poll1, sizeof(poll), 1, poll1Ptr);

            while(strcmp(poll1.question, poll2.question) != 0)
            {
                fwrite(&poll1, sizeof(poll), 1, poll2Ptr);

                if(feof(poll1Ptr))
                {
                    puts("BUG");
                }

                fread(&poll1, sizeof(poll), 1, poll1Ptr);
            }

            if(select == 'a' || select == 'A')
            {
                poll2.A++;
            }
            else if(select == 'b' || select == 'B')
            {
                poll2.B++;
            }
            if(select == 'c' || select == 'C')
            {
                poll2.C++;
            }
            if(select == 'd' || select == 'D')
            {
                poll2.D++;
            }

            fwrite(&poll2, sizeof(poll), 1, poll2Ptr);

            while(!feof(poll1Ptr))
            {
                fread(&poll1, sizeof(poll), 1, poll1Ptr);
                fwrite(&poll2, sizeof(poll), 1, poll2Ptr);
            }

            fclose(poll1Ptr);
            fclose(poll2Ptr);
        }
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void check_news(void)
{
    FILE *newsPtr = fopen("News.txt", "rb");

    if(newsPtr == NULL)
    {
        puts("not-found");

        fclose(newsPtr);

        return;
    }
    else
    {
        while(!feof(newsPtr))
        {
            char text[50];
            fscanf(newsPtr, "%s", text);
            printf("%s", text);
        }
    }

    fclose(newsPtr);

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void payment_log(client *logined_client)
{
    FILE *cfPtr = fopen("Payment.dat", "ab+");

    if(cfPtr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);

        return;
    }
    else
    {
        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");
        cyan();

        
        payment payment1;

        rewind(cfPtr);

        while(!feof(cfPtr))
        {
            fread(&payment1, sizeof(payment), 1, cfPtr);

            if(strcmp(payment1.client_username, logined_client->username) == 0)
            {
                printf("%s | %s | %s", payment1.date, payment1.time, payment1.subject);
            }
        }

        fclose(cfPtr);
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void change_self(client *logined_client)
{
    FILE *selfPtr = fopen("Self.dat", "rb");
    FILE *reserve1Ptr;
    FILE *reserve2Ptr;

    if(reserve_file_number == 1)
    {
        reserve1Ptr = fopen("Reserves1.dat", "ab+");
        reserve2Ptr = fopen("Reserves2.dat", "wb");
        rewind(reserve1Ptr);
        reserve_file_number = 1;
    }
    else
    {
        reserve1Ptr = fopen("Reserves2.dat", "ab+");
        reserve2Ptr = fopen("Reserves1.dat", "wb");
        rewind(reserve1Ptr);
        reserve_file_number = 2;
    }

    if(selfPtr == NULL || reserve1Ptr == NULL || reserve2Ptr == NULL)
    {
        puts("File could not be opened / there is not any active self.");

        fclose(selfPtr);
        fclose(reserve1Ptr);
        fclose(reserve2Ptr);

        return;
    }

    purple();
    puts("----------------------------------------------------------------------------");
    printf("\n\n\n\n\n\n");
    cyan();

    reserve reserve1;
    self self1;

    int type;

    while(!feof(selfPtr))
    {
        fread(&self1, sizeof(self), 1, selfPtr);

        if(strcmp(logined_client->type, "male") == 0)
        {
            type = 1;
        }


        if(self1.self_type == type)
        {
            printf("%u | %s | %s \n", self1.id, self1.name, self1.address);
        }
    }

    rewind(selfPtr);

    purple();
    puts("----------------------------------------------------------------------------");
    cyan();

    while(!feof(reserve1Ptr))
    {
        fread(&reserve1, sizeof(reserve), 1, reserve1Ptr);

        if(strcmp(reserve1.client_username, logined_client->username) == 0)
        {
            printf("%s | %u | %s | %u\n", reserve1.date, reserve1.self_id, reserve1.meal, reserve1.food_id);
        }
    }

    rewind(reserve1Ptr);

    purple();
    puts("----------------------------------------------------------------------------");
    cyan();

    unsigned int prev_self_id;
    unsigned int new_self_id;

    printf("Current self_ID : ");
    scanf("%u", &prev_self_id);
    printf("\nNew self_ID : ");
    scanf("%u", &new_self_id);

    fread(&reserve1, sizeof(reserve), 1, reserve1Ptr);

    while(reserve1.self_id != new_self_id)
    {
        if(feof(reserve1Ptr))
        {
            puts("invalid");

            fclose(selfPtr);
            fclose(reserve1Ptr);
            fclose(reserve2Ptr);

            return;
        }

        fwrite(&reserve1, sizeof(reserve), 1, reserve2Ptr);
        fread(&reserve1, sizeof(reserve), 1, reserve1Ptr);
    }

    reserve1.self_id = new_self_id;

    fwrite(&reserve1, sizeof(reserve), 1, reserve2Ptr);

    while(!feof(reserve1Ptr))
    {
        fread(&reserve1, sizeof(reserve), 1, reserve2Ptr);
        fwrite(&reserve1, sizeof(reserve), 1, reserve2Ptr);
    }

    fclose(selfPtr);
    fclose(reserve1Ptr);
    fclose(reserve2Ptr);

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void daily_reserve(client *logined_client)
{
    FILE *cfPtr;
    FILE *selfPtr = fopen("Self.dat", "rb+");
    FILE *planPtr;
    FILE *plan2Ptr;
    FILE *foodPtr = fopen("Foods.dat", "rb+");

    if(plan_file_number == 1)
    {
        planPtr = fopen("Plans1.dat", "ab+");
        plan2Ptr = fopen("Plans2.dat", "wb+");
        plan_file_number = 2;
        rewind(planPtr);
    }
    else
    {
        planPtr = fopen("Plans2.dat", "ab+");
        plan2Ptr = fopen("Plans1.dat", "wb+");
        plan_file_number = 1;
        rewind(planPtr);
    }

    if(reserve_file_number == 1)
    {
        cfPtr = fopen("Reserves1.dat", "ab+");
    }
    else
    {
        cfPtr = fopen("Reserves2.dat", "ab+");
    }

    if(cfPtr == NULL || selfPtr == NULL || planPtr == NULL || foodPtr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);
        fclose(foodPtr);
        fclose(planPtr);
        fclose(plan2Ptr);
        fclose(selfPtr);

        return;
    }
    else
    {
        self self1;
        reserve reserve1;
        plan plan1;
        food food1;

        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");
        cyan();

        puts("        Select Self        ");

        rewind(selfPtr);
        rewind(cfPtr);

        while(!feof(selfPtr))
        {
            fread(&self1, sizeof(self), 1, selfPtr);

            printf("Self ID : %u, Self name : %s\n", self1.id, self1.name);
        }

        unsigned int self_id;

        purple();
        printf("\n\n\n\n\n\n");
        puts("----------------------------------------------------------------------------");
        cyan();
        printf("Self ID : ");

        scanf("%u", &self_id);
        
        rewind(selfPtr);
        fread(&self1, sizeof(self), 1, selfPtr);

        while(self1.id != self_id && !feof(selfPtr))
        {
            fread(&self1, sizeof(self), 1, selfPtr);

            if(feof(selfPtr))
            {
                puts("not-found");

                fclose(cfPtr);
                fclose(foodPtr);
                fclose(planPtr);
                fclose(plan2Ptr);
                fclose(selfPtr);

                return;
            }
        }

        reserve1.self_id = self_id;

        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");

        cyan();
        rewind(planPtr);
        
        fread(&plan1, sizeof(plan), 1, planPtr);

        while(!feof(planPtr))
        {
            if(plan1.self_id == self_id)
            {
                printf("%s\n", plan1.date);
            }

            fread(&plan1, sizeof(plan), 1, planPtr);
        }

        purple();
        printf("\n\n\n\n\n\n");
        puts("----------------------------------------------------------------------------");

        cyan();
        printf("Date : ");
        char Date[11];
        gets(Date);

        if(Date[5] != '-')
        {
            puts("invalid");

            fclose(cfPtr);
            fclose(foodPtr);
            fclose(planPtr);
            fclose(plan2Ptr);
            fclose(selfPtr);

            return;
        }
        else if(Date[8] != '-')
        {
            puts("invalid");

            fclose(cfPtr);
            fclose(foodPtr);
            fclose(planPtr);
            fclose(plan2Ptr);
            fclose(selfPtr);

            return;
        }

        strcpy(plan1.date, Date);

        rewind(planPtr);

        fread(&plan1, sizeof(plan), 1, planPtr);

        while(plan1.date != reserve1.date && !feof(selfPtr))
        {
            if(feof(planPtr))
            {
                puts("not-found");

                fclose(cfPtr);
                fclose(foodPtr);
                fclose(planPtr);
                fclose(plan2Ptr);
                fclose(selfPtr);

                return;
            }

            fread(&plan1, sizeof(plan), 1, planPtr);
        }

        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");

        cyan();
        rewind(planPtr);

        fread(&plan1, sizeof(plan), 1, planPtr);

        while(!feof(planPtr))
        {
            if(plan1.self_id == self_id && strcmp(reserve1.date, plan1.date) == 0)
            {
                printf("Meal : %s\n", plan1.type);
            }
        }

        purple();
        printf("\n\n\n\n\n\n");
        puts("----------------------------------------------------------------------------");
        cyan();

        printf("Meal : ");
        scanf("%s", reserve1.meal);

        rewind(planPtr);

        fread(&plan1, sizeof(plan), 1, planPtr);

        while(plan1.self_id != self_id || strcmp(reserve1.date, plan1.date) != 0)
        {
            if(feof(planPtr))
            {
                puts("not-found");

                fclose(cfPtr);
                fclose(foodPtr);
                fclose(planPtr);
                fclose(plan2Ptr);
                fclose(selfPtr);

                return;
            }

            fread(&plan1, sizeof(plan), 1, planPtr);
        }

        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");
        cyan();

        puts("        Select Food        ");

        rewind(foodPtr);
        rewind(planPtr);

        fread(&plan1, sizeof(plan), 1, planPtr);
        fread(&food1, sizeof(food), 1, foodPtr);

        while(plan1.self_id == self_id && strcmp(reserve1.date, plan1.date) == 0 && strcmp(plan1.type, reserve1.meal) == 0 && !feof(planPtr))
        {
            printf("Food ID : %u\n", plan1.food_id);
        }

        unsigned int food_id;

        purple();
        printf("\n\n\n\n\n\n");
        puts("----------------------------------------------------------------------------");
        cyan();
        printf("Food ID : ");

        scanf("%u", &food_id);

        rewind(planPtr);

        fread(&plan1, sizeof(plan), 1, planPtr);

        while(plan1.self_id != self_id || strcmp(reserve1.date, plan1.date) != 0 || strcmp(plan1.type, reserve1.meal) != 0)
        {
            if(feof(planPtr))
            {
                puts("not-found");

                fclose(cfPtr);
                fclose(foodPtr);
                fclose(planPtr);
                fclose(plan2Ptr);
                fclose(selfPtr);

                return;
            }

            fread(&plan1, sizeof(plan), 1, planPtr);
        }

        if(plan1.amount > 0)
        {
            int plan_year;
            int plan_month;
            int plan_day;

            int open_time_hour;
            int open_time_minute;
        
            int close_time_hour;
            int close_time_minute;

            sscanf(self1.open_time, "%d:%d", &open_time_hour, &open_time_minute);
            sscanf(self1.close_time, "%d:%d", &close_time_hour, &close_time_minute);

            sscanf(plan1.date, "%d-%d-%d", &plan_year, &plan_month, &plan_day);

            if(plan_year == date_year && plan_month == date_month && plan_day == date_day && (open_time_hour * 60) + open_time_minute <= (date_hour * 60) + date_minute && (close_time_hour * 60) + close_time_minute > (date_hour * 60) + date_minute + 30)
            {
                plan plan2;

                fread(&plan2, sizeof(plan), 1, planPtr);

                while(plan2.food_id != plan1.food_id || plan2.self_id != plan1.self_id || strcmp(plan2.date, plan1.date) != 0 || strcmp(plan2.type, plan1.type) != 0)
                {
                    fread(&plan2, sizeof(plan), 1, planPtr);

                    if(plan2.food_id == plan1.food_id || plan2.self_id == plan1.self_id || strcmp(plan2.date, plan1.date) == 0 || strcmp(plan2.type, plan1.type) == 0)
                    {
                        break;
                    }

                    fwrite(&plan2, sizeof(plan), 1, plan2Ptr);

                    if(feof(planPtr))
                    {
                        puts("not-found");

                        fclose(cfPtr);
                        fclose(foodPtr);
                        fclose(planPtr);
                        fclose(plan2Ptr);
                        fclose(selfPtr);

                        return;
                    }
                }

                fwrite(&plan1, sizeof(plan), 1, plan2Ptr);

                while(!feof(planPtr))
                {
                    fread(&plan2, sizeof(plan), 1, planPtr);
                    fwrite(&plan2, sizeof(plan), 1, plan2Ptr);
                }

                while(logined_client->wallet < 2 * plan1.cost)
                {
                    charge_account(logined_client);
                }

                plan1.amount--;

                logined_client->wallet -= 2 * plan1.cost;

                strcpy(reserve1.client_username, logined_client->username);

                fwrite(&reserve1, sizeof(reserve), 1, cfPtr);

                fclose(cfPtr);
                fclose(foodPtr);
                fclose(planPtr);
                fclose(plan2Ptr);
                fclose(selfPtr);

                printf("\n\n\n\n\n\n");
                purple();
                puts("----------------------------------------------------------------------------");
                puts("success");
            }
            else
            {
                puts("permission-denid");
                return;
            }
        }
        else
        {
            puts("not-found");
            return;
        }
    }

    return;
}

void cancel_reserve(client *logined_client)
{
    FILE *reserve1Ptr;
    FILE *reserve2Ptr;
    FILE *plan1Ptr;
    FILE *plan2Ptr;
    FILE *paymentPtr = fopen("Payment.dat", "ab");

    if(reserve_file_number == 1)
    {
        reserve1Ptr = fopen("Reserves1.dat", "ab+");
        reserve2Ptr = fopen("Reserves2.dat", "wb+");
        rewind(reserve1Ptr);
        reserve_file_number = 2;
    }
    else
    {
        reserve1Ptr = fopen("Reserves2.dat", "rb+");
        reserve2Ptr = fopen("Reserves1.dat", "wb+");
        rewind(reserve1Ptr);
        reserve_file_number = 1;
    }

    if(plan_file_number == 1)
    {
        plan1Ptr = fopen("Plans1.dat", "ab+");
        plan2Ptr = fopen("Plans2.dat", "wb+");
        rewind(plan1Ptr);
        plan_file_number = 2;
    }
    else
    {
        plan1Ptr = fopen("Plans2.dat", "ab+");
        plan2Ptr = fopen("Plans1.dat", "wb+");
        rewind(plan1Ptr);
        plan_file_number = 1;
    }

    if(reserve1Ptr == NULL || reserve2Ptr == NULL || plan1Ptr == NULL || plan2Ptr == NULL || paymentPtr == NULL)
    {
        puts("File could not be opened.");

        fclose(reserve1Ptr);
        fclose(reserve2Ptr);
        fclose(plan1Ptr);
        fclose(plan2Ptr);
        fclose(paymentPtr);

        return;
    }
    else
    {
        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");
        cyan();

        // show reserved plans fo logined_client id

        reserve reserve1;
        reserve reserve2;

        plan plan1;

        fread(&reserve1, sizeof(reserve), 1, reserve1Ptr);

        while(feof(reserve1Ptr))
        {
            if(strcmp(reserve1.client_username, logined_client->username) != 0)
            {
                printf("%s | %u | %s | %u\n", reserve1.date, reserve1.self_id, reserve1.meal, reserve1.food_id);
            }

            fread(&reserve1, sizeof(reserve), 1, reserve1Ptr);
        }

        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");
        
        cyan();

        printf("Date : ");
        char date[11];
        gets(date);

        if(date[5] != '-')
        {
            puts("invalid");

            fclose(reserve1Ptr);
            fclose(reserve2Ptr);
            fclose(plan1Ptr);
            fclose(plan2Ptr);
            fclose(paymentPtr);

            return;
        }
        else if(date[8] != '-')
        {
            puts("invalid");

            fclose(reserve1Ptr);
            fclose(reserve2Ptr);
            fclose(plan1Ptr);
            fclose(plan2Ptr);
            fclose(paymentPtr);

            return;
        }

        printf("Meal : ");
        char Meal[7];
        gets(Meal);

        strcpy(reserve2.client_username, logined_client->username);
        strcpy(reserve2.date, date);
        strcpy(reserve2.meal, Meal);

        rewind(reserve1Ptr);

        fread(&reserve1, sizeof(reserve), 1, reserve1Ptr);

        while(strcmp(reserve1.client_username, reserve2.client_username) != 0 || strcmp(reserve1.date, reserve2.date) != 0 || strcmp(reserve1.meal, reserve2.meal) != 0)
        {
            fwrite(&reserve1, sizeof(reserve), 1, reserve2Ptr);
            fread(&reserve1, sizeof(reserve), 1, reserve2Ptr);

            if(feof(reserve1Ptr))
            {
                puts("invalid");

                fclose(reserve1Ptr);
                fclose(reserve2Ptr);
                fclose(plan1Ptr);
                fclose(plan2Ptr);
                fclose(paymentPtr);

                return;
            }
        }

        reserve2.food_id = reserve1.food_id;
        reserve2.self_id = reserve1.self_id;

        fread(&plan1, sizeof(plan), 1, plan1Ptr);

        while(plan1.self_id != reserve2.self_id || strcmp(plan1.date, reserve2.date) != 0 || reserve2.food_id != plan1.food_id || strcmp(plan1.type, reserve2.meal) != 0)
        {
            fwrite(&plan1, sizeof(plan), 1, plan2Ptr);

            if(!feof(plan1Ptr))
            {
                puts("BUG");

                fclose(reserve1Ptr);
                fclose(reserve2Ptr);
                fclose(plan1Ptr);
                fclose(plan2Ptr);
                fclose(paymentPtr);

                return;
            }

            fread(&plan1, sizeof(plan), 1, plan1Ptr);
        }

        plan1.amount++;
        logined_client->wallet += plan1.cost;

        payment payment1;

        strcpy(payment1.client_username, logined_client->username);
        sprintf(payment1.date, "%d-%d-%d", date_year, date_month, date_day);
        sprintf(payment1.time, "%d:%d", date_hour, date_minute);
        strcpy(payment1.subject, "Reserve Canceled");

        fwrite(&payment1, sizeof(payment), 1, paymentPtr);

        fwrite(&plan1, sizeof(plan), 1, plan2Ptr);

        while(!feof(plan1Ptr))
        {
            fread(&plan1, sizeof(plan), 1, plan1Ptr);
            fwrite(&plan1, sizeof(plan), 1, plan2Ptr);
        }

        fwrite(&reserve2, sizeof(reserve), 1, reserve2Ptr);

        while(!feof(reserve1Ptr))
        {
            fread(&reserve1, sizeof(reserve), 1, reserve2Ptr);
            fwrite(&reserve1, sizeof(reserve), 1, reserve2Ptr);
        }

        fclose(reserve1Ptr);
        fclose(reserve2Ptr);
        fclose(plan1Ptr);
        fclose(plan2Ptr);
        fclose(paymentPtr);
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void reserved_plan(client* logined_client)
{
    FILE *reservePtr;

    if(reserve_file_number == 1)
    {
        reservePtr = fopen("Reserves1.dat", "ab+");
        rewind(reservePtr);
    }
    else
    {
        reservePtr = fopen("Reserves2.dat", "ab+");
        rewind(reservePtr);
    }

    if(reservePtr == NULL)
    {
        puts("File could not be opened.");

        fclose(reservePtr);

        return;
    }
    else
    {
        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");
        cyan();

        reserve reserve1;

        do
        {
            fread(&reserve1, sizeof(reserve), 1, reservePtr);

            if(strcmp(reserve1.client_username, logined_client->username) == 0)
            {
                printf("%d | %s | %s | %d", reserve1.self_id, reserve1.date, reserve1.meal, reserve1.food_id);
            }

        } while(!feof(reservePtr));

        fclose(reservePtr);
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void send_charge(void)
{
    purple();
    puts("----------------------------------------------------------------------------");
    cyan();

    printf("\n\n\n\n\n\n");

    FILE *cfPtr;
    FILE *cf2Ptr;

    if(file_number == 1)
    {
        cfPtr = fopen("Clients1.dat", "rb+");
        cf2Ptr = fopen("Clients2.dat", "wb+");
        file_number = 2;
    }
    else
    {
        cfPtr = fopen("Clients2.dat", "rb+");
        cf2Ptr = fopen("Clients1.dat", "wb+");
        file_number = 1;
    }

    if(cfPtr == NULL || cf2Ptr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);
        fclose(cf2Ptr);

        return;
    }
    else
    {
        client client1;
        printf("Username/SStudent ID : ");

        char username[21];
        scanf("%20s", username);

        while(!feof(cfPtr))
        {
            fread(&client1, sizeof(client), 1, cfPtr);

            if(strcmp(client1.username, username) == 0)
            {
                break;
            }
            else
            {
                fwrite(&client1, sizeof(client), 1, cf2Ptr);
            }

            if(feof(cfPtr))
            {
                puts("User not found.");

                fclose(cfPtr);
                fclose(cf2Ptr);

                return;
            }
        }

        printf("Amount : ");
        unsigned long long int amount;
        scanf("%llu", &amount);

        printf("\n\nSending charge to %s %s", client1.name, client1.family_name);
        
        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        cyan();

        puts("1.Continue                   2.Cancel");
        int a;
        scanf("%d", &a);

        if(a == 2)
        {   
            fclose(cfPtr);
            fclose(cf2Ptr);

            printf("\n\n\n\n\n\n");
            purple();
            puts("----------------------------------------------------------------------------");
            puts("success");

            return;
        }
        if(a == 1)
        {
            client1.wallet += amount;

            fwrite(&client1, sizeof(client), 1, cf2Ptr);

            while(!feof(cfPtr))
            {
                fread(&client1, sizeof(client), 1, cfPtr);
                fwrite(&client1, sizeof(client), 1, cf2Ptr);
            }
        }
    }

    fclose(cfPtr);
    fclose(cf2Ptr);

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void charge_account(client *logined_client)
{
    purple();
    puts("----------------------------------------------------------------------------");
    cyan();

    printf("\n\n\n\n\n\n");

    FILE *cfPtr;
    FILE *cf2Ptr;
    FILE *paymentPtr = fopen("Payment.dat", "ab");

    if(file_number == 1)
    {
        cfPtr = fopen("Clients1.dat", "rb+");
        cf2Ptr = fopen("Clients2.dat", "wb+");
        file_number = 2;
    }
    else
    {
        cfPtr = fopen("Clients2.dat", "rb+");
        cf2Ptr = fopen("Clients1.dat", "wb+");
        file_number = 1;
    }

    if(cfPtr == NULL || cf2Ptr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);
        fclose(cf2Ptr);
        fclose(paymentPtr);

        return;
    }
    else
    {
        client client1;

        while(!feof(cfPtr))
        {
            fread(&client1, sizeof(client), 1, cfPtr);

            if(strcmp(client1.username, logined_client->username) == 0 && client1.password == logined_client->password)
            {
                break;
            }
            else
            {
                fwrite(&client1, sizeof(client), 1, cf2Ptr);
            }

            if(feof(cfPtr))
            {
                puts("User not found. BUG");

                fclose(cfPtr);
                fclose(cf2Ptr);
                fclose(paymentPtr);

                return;
            }
        }

        printf("Amount : ");
        unsigned long long int amount;
        scanf("%llu", &amount);

        client1.wallet += amount;
        logined_client->wallet += amount;

        payment payment1;

        strcpy(payment1.client_username, logined_client->username);
        sprintf(payment1.date, "%d-%d-%d", date_year, date_month, date_day);
        sprintf(payment1.time, "%d:%d", date_hour, date_minute);
        strcpy(payment1.subject, "Account charged by client himself/herself");

        fwrite(&payment1, sizeof(payment), 1, paymentPtr);

        printf("\nCard number : ");
        unsigned long long int num;
        scanf("%llu", &num);

        printf("\nCard password : ");
        unsigned long long int password;
        scanf("%llu", &password);

        fwrite(&client1, sizeof(client), 1, cf2Ptr);

        while(!feof(cfPtr))
        {
            fread(&client1, sizeof(client), 1, cfPtr);
            fwrite(&client1, sizeof(client), 1, cf2Ptr);
        }
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");
    
    fclose(cfPtr);
    fclose(cf2Ptr);
    fclose(paymentPtr);

    return;
}

void take_food(client *logined_client)
{
    FILE *reserve1Ptr;
    FILE *reserve2Ptr;
    FILE *selfPtr = fopen("Self.dat", "rb");

    if(reserve_file_number == 1)
    {
        reserve1Ptr = fopen("Reserves1.dat", "ab+");
        reserve2Ptr = fopen("Reserves2.dat", "wb+");
        rewind(reserve1Ptr);
        reserve_file_number = 2;
    }
    else
    {
        reserve1Ptr = fopen("Reserves2.dat", "ab+");
        reserve2Ptr = fopen("Reserves2.dat", "wb+");
        rewind(reserve1Ptr);
        reserve_file_number = 1;
    }

    if(reserve1Ptr == NULL || reserve2Ptr == NULL || selfPtr == NULL)
    {
        puts("File could not be opened.");

        fclose(reserve1Ptr);
        fclose(reserve2Ptr);
        fclose(selfPtr);

        return;
    }
    else
    {
        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");
        cyan();

        // show reserved plans fo logined_client id

        reserve reserve1;
        reserve reserve2;

        fread(&reserve1, sizeof(reserve), 1, reserve1Ptr);

        while(feof(reserve1Ptr))
        {
            if(strcmp(reserve1.client_username, logined_client->username) != 0)
            {
                printf("%s | %u | %s | %u\n", reserve1.date, reserve1.self_id, reserve1.meal, reserve1.food_id);
            }
        }

        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");
        
        cyan();

        printf("Reserve date : \n");
        char date[11];
        gets(date);

        if(date[5] != '-')
        {
            puts("invalid");

            fclose(reserve1Ptr);
            fclose(reserve2Ptr);
            fclose(selfPtr);

            return;
        }
        else if(date[8] != '-')
        {
            puts("invalid");

            fclose(reserve1Ptr);
            fclose(reserve2Ptr);
            fclose(selfPtr);

            return;
        }

        printf("Self-ID : \n");
        unsigned int self_id;
        scanf("%u", &self_id);
        
        printf("Meal : ");
        char Meal[7];
        gets(Meal);

        reserve2.self_id = self_id;
        strcpy(reserve2.meal, Meal);
        strcpy(reserve2.date, date);
        strcpy(reserve2.client_username, logined_client->username);

        rewind(reserve1Ptr);

        fread(&reserve1, sizeof(reserve), 1, reserve1Ptr);

        while(reserve1.self_id != reserve2.self_id || strcmp(reserve1.date, reserve2.date) != 0 || strcmp(reserve1.client_username, logined_client->username) != 0 || strcmp(reserve1.meal, reserve2.meal) != 0)
        {
            fwrite(&reserve1, sizeof(reserve), 1, reserve2Ptr);

            if(feof(reserve1Ptr))
            {
                puts("invalid");

                fclose(reserve1Ptr);
                fclose(reserve2Ptr);
                fclose(selfPtr);

                return;
            }
        }

        rewind(selfPtr);

        self self1;

        fread(&self1, sizeof(self), 1, selfPtr);

        while(self1.id != self_id)
        {
            if(feof(selfPtr))
            {
                puts("invalid");

                fclose(reserve1Ptr);
                fclose(reserve2Ptr);
                fclose(selfPtr);

                return;
            }

            fread(&self1, sizeof(self), 1, selfPtr);
        }

        int open_time_hour;
        int open_time_minute;
        
        int close_time_hour;
        int close_time_minute;

        sscanf(self1.open_time, "%d:%d", &open_time_hour, &open_time_minute);
        sscanf(self1.close_time, "%d:%d", &close_time_hour, &close_time_minute);

        if((open_time_hour * 60) + open_time_minute > (date_hour * 60) + date_minute || (close_time_hour * 60) + close_time_minute < (date_hour * 60) + date_minute)
        {
            puts("permission-denid");

            fclose(reserve1Ptr);
            fclose(reserve2Ptr);
            fclose(selfPtr);

            return;
        }

        reserve2.food_id = reserve1.food_id;

        fwrite(&reserve2, sizeof(reserve), 1, reserve2Ptr);

        while(!feof(reserve1Ptr))
        {
            fread(&reserve1, sizeof(reserve), 1, reserve1Ptr);
            fwrite(&reserve1, sizeof(reserve), 1, reserve2Ptr);   
        }

        fclose(reserve1Ptr);
        fclose(reserve2Ptr);
        fclose(selfPtr);
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void RESERVE(client *logined_client)
{
    FILE *cfPtr;
    FILE *selfPtr = fopen("Self.dat", "rb+");
    FILE *planPtr;
    FILE *plan2Ptr;
    FILE *foodPtr = fopen("Foods.dat", "rb+");
    FILE *paymentPtr = fopen("Payment.dat", "ab");

    if(plan_file_number == 1)
    {
        planPtr = fopen("Plans1.dat", "ab+");
        plan2Ptr = fopen("Plans2.dat", "wb+");
        plan_file_number = 2;
        rewind(planPtr);
    }
    else
    {
        planPtr = fopen("Plans2.dat", "ab+");
        plan2Ptr = fopen("Plans1.dat", "wb+");
        plan_file_number = 1;
        rewind(planPtr);
    }

    if(reserve_file_number == 1)
    {
        cfPtr = fopen("Reserves1.dat", "ab+");
    }
    else
    {
        cfPtr = fopen("Reserves2.dat", "ab+");
    }

    if(cfPtr == NULL || selfPtr == NULL || planPtr == NULL || foodPtr == NULL || plan2Ptr == NULL || paymentPtr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);
        fclose(foodPtr);
        fclose(planPtr);
        fclose(selfPtr);
        fclose(plan2Ptr);
        fclose(paymentPtr);

        return;
    }
    else
    {
        self self1;
        reserve reserve1;
        plan plan1;
        food food1;

        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");
        cyan();

        puts("        Select Self        ");

        rewind(selfPtr);
        rewind(cfPtr);

        while(!feof(selfPtr))
        {
            fread(&self1, sizeof(self), 1, selfPtr);

            printf("Self ID : %u, Self name : %s\n", self1.id, self1.name);
        }

        unsigned int self_id;

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        cyan();

        printf("Self ID : ");

        scanf("%u", &self_id);
        
        rewind(selfPtr);
        fread(&self1, sizeof(self), 1, selfPtr);

        while(self1.id != self_id && !feof(selfPtr))
        {
            fread(&self1, sizeof(self), 1, selfPtr);

            if(feof(selfPtr))
            {
                puts("not-found");

                fclose(cfPtr);
                fclose(foodPtr);
                fclose(planPtr);
                fclose(selfPtr);
                fclose(plan2Ptr);
                fclose(paymentPtr);

                return;
            }
        }

        reserve1.self_id = self_id;

        purple();
        puts("----------------------------------------------------------------------------");
        cyan();
        printf("\n\n\n\n\n\n");

        rewind(planPtr);
        
        fread(&plan1, sizeof(plan), 1, planPtr);

        if(plan1.self_id == self_id)
        {
            printf("%s\n", plan1.date);
        }

        while(!feof(planPtr))
        {
            if(plan1.self_id == self_id)
            {
                printf("%s\n", plan1.date);
            }

            fread(&plan1, sizeof(plan), 1, planPtr);
        }

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        cyan();

        printf("Date : ");
        char Date[11];
        scanf("%s", Date);

        if(Date[4] != '-')
        {
            puts("invalid");

            fclose(cfPtr);
            fclose(foodPtr);
            fclose(planPtr);
            fclose(selfPtr);
            fclose(plan2Ptr);
            fclose(paymentPtr);

            return;
        }
        else if(Date[7] != '-')
        {
            puts("invalid");

            fclose(cfPtr);
            fclose(foodPtr);
            fclose(planPtr);
            fclose(selfPtr);
            fclose(plan2Ptr);
            fclose(paymentPtr);

            return;
        }

        strcpy(reserve1.date, Date);

        rewind(planPtr);

        fread(&plan1, sizeof(plan), 1, planPtr);

        while(strcmp(plan1.date, reserve1.date) != 0 && !feof(selfPtr))
        {
            fread(&plan1, sizeof(plan), 1, planPtr);

            if(feof(planPtr))
            {
                puts("not-found");

                fclose(cfPtr);
                fclose(foodPtr);
                fclose(planPtr);
                fclose(selfPtr);
                fclose(plan2Ptr);
                fclose(paymentPtr);

                return;
            }
        }

        purple();
        puts("----------------------------------------------------------------------------");
        cyan();
        printf("\n\n\n\n\n\n");

        rewind(planPtr);

        fread(&plan1, sizeof(plan), 1, planPtr);

        while(!feof(planPtr))
        {
            if(plan1.self_id == self_id && strcmp(reserve1.date, plan1.date) == 0)
            {
                printf("Meal : %s\n", plan1.type);
            }

            fread(&plan1, sizeof(plan), 1, planPtr);
        }

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        cyan();

        printf("Meal : ");
        scanf("%s", reserve1.meal);

        rewind(planPtr);

        fread(&plan1, sizeof(plan), 1, planPtr);

        while(plan1.self_id != self_id || strcmp(reserve1.date, plan1.date) != 0)
        {
            if(feof(planPtr))
            {
                puts("not-found");

                fclose(cfPtr);
                fclose(foodPtr);
                fclose(planPtr);
                fclose(selfPtr);
                fclose(plan2Ptr);
                fclose(paymentPtr);

                return;
            }

            fread(&plan1, sizeof(plan), 1, planPtr);
        }

        purple();
        puts("----------------------------------------------------------------------------");
        cyan();
        printf("\n\n\n\n\n\n");

        puts("        Select Food        ");

        rewind(foodPtr);
        rewind(planPtr);

        fread(&plan1, sizeof(plan), 1, planPtr);
        fread(&food1, sizeof(food), 1, foodPtr);

        while(plan1.self_id == self_id && strcmp(reserve1.date, plan1.date) == 0 && strcmp(plan1.type, reserve1.meal) == 0 && !feof(planPtr))
        {
            printf("Food ID : %u\n", plan1.food_id);

            fread(&plan1, sizeof(plan), 1, planPtr);
        }

        unsigned int food_id;

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        cyan();

        printf("Food ID : ");

        scanf("%u", &food_id);

        reserve1.food_id = food_id;

        if(plan1.amount > 0)
        {
            int plan_date_year;
            int plan_date_month;
            int plan_date_day;

            sscanf(plan1.date, "%d-%d-%d", &plan_date_year, &plan_date_month, &plan_date_day);

            if(date_day + 2 < plan_date_day)
            {
                plan1.amount--;
                plan plan2;

                fread(&plan2, sizeof(plan), 1, planPtr);

                while(plan2.food_id != plan1.food_id || plan2.self_id != plan1.self_id || strcmp(plan2.date, plan1.date) != 0 || strcmp(plan2.type, plan1.type) != 0)
                {
                    fread(&plan2, sizeof(plan), 1, planPtr);

                    if(plan2.food_id == plan1.food_id || plan2.self_id == plan1.self_id || strcmp(plan2.date, plan1.date) == 0 || strcmp(plan2.type, plan1.type) == 0)
                    {
                        break;
                    }

                    fwrite(&plan2, sizeof(plan), 1, plan2Ptr);

                    if(feof(planPtr))
                    {
                        puts("not-found");

                        fclose(cfPtr);
                        fclose(foodPtr);
                        fclose(planPtr);
                        fclose(selfPtr);
                        fclose(plan2Ptr);
                        fclose(paymentPtr);

                        return;
                    }
                }

                fwrite(&plan1, sizeof(plan), 1, plan2Ptr);

                while(!feof(planPtr))
                {
                    fread(&plan2, sizeof(plan), 1, planPtr);
                    fwrite(&plan2, sizeof(plan), 1, plan2Ptr);
                }

                while(logined_client->wallet < plan1.cost)
                {
                    charge_account(logined_client);
                }

                logined_client->wallet -= plan1.cost;

                payment payment1;
                
                strcpy(payment1.client_username, logined_client->username);
                sprintf(payment1.date, "%d-%d-%d", date_year, date_month, date_day);
                sprintf(payment1.time, "%d:%d", date_hour, date_minute);
                strcpy(payment1.subject, "Food reserved");

                fwrite(&payment1, sizeof(payment), 1, paymentPtr);

                strcpy(reserve1.client_username, logined_client->username);

                fwrite(&reserve1, sizeof(reserve), 1, cfPtr);

                fclose(cfPtr);
                fclose(foodPtr);
                fclose(planPtr);
                fclose(selfPtr);
                fclose(plan2Ptr);
                fclose(paymentPtr);

                printf("\n\n\n\n\n\n");
                purple();
                puts("----------------------------------------------------------------------------");
                puts("success");
            }
            else
            {
                puts("permission-denid");
                return;
            }
        }
        else
        {
            puts("not-found");
            return;
        }
    }

    return;
}

void add_poll(void)
{
    FILE *poll1Ptr;

    if(poll_file_number == 1)
    {
        poll1Ptr = fopen("Polls1.dat", "ab+");
    }
    else
    {
        poll1Ptr = fopen("Polls2.dat", "ab+");
    }

    if(poll1Ptr == NULL)
    {
        puts("File could not be opened.");

        fclose(poll1Ptr);

        return;
    }
    else
    {
        poll poll1;
        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");

        cyan();

        printf("Poll's deadline : ");
        char Date[11];
        scanf("%s", Date);

        if(Date[4] != '-')
        {
            puts("invalid");

            fclose(poll1Ptr);

            return;
        }
        else if(Date[7] != '-')
        {
            puts("invalid");

            fclose(poll1Ptr);

            return;
        }

        strcpy(poll1.date, Date);

        printf("\nA's text : ");
        gets(poll1.A_text);

        poll1.A = 0;

        printf("\nB's text : ");
        gets(poll1.B_text);

        poll1.B = 0;

        printf("\nC's text : ");
        gets(poll1.C_text);

        poll1.C = 0;

        printf("\nD's text : ");
        gets(poll1.D_text);

        poll1.D = 0;

        fwrite(&poll1, sizeof(poll), 1, poll1Ptr);

        fclose(poll1Ptr);

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        puts("success");
    }

    return;
}

void add_news(void)
{
    FILE *cfPtr = fopen("News.txt", "a");

    if(cfPtr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);

        return;
    }
    else
    {
        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");
        cyan();

        printf("Title : ");

        char title[100];
        gets(title);

        printf("\nMessage : ");

        char message[200];
        gets(message);

        fputs(title, cfPtr);
        fputs(message, cfPtr);

        fclose(cfPtr);
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void person_function(void)
{
    FILE *functionPtr = fopen("Function.dat", "ab+");
    rewind(functionPtr);

    FILE *client1Ptr;

    if(file_number == 1)
    {
        client1Ptr = fopen("Clients1.dat", "rb");
    }
    else
    {
        client1Ptr = fopen("Clients2.dat", "rb");
    }
    
    if(functionPtr == NULL || client1Ptr == NULL)
    {
        puts("File could not be opened / couldn't find any student that made action.");

        fclose(functionPtr);
        fclose(client1Ptr);

        return;
    }
    
    client client1;
    function function1;

    purple();
    puts("----------------------------------------------------------------------------");
    cyan();

    printf("\n\n\n\n\n\n");


    while(!feof(client1Ptr))
    {
        fread(&client1, sizeof(client), 1, client1Ptr);

        if(strcmp(client1.type, "student") == 0)
        {
            printf("username : %s | Name : %s | Family name : %s\n", client1.username, client1.name, client1.family_name);
        }
    }

    rewind(client1Ptr);

    purple();
    puts("----------------------------------------------------------------------------");
    cyan();

    printf("username : ");
    char username[21];
    scanf("%s", username);

    fread(&client1, sizeof(client), 1, client1Ptr);

    while(strcmp(client1.username, username) != 0)
    {
        if(feof(client1Ptr))
        {
            puts("invalid");

            fclose(client1Ptr);
            fclose(functionPtr);

            return;
        }

        fread(&client1, sizeof(client), 1, client1Ptr);
    }

    rewind(client1Ptr);

    while(!feof(functionPtr))
    {
        fread(&function1, sizeof(function), 1, functionPtr);

        if(strcmp(function1.client_username, username))
        {
            printf("%s | %s | %s\n", function1.date, function1.time, function1.subject);
        }
    }

    fclose(client1Ptr);
    fclose(functionPtr);

    return;
}

void charge_student_account(void)
{
    FILE *cfPtr;
    FILE *cf2Ptr;
    FILE *paymentPtr = fopen("Payment.dat", "ab");

    int action;
    client client1;

    if(file_number == 1)
    {
        cfPtr = fopen("Clients1.dat", "rb+");
        cf2Ptr = fopen("Clients2.dat", "wb");
        file_number = 2;
    }
    else
    {
        cfPtr = fopen("Clients2.dat", "rb+");
        cf2Ptr = fopen("Clients1.dat", "wb");
        file_number = 1;
    }

    if(cfPtr == NULL || cf2Ptr == NULL || paymentPtr == NULL)
    {
        puts("File could not be opened / there no active student atm.");

        fclose(cfPtr);
        fclose(cf2Ptr);
        fclose(paymentPtr);

        return;
    }

    while(1)
    {
        purple();
        puts("----------------------------------------------------------------------------");
        cyan();
        printf("\n\n\n\n\n\n");

        while(!feof(cfPtr))
        {
            fread(&client1, sizeof(client), 1, cfPtr);

            if(strcmp(client1.type, "student") == 0)
            {
                printf("%s | %s | %s | %lld | %s\n", client1.name, client1.family_name, client1.username, client1.national_id_code, client1.username);
            }
        }

        rewind(cfPtr);

        printf("Username : ");

        char username[21];
        scanf("%20s", username);

        rewind(cfPtr);

        do{
            fread(&client1, sizeof(client), 1, cfPtr);
            
            if(strcmp(username, client1.username) != 0)
            {
                fwrite(&client1, sizeof(client), 1, cf2Ptr);
            }

        } while( strcmp(username, client1.username) != 0 && !feof(cfPtr) );

        if(feof(cfPtr))
        {
            puts("Username Not found.");
            puts("1.try again");
            puts("2.Exit");

            purple();
            puts("----------------------------------------------------------------------------");
            cyan();

            scanf("%d", &action);
        }
        else 
        {
            printf("Charge amount : ");

            unsigned long long int charge;
            scanf("%llu", &charge);

            client1.wallet += charge;

            payment payment1;

            strcpy(payment1.client_username, client1.username);
            sprintf(payment1.date, "%d-%d-%d", date_year, date_month, date_day);
            sprintf(payment1.time, "%d:%d", date_hour, date_minute);
            strcpy(payment1.subject, "Account charged by admin");

            fwrite(&payment1, sizeof(payment), 1, paymentPtr);

            break;
        }

        if(action == 2)
        {
            break;
        }
    }

    if(action == 2)
    {
        fclose(cfPtr);
        fclose(cf2Ptr);
        fclose(paymentPtr);

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        puts("success");

        return;
    }
    else
    {
        fwrite(&client1, sizeof(client), 1, cf2Ptr);

        while(!feof(cfPtr))
        {
            fread(&client1, sizeof(client), 1, cfPtr);
            fwrite(&client1, sizeof(client), 1, cf2Ptr);
        }

        fclose(cfPtr);
        fclose(cf2Ptr);
        fclose(paymentPtr);
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void define_meal_plan(void)
{
    FILE *cfPtr;
    FILE *cf2Ptr = fopen("Foods.dat", "rb");
    FILE *cf3Ptr = fopen("Self.dat", "rb");

    if(plan_file_number == 1)
    {
        cfPtr = fopen("Plans1.dat", "ab+");
    }
    else
    {
        cfPtr = fopen("Plans2.dat", "ab+");
    }

    if(cfPtr == NULL || cf2Ptr == NULL || cf3Ptr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);
        fclose(cf2Ptr);
        fclose(cf3Ptr);

        return;
    }
    else
    {
        self self1;
        food food1;
        plan plan1;

        purple();
        puts("----------------------------------------------------------------------------");
        cyan();

        printf("\n\n\n\n\n\n");

        puts("       Select self       ");

        while(!feof(cf3Ptr))
        {
            fread(&self1, sizeof(self), 1, cf3Ptr);
            printf("Self ID : %d, Self name : %s\n", self1.id, self1.name);
        }

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        cyan();

        printf("Self ID : ");

        unsigned int id;
        scanf("%u", &id);

        purple();
        puts("----------------------------------------------------------------------------");
        cyan();

        plan1.self_id = id;

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        cyan();

        puts("        Select date        ");

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        cyan();

        printf("Date : ");
        scanf("%10s", plan1.date);

        purple();
        puts("----------------------------------------------------------------------------");
        cyan();
        printf("\n\n\n\n\n\n");

        puts("       Select food       ");

        while(!feof(cf2Ptr))
        {
            fread(&food1, sizeof(food), 1, cf2Ptr);
            printf("Food ID : %d, Food name : %s\n", food1.id, food1.name);
        }

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        cyan();

        printf("Food ID : ");

        scanf("%u", &id);

        plan1.food_id = id;

        purple();
        puts("----------------------------------------------------------------------------");
        cyan();
        printf("\n\n\n\n\n\n");

        printf("Amount of food : ");
        unsigned int amount;
        scanf("%u", &amount);
        
        purple();
        puts("----------------------------------------------------------------------------");
        cyan();
        printf("\n\n\n\n\n\n");

        puts("        Select Meal        ");
        
        puts("1.Launch");
        puts("2.Dinner");

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        cyan();

        printf("Meal : ");

        scanf("%s", plan1.type);

        plan1.cost = food1.price;

        fwrite(&plan1, sizeof(plan), 1, cfPtr);

        fclose(cfPtr);
        fclose(cf2Ptr);
        fclose(cf3Ptr);
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void define_food(void)
{
    FILE *cfPtr = fopen("Foods.dat", "ab+");

    if(cfPtr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);

        return;
    }
    else
    {
        food food1;

        purple();
        puts("----------------------------------------------------------------------------");
        cyan();
        printf("\n\n\n\n\n\n");

        printf("Id : ");
        scanf("%u", &food1.id);

        printf("\nName : ");
        scanf("%20s", food1.name);

        printf("\nType (1.Main-food 2.Dessert) : ");
        scanf("%d", &food1.type);

        printf("\nPrice : ");
        scanf("%llu", &food1.price);

        purple();
        puts("----------------------------------------------------------------------------");

        fwrite(&food1, sizeof(food), 1, cfPtr);

        fclose(cfPtr);

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        puts("success");
    }

    return;
}

void define_self(void)
{
    purple();
    puts("----------------------------------------------------------------------------");
    cyan();
    printf("\n\n\n\n\n\n");

    FILE *cfPtr = fopen("Self.dat", "ab+");
    self self1;

    if(cfPtr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);

        return;
    }
    else
    {
        printf("Id : ");
        scanf("%d", &self1.id);

        printf("\nName : ");
        scanf("%20s", self1.name);

        printf("\nAddress : ");
        scanf("%20s", self1.address);

        printf("\nCapacity : ");
        scanf("%u", &self1.capacity);

        printf("\nSelf's type (1.Male 2.Female) : ");
        scanf("%d", &self1.self_type);

        printf("\nMeal (1.launch 2.dinner) : ");
        scanf("%d", &self1.Meal_time);

        printf("\nOpen-time : ");
        char Open_time[6];
        scanf("%s", Open_time);

        if(Open_time[2] != ':')
        {
            puts("invalid");

            fclose(cfPtr);

            return;
        }
        strcpy(self1.open_time, Open_time);

        printf("\nClose-time : ");
        char Close_time[5];
        scanf("%s", Close_time);

        if(Close_time[2] != ':')
        {
            puts("invalid");

            fclose(cfPtr);

            return;
        }
        strcpy(self1.close_time, Close_time);

        fwrite(&self1, sizeof(self), 1, cfPtr);

        fclose(cfPtr);
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void deactivate(void)
{
    FILE *cfPtr;
    FILE *cf2Ptr;

    int action;
    client client1;

    if(file_number == 1)
    {
        cfPtr = fopen("Clients1.dat", "rb+");
        cf2Ptr = fopen("Clients2.dat", "wb+");
        file_number = 2;
    }
    else
    {
        cfPtr = fopen("Clients2.dat", "rb+");
        cf2Ptr = fopen("Clients1.dat", "wb+");
        file_number = 1;
    }

    if(cfPtr == NULL || cf2Ptr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);
        fclose(cf2Ptr);

        return;
    }

    while(1)
    {
        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");
        cyan();

        while(!feof(cfPtr))
        {
            fread(&client1, sizeof(client), 1, cfPtr);

            if(strcmp(client1.type, "student") == 0)
            {
                printf("%s | %s | %s | %lld | %s\n", client1.name, client1.family_name, client1.username, client1.national_id_code, client1.username);
            }
        }

        printf("Username : ");

        char username[21];
        scanf("%20s", username);

        rewind(cfPtr);

        do{
            fread(&client1, sizeof(client), 1, cfPtr);
            
            if(strcmp(username, client1.username) != 0)
            {
                fwrite(&client1, sizeof(client), 1, cf2Ptr);
            }

        } while( strcmp(username, client1.username) != 0 && !feof(cfPtr) );

        if(feof(cfPtr))
        {
            puts("Username Not found.");
            puts("1.try again");
            puts("2.Exit");

            purple();
            puts("----------------------------------------------------------------------------");
            cyan();

            scanf("%d", &action);
        }
        else if(strcmp(client1.type, "Admin") == 0)
        {
            puts("Permission denied.");
            puts("1.try again");
            puts("2.Exit");

            purple();
            puts("----------------------------------------------------------------------------");
            cyan();

            scanf("%d", &action);
        }
        else 
        {
            client1.approve = 0;
            break;
        }

        if(action == 2)
        {
            break;
        }
    }

    if(action == 2)
    {
        fclose(cfPtr);
        fclose(cf2Ptr);

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        puts("success");

        return;
    }
    else
    {
        fwrite(&client1, sizeof(client), 1, cf2Ptr);

        while(!feof(cfPtr))
        {
            fread(&client1, sizeof(client), 1, cfPtr);
            fwrite(&client1, sizeof(client), 1, cf2Ptr);
        }

        fclose(cfPtr);
        fclose(cf2Ptr);
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void remove_student(void)
{
    FILE *cfPtr;
    FILE *cf2Ptr;

    int action;
    client client1;

    if(file_number == 1)
    {
        cfPtr = fopen("Clients1.dat", "rb+");
        cf2Ptr = fopen("Clients2.dat", "wb");
        file_number = 2;
    }
    else
    {
        cfPtr = fopen("Clients2.dat", "rb+");
        cf2Ptr = fopen("Clients1.dat", "wb");
        file_number = 1;
    }

    if(cfPtr == NULL || cf2Ptr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);
        fclose(cf2Ptr);

        return;
    }

    while(1)
    {
        purple();
        puts("----------------------------------------------------------------------------");
        printf("\n\n\n\n\n\n");
        cyan();

        while(!feof(cfPtr))
        {
            fread(&client1, sizeof(client), 1, cfPtr);

            if(strcmp(client1.type, "student") == 0)
            {
                printf("%s | %s | %s | %lld | %s\n", client1.name, client1.family_name, client1.username, client1.national_id_code, client1.username);
            }
        }

        rewind(cfPtr);

        printf("Username : ");

        char username[21];
        scanf("%20s", username);

        rewind(cfPtr);

        do{
            fread(&client1, sizeof(client), 1, cfPtr);
            
            if(strcmp(username, client1.username) != 0)
            {
                fwrite(&client1, sizeof(client), 1, cf2Ptr);
            }

        } while( strcmp(username, client1.username) != 0 && !feof(cfPtr) );

        if(feof(cfPtr))
        {
            puts("Username Not found.");
            puts("1.try again");
            puts("2.Exit");

            puts("----------------------------------------------------------------------------");

            scanf("%d", &action);
        }
        else if(strcmp(client1.type, "Admin") == 0)
        {
            puts("Permission denied.");
            puts("1.try again");
            puts("2.Exit");

            puts("----------------------------------------------------------------------------");

            scanf("%d", &action);
        }
        else 
        {
            break;
        }

        if(action == 2)
        {
            break;
        }
    }

    if(action == 2)
    {
        fclose(cfPtr);
        fclose(cf2Ptr);

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        puts("success");

        return;
    }
    else
    {
        while(!feof(cfPtr))
        {
            fread(&client1, sizeof(client), 1, cfPtr);
            fwrite(&client1, sizeof(client), 1, cf2Ptr);
        }

        fclose(cfPtr);
        fclose(cf2Ptr);
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void change_student_password(void)
{
    FILE *cfPtr;
    FILE *cf2Ptr;

    int action;
    client client1;
    client client2;

    if(file_number == 1)
    {
        cfPtr = fopen("Clients1.dat", "ab+");
        cf2Ptr = fopen("Clients2.dat", "w");
        fclose(cf2Ptr);
        cf2Ptr = fopen("Clients2.dat", "wb");
        rewind(cfPtr);
        file_number = 2;
    }
    else
    {
        cfPtr = fopen("Clients2.dat", "ab+");
        cf2Ptr = fopen("Clients1.dat", "w");
        fclose(cf2Ptr);
        cf2Ptr = fopen("Clients1.dat", "wb");
        rewind(cfPtr);
        file_number = 1;
    }

    if(cfPtr == NULL || cf2Ptr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);
        fclose(cf2Ptr);

        return;
    }

    while(1)
    {
        purple();
        puts("----------------------------------------------------------------------------");
        cyan();

        printf("\n\n\n\n\n\n");

        while(!feof(cfPtr))
        {
            fread(&client1, sizeof(client), 1, cfPtr);

            if(strcmp(client1.type, "student") == 0)
            {
                printf("%s | %s | %s | %lld | %s\n", client1.name, client1.family_name, client1.username, client1.national_id_code, client1.username);
            }
        }

        rewind(cfPtr);

        printf("Username : ");

        char username[21];
        scanf("%20s", username);

        do{
            fread(&client1, sizeof(client), 1, cfPtr);
            
            if(strcmp(username, client1.username) != 0)
            {
                fwrite(&client1, sizeof(client), 1, cf2Ptr);
            }

        } while( strcmp(username, client1.username) != 0 && !feof(cfPtr));

        if(feof(cfPtr))
        {
            puts("Username Not found.");
            puts("1.try again");
            puts("2.Exit");

            purple();
            puts("----------------------------------------------------------------------------");
            cyan();

            scanf("%d", &action);
        }
        else 
        {            
            purple();
            puts("----------------------------------------------------------------------------");
            cyan();

            printf("\n\n\n\n\n\n");

            printf("New password : ");
            
            char password[21];
            scanf("%20s", password);

            client2 = client1;

            strcpy(client2.password, password);
            break;
        }

        if(action == 2)
        {
            break;
        }
    }

    if(action == 2)
    {
        fclose(cfPtr);
        fclose(cf2Ptr);

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        puts("success");
    
        return;
    }
    else
    {   
        fwrite(&client2, sizeof(client), 1, cf2Ptr);

        while(!feof(cfPtr))
        {
            fread(&client1, sizeof(client), 1, cfPtr);
            fwrite(&client1, sizeof(client), 1, cf2Ptr);
        }

        fclose(cfPtr);
        fclose(cf2Ptr);
    }

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void approve(void)
{
    FILE *cfPtr;
    FILE *cf2Ptr;

    client client1;

    if(file_number == 1)
    {
        cfPtr = fopen("Clients1.dat", "rb+");
        cf2Ptr = fopen("Clients2.dat", "w");
        fclose(cf2Ptr);
        cf2Ptr = fopen("Clients2.dat", "wb");
        file_number = 2;
    }
    else
    {
        cfPtr = fopen("Clients2.dat", "rb+");
        cf2Ptr = fopen("Clients1.dat", "w");
        fclose(cf2Ptr);
        cf2Ptr = fopen("Clients1.dat", "wb+");
        file_number = 1;
    }

    if(cfPtr == NULL || cf2Ptr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);
        fclose(cf2Ptr);

        return;
    }

    purple();
    puts("----------------------------------------------------------------------------");
    printf("\n\n\n\n\n\n");

    yellow();
    while(!feof(cfPtr))
    {
        fread(&client1, sizeof(client), 1, cfPtr);

        if(client1.approve == 0)
        {
            printf("Username : %s\n", client1.username);
            printf("Name : %s\n", client1.name);
            printf("Family-name : %s\n", client1.family_name);

            green();
            puts("-----------------");
            yellow();
        }
    }

    purple();
    printf("\n\n\n\n\n\n");
    puts("----------------------------------------------------------------------------");

    yellow();
    printf("Username : ");

    char username[21];
    scanf("%20s", username);

    rewind(cfPtr);

    while(!feof(cfPtr))
    {
        fread(&client1, sizeof(client), 1, cfPtr);
        if(strcmp(client1.username, username) == 0)
        {
            break;
        }
            
        fwrite(&client1, sizeof(client), 1, cf2Ptr);

        if(feof(cfPtr))
        {
            puts("Invalid");
            return;
        }
    }

    client1.approve = 1;

    fwrite(&client1, sizeof(client), 1, cf2Ptr);

    while(!feof(cfPtr))
    {
        fread(&client1, sizeof(client), 1, cfPtr);
        fwrite(&client1, sizeof(client), 1, cf2Ptr);
    }

    fclose(cfPtr);
    fclose(cf2Ptr);

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    puts("success");

    return;
}

void change_password(client *logined_client)
{
    FILE *cfPtr;
    FILE *cf2Ptr;
    
    if(file_number == 1)
    {
        cfPtr = fopen("Clients1.dat", "rb+");
        cf2Ptr = fopen("Clients2.dat", "w");
        fclose(cf2Ptr);
        cf2Ptr = fopen("Clients2.dat", "wb");
        file_number = 2;
    }
    else
    {
        cfPtr = fopen("Clients2.dat", "rb+");
        cf2Ptr = fopen("Clients1.dat", "w");
        fclose(cf2Ptr);
        cf2Ptr = fopen("Clients1.dat", "wb");
        file_number = 1;
    }

    if( cfPtr == NULL || cf2Ptr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);
        fclose(cf2Ptr);

        return;
    }
    else
    {
        client client1;
        rewind(cfPtr);

        do {

            fread(&client1, sizeof(client), 1, cfPtr);
            if(strcmp(logined_client->username, client1.username) != 0)
            {
                fwrite(&client1, sizeof(client), 1, cf2Ptr);
            }

        } while( strcmp(logined_client->username, client1.username) != 0);

        printf("\n\n\n\n\n\n");
        
        printf("Password : ");

        char curr_password[21];
        scanf("%20s", curr_password);

        while(strcmp(logined_client->password, curr_password) != 0)
        {
            puts("Wrong password.");
            puts("1.try again");
            puts("2.Exit");

            printf("\n\n\n\n\n\n");
            puts("----------------------------------------------------------------------------");

            int a;
            scanf("%d", &a);

            if(a == 1)
                scanf("%20s", curr_password);

            if(a == 2)
                return;
        }

        printf("New password : ");

        char password[21];
        scanf("%20s", password);

        strcpy(client1.password, password);

        *logined_client = client1;

        fwrite(&client1, sizeof(client), 1, cf2Ptr);

        while(!feof(cfPtr))
        {
            fread(&client1, sizeof(client), 1, cfPtr);
            fwrite(&client1, sizeof(client), 1, cf2Ptr);
        }

        fclose(cfPtr);
        fclose(cf2Ptr);

        printf("\n\n\n\n\n\n");
        purple();
        puts("----------------------------------------------------------------------------");
        puts("success");

        return;
    }
}

int menu(client *logined_client)
{
    if(strcmp(logined_client->type, "admin") == 0) // admin
    {
        while(1)
        {
            puts("----------------------------------------------------------------------------");
            printf("\n\n\n\n\n\n");

            cyan();
            puts("1  | Change your password");
            puts("2  | Approve");
            puts("3  | Change student's password");
            puts("4  | Remove student");
            puts("5  | Deactivate");
            puts("6  | Define self");
            puts("7  | Define food");
            puts("8  | Define meal plan");
            puts("9  | Charge student's account");
            puts("10 | Person's function");
            puts("11 | Add news");
            puts("12 | Add poll");
            puts("13 | Register");
            puts("14 | change date/time");
            
            printf("\n");

            puts("-1 | Log out");

            green();
            puts("----------------------------------------------------------------------------");
            printf("current date : %d-%d-%d  |  current time : %d-%d\n", date_year, date_month, date_day, date_hour, date_minute);
            puts("----------------------------------------------------------------------------");

            printf("\n\n\n\n\n\n");
            purple();
            puts("----------------------------------------------------------------------------");
        
            int action;
            scanf("%d", &action);

            if(action == 1)
            {
                change_password(logined_client);
            }

            if(action == 2)
            {
                approve();
            }

            if(action == 3)
            {
                change_student_password();
            }

            if(action == 4)
            {
                remove_student();
            }

            if(action == 5)
            {
                deactivate();
            }

            if(action == 6)
            {
                define_self();
            }

            if(action == 7)
            {
                define_food();
            }
            
            if(action == 8)
            {
                define_meal_plan();
            }

            if(action == 9)
            {
                charge_student_account();
            }

            if(action == 10)
            {
                person_function();
            }

            if(action == 11)
            {
                add_news();
            }

            if(action == 12)
            {
                add_poll();
            }

            if(action == 13)
            {
                register_window(logined_client);
            }

            if(action == 14)
            {
                change_date_time();
            }

            if(action == -1)
            {
                return 0;
            }
        }
    }
    else // student
    {
        while(1)
        {
            purple();
            puts("----------------------------------------------------------------------------");
            printf("\n\n\n\n\n\n");

            cyan();
            puts("1  | Change password");
            puts("2  | Reserve");
            puts("3  | Take food");
            puts("4  | Charge account");
            puts("5  | Send charge");
            puts("6  | reserved plan");
            puts("7  | Cancel reserve");
            puts("8  | Daily reserve");
            puts("9  | Change self");
            puts("10 | Payment log");
            puts("11 | Check news");
            puts("12 | vote");

            printf("\n");

            puts("-1 | Log out");

            green();
            puts("----------------------------------------------------------------------------");
            printf("current date : %d-%d-%d  |  current time : %d-%d\n", date_year, date_month, date_day, date_hour, date_minute);
            puts("----------------------------------------------------------------------------");

            printf("\n\n\n\n\n\n");
            purple();
            puts("----------------------------------------------------------------------------");
        
            int action;
            scanf("%d", &action);

            if(action == 1)
            {
                change_password(logined_client);
            }
            
            if(action == 2)
            {
                RESERVE(logined_client);
            }

            if(action == 3)
            {
                take_food(logined_client);
            }

            if(action == 4)
            {
                charge_account(logined_client);
            }

            if(action == 5)
            {
                send_charge();
            }

            if(action == 6)
            {
                reserved_plan(logined_client);
            }

            if(action == 7)
            {
                cancel_reserve(logined_client);
            }

            if(action == 8)
            {
                daily_reserve(logined_client);
            }

            if(action == 9)
            {
                change_self(logined_client);
            }

            if(action == 10)
            {
                payment_log(logined_client);
            }

            if(action == 11)
            {
                check_news();
            }

            if(action == 12)
            {
                vote();
            }

            if(action == -1)
            {
                return 0;
            }
        }
    }
}

void firstClient(void)
{
    client client1 = {"", "", "Admin", "Admin", 0, "", "Male", "admin", 1, 0};
    
    FILE *cfPtr;

    if(file_number == 1)
    {
        cfPtr = fopen("Clients1.dat", "ab+");
    }
    else
    {
        cfPtr = fopen("Clients2.dat", "ab+");
    }

    if(cfPtr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);

        return;
    }

    fwrite(&client1, sizeof(client), 1, cfPtr);

    fclose(cfPtr);

    return;
}

int check_UsernameAndPassword(char *username, char* password, client *logined_client)
{
    FILE *cfPtr;

    if(file_number == 1)
    {
        cfPtr = fopen("Clients1.dat", "ab+");
    }
    else
    {
        cfPtr = fopen("Clients2.dat", "ab+");
    }

    if(cfPtr == NULL)
    {
        puts("File could not be opened.");

        fclose(cfPtr);

        return 1;
    }
    else
    {   
        client client1;

        rewind(cfPtr);

        while(!feof(cfPtr))
        {
            fread(&client1, sizeof(client), 1, cfPtr);

            if(strcmp(client1.username, username) == 0)
            {
                if(strcmp(client1.password, password) == 0)
                {
                    if(client1.approve == 1)
                    {
                        *logined_client = client1;
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return 1;
                }
            }
        }  
    }
    fclose(cfPtr);

    return 1;
}

int login_window(client *logined_client)
{
    char username[21];
    char password[21];

    purple();
    puts("----------------------------------------------------------------------------");
    printf("\n\n\n\n\n\n");

    cyan();
    printf("Username : ");
    scanf("%20s", username);

    printf("\nPassword : ");
    scanf("%20s", password);

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");

    if(check_UsernameAndPassword(username, password, logined_client) == 1)
    {
        puts("Password/Username not corrent or you are not approved yet");
        return 1;
    }

    puts("success");

    return 0;
}

void register_window(client *logined_client)
{
    purple();
    puts("----------------------------------------------------------------------------");
    printf("\n\n\n\n\n\n");

    client client1 = {"", "", "", "", 0, "", -1};

    cyan();
    printf("Name : ");
    scanf("%20s", client1.name);

    printf("Family name : ");
    scanf("%20s", client1.family_name);

    printf("Username : ");
    scanf("%20s", client1.username);

    printf("Password : ");
    scanf("%20s", client1.password);

    printf("National-id-code : ");
    scanf("%lld", &client1.national_id_code);

    printf("Birthday : ");
    char date[11];
    scanf("%s", date);

    if(date[4] != '-')
    {
        puts("invalid");
        return;
    }
    else if(date[7] != '-')
    {
        puts("invalid");
        return;
    }

    strcpy(client1.birthday, date);

    printf("Gender : ");
    scanf("%s", client1.gender);

    printf("Type : ");
    scanf("%s", client1.type);

    client1.wallet = 1;
    client1.approve = 0;

    FILE *cfPtr;

    if(file_number == 1)
    {
        cfPtr = fopen("Clients1.dat", "ab+");
    }
    else
    {
        cfPtr = fopen("Clients2.dat", "ab+");
    }

    if(cfPtr == NULL)
    {
        puts("File could not be opened.");
    }
    else 
    {
        if(strcmp(logined_client->username, "admin") == 0)
        {
            client1.approve = 1;
            fwrite(&client1, sizeof(client), 1, cfPtr);
        }
        else
        {
            fwrite(&client1, sizeof(client), 1, cfPtr);
        }
    }

    fclose(cfPtr);

    puts("success");

    return;
}

int first_window(void)
{   
    purple();
    puts("----------------------------------------------------------------------------");
    printf("\n\n\n\n\n\n");

    cyan();
    printf("%s\n", "1.Login");
    printf("%s\n", "2.Register");

    printf("\n\n\n\n\n\n");
    purple();
    puts("----------------------------------------------------------------------------");
    
    int action;
    scanf("%d", &action);

    if(action == 1)
    return 1;
    
    else
    return 2;
}

int main(void)
{
    firstClient();

    client *logined_client = (client *)malloc(sizeof(client));

    start: // label

    while(1)
    {
        int result = first_window();
        
        if(result == 2)
        {
            register_window(logined_client);
        }
        else
        {
            int result2 = login_window(logined_client);
            
            if(result2 == 0)
            {
                break;
            }
        }
    }

    while(1)
    {
        int res = menu(logined_client);

        if(res == 0)
        {
            break;
        }
    }

    goto start;
    
    return 0;
}