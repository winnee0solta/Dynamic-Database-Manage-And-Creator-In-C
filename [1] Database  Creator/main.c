/*
    AUTHOR : AVINA NAKARMI
    CLASS  :2020
*/
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include <unistd.h>
#include <windows.h>
#define SIZE 200


void sign_up(char *user_id[],char *password[]);
int sign_in();
int create_project();
int last_id();
void show_project_list();
void delete_project();
void row_details(int);

int main()
{

    char menu_option=0;
    char user_id[50],password[50];
    int flag=0,flag2=0,id_value;
    FILE *fp;
    fp=fopen("Database/credentials/credentials.txt","r");

    if( fscanf(fp,"%s%s",user_id,password) != 2)
    {
        fclose(fp);
        system("cls");
        printf("\n\n\t\t\tSIGN UP \n\n");
        sign_up(&user_id,&password);
    }
    else
    {
        fclose(fp);
        system("cls");
            printf("\n\n\t\t\tSIGN IN \n\n");
            flag=sign_in();
            if (flag == 1)
            {
                printf("\n SUCCESSFUL SIGN IN");
                getch();
            }
            else
            {
                printf("\n TOO MANY INCORRECT ATTEMPTS");
                exit(0);
            }
            //when sign is true starts
        do{
            system("cls");
            fflush(stdin);
            mainmenu(&menu_option);
            switch(menu_option)
            {
                    case '1' :
                        //main theme of the project starts
                         id_value = create_project();
                         row_details(id_value);
                        //main theme of the project ends
                        break;

                    case '2' :
                        show_project_list();
                        getch();
                        break;

                    case '3' :
                        delete_project();
                        break;

                    case '4' :
                        sign_up(&user_id,&password);
                        break;

                    case '5' :
                        system("cls");
                        flag2 = 1;
                        printf("\n\n\n\t\t\tHave A Good Day\n");
                        printf("\n\t\t\tPress any key..");
                        getch();
                        break;

                    default :
                        system("cls");
                        printf("\n\n\n\t\t\tEnter Valid choice \n");
                        printf("\n\t\t\tPress any key..");
                        getch();
                        break;
        }//switch ends

    }while(flag2 == 0);
        //when sign is true ends
    }

}//main ends
void sign_up (char *user_id[],char *password[])
{
            system("cls");
            FILE *fp1;
            char choice;
            fp1=fopen("Database/credentials/credentials.txt","w");
            fflush(stdin);
            printf("\n\n\n\t\t\tenter new user id..\t");
            gets(user_id);
            fprintf(fp1,"%s\n",user_id);
            printf("\n\t\t\tenter new password..   .\t");
            gets(password);
            fprintf(fp1,"%s\n",password);
            fclose(fp1);
            printf("\n\n\n\t\t\t******You have successfully signed up*****\n\n");

}

//reads user id and password for login and compares with sign up file for login status
int sign_in ()
{
    FILE *fp1;
    char u[50],p[50];
    char user_id[50],password[50];
    int count=0;
    system("cls");
    fp1=fopen("Database/credentials/credentials.txt","r");
    //reads user id and password
    while(count<3)
          {
              system("cls");
              fflush(stdin);

            printf("\n\n\n\t\t\tUSER ID :\t\t");
            gets(u);
            printf("\n\t\t\tPASSWORD :\t");
            gets(p);
            //compares used id and password with sign up file
            while(!feof(fp1))
            {
                fscanf(fp1,"%s",user_id);
                fscanf(fp1,"%s",password);

            }
            if((strcmp(u,user_id)==0)&&(strcmp(p,password)==0))
                {
                    return 1;
                    break;
                }
                else
                {
                    printf("\ninvalid details\n");
                    getch();
                }
            count++;
          }
          if(count==3)
            system("cls");
    fclose(fp1);
     return 0;
}

int last_id()
{
    int last_id_value=0;
    char name[SIZE];
    FILE *fp;
    fp=fopen("Database/projectlist.txt","r");
    while(fscanf(fp,"%d%s",&last_id_value,name) == 2)
    {
     //loop for the last id
    }
    fclose(fp);
    return last_id_value;
}//last_id() ends

int create_project()
{
    system("cls");
    int id_value;
    char name_project[SIZE];

    printf("\n\n\t\t\tEnter the name of the project:\t");
    scanf("%s",name_project);
    id_value = last_id() + 1;
    FILE *fp;
    fp=fopen("Database/projectlist.txt","a");
    fprintf(fp,"%d\n%s\n",id_value,name_project);
    fclose(fp);

    char buf[0x100];
    snprintf(buf, sizeof(buf), "Database/projects/project_%d",id_value);
    mkdir(buf);

    char buf2[0x100];
    snprintf(buf2, sizeof(buf2), "Database/projects/project_%d/project_title.txt",id_value);
    fp=fopen(buf2,"w");
    fprintf(fp,"%s\n",name_project);
    fclose(fp);

    system("cls");
    printf("\n\n\n\t\t\tSuccessfully created !!");
    printf("\n\n\t\t\tPress any key to continue \t");
    getch();
    return id_value;
}

void show_project_list()
{
    system("cls");
    fflush(stdin);
    int id_value;
    char name_project[SIZE];
    FILE *fp;
    fp=fopen("Database/projectlist.txt","r");
    printf("\n\n\n\t\t\tID    NAME OF THE PROJECT\n");
    while(fscanf(fp,"%d%s",&id_value,name_project) == 2)
    {
        printf("\t\t\t%3d%10s\n",id_value,name_project);
    }
    fclose(fp);

}//show_project_list(void) ends

void delete_project()
{
    int id_to_scan;
    char name_to_scan[SIZE];
    int id_value,last_id_value;
    show_project_list();
    printf("\n\t\t\tEnter the id of the project to be deleted.");
    scanf("%d",&id_value);
    last_id_value=last_id();

    if(id_value <= last_id_value)
    {
         FILE *fp2,*fp1;
        //remove data from list
            fp1=fopen("Database/projectlist.txt","r");
            fp2=fopen("Database/replica_projectlist.txt","w");
            while(fscanf(fp1,"%d%s",&id_to_scan,name_to_scan) == 2)
            {
                if(id_to_scan == id_value)
                {
                    continue;
                }
                fprintf(fp2,"%d\n%s\n",id_to_scan,name_to_scan);
            }
            fclose(fp1);
            fclose(fp2);
            remove("Database/projectlist.txt");
            rename("Database/replica_projectlist.txt","Database/projectlist.txt");
        //remove full folder
           char buf[0x100];
           snprintf(buf, sizeof(buf), "Database/projects/project_%d",id_value);
           rmdir(buf);
    }
    else
    {
        system("cls");
        printf("\n\n\n\t\t\tEnter Valid ID \n");
        printf("\n\t\t\tPress any key..");
        getch();
    }

}//delete_project() ends

void row_details(int id_value)
{
    int i,rows,flag = 0;
    char row_type_choice;
    char row_title[SIZE],integer_str[] ="INTEGER",string_str[]="STRING";
    FILE *fp,*fp1;
    do
    {
     system("cls");
    printf("\n\n\t\t\tEnter the no of rows to be added in the project\t");
    scanf("%d",&rows);
    if (rows != 0 && rows > 0)
    {
        //adding id automatically in the row
        char buf2[0x100];
        snprintf(buf2, sizeof(buf2), "Database/projects/project_%d/project_head.txt",id_value);
        fp=fopen(buf2,"a+");
        fprintf(fp,"ID\nINTEGER\n");
        //adding no of row file
        char buf3[0x100];
        snprintf(buf3, sizeof(buf3), "Database/projects/project_%d/project_row.txt",id_value);
        fp1=fopen(buf3,"w");
        fprintf(fp1,"%d\n",rows+1);
        fclose(fp1);

         for(i=1;i <= rows ; i++)
    {
        system("cls");
        printf("\n\n\t\t\tEnter the title for the %d row\t",i);
        scanf("%s",row_title);
        typemenu();
        fflush(stdin);
        printf("\n\t\t\tEnter the type of the %d row\t",i);
        scanf("%c",&row_type_choice);
        if(row_type_choice == '1')
        {
           fprintf(fp,"%s\n%s\n",row_title,integer_str);
        }else if(row_type_choice == '2')
        {
           fprintf(fp,"%s\n%s\n",row_title,string_str);
        }

    }
    fclose(fp);
    flag = 1;
    }
    else
    {
        system("cls");
        printf("\n\n\n\t\t\tINVALID NO OF ROWS");
        printf("\n\n\t\t\tPress any key to continue again\t");
        getch();
    }
    }while(flag == 0);

}
