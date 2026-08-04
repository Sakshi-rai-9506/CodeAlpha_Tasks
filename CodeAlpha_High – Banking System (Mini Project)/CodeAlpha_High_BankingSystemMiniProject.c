#include <stdio.h>
#include <stdlib.h>

struct Account
{
    int accountNo;
    char name[50];
    float balance;
};

void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();

int main()
{
    int choice;

    while(1)
    {
        printf("\n====================================");
        printf("\n     BANK ACCOUNT MANAGEMENT");
        printf("\n====================================");
        printf("\n1. Create Account");
        printf("\n2. Deposit");
        printf("\n3. Withdraw");
        printf("\n4. Balance Enquiry");
        printf("\n5. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                deposit();
                break;

            case 3:
                withdraw();
                break;

            case 4:
                balanceEnquiry();
                break;

            case 5:
                printf("\nThank You!\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}

// Create Account
void createAccount()
{
    FILE *fp;
    struct Account a;

    fp = fopen("bank.dat","ab");

    if(fp==NULL)
    {
        printf("\nFile Error!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d",&a.accountNo);

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]",a.name);

    printf("Enter Initial Balance: ");
    scanf("%f",&a.balance);

    fwrite(&a,sizeof(a),1,fp);

    fclose(fp);

    printf("\nAccount Created Successfully!\n");
}

// Deposit Money
void deposit()
{
    FILE *fp;
    struct Account a;
    int acc, found=0;
    float amount;

    fp=fopen("bank.dat","rb+");

    if(fp==NULL)
    {
        printf("\nNo Account Found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d",&acc);

    while(fread(&a,sizeof(a),1,fp))
    {
        if(a.accountNo==acc)
        {
            printf("Enter Deposit Amount: ");
            scanf("%f",&amount);

            a.balance += amount;

            fseek(fp,-sizeof(a),SEEK_CUR);
            fwrite(&a,sizeof(a),1,fp);

            printf("\nDeposit Successful!");
            printf("\nCurrent Balance = %.2f\n",a.balance);

            found=1;
            break;
        }
    }

    if(!found)
        printf("\nAccount Not Found!\n");

    fclose(fp);
}

// Withdraw Money
void withdraw()
{
    FILE *fp;
    struct Account a;
    int acc, found=0;
    float amount;

    fp=fopen("bank.dat","rb+");

    if(fp==NULL)
    {
        printf("\nNo Account Found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d",&acc);

    while(fread(&a,sizeof(a),1,fp))
    {
        if(a.accountNo==acc)
        {
            printf("Enter Withdraw Amount: ");
            scanf("%f",&amount);

            if(amount > a.balance)
            {
                printf("\nInsufficient Balance!\n");
            }
            else
            {
                a.balance -= amount;

                fseek(fp,-sizeof(a),SEEK_CUR);
                fwrite(&a,sizeof(a),1,fp);

                printf("\nWithdrawal Successful!");
                printf("\nRemaining Balance = %.2f\n",a.balance);
            }

            found=1;
            break;
        }
    }

    if(!found)
        printf("\nAccount Not Found!\n");

    fclose(fp);
}

// Balance Enquiry
void balanceEnquiry()
{
    FILE *fp;
    struct Account a;
    int acc, found=0;

    fp=fopen("bank.dat","rb");

    if(fp==NULL)
    {
        printf("\nNo Account Found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d",&acc);

    while(fread(&a,sizeof(a),1,fp))
    {
        if(a.accountNo==acc)
        {
            printf("\nAccount Number : %d",a.accountNo);
            printf("\nAccount Holder : %s",a.name);
            printf("\nCurrent Balance: %.2f\n",a.balance);

            found=1;
            break;
        }
    }

    if(!found)
        printf("\nAccount Not Found!\n");

    fclose(fp);
}