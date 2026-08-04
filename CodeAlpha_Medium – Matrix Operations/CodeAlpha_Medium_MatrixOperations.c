#include <stdio.h>

#define MAX 10

// Function for Matrix Addition
void addMatrix(int a[MAX][MAX], int b[MAX][MAX], int r, int c)
{
    int sum[MAX][MAX];

    printf("\nMatrix Addition:\n");

    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            sum[i][j]=a[i][j]+b[i][j];
            printf("%4d",sum[i][j]);
        }
        printf("\n");
    }
}

// Function for Matrix Multiplication
void multiplyMatrix(int a[MAX][MAX], int b[MAX][MAX], int r1, int c1, int c2)
{
    int mul[MAX][MAX];

    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c2;j++)
        {
            mul[i][j]=0;

            for(int k=0;k<c1;k++)
            {
                mul[i][j]+=a[i][k]*b[k][j];
            }
        }
    }

    printf("\nMatrix Multiplication:\n");

    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c2;j++)
        {
            printf("%4d",mul[i][j]);
        }
        printf("\n");
    }
}

// Function for Matrix Transpose
void transposeMatrix(int a[MAX][MAX], int r, int c)
{
    printf("\nTranspose of Matrix:\n");

    for(int i=0;i<c;i++)
    {
        for(int j=0;j<r;j++)
        {
            printf("%4d",a[j][i]);
        }
        printf("\n");
    }
}

int main()
{
    int a[MAX][MAX], b[MAX][MAX];
    int r1,c1,r2,c2;
    int choice;

    printf("========== MATRIX OPERATIONS ==========\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Matrix Transpose\n");

    printf("\nEnter your choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:

            printf("Enter rows and columns of Matrix A: ");
            scanf("%d%d",&r1,&c1);

            printf("Enter elements of Matrix A:\n");
            for(int i=0;i<r1;i++)
                for(int j=0;j<c1;j++)
                    scanf("%d",&a[i][j]);

            printf("Enter elements of Matrix B:\n");
            for(int i=0;i<r1;i++)
                for(int j=0;j<c1;j++)
                    scanf("%d",&b[i][j]);

            addMatrix(a,b,r1,c1);
            break;

        case 2:

            printf("Enter rows and columns of Matrix A: ");
            scanf("%d%d",&r1,&c1);

            printf("Enter rows and columns of Matrix B: ");
            scanf("%d%d",&r2,&c2);

            if(c1!=r2)
            {
                printf("Matrix Multiplication Not Possible!\n");
                return 0;
            }

            printf("Enter Matrix A:\n");
            for(int i=0;i<r1;i++)
                for(int j=0;j<c1;j++)
                    scanf("%d",&a[i][j]);

            printf("Enter Matrix B:\n");
            for(int i=0;i<r2;i++)
                for(int j=0;j<c2;j++)
                    scanf("%d",&b[i][j]);

            multiplyMatrix(a,b,r1,c1,c2);
            break;

        case 3:

            printf("Enter rows and columns: ");
            scanf("%d%d",&r1,&c1);

            printf("Enter Matrix:\n");
            for(int i=0;i<r1;i++)
                for(int j=0;j<c1;j++)
                    scanf("%d",&a[i][j]);

            transposeMatrix(a,r1,c1);
            break;

        default:
            printf("Invalid Choice!");
    }

    return 0;
}