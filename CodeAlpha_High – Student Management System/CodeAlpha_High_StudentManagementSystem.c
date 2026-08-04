#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int roll;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main()
{
    int choice;

    while(1)
    {
        printf("\n==============================");
        printf("\n STUDENT MANAGEMENT SYSTEM");
        printf("\n==============================");
        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank You!\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}

// Add Student
void addStudent()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat","ab");

    if(fp==NULL)
    {
        printf("File Error!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d",&s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]",s.name);

    printf("Enter Marks: ");
    scanf("%f",&s.marks);

    fwrite(&s,sizeof(s),1,fp);

    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}

// Display Students
void displayStudents()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat","rb");

    if(fp==NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n-------------------------------------");
    printf("\nRoll\tName\t\tMarks");
    printf("\n-------------------------------------");

    while(fread(&s,sizeof(s),1,fp))
    {
        printf("\n%d\t%s\t\t%.2f",s.roll,s.name,s.marks);
    }

    fclose(fp);
}

// Search Student
void searchStudent()
{
    FILE *fp;
    struct Student s;
    int roll, found=0;

    fp=fopen("students.dat","rb");

    if(fp==NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d",&roll);

    while(fread(&s,sizeof(s),1,fp))
    {
        if(s.roll==roll)
        {
            printf("\nStudent Found");
            printf("\nRoll : %d",s.roll);
            printf("\nName : %s",s.name);
            printf("\nMarks: %.2f\n",s.marks);

            found=1;
            break;
        }
    }

    if(!found)
        printf("\nStudent Not Found!\n");

    fclose(fp);
}

// Update Student
void updateStudent()
{
    FILE *fp;
    struct Student s;
    int roll, found=0;

    fp=fopen("students.dat","rb+");

    if(fp==NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Update: ");
    scanf("%d",&roll);

    while(fread(&s,sizeof(s),1,fp))
    {
        if(s.roll==roll)
        {
            printf("\nEnter New Name: ");
            scanf(" %[^\n]",s.name);

            printf("Enter New Marks: ");
            scanf("%f",&s.marks);

            fseek(fp,-sizeof(s),SEEK_CUR);

            fwrite(&s,sizeof(s),1,fp);

            printf("\nRecord Updated Successfully!\n");

            found=1;
            break;
        }
    }

    if(!found)
        printf("\nStudent Not Found!\n");

    fclose(fp);
}

// Delete Student
void deleteStudent()
{
    FILE *fp,*temp;
    struct Student s;
    int roll, found=0;

    fp=fopen("students.dat","rb");

    if(fp==NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    temp=fopen("temp.dat","wb");

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d",&roll);

    while(fread(&s,sizeof(s),1,fp))
    {
        if(s.roll==roll)
        {
            found=1;
        }
        else
        {
            fwrite(&s,sizeof(s),1,temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat","students.dat");

    if(found)
        printf("\nStudent Deleted Successfully!\n");
    else
        printf("\nStudent Not Found!\n");
}