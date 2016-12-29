#ifndef SCAN_FUNCTIONS_H_INCLUDED
#define SCAN_FUNCTIONS_H_INCLUDED

/// this function to skip spaces from input to be easy to discover any wrong inputs
void SkipSpacesScan(char str[]){
    int ch,i=0,flag=0;
    while((ch=getchar())!='\n'){
        if((ch==' '|| ch=='\t') && flag==0){/// skip spaces
            continue;
        }
        flag=1;
        str[i++]=ch;
        if(ch==' '){/// print only one space between 2 char
            flag=0;
        }
    }
    str[i]='\0';
}

///this function to check if thee input number is correct or not
int filterSpaces(char input[]){
    if((input[0]-'0')<=9 && (input[0]-'0')>=0 && (input[1]-'0')<=9 && (input[1]-'0')>=0) {
       if((input[2]==' ' && input[3]=='\0')|| (input[2]=='\0')){
            ///--num-num-space-end  OR num-num-end
       }

        }else if((input[0]-'0')<=9 && (input[0]-'0') >= 0 && ((input[1]==' ' && input[2]=='\0')|| input[1]=='\0')){
            ///--num-space-end  OR num-end
        }else{///--ERROR
            return 0;
        }
        return 1;
}


///---------------------------To Avoid User Wrong Inputs----------------------------
void getInput(char operation[],int *i,int *j,int n,int m,char arr[n][m][2],int *moves){
    color(13);
    printf(" I Want To : ");
    color(7);

    /// loop until correct input
    for(;;){
        ///scan operation
        fflush(stdin);
        scanf("%s",operation);
        operation[0]=toupper(operation[0]);///--operation can be upper or lower case
        if((operation[0]=='S' ||operation [0]=='M') && operation[1]=='\0'){///--to save without input coordinates
            break;
        }
        if(operation[0]>='A'&& operation[1]!='\0'){///--if operation not a single character
            *moves+=1;
            color(12);
            printf(" Operation Is Only 1 Character !\n\n");
            color(13);
            printf(" I Want To : ");
            color(7);
            continue;
        }

        ///scan coordinate
        char index_i[10];
        char index_j[10];

        scanf("%s %s",index_i,index_j);

        /// IF Raw Number IS NOT CORRECT
        if(!filterSpaces(index_i)){
            *moves+=1;
            color(12);
            printf(" Please Enter A Valid Raw Number\n\n");
            color(13);
            printf(" I Want To : ");
            color(7);
            continue;
        }
        /// IF Column Number IS NOT CORRECT
        if(!filterSpaces(index_j)){
            *moves+=1;
            color(12);
            printf(" Please Enter A Valid Column Number\n\n");
            color(13);
            printf(" I Want To : ");
            color(7);
            continue;
        }

        ///change strings to int
        *i=strtol(index_i,NULL,10);
        *j=strtol(index_j,NULL,10);

        ///--To Avoid Any thing But The Limit
         if(!(*i>=0 && *i<n && *j>=0 && *j<m)){
            *moves+=1;
            color(12);
            printf(" Please Enter Correct Coordinates  !\n\n");
            color(13);
            printf(" I Want To : ");
            color(7);
            continue;
        }
        break;
    }
}




///scan rows or columns
void inputGrid (int *container,char *r_c){
    /// loop until correct input
    for(;;){
        color(7);
        printf(" Please Enter Number Of ");
        color(14);
        printf("%s ",r_c);
        color(10);
        printf("(Min 2, Max 99) ");
        color(7);
        //gets(input);
        char input[10];
        fflush(stdin);///clear scan memory
        SkipSpacesScan(input); ///skip spaces
        ///check if input is correct or not
        if(!filterSpaces(input)){
            color(12);
            printf(" Please Enter A Valid Number\n");
            continue;
        }


        *container=strtol(input,NULL,10);///--converts first char num to int num
        if(*container>=2 && *container<=99){///--In Range
            color(14);
            printf(" Number Of %s Is %d\n",r_c,*container);
            break;
        }else{///--Out Of Range
            color(12);
            printf(" Please Enter A Valid Number\n");
        }

    }
}


///scan first cell coordinates correctly
void getstart (int *f_i,int *f_j,int n,int m,char arr[n][m][2]){
    /// loop until correct input
    for(;;){
        color(12);
        printf("\tPlease Enter Row Column  ex: 0 0\n");
        printf(" Anything After A Correct Sequence Will Be Ignored\n\n");
        color(13);
        printf(" First Cell To Open : ");

        fflush(stdin);///clear scan's memory
        ///scan the two coordinates in two strings
        char index_i[10];
        char index_j[10];
        scanf("%s %s",index_i,index_j);


        ///Correct Input
        if(!filterSpaces(index_j)){
            color(12);
            printf(" Please Enter A Valid Number\n\n");
            continue;
        }
        ///Correct Input
        if(!filterSpaces(index_i)){
            color(10);
            printf(" Please Enter A Valid Number\n\n");
            continue;
        }

        ///--converts first char num to int num
        *f_i=strtol(index_i,NULL,10);
        *f_j=strtol(index_j,NULL,10);
        ///To Avoid Any thing But The Limit
        if(!(*f_i>=0 && *f_i<n && *f_j>=0 && *f_j<m)){
            color(12);
            printf(" Please Input An Existing Coordinate !\n\n");
            continue;
        }
        break;///end loop when we have correct input
    }
}


#endif // SCAN_FUNCTIONS_H_INCLUDED
