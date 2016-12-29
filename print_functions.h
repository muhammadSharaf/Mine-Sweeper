#ifndef PRINT_FUNCTIONS_H_INCLUDED
#define PRINT_FUNCTIONS_H_INCLUDED

int color(int x){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, x);
    return x;
}
int colorCases (int i,int j,int n,int m,char arr[n][m][2]){
    switch(arr[i][j][1]){
        case 'X': return 7;
        case 'F': return 4;
        case '?': return 4;
        case ' ': return 0;
        case '1': return 13;
        case '2': return 10;
        case '3': return 14;
        case '4': return 9;

        //--LOOSING COLORS--
        case '/': return 3;
        case 'M': return 11;
        case '!': return 15;
        case  15: return 12;
    }
}


/// two function to print mine sweeper logo
///(1)
///this function print line by line when it is called several times from mine Sweeper function
void printMineSweeper(char *str){
    int i=0;
    while(str[i]!='\0'){

        color(12);
        if(str[i]==' '){
            printf("%c",str[i]);
        }else{
            printf("%c",str[i]);
            usleep(1);
        }
        i++;
    }
    printf("\n");
}
///(2)
///this function to define strings and call printMineSweeper
void mineSweeper(){
    printf("\n\n");
    char str0[]="  #     #                                                                     ";
    char str1[]="  ##   ## # #    # ######     ####  #    # ###### ###### #####  ###### #####  ";
    char str2[]="  # # # # # ##   # #         #      #    # #      #      #    # #      #    # ";
    char str3[]="  #  #  # # # #  # #####      ####  #    # #####  #####  #    # #####  #    # ";
    char str4[]="  #     # # #  # # #              # # ## # #      #      #####  #      #####  ";
    char str5[]="  #     # # #   ## #         #    # ##  ## #      #      #      #      #   #  ";
    char str6[]="  #     # # #    # ######     ####  #    # ###### ###### #      ###### #    # ";

    ///send line by line to printMineSweeper function to print it
    printMineSweeper(str0);
    printMineSweeper(str1);
    printMineSweeper(str2);
    printMineSweeper(str3);
    printMineSweeper(str4);
    printMineSweeper(str5);
    printMineSweeper(str6);
}

///(3)
///this function to print main menu choices
void PrintMainMenu (int continue_case){
    system("cls");///clear cmd window
    mineSweeper();///call this function to print logo

    printf("\n\n\n");
    ///--SAMPOLS  16,17 are '><'  250 is '-' '-'
    /// call color function to change words color

    /// to check if we need to add continue choice to main menu when the game is paused or not
    if(continue_case==1){
        color(8);
        printf("\t\t\t   %c ",16);
        color(10);
        printf(" %cC%cONTINUE ",250,250);
        color(8);
        printf(" %c\n\n\n",17);
    }

    ///print other choices

    color(9);
    printf("\t\t\t%c ",16);
    color(11);
    printf(" %cS%cTART NEW GAME ",250,250);
    color(9);
    printf(" %c\n\n\n",17);

    color(10);
    printf("\t\t\t  %c ",16);
    color(14);
    printf(" %cL%cOAD A GAME ",250,250);
    color(10);
    printf(" %c\n\n\n",17);

    color(10);
    printf("\t\t\t  %c ",16);
    color(14);
    printf(" %cG%cREAT SCORE ",250,250);
    color(10);
    printf(" %c\n\n\n",17);

    color(10);
    printf("\t\t\t  %c ",16);
    color(14);
    printf(" %cH%cOW TO PLAY ",250,250);
    color(10);
    printf(" %c\n\n\n",17);

    color(5);
    printf("\t\t\t     %c ",16);
    color(12);
    printf(" %cE%cXIT ",250,250);
    color(5);
    printf(" %c\n\n\n",17);
}
 ///(4)
 ///


 void printLogo(){
    int i,r;

    r=rand()%15;///to change color of logo every once
    if(r==0){
        r=14;
    }
    color(r);
    printf("\t\t\t %c MINE SWEEPER %c\n",175,174);
    printf("\t\t\t ");
    for(i=0;i<8;i++){
        printf("%c ",126);
    }
    printf("\n\n");
    color(7);
}


void printGrid(int rows,int columns,char arr[rows][columns][2]){

    int i,j,r;
    ///Print Horizontal Index
    printf("    ");
    color(8);
    for(r=0;r<columns;r++){
        printf("  %2d",r);
    }

    ///Print top Border
    printf("\n      ");
    color(3);
    for(r=0;r<columns;r++){
        printf("%c%c%c ",196,196,196);
    }
    printf("\n");

    ///Print Array Elements + Borders
    for(i=0;i<rows;i++){
        color(8);
        printf("  %2d ",i);
        color(3);
        printf("%c",179);
        for(j=0;j<columns;j++){
            color(colorCases(i,j,rows,columns,arr));///to chose different color to each elements
            printf(" %c",arr[i][j][1]);
            color(3);
            printf(" %c",179);
        }
        printf("\n      ");

        for(r=0;r<columns;r++){
            printf("%c%c%c ",196,196,196);
        }
        printf("\n");
    }
    color(15);
    printf("\n");
}

void printInfo (int mins,int secs,int moves,int flags,int qus_marks,int remained_mines ){
    color(8);
    printf("   TIME ");
    color(14);
    printf("%0.2d:%0.2d   ",mins,secs);

    color(8);
    printf("MOVES ");
    color(14);
    printf("%d   ",moves);

    color(8);
    printf("FLAGS ");
    color(14);
    printf("%d   ",flags);

    color(8);
    printf("QUS_MARKS ");
    color(14);
    printf("%d   ",qus_marks);

    color(8);
    printf("REMAINED_MINES ");
    color(14);
    printf("%d   ",remained_mines);
    printf("\n\n");


    ///Instructions
    color(10);
    printf(" Press  O raw column  to     open     ex: O 0 0\n");
    printf(" Press  F raw column  to flag/unflag  ex: F 0 0\n");
    printf(" Press  Q raw column  to mark/unmark  ex: Q 0 0\n");
    printf(" Press  M  to Main Menu\n");
    printf(" Press  S  to save\n\n");

    color(12);
    printf("       You Must Enter The Full Sequence To Go\n");
    printf("  Anything After A Correct Sequence Will Be Ignored\n");
    printf("     Wrong Sequence Will Be Considered As A Move\n");
    printf("\n");
}






#endif // PRINT_FUNCTIONS_H_INCLUDED
