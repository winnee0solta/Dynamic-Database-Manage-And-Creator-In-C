/*
    AUTHOR : AVINA NAKARMI
    CLASS  :2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#define SIZE 200
#include "menu.h"


void read_row(int *,int);
void show_project_list();
void add_item(int ,int );
void show_database(int ,int );

int main()
{

            int rows =0,id_value,flag=0;
            char menu_option,item_choice;

            //show the list of the project and take the id
            show_project_list();
            printf("\n\t\t\tEnter the id of the project to be opened..\t");
            scanf("%d",&id_value);



do
{
            system("cls");
            read_row(&rows,id_value);
            show_title(id_value);
            mainmenu(&menu_option);

            switch(menu_option)
            {
                    case '1' :
                            do{
                                add_item(rows,id_value);
                                system("cls");
                                fflush(stdin);
                                printf("\n\t\t\tDo you want to add another item in the database (y/n)..\t");
                                scanf("%c",&item_choice);

                            }while(toupper(item_choice) == 'Y');
;
                        break;

                    case '2' :
                            show_database(rows,id_value);
                            getch();
                        break;

                    case '3' :
                            search_database(rows,id_value);
                        break;

                    case '4' :
                        system("cls");
                        flag = 1;
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

}while(flag == 0);

return 0;
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


void read_row(int *row,int id_value)
{
            FILE *fp1;
            char buf3[0x100];
            snprintf(buf3, sizeof(buf3), "Database/projects/project_%d/project_row.txt",id_value);
            fp1=fopen(buf3,"r");
            fscanf(fp1,"%d",&*row);
            fclose(fp1);

}

int last_id(int row,int id_value)
{
            int last_id_value=0,i;
            char name[SIZE];
            FILE *fp;
            char buf3[0x100];
            snprintf(buf3, sizeof(buf3), "Database/projects/project_%d/project_%d_database.txt",id_value,id_value);

            fp=fopen(buf3,"r");
            while(fscanf(fp,"%d",&last_id_value) == 1)
            {
                //loop the remaining rows data
                for(i=1;i <= row-1;i++)
                {
                    fscanf(fp,"%s",name);
                }

            }
            fclose(fp);

            return last_id_value;

}//last_id() ends

void add_item(int row,int id_value)
{
            system("cls");
            int i,int_value,id;
            char string1[20][SIZE],string2[20][SIZE],string_value[SIZE];
            FILE *fp1;
            char buf2[0x100];
            snprintf(buf2, sizeof(buf2), "Database/projects/project_%d/project_head.txt",id_value);
            fp1=fopen(buf2,"r");

            for(i=0;i < row;i++)
            {
            fscanf(fp1,"%s",string1[i]);
            fscanf(fp1,"%s",string2[i]);
            }

            fclose(fp1);

            char buf3[0x100];
            snprintf(buf3, sizeof(buf3), "Database/projects/project_%d/project_%d_database.txt",id_value,id_value);
            fp1=fopen(buf3,"a");

            //auto add id
            id = last_id(row,id_value) + 1;
            fprintf(fp1,"%d\n",id);

            //for remaining row part
            for(i=1;i< row ;i++)
            {
                printf("\n\t\t\tEnter %s :\t",string1[i]);

                if(strcmp(string2[i],"INTEGER") == 0)
                {
                scanf("%d",&int_value);
                fprintf(fp1,"%d\n",int_value);
                }

                else if(strcmp(string2[i],"STRING") == 0)
                {
                scanf("%s",string_value);
                fprintf(fp1,"%s\n",string_value);
                }

            }
            fclose(fp1);

}//add_item ends

void show_database(int row,int id_value)
{
            system("cls");
            int id;char name[SIZE],i;
            char string1[20][SIZE],string2[20][SIZE];
            FILE *fp1;
            char buf2[0x100];

            snprintf(buf2, sizeof(buf2), "Database/projects/project_%d/project_head.txt",id_value);

            fp1=fopen(buf2,"r");

            for(i=0;i < row;i++)
            {
                fscanf(fp1,"%s",string1[i]);
                fscanf(fp1,"%s",string2[i]);
            }

            fclose(fp1);

            printf("\n\n\n\t");

            for(i=0;i< row ;i++)
            {
                printf("%10s",string1[i]);
            }
            printf("\n");

            char buf[0x100];
            snprintf(buf, sizeof(buf), "Database/projects/project_%d/project_%d_database.txt",id_value,id_value);

            fp1=fopen(buf,"r");
            while(fscanf(fp1,"%d",&id) == 1)
            {
            //loop the remaining row data other than id
            printf("\t");
            printf("%10d",id);

            for(i=1;i <= row-1;i++)
            {
                fscanf(fp1,"%s",name);
                printf("%10s",name);
            }
            printf("\n");
            }

            fclose(fp1);
            printf("\n\t\t\tPress any key to continue..");


}//show_database ends..

void search_database(int row,int id_value)
{
            int id,id_scan,flag =0,i;
            char name[SIZE];
            FILE *fp1,*fp2;
            show_database(row,id_value);

            printf("\n\t\tEnter the ID of the database to search..\t");
            scanf("%d",&id);

            system("cls");
            char buf[0x100];
            snprintf(buf, sizeof(buf), "Database/projects/project_%d/project_%d_database.txt",id_value,id_value);
            fp1=fopen(buf,"r");

            while(fscanf(fp1,"%d",&id_scan) == 1)
        {
            //loops the remaining row data

            if(id == id_scan)
            {
            //displaying head
            char string1[20][SIZE],string2[20][SIZE];
            char buf2[0x100];
            snprintf(buf2, sizeof(buf2), "Database/projects/project_%d/project_head.txt",id_value);

            fp2=fopen(buf2,"r");

                for(i=0;i < row;i++)
                {
                    fscanf(fp2,"%s",string1[i]);
                    fscanf(fp2,"%s",string2[i]);
                }
            fclose(fp2);
            printf("\n\n\n\t");

                for(i=0;i< row ;i++)
                {
                    printf("%10s",string1[i]);
                }

            printf("\n\t%10d",id);

                for(i=1;i <= row-1;i++)
                {
                    fscanf(fp1,"%10s",name);
                    printf("%10s",name);
                }

            printf("\n");

            flag = 1;
            }else if (id != id_scan)
            {
                for(i=1;i <= row-1;i++)
                {
                    fscanf(fp1,"%s",name);
                }
            }

        }
            fclose(fp1);

            if(flag == 0)
            {
            system("cls");
            printf("\n\n\t\t\tInvalid ID..");
            }else if (flag = 1)
            {
                printf("\n\n\n\t\t****Successfully Searched Database!!*****\n");
                printf("\t\tPress any key..");
                getch();
            }

}
