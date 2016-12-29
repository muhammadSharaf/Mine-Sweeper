#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
///--FUNCTION FILES--
#include "print_functions.h"
#include "scan_functions.h"
#include "main_menu_functions.h"
#include "file_functions.h"
#include "game_loop_functions.h"
#include "startup_functions.h"
#include "time_functions.h"


int main()
{
    system("MODE 80,400");///to fix size of cmd window

    ///check variables (exit) if the player want to exit and(continue)to add continue to main menu choices when he pause the game
    int exit_case=0,continue_case=0;
    int ScoreList_continue;///check if the player paused the game then he goes to high score list so still print continue choice
    ///check if the player paused the game then he goes to load and he don't find any game so still print continue choice
    int load_continue;

    ///main menu loop until the user want to exit
    while(!exit_case){
        ScoreList_continue=continue_case;///if he paused the game and go to high score list still print continue choice
        ///check if the player paused the game then he goes to load and he don't find any game so still print continue choice
        load_continue=continue_case;

        PrintMainMenu(continue_case); ///print user interface
        char scan[100];///string to scan from user
        color(13);
        printf("\t   PLEASE SELECT AN OPTION BY TYPING ITS FIRST LETTER\n\t\t\t\t");
        color(10);


        /// for loop until the user enter a valid input
        for(;;){
            fflush(stdin);/// clear scanf memory before scan
            SkipSpacesScan(scan);///scan user choice by this function to avoid wrong inputs
            scan[0]=toupper(scan[0]);///operation can be upper or lower case

            ///to prevent user from choosing continue choice when he start new game not pause a  current game
            if(continue_case!=1 && scan[0]=='C' &&scan[1]=='\0'){
                color(12);
                printf("\t\t Please Enter A Valid Letter !\n\t\t\t\t");
                color(10);
                continue;
            }

            /// if operation not a single character
            if((scan[0]=='C' ||scan[0]=='S'||scan[0]=='L'||scan[0]=='G'||scan[0]=='H'||scan[0]=='E')
               &&((scan[1]==' '&&scan[2]=='\0' )||scan[1]=='\0')){

                break;
               }
               else{
                   color(12);
                   printf("\t\t Please Enter A Valid Letter !\n\t\t\t\t");
                   color(10);
                   continue;
                }
        }

        continue_case=0;/// to avoid print continue choice in the beginning of play

        ///switch to lead any choice to its function
        switch (scan[0]){

                ///CONTINUE
                case 'C':{
                    Continue(&continue_case);
                    break;
                }

                ///START NEW GAME
                case 'S':{
                    StartNewGame(&continue_case);
                    break;
                }

                ///LOAD GAME
                case 'L':{
                    LoadGame(&continue_case,load_continue);
                    break;
                }

                ///GET HIGH SCORE
                case 'G':{
                    HighScoreList();
                    continue_case=ScoreList_continue;///if he paused the game and go to highScoreList still print continue choice
                    break;
                }

                ///HOW TO PLAY
                case 'H':{

                    break;
                }

                ///EXIT
                case 'E':{
                    exit_case=1;
                    break;
                }
        }///end switch


    }///end main menu loop


    return 0;
}
