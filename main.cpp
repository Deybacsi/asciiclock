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

using namespace std;


#include "inc/common.h"
#include "inc/screen.h"

#include "inc/clock_digits.h"

#include "inc/clock_digital.cpp"
#include "inc/clock_analog.cpp"

#include "inc/backg_snow.cpp"
#include "inc/backg_starfield.cpp"

s_simplechar WRITECHAR = { 32, 2, 8, false, false, false};

// define the effects
typedef void (*myfunctions)();

// 0 - init
// 1 - calc next frame
// 2 - draw act frame to layers

myfunctions background[][3] = {
    { init_bg_snow, calc_bg_snow, draw_bg_snow},    // snow effect
    { init_bg_star, calc_bg_star, draw_bg_star}     // starfield
};


// the actual background effect
int ACT_BG_EFFECT = 1;

int main()
{	int ch;


    srand(GetMilliCount());
    initscreen();
    clear();

    // elapsed time counter in msec
    int nTimeElapsed =0;


    // initialize background
    background[ACT_BG_EFFECT][0]();
init_clock_digital();
    do {
        int nTimeStart = GetMilliCount();


        checktime();

        // calculate next background frame
        background[ACT_BG_EFFECT][1]();
        // put background frame to layers
        background[ACT_BG_EFFECT][2]();

        //stringxy(4, 2,2 , WRITECHAR, ACT_TIMESTR[0]);

        draw_clock_digital((SCREENX-(DIGITDESIGNS[ACTDIGITDESIGN].x*5)) /2 ,(SCREENY-DIGITDESIGNS[ACTDIGITDESIGN].y) /2);

        
        //stringxy(4, 2,5 , WRITECHAR, to_string(nTimeElapsed));
        
        mergelayers();

        printscreen();

        //gotoxy(10,3);
        //printf("%d:%d:%s", ACT_HOUR[0], ACT_MIN[0],inttostr2(ACT_SEC[0]).c_str());
        //printf("%s", ACT_TIMESTR[0].c_str());



        // get elapsed time in ms
        int nTimeElapsed = GetMilliSpan( nTimeStart );
        // wait some ms to have the needed FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(FPS2MILLISEC-nTimeElapsed));
    } while ( cin.peek() != EOF );	



	return 0;
}
