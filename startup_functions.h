#ifndef STARTUP_FUNCTIONS_H_INCLUDED
#define STARTUP_FUNCTIONS_H_INCLUDED



///Make all the back array 0 and user's array closed 'X'
void zeroAll(int n,int m,char arr[n][m][2]){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            arr[i][j][0]='0';
            arr[i][j][1]='X';
        }
    }
}

///Generate numbers according to bombs
void numSystem (int bomb_i,int bomb_j,int n,int m,char arr[n][m][2]){
    int i,j;
    for(i=bomb_i-1;i<=bomb_i+1;i++){
        if(i<0 || i>n-1){continue;}
        for(j=bomb_j-1;j<=bomb_j+1;j++){
            if(j<0 || j>m-1){continue;}///to avoid edge limits
            if(arr[i][j][0]==15){///if there was another mine in this cell
                continue;
            }else{
                arr[i][j][0]++;
            }
        }
    }
}
///Generate random Bombs and call numSystem function to add numbers to cells around the mine
void randBomb(int f_i,int f_j,int n,int m,char arr[n][m][2]){
    srand(time(NULL));
    int bomb_number,i,j;
    bomb_number=1+(n*m)/10;
    while(bomb_number!=0){
        i=rand()%n;
        j=rand()%m;
        if (arr[i][j][0]==15 || (i==f_i && j==f_j)){
            continue;///the random bomb maybe already exists
        }else{
            arr[i][j][0]=15;
            numSystem(i,j,n,m,arr);
            bomb_number--;
        }
    }
}
///Generating the empty cells (no mines around it)
void emptyZero(int n,int m,char arr[n][m][2]){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(arr[i][j][0]=='0'){
                arr[i][j][0]=' ';
            }
        }
    }
}





///--Generating the game startup setup
void startup (int n,int m,char arr[n][m][2]){

    int f_i,f_j;

    zeroAll(n,m,arr); ///Make all the back array 0 and user's array closed 'X'

    system("cls");/// clear cmd window
    printLogo();
    printGrid(n,m,arr);

    getstart(&f_i,&f_j,n,m,arr);///scan first cell coordinates

    randBomb(f_i,f_j,n,m,arr);///spread the mines randomly and put numbers around it
    emptyZero(n,m,arr);/// make all cells that haven't mines around it as empty cell

    /// open frist cell
    arr[f_i][f_j][1]=arr[f_i][f_j][0];
    ///if first was empty cell
    if (arr[f_i][f_j][0]==' '){
        multiOpen(f_i,f_j,n,m,arr);///Empty Cell SelfOpen when player open empty cell
    }

    debugFile(n,m,arr);/// save the array in debug file to help us in tracing

}





#endif // STARTUP_FUNCTIONS_H_INCLUDED
