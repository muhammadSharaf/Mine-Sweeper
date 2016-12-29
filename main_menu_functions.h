#ifndef MAIN_MENU_FUNCTIONS_H_INCLUDED
#define MAIN_MENU_FUNCTIONS_H_INCLUDED

void Continue(int*continue_case){
    ///variables
    time_t start_time; /// time variable to take start time
    int rows,columns,mins,secs,moves,flags,qus_marks,remained_mines,s_secs,s_mins; ///main variables in game
    int FileExesit_check; ///to check if the save file is  exist or not

    subload("continue.txt",&rows,&columns,&FileExesit_check);///load n,m to define array size

     if(FileExesit_check==1){
        char arr[rows][columns][2];
        load("continue.txt",rows,columns,arr,&moves,&s_mins,&s_secs,&flags,&qus_marks,&remained_mines);

        time(&start_time);///--takes new start point
        timePassed(start_time,&mins,&secs,s_secs,s_mins);

        GameLoop(rows,columns,arr,&moves,&flags,&qus_marks,&remained_mines,start_time,&mins,&secs,s_secs,s_mins,&*continue_case);
    }
}



///
void StartNewGame(int*continue_case){
    ///variables
    time_t start_time; /// time variable to take start time
    int rows,columns,mins=0,secs=0,moves=0,flags=0,qus_marks=0,remained_mines=0,s_secs=0,s_mins=0; ///main variables in game

    ///scan rows columns
    system("cls");///clear cmd window
    printLogo();
    inputGrid(&rows,"rows");/// scan rows
    inputGrid(&columns,"Columns");///scan columns
    color(10);
    printf("\nNUMBER OF ROWS IS %d\tNUMBER OF COLUMNS IS %d",rows,columns);
    pause(1);

    remained_mines=1+(rows*columns)/10;

    ///--Start Game
    char arr[rows][columns][2];

    ///scan frist cell and generate arrays and spread mines randomly
    startup(rows,columns,arr);
    moves++;///add frist move



    ///start to calculate the passed time
    time(&start_time);
    timePassed(start_time,&mins,&secs,s_secs,s_mins);


    GameLoop(rows,columns,arr,&moves,&flags,&qus_marks,&remained_mines,start_time,&mins,&secs,s_secs,s_mins,&*continue_case);

}



void LoadGame(int *continue_case,int load_continue){
    ///variables
    time_t start_time; /// time variable to take start time
    int rows,columns,mins,secs,moves,flags,qus_marks,remained_mines,s_secs,s_mins; ///main variables in game
    int FileExesit_check; ///to check if the save file is  exist or not


    subload("save.txt",&rows,&columns,&FileExesit_check);///load n,m to define array size

    if(FileExesit_check==1){
        char arr[rows][columns][2];
        load("save.txt",rows,columns,arr,&moves,&s_mins,&s_secs,&flags,&qus_marks,&remained_mines);

        time(&start_time);///takes new start point
        timePassed(start_time,&mins,&secs,s_secs,s_mins);

        GameLoop(rows,columns,arr,&moves,&flags,&qus_marks,&remained_mines,start_time,&mins,&secs,s_secs,s_mins,&*continue_case);
    }
    else{
        *continue_case=load_continue;
    }

}

#endif // MAIN_MENU_FUNCTIONS_H_INCLUDED
