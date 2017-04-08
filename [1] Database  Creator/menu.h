
void mainmenu(char *option)
{
printf("\n\n\n\n");
 printf("\t\t\tCreate a Project           [1]\n");
 printf("\t\t\tShow   a project           [2]\n");
 printf("\t\t\tDelete a project           [3]\n");
 printf("\t\t\tChange Password            [4]\n");
 printf("\t\t\tExit the Project           [5]\n");
 printf("\n\t\t\tChoose one of the option.............\t");
scanf("%c",&*option);
}
void typemenu()
{
 printf("\n\t\t\tINTEGER           [1]\n");
 printf("\t\t\tSTRING            [2]\n");
}


char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result,s1);
    strcat(result,s2);
    return result;
}


/*

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

                char *special_char1 = "%10s";
                char *special_char2 = "%10s",*special_char3 ;
            for(i=1;i< row ;i++)
            {
            special_char3 = concat(special_char2,special_char1);
            special_char2 =special_char3;
            }
            //for second part
            char buf[0x100];
            char *str1="string1[1]",*str2,*str3;
            for(i=2;i<= row ;i++)
            {
              snprintf(buf, sizeof(buf), ",string1[%d]",i);
                str3 = concat(str1,buf);
                str1=str3;
            }
            */
