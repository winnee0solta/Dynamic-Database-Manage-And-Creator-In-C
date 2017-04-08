void mainmenu(char *option)
{
        printf("\t\t\tAdd item in DATABASE       [1]\n");
        printf("\t\t\tShow DATABASE              [2]\n");
        printf("\t\t\tSearch DATABASE            [3]\n");
        printf("\t\t\tExit the Project           [4]\n");
        printf("\n\t\t\tChoose one of the option.............\t");
        scanf("%c",&*option);
}
void show_title(int id_value)
{
  char title[SIZE];
        FILE *fp1;
        char buf3[0x100];
        snprintf(buf3, sizeof(buf3), "Database/projects/project_%d/project_title.txt",id_value);
        fp1=fopen(buf3,"r");
        fscanf(fp1,"%s",title);
        fclose(fp1);
        fflush(stdin);
        printf("\n\n\t\t********** %s Database Management System********\n\n\n",title);
}
