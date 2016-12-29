#ifndef GAME_LOOP_FUNCTIONS_H_INCLUDED
#define GAME_LOOP_FUNCTIONS_H_INCLUDED





void lose(int n,int m,char arr[n][m][2],int *case_lose){
    int i,j;
    //--Convert The whole Array
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(arr[i][j][1]=='X' || arr[i][j][1]=='F' || arr[i][j][1]=='?'){//--Not Opened Cell
                if(arr[i][j][1]=='F' && arr[i][j][0]==15){//--Right Flag
                    arr[i][j][1]=15;
                }else if(arr[i][j][1]=='F' && arr[i][j][0]!=15){//--Wrong Flag
                    arr[i][j][1]='/';
                }else if(arr[i][j][1]!='F' && arr[i][j][0]==15){//--Missed Mine
                    arr[i][j][1]='M';
                }else if(arr[i][j][1]!='F' && arr[i][j][0]!=15){//--Normal Cell
                    arr[i][j][1]=arr[i][j][0];
                }else  if(arr[i][j][1]=='!'){//--More than one mine can be pressed
                    continue;
                }
            }
        }
    }
    *case_lose=0;


}
/***************************************************/

/// win function
void win_check(int rows,int columns,char arr[rows][columns][2],int moves,time_t start_t,int mins ,int secs,
               int s_secs,int s_mins,int flags,int qus_marks,int mines,int*flag ){


    int i, j,counter=0,mines_num;
    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            if(arr[i][j][0]== 15 && (arr[i][j][1]=='X'|| arr[i][j][1]=='F'|| arr[i][j][1]=='?')){
                counter++ ;
            }
            if(arr[i][j][0]!= 15 && (arr[i][j][1]=='X'|| arr[i][j][1]=='F'|| arr[i][j][1]=='?')){
                counter++ ;
            }
        }

    }
    mines_num=1+(rows*columns)/10;
    ///if the player wins
    if(counter==mines_num){

        ///make all mines 'F'
        for(i=0;i<rows;i++){
            for(j=0;j<columns;j++){
                if(arr[i][j][0]== 15){
                    arr[i][j][1]='F';
                }
            }
        }

        *flag=0;/// to end game loop

        int player_score;
        int time;
        char player_name[256];

        timePassed(start_t,&mins,&secs,s_secs,s_mins);
        time=mins*60+secs;

        if (time!=0){
        player_score = (pow(rows,4)*pow(columns,4))/(time * moves);
        }
        else{
            player_score = (pow(rows,4)*pow(columns,4));
        }




        system("cls");///clear cmd window
        printLogo();
        printGrid(rows,columns,arr);
        printInfo(mins,secs,moves,flags,qus_marks,mines);
        color(6);
        printf("\ncongratulation you won\nplease,enter your name : ");



        fflush(stdin);
        SkipSpacesScan(player_name);///scan user's name by this function to avoid wrong inputs
        ///capital all name's letters
        for(i=0;player_name[i]!=0;i++){
            player_name[i]=toupper(player_name[i]);
        }

        int rank1;
        score_rank(player_name,&player_score,&rank1);///call rank function



        ///print rank
        printf("your scoer is : %d \nyour rank is : %d\n\n",player_score,rank1);
        color(10);
        printf("Press Any Key To Go To Main Menu...");
        fflush(stdin);
        getchar();
    }

}





///--------------------Empty Cell SelfOpen when player open empty cell-----------------------
void multiOpen (int parent_i,int parent_j,int n,int m,char arr[n][m][2]){
    int i,j;
    for(i=parent_i-1;i<=parent_i+1;i++){
        if(i<0 || i>n-1){continue;}
        for(j=parent_j-1;j<=parent_j+1;j++){
            if(j<0 || j>m-1){continue;}
            if (i==parent_i && j==parent_j){
                continue;
            }
            if (arr[i][j][1]=='X' || arr[i][j][1]=='?'){///--Not To Open An Opened Empty Cell or flag cell
                if(arr[i][j][0]==' '){
                    arr[i][j][1]=arr[i][j][0];
                    multiOpen(i,j,n,m,arr);
                }
                else
                    arr[i][j][1]=arr[i][j][0];
             }
        }
    }
}

///---------------------------Count Flags Around Number---------------------------
char flagCounter(int parent_i,int parent_j,int n,int m, char arr[n][m][2]){
    int i,j;
    char counter='0';
    for(i=parent_i-1;i<=parent_i+1;i++){
        if(i<0 || i>n-1){continue;}
        for(j=parent_j-1;j<=parent_j+1;j++){
            if(j<0 || j>m-1){continue;}
            if (i==parent_i && j==parent_j){
                continue;
                }
            if(arr[i][j][1]=='F'){
                counter++;
            }
        }
    }
    return counter;
}

///---------------------------Open Number Again---------------------------
void numAgain(int parent_i,int parent_j,int n,int m, char arr[n][m][2],int *case_lose, int* correct_case){
    int i,j,w_flag=0;
    char flags;
    flags=flagCounter(parent_i,parent_j,n,m,arr);
    if (flags==arr[parent_i][parent_j][0]){
        for(i=parent_i-1;i<=parent_i+1;i++){
            if(i<0 || i>n-1){continue;}
            for(j=parent_j-1;j<=parent_j+1;j++){
                if(j<0 || j>m-1){continue;}
                if (i==parent_i && j==parent_j){
                    continue;
                }
                if(arr[i][j][1]=='X' || arr[i][j][1]=='?'){///--Closed And Not Flag Cell
                    if(arr[i][j][0]>='1'){///--Unopened Number
                        arr[i][j][1]=arr[i][j][0];
                    }else if(arr[i][j][0]==' '){///--Unopened Empty Cell
                        arr[i][j][1]=arr[i][j][0];
                        multiOpen(i,j,n,m,arr);
                    }else if(arr[i][j][0]==15){///--Mine (if flags were wrong set)
                        arr[i][j][1]='!';
                        w_flag=1;///--Indicator For Losing
                    }
                }
            }
        }
        if (w_flag==1){
            lose(n,m,arr,&*case_lose);
        }
    }else{///--Number Not Equal Flags Surrounding It
        color(12);
        printf(" This Is an Opened Number !\n\n");
        *correct_case=1;/// if user input incorrectly make continue to while (game loop) to begin it from the frist
    }
}

///---------------------------Open An Opened Cell---------------------------
void openAgain(int i,int j,int n,int m,char arr[n][m][2],int *case_lose, int *correct_case){
    if (arr[i][j][1]==' '){
                    color(12);
                    printf(" This Cell Is Already Opened !\n\n");
                    *correct_case=1;/// if user input incorrectly make continue to while (game loop) to begin it from the frist
                    //printGrid(n,m,arr);
            }else if(arr[i][j][1]>='1'){//--Number May Be Surrounded By Equivalent Flags
                numAgain(i,j,n,m,arr,&*case_lose,&*correct_case);
               // printGrid(n,m,arr);
                }
}

///---------------------------Open Operation---------------------------
void openCases(int i,int j,int n,int m,char arr[n][m][2],int *case_lose,int* correct_case){
   // system("cls");

    if(arr[i][j][1]=='F'){///--Trying To open Flag Sign
            color(12);
            printf(" Attention this is flag !\n\n");
            *correct_case=1;/// if user input incorrectly make continue to while (game loop) to begin it from the frist
           // printGrid(n,m,arr);
        }else if(arr[i][j][1]!='X' && arr[i][j][1]!='?'){///--Trying ToOpen An Opened Cell
            openAgain(i,j,n,m,arr,&*case_lose,&*correct_case);
        }else if (arr[i][j][0]==15){///--Opened A MINE
            lose(n,m,arr,&*case_lose);
            arr[i][j][1]='!';
           // printGrid(n,m,arr);
        }else if(arr[i][j][0]>='1'){///--Unopened Number
            arr[i][j][1]=arr[i][j][0];
           // printGrid(n,m,arr);
        }else if(arr[i][j][0]==' '){///--Unopened Empty Cell
            arr[i][j][1]=' ';
            multiOpen(i,j,n,m,arr);
           // printGrid(n,m,arr);
    }
}


///---------------------------Flag Operation---------------------------
void flagCases(int i,int j,int n,int m,char arr[n][m][2],int *flag_num,int*qus_markes,int*mines,int*correct_case){
    if(arr[i][j][1]=='X'){ ///--If Not Flag
            arr[i][j][1]='F';
            *flag_num+=1;
            *mines-=1;
    }
    else if(arr[i][j][1]=='?'){
            arr[i][j][1]='F';
            *flag_num+=1;
            *mines-=1;
            *qus_markes-=1;
    }
    else if(arr[i][j][1]=='F'){///--If Already Flag Remove It
            arr[i][j][1]='X';
            *flag_num-=1;
            *mines+=1;
    }
    else{///--Trying To Flag An Opened Cell
            color(12);
            printf(" This Is Already Open !\n\n");
            *correct_case=1;/// if user input incorrectly make continue to while (game loop) to begin it from the frist
        }
        //printGrid(n,m,arr);
}

///---------------------------Question Operation---------------------------
void questionCases(int i,int j,int n,int m,char arr[n][m][2],int *flag_num,int*qus_markes,int*mines,int*correct_case){
    if(arr[i][j][1]=='X'){//--If Not ?
            arr[i][j][1]='?';
            *qus_markes+=1;
        }else if(arr[i][j][1]=='F'){
            arr[i][j][1]='?';
            *flag_num-=1;
            *qus_markes+=1;
            *mines+=1;
        }else if (arr[i][j][1]=='?'){///--If ? Remove It
            arr[i][j][1]='X';
            *qus_markes+=1;
        }else{///--Trying To ? An Opened Cell
            color(12);
            printf(" This Is Already Open !\n\n");
            *correct_case=1;/// if user input incorrectly make continue to while (game loop) to begin it from the frist
        }
        //printGrid(n,m,arr);
}



///---------------------------Which Operation ! ---------------------------
void GameLoop(int n,int m,char arr[n][m][2],int *moves,int *flags,int *qus_marks,int *mines,
              time_t start_t,int *mins,int *secs,int s_secs,int s_mins,int*continue_case){

    int i,j,flag=1;///i and j are index of chosen cell and flag to check the end of game loop
    char operation[256];///string to scan operation
    int correct_case;/// if user input incorrectly make continue to while (game loop) to begin it from the frist

    system("cls");///clear cmd window
    printLogo();
    printGrid(n,m,arr);
    printInfo(*mins,*secs,*moves,*flags,*qus_marks,*mines);
    win_check(n,m, arr,* moves, start_t,*mins , *secs,s_secs,s_mins,*flags,*qus_marks,*mines,&flag );///if the player win from first cell
    if(!flag){return 0;}///if the player wins end game loop function


    ///loop to continue scan until the player lose or win

    while(flag==1){

        correct_case=0;
        getInput(operation,&i,&j,n,m,arr,&*moves);///scan operation and cell position correctly
        /// lead any operation for its function
        switch (operation[0]){
            case 'M':{

                timePassed(start_t,&*mins,&*secs,s_secs,s_mins);///TO GET CURRETNT SAVE TIME
                saveFile("continue.txt",n,m,arr,*mins,*secs,*moves,*flags,*qus_marks,*mines);
                *continue_case=1;
                return ;/// exit from Game loop function
            }
            case 'S':{

                timePassed(start_t,&*mins,&*secs,s_secs,s_mins);///--TO GET CURRETNT SAVE TIME
                saveFile("save.txt",n,m,arr,*mins,*secs,*moves,*flags,*qus_marks,*mines);

                color(10);
                printf("   Game Saved\n\n");
                continue;
            }


            case 'O':{
                openCases(i,j,n,m,arr,&flag,&correct_case);
                if(correct_case){
                    *moves+=1;
                    continue;
                }
                break;
            }
            case 'F':{
                if(*flags==1+(n * m)/10 && arr[i][j][1]!='F'){
                    color (9);
                    printf("\nsorry !\tyou reach the max number of flags.\n\n");
                    *moves+=1;
                    continue;
                }
                else{
                    flagCases(i,j,n,m,arr,&*flags,&*qus_marks,&*mines,&correct_case);
                    if(correct_case){
                        *moves+=1;
                        continue;
                    }

                }

                break;
            }
            case 'Q':{
                questionCases(i,j,n,m,arr,&*flags,&*qus_marks,&*mines,&correct_case);
                if(correct_case){
                   *moves+=1;
                    continue;
                }
                break;
            }
            default:///--if operation is one character but not correct
                color(12);
                printf("Please Select An Correct Operation !\n\n");
                *moves+=1;
                continue;
            }
        *moves+=1;///if he input inputs correctly
        if(!flag){///if the player is lose

                timePassed(start_t,&*mins,&*secs,s_secs,s_mins);
                system("cls");///clear cmd window
                printLogo();
                printGrid(n,m,arr);
                printInfo(*mins,*secs,*moves,*flags,*qus_marks,*mines);
                color(12);
                printf("\n\t\tYOU LOST,GAME OVEER\n\n\t ");
                color(10);
                printf("Press Any Key To Go To Main Menu...");
                fflush(stdin);
                getchar();
        }

        win_check(n,m, arr, *moves,start_t ,*mins , *secs,s_secs,s_mins,*flags,*qus_marks,*mines,&flag );
        if(flag){///if the player don't win or don't lose yet

            timePassed(start_t,&*mins,&*secs,s_secs,s_mins);
            system("cls");///clear cmd window
            printLogo();
            printGrid(n,m,arr);
            printInfo(*mins,*secs,*moves,*flags,*qus_marks,*mines);
        }
    }
}







#endif // GAME_LOOP_FUNCTIONS_H_INCLUDED
