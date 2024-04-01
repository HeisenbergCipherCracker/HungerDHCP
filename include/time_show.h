#ifndef TIME_SHOW_H
#define TIME_SHOW_H
#include <time.h>

#include<stdio.h>

time_t current_time;

char printTime(){
    printf("%s", ctime(&current_time));
    return 0;
}

#endif // TIME_SHOW_H