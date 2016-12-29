#ifndef FILE_FUNCTIONS_H_INCLUDED
#define FILE_FUNCTIONS_H_INCLUDED

void saveFile (char *fileName,int n,int m,char arr[n][m][2],int mins,int secs,int moves,int flags,int qus_marks,int mines){
        FILE *save;
        int i,j;
        save=fopen(fileName,"w");
        ///save rows and columns
        fprintf(save,"%d\n%d\n",n,m);

        ///save two arrays
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                fprintf(save,"%c",arr[i][j][0]);
            }
            fprintf(save,"\n");
        }
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                fprintf(save,"%c",arr[i][j][1]);
            }
            fprintf(save,"\n");
        }

        ///save remained information
        fprintf(save,"%d\n",mins);
        fprintf(save,"%d\n",secs);
        fprintf(save,"%d\n",moves);
        fprintf(save,"%d\n",flags);
        fprintf(save,"%d\n",qus_marks);
        fprintf(save,"%d\n",mines);
        fclose(save);
}


/*********************************************/
///load function


void subload(char *fileName,int *rows,int *columns,int *FileExesit_check){
    FILE*f=fopen(fileName,"r");
    ///if the file is not exist (nobody saved any game before)

    if(access(fileName,F_OK) != -1){
        fscanf(f,"%d",&*rows);
        fscanf(f,"%d",&*columns);
        *FileExesit_check=1;
    }
    else{
       system("cls");
       color(9);
       printf("\n\n\n\tyou haven't saved any game yet\n\n");
       color(10);
       printf("\tplease, enter any key to go to main menu");
       fflush(stdin);
       getchar();

       *FileExesit_check=0;
    }
}


void load(char *fileName,int n,int m,char arr[n][m][2],int *moves,int *mins,int *secs,int *flags,int *qus_markes,int *mines ){

    FILE*f=fopen(fileName,"r");
    char take[256];
    int i,j;

///read rows and columns again to skip them
    fscanf(f,"%d",&n);
    fscanf(f,"%d",&m);
    fgets(take,256,f);///this to go to next line

///read two arrays
    for(i=0;i<n;i++){
        fgets(take,256,f);///read line by line and save in take string
        for(j=0;j<m;j++){
            arr[i][j][0]=take[j];///save line by line in arr
        }
    }
    for(i=0;i<n;i++){
        fgets(take,256,f);
        for(j=0;j<m;j++){
            arr[i][j][1]=take[j];
        }
    }
///read move and flags and time and qus_marks and remained_mines
    fscanf(f,"%d",mins);
    fscanf(f,"%d",secs);
    fscanf(f,"%d",moves);
    fscanf(f,"%d",flags);
    fscanf(f,"%d",qus_markes);
    fscanf(f,"%d",mines);

    fclose(f);
}





/***********************************/

void debugFile (int n,int m,char arr[n][m][2]){
    FILE *debug;
    debug=fopen("debug.txt","w");
    int i,j,r;
    ///--Print Horizontal Index
    fprintf(debug,"  ");
    for(r=0;r<m;r++){
        fprintf(debug,"  %2d",r);
    }
    ///--Print top Border
    fprintf(debug,"\n    ");
    for(r=0;r<m;r++){
        fprintf(debug,"--- ");
    }
    fprintf(debug,"\n");
    ///--Print Array Elements + Borders
    for(i=0;i<n;i++){
        fprintf(debug,"%2d |",i);
        for(j=0;j<m;j++){
            fprintf(debug," %c |",arr[i][j][0]);
        }
        fprintf(debug,"\n    ");
        for(r=0;r<m;r++){
            fprintf(debug,"--- ");
        }
        fprintf(debug,"\n");
    }
    fclose(debug);
}



/*********************************************************/
///rank function
void score_rank(char newName[256],int *newScore,int*rank1){

    FILE* scoref;
    FILE* namef;
    int scoreArr[256];
    char nameArr[256][256];
    char take[256];
    int i,j;





    ///read old score array

    scoref=fopen("score.txt","r");


    if(access("score.txt",F_OK)!=-1){///if the file is not saved before

    i=0;
    while(!feof(scoref)){
        fscanf(scoref,"%d",&scoreArr[i]);
        i++;
    }
    fclose(scoref);

/// read name array
    namef=fopen("name.txt","r");
    j=0;
    while(!feof(namef)){
      fgets(take,256,namef);
      if(take[0]!=0){

        for(i=0;take[i]!=10 ;i++){///10 ='\n'
            nameArr[j][i]=take[i];
        }
        ///clear take string
        for(i=0;take[i]!=0;i++){
            take[i]=0;
        }
        j++;
      }
    }
    fclose(namef);

/// add the new score

    int counter=0,found=1;
    ///loop until we find the name or end the list
    while(found&&nameArr[counter][0]!=0){
        found=0;
        for(i=0;newName[i]!=0;i++){
            if(nameArr[counter][i]!=newName[i]){
                found=1;

                if(nameArr[counter][i]==' ' && nameArr[counter][i+1]==0){
                    found=0;
                }
        }
        counter++;
    }

    ///if we found the name add his score to old score
    if(!found){
        scoreArr[counter-1]+=*newScore;
        *newScore=scoreArr[counter-1];
    }
    else{
        for(i=0;newName[i]!=0;i++){
            nameArr[counter][i]=newName[i];
        }
        scoreArr[counter]=*newScore;
        *newScore=scoreArr[counter];
    }


///sorting and calculate the rank
    if(!found){///if the name is old
        i=counter-1;///i is the index of the player name
    }
    else{
        i=counter;
    }
    found=1;///to check the list is sorted or not
    int temp ;
    char temp1[256];

    *rank1=1;/// if the new player the frist winner player
    for(i;i>0&&found;i--){///i>0 to avoid compare with scoreArr[-1]
        if(scoreArr[i]>scoreArr[i-1]){
           temp=scoreArr[i];
           scoreArr[i]=scoreArr[i-1];
           scoreArr[i-1]=temp;

           for(j=0;nameArr[i][j]!=0;j++){
              temp1[j]=nameArr[i][j];
           }
           temp1[j]=0;
           for(j=0;nameArr[i-1][j]!=0;j++){
              nameArr[i][j]=nameArr[i-1][j];
           }
           nameArr[i][j]=0;
           for(j=0;temp1[j]!=0;j++){
              nameArr[i-1][j]=temp1[j];
           }
           nameArr[i-1][j]=0;
           for(j=0;temp1[j]!=0;j++){
             temp1[j]=0;
           }
           *rank1=i;
        }
        else{
            *rank1=i+1;
            found=0;
        }
    }
    }

    }else{
        *rank1=1;
        scoreArr[0]=*newScore;
        for(i=0;newName[i]!=0;i++){
            nameArr[0][i]=newName[i];
        }
    }

///rewrite in the files
    scoref=fopen("score.txt","w");
    for(i=0;nameArr[i][0]!=0;i++){
        fprintf(scoref,"%d\n",scoreArr[i]);
    }

    fclose(scoref);



///read names
    namef=fopen("name.txt","w");
    for (i=0;nameArr[i][0]!=0;i++){
        for(j=0;nameArr[i][j]!=0;j++){
            fprintf(namef,"%c",nameArr[i][j]);
        }
        fprintf(namef,"\n");
    }

    fclose(namef);
}



/**************************************/
void HighScoreList(){

    FILE* scoref;
    FILE* namef;
    int scoreArr[256];
    char nameArr[256][256];
    char take[256];
    int i,j,counter;




    ///read  score array

    scoref=fopen("score.txt","r");

    ///if the file is not exist (nobody saved any game before)

    if(access("score.txt",F_OK) != -1){

        i=0;
        while(!feof(scoref)){
            fscanf(scoref,"%d",&scoreArr[i]);
            i++;
        }
        fclose(scoref);

        /// read name array
        namef=fopen("name.txt","r");
        j=0;
        while(!feof(namef)){
            fgets(take,256,namef);
            if(take[0]!=0){

                for(i=0;take[i]!=10 ;i++){
                    nameArr[j][i]=take[i];
                }
                ///clear take string
                for(i=0;take[i]!=0;i++){
                    take[i]=0;
                }
                j++;
            }
        }
        fclose(namef);


         ///print list of high scores
        system("cls");
        printf("\n\n\n");
        color(13);
        printf("\t\t# # ###  ## # #      ##  ##  #  ##  ###  ## \n");
        printf("\t\t# #  #  #   # #     #   #   # # # # #   #   \n");
        printf("\t\t###  #  # # ###      #  #   # # ##  ##   #  \n");
        printf("\t\t# #  #  # # # #       # #   # # # # #     # \n");
        printf("\t\t# # ###  ## # #     ##   ##  #  # # ### ##  \n\n\n");


        counter=j;
        for(i=0;i<counter;i++){
            color(8);
            printf("\t  %2d. ",i+1);
            for(j=0;j<20;j++){
                color(10);
                printf("%C",nameArr[i][j]);
            }
            color(8);
            printf("...\t");
            color(14);
            printf("%10d\n\n",scoreArr[i]);
        }
    }
    else{///file is not exist
       system("cls");
       color(9);
       printf("\n\n\n\tNOBODY PLAYED BEFORE\n\n");


    }

        color(15);
        printf("\n\n\tPress Any Key To Go To Main Menu...");
        fflush(stdin);
        getchar();
}



#endif // FILE_FUNCTIONS_H_INCLUDED
