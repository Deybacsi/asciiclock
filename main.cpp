#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <sys/timeb.h>
#include <math.h>
#define PI 3.14159265

using namespace std;


#include "inc/common.h"
#include "inc/screen.h"
#include "inc/3d.h"

#include "inc/clock_digits.h"

#include "inc/clock_digital.cpp"
#include "inc/clock_analog.cpp"

#include "inc/backg_snow.cpp"
#include "inc/backg_starfield.cpp"
#include "inc/backg_plasma.cpp"
#include "inc/backg_matrix.cpp"
#include "inc/backg_fire.cpp"

#include "inc/foreg_cube.cpp"


// define the effects
typedef void (*myfunctions)();

// 0 - init
// 1 - calc next frame
// 2 - draw act frame to layers

myfunctions background[][3] = {
    { init_bg_snow, calc_bg_snow, draw_bg_snow},            // snow effect
    { init_bg_star, calc_bg_star, draw_bg_star},            // starfield
    { init_bg_plasma, calc_bg_plasma, draw_bg_plasma},      // plasma
    { init_bg_matrix, calc_bg_matrix, draw_bg_matrix},      // matrix
    { init_bg_fire, calc_bg_fire, draw_bg_fire}             // fire
     
};

/*
myfunctions foreground[][3] = {
    { init_fg_cube, calc_fg_cube, draw_fg_cube}             // cube
};
*/

const int   BG_EFFECTNO=5,
            FG_EFFECTNO=1;

int         ACT_BG_EFFECT=3,
            ACT_FG_EFFECT=0;


void init_all() {
    initscreen();
    clear();
    // randomize clock charset design
    ACTDIGITDESIGN=rand() % MAXDIGITDESIGNS;
    // randomize clock color
    CLOCKCOLOR=rand() % 8;
    // the actual background effect
    ACT_BG_EFFECT = rand() % BG_EFFECTNO;
    //ACT_BG_EFFECT=4;
    // initialize background & foreground effects
    background[ACT_BG_EFFECT][0]();
    // foreground[ACT_FG_EFFECT][0]();
        
}


int main(){
    int ch;

    srand(GetMilliCount());

    // elapsed time counter in msec
    int nTimeElapsed =0;


    init_all();

    init_clock_digital();
    do {
        int nTimeStart = GetMilliCount();

        checktime();
        if (LAST_MINSTR[0] != ACT_MINSTR[0]) {
            init_all();
        }
     

        // calculate next background frame
        background[ACT_BG_EFFECT][1]();

        // put background frame to layers
        background[ACT_BG_EFFECT][2]();

        //stringxy(4, 2,2 , WRITECHAR, ACT_TIMESTR[0]);

        draw_clock_digital((SCREENX-(DIGITDESIGNS[ACTDIGITDESIGN].x*5)) /2 ,(SCREENY-DIGITDESIGNS[ACTDIGITDESIGN].y) /2);

        // calculate next foreground frame
        // foreground[ACT_FG_EFFECT][1]();

        // put background frame to layers
        // foreground[ACT_FG_EFFECT][2]();

        //stringxy(4, 2,5 , WRITECHAR, to_string(nTimeElapsed));
        
        mergelayers();

        printscreen();

        //gotoxy(10,3);
        //printf("%d:%d:%s", ACT_HOUR[0], ACT_MIN[0],inttostr2(ACT_SEC[0]).c_str());
        //printf("%s", ACT_TIMESTR[0].c_str());

        LAST_MINSTR[0]=ACT_MINSTR[0];

        // get elapsed time in ms
        int nTimeElapsed = GetMilliSpan( nTimeStart );
        // wait some ms to have the needed FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(FPS2MILLISEC-nTimeElapsed));
    } while ( cin.peek() != EOF );	



	return 0;
}
