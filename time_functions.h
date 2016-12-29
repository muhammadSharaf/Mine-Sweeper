#ifndef TIME_FUNCTIONS_H_INCLUDED
#define TIME_FUNCTIONS_H_INCLUDED

///when we need to freeze cmd some secs
void pause(int sec){
    time_t start_t, end_t;
    double diff_t;

    time(&start_t);
    do{
        time(&end_t);
    }while(diff_t = difftime(end_t, start_t)<sec);
}

///calculate the passed time
void timePassed (time_t start_t,int *mins,int *secs,int s_secs,int s_mins){
    time_t end_t;
    int diff_t;

    time(&end_t);
    diff_t = difftime(end_t, start_t);

    diff_t+=((s_mins*60)+s_secs);///add played time to saved time

    *secs=diff_t%60;
    *mins=diff_t/60;
}




#endif // TIME_FUNCTIONS_H_INCLUDED
