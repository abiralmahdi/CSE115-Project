#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int input,i=0,Num;

// Structure of the employee data
struct EmpData{
    long long int contact;
    int empID, salary;
    char name[100], email[30], address[100], post[50];
};


typedef struct EmpData employee;
employee emp1[5];

// This is the main menu
void mainMenu()
{
    int employeeID;
    char chr;
    system("cls");
    // The menu options
    printf("========================  EMPLOYEE MANAGEMENT SYSTEM  ========================\n");
    printf("\n  Welcome to main menu. Please select any of the following options: \n\n");
    printf("\t1. Press 1 to display all the employee data.\n");
    printf("\t2. Press 2 to enter a new employee to records.\n");
    printf("\t3. Press 3 to delete an employee from records.\n");
    printf("\t4. Press 4 to edit an employee record.\n");
    printf("\t5. Press 5 to search an employee with ID.\n");
    printf("\t6. Press 6 to send  an employee on leave/vacation.\n");
    printf("\t7. Press 7 to view all the employees on vacation.\n");
    printf("\n===============================================================================\n");

    printf("\nEnter your input: "); // The user input for the menu options
    scanf("%d", &input);

    if(input==1)
    {
        system("cls");              // Clear the screen or make it blank
        displayEmployees();
    }
    else if(input==2)
    {
        system("cls");
        addEmployee();

    }
    else if(input==3)
    {
        system("cls");
        deleteEmployee(employeeID);
    }
    else if(input==4)
    {
        system("cls");
        edit(emp1);
    }
    else if (input==5){
        system("cls");
        searchEmployee();
    }
    else if (input==6){
        system("cls");
        sendOnLeave();
    }
    else if (input==7){
        system("cls");
        displayLeaveEmployees();
    }
    else
    {
        system("cls");
        printf("Error: Invalid Input.");
        fflush(stdin);
        returnToMenu();
    }
}
void checkDirectory()
{
    DIR* dir = opendir("Employees");
    DIR* dir2 = opendir("Leave");
    if (dir)
    {
        /* Directory exists. */
        closedir(dir);
    }
    else
    {
        mkdir("Employees");
    }
    if (dir2)
    {
        /* Directory exists. */
        closedir(dir2);
    }
    else
    {
        mkdir("Leave");
    }
}

// Function for counting the number of employees
int countFiles()
{
    int numberOfFiles=0;
    DIR *d;
    struct dirent *dir;
    d = opendir("./Employees");  // Opening the directory where employees are stored
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            numberOfFiles++;    // Counting the number of employee files
        }
        closedir(d);
    }
    return numberOfFiles-2;     // Returning the number of employees

}


// Function for counting the number of employees on leave
int countFilesLeave()
{
    int numberOfFiles=0;
    DIR *d;
    struct dirent *dir;
    d = opendir("./Leave");  // Opening the directory where leave records are stored
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            numberOfFiles++;    // Counting the number of employee files
        }
        closedir(d);
    }
    return numberOfFiles-2;     // Returning the number of employees

}


// Function that sends employees on leave
void sendOnLeave()
{
    checkDirectory();
    char empId[10], folderNamee[10], folderName2[10],ch, empId2[10], contentt[255];
    FILE*fp=NULL;
    FILE*fp2=NULL;
    strcpy(folderName2,"./Leave/");
    printf("Enter the ID of the employee who will go to leave: ");
    scanf("%s",&empId);
    fflush(stdin);

    strcat(empId,".txt");
    strcpy(empId2,empId);

    strcpy(folderNamee,"./Employees/");
    strcat(folderNamee,empId2);

    fp=fopen(folderNamee, "r");

    strcat(folderName2,empId2);

    fp2=fopen(folderName2, "w");


    fgets(contentt,255,fp);

    fprintf(fp2,"%s",contentt);

    printf("Employee sent on Leave!");
    fclose(fp);
    fclose(fp2);

    returnToMenu();

}


// Function that displays employees on leave
void displayLeaveEmployees()
{
    FILE *fcpy=NULL;
    char folderName[50];
    char fileName2[10], content[300];
    strcpy(folderName,"./Leave/");
    printf("Employees those are on leave/vacation are as follows: \n");
    printf("ID\t\tName\t\tEmail\t\t\t\t\tContact\t\t\tAddress\t\t\t\tPost\t\tSalary \n");
    printf("========================================================================================================================================\n");
    // Display employee data from each file using for loop

    for (int i=0; i<countFilesLeave(); i++)
    {
        // Getting the file name from the employee ID
        sprintf(fileName2, "%d", 100+i);
        strcat(fileName2,".txt");
        strcat(folderName,fileName2);

        fcpy=fopen(folderName, "r");

        if (fcpy!=NULL){
            fgets(content, 255, fcpy);
            printf("%s",content);       // Printing the contents of the file
            fclose(fcpy);
            strcpy(folderName,"./Employees/");
            strcpy(fileName2,"");
        }

    }
    returnToMenu();
}






// Function for displaying all the employee data
void displayEmployees()
{
    FILE *fcpy=NULL;
    char folderName[50];
    char fileName2[10], content[300];
    strcpy(folderName,"./Employees/");
    printf("ID\t\tName\t\tEmail\t\t\t\t\tContact\t\t\tAddress\t\tPost\tSalary \n");
    printf("========================================================================================================================================\n");
    // Display employee data from each file using for loop

    for (int i=0; i<countFiles(); i++)
    {
        // Getting the file name from the employee ID
        sprintf(fileName2, "%d", 100+i);
        strcat(fileName2,".txt");
        strcat(folderName,fileName2);

        fcpy=fopen(folderName, "r");
        fgets(content, 255, fcpy);
        printf("%s",content);       // Printing the contents of the file
        fclose(fcpy);
        strcpy(folderName,"./Employees/");
        strcpy(fileName2,"");
    }
    returnToMenu();
}



// Function for deleting an employee from records
int deleteEmployee(int id)
{
    int m;
    char fnamex[50];
    FILE *p=NULL;
    char folderName[50];
    strcpy(folderName,"./Employees/");

    printf("\nEnter the employee id you want to delete: ");
    scanf("%d",&m);

    // Getting the file name from the employee ID
    sprintf(fnamex, "%d", m);
    strcat(fnamex,".txt");
    strcat(folderName,fnamex);

    p=fopen(folderName,"w");
    fprintf(p,"%d",m);
    fprintf(p,"\t\t[Employee has been deleted]\n");

    fclose(p);
    returnToMenu();
}

// Function for editing an employee from records
void edit(employee emp1[])
{
    char folderName[50];
    strcpy(folderName, "./Employees/");

    FILE *fptr2=NULL;
    char a[10];
    int b;
    printf("Enter employee ID to want to edit: ");
    scanf("%d",&b);
    sprintf(a, "%d", b);

    fflush(stdin);
    fflush(stdin);

    // Getting the file name from the employee ID
    strcat(a,".txt");
    strcat(folderName,a);

    fptr2=fopen(folderName, "w");
    checkDirectory();
    printf("\nName: ");
    gets(emp1[b-100].name);
    fflush(stdin);
    printf("Email: ");
    gets(emp1[b-100].email);
    strcat(emp1[b-100].email, "@gmail.com");
    fflush(stdin);
    printf("Contact: ");
    scanf("%lld", &emp1[b-100].contact);
    fflush(stdin);
    printf("Address: ");
    gets(emp1[b-100].address);
    fflush(stdin);
    printf("Post: ");
    gets(emp1[b-100].post);
    fflush(stdin);
    printf("Salary: ");
    scanf("%d", &emp1[b-100].salary);
    fflush(stdin);

    // Entering the employee data in the file
    fprintf(fptr2,"%d\t\t%s\t\t%s\t\t%lld\t\t%s\t\t%s\t\t%d \n",b,emp1[b-100].name,emp1[b-100].email,emp1[b-100].contact,emp1[b-100].address,emp1[b-100].post,emp1[b-100].salary);
    fclose(fptr2);
    printf("\nEmployee edited successfully!");
    returnToMenu();
}

// Function for adding an employee to records [DONE]
int addEmployee()
{
    FILE *fptr1=NULL;
    FILE *IDptr=NULL;
    FILE *readID;
    char buff[500];
    int lastID;
    char fileName1[10];
    char folderName[50];
    strcpy(folderName, "./Employees/");
    readID=fopen("IDRecords.txt","r");

    // Check if the number of employees is zero or not
    checkDirectory();
    if(readID == NULL)
    {
        printf("How many employees you want to add: ");
        scanf("%d",&Num);
        printf("\nEnter a new employee: \n");

        for( i=0; i<Num; i++)
        {
            printf("\nID: %d", i+100); // If zero, then employee ID will start from 100
            emp1[i].empID=i+100;
            fflush(stdin);
            printf("\nName: ");
            gets(emp1[i].name);
            fflush(stdin);
            printf("Email: ");
            gets(emp1[i].email);
            strcat(emp1[i].email, "@gmail.com");
            fflush(stdin);
            printf("Contact: ");
            scanf("%lld", &emp1[i].contact);
            fflush(stdin);
            printf("Address: ");
            gets(emp1[i].address);
            fflush(stdin);
            printf("Post: ");
            gets(emp1[i].post);
            fflush(stdin);
            printf("Salary: ");
            scanf("%d", &emp1[i].salary);
            fflush(stdin);
            sprintf(fileName1, "%d", i+100);
            strcat(fileName1, ".txt");
            strcat(folderName,fileName1);
            fptr1=fopen(folderName,"w");
            // Entering the employee data in the file
            fprintf(fptr1,"%d\t\t%s\t\t%s\t\t%lld\t\t%s\t\t%s\t\t%d \n",emp1[i].empID,emp1[i].name,emp1[i].email,emp1[i].contact,emp1[i].address,emp1[i].post,emp1[i].salary);
            fclose(fptr1);

            // Entering the last ID in another file for further use
            IDptr=fopen("IDRecords.txt","w");
            fprintf(IDptr, "%d", i+100);
            fclose(IDptr);
            strcpy(folderName, "./Employees/");
        }
        fflush(stdin);
    }
    else
    {
        printf("How many employees you want to add: ");
        scanf("%d",&Num);

        fscanf(readID, "%s", buff);
        fflush(stdin);
        lastID=atoi(buff);

        for (int i=1; i<=Num; i++)
        {
            printf("\nID: %d", i+lastID);    // If not zero, employee ID will start from the last ID stored in IDRecords.txt file
            emp1[i].empID=i+lastID;
            fflush(stdin);
            printf("\nName: ");
            gets(emp1[i].name);
            fflush(stdin);
            printf("Email: ");
            gets(emp1[i].email);
            strcat(emp1[i].email, "@gmail.com");
            fflush(stdin);
            printf("Contact: ");
            scanf("%lld", &emp1[i].contact);
            fflush(stdin);
            printf("Address: ");
            gets(emp1[i].address);
            fflush(stdin);
            printf("Post: ");
            gets(emp1[i].post);
            fflush(stdin);
            printf("Salary: ");
            scanf("%d", &emp1[i].salary);
            fflush(stdin);
            sprintf(fileName1, "%d", i+lastID);
            strcat(fileName1, ".txt");
            strcat(folderName,fileName1);
            fptr1=fopen(folderName,"w");

            // Enter employee data from the file
            fprintf(fptr1,"%d\t\t%s\t\t%s\t\t%lld\t\t%s\t\t%s\t\t%d \n",emp1[i].empID,emp1[i].name,emp1[i].email,emp1[i].contact,emp1[i].address,emp1[i].post,emp1[i].salary);
            fclose(fptr1);
            IDptr=fopen("IDRecords.txt","w");
            fprintf(IDptr, "%d", i+lastID);
            fclose(IDptr);
            strcpy(folderName, "./Employees/");

        }
        fflush(stdin);
        fclose(readID);
    }

    returnToMenu();

}

// Function for returning to main menu or to exit
int returnToMenu()
{
    fflush(stdin);
    printf("\n\nEnter M to return to main menu: ");
    scanf("%c", &input);
    fflush(stdin);
    if (input=='M'|| input=='m')
    {
        mainMenu();
    }
}


// Function for searching the employee
void searchEmployee()
{
    int id;
    char str[5], content[255], folderName[50];
    strcpy(folderName,"./Employees/");
    printf("Enter employee ID: ");
    scanf("%d",&id);
    sprintf(str, "%d", id);
    strcat(str,".txt");
    strcat(folderName,str);
    FILE *fp=fopen(folderName,"r");
    if (fp==NULL)
    {
        printf("No such employees found");
    }
    else
    {
        fgets(content,255,fp);
        printf("ID\t\tName\t\tEmail\t\t\t\t\tContact\t\t\tAddress\t\tPost\t\tSalary \n");
        printf("========================================================================================================================================\n");
        puts(content);
        fclose(fp);
    }
    returnToMenu();

}

// Check if username exists
int checkUsername(char *username[100], char *loginData[2][2]){
    int flag=0;
    for (int k=0; k<2; k++)
    {
        if (strcmp(username,loginData[k][0])==0)
        {
            flag=1;
        }
    }
    return flag;
}



// Function for user authentication
int authenticate(char *username[100],char password[8],char*loginData[2][2],int k)
{
    int isAuthenticated=0;

    // Check if the password is correct
    if (strcmp(password,loginData[k][1])==0)
    {
        isAuthenticated=1;
    }
    return isAuthenticated;
}




// Function for encrypting the password to asterisks
void encryptPassword(char password[8])
{
    int p=0;
    do
    {
        password[p]=getch();
        if(password[p]!='\r' && password[p]!='\b')
        {
            printf("*");
        }
        p++;
    }
    while(password[p-1]!='\r');
    printf("\n");
    password[p-1]='\0';
}




int main()
{
    // Username and passwords 2D array
    char* loginArr[2][2]= {{"kuresh","123"},{"abir","456"}};

    char* username[100];
    char password[8];
    char ch;
    int flag=0;

    printf("========================  EMPLOYEE MANAGEMENT SYSTEM  ========================\n");
    printf("\n\tPlease Enter your login credentials\n");
    printf("\n\tUsername: ");
    gets(username);


    if (checkUsername(&username, &loginArr)==0)
    {
        printf("Username is not found\n");
    }
    else
    {
        for (int k=0; k<2; k++)
        {
            if (strcmp(username,loginArr[k][0])==0)
            {
                printf("\tPassword: ");

                // Hiding the password input using asterisks(*)
                encryptPassword(password);

                // Check if the password is correct
                if(authenticate(&username, &password, &loginArr, k)==1)
                {
                    system("cls");
                    mainMenu();
                    break;
                }
                else
                {
                    printf("Password is not valid\n");
                    break;
                }
            }
        }
    }
}
