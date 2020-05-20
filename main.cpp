#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <sstream>
#include <fstream>
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


/* array with effects

   0 - init
   1 - calc next frame
   2 - draw act frame to layers

*/
myfunctions background[][3] = {
    { init_bg_snow, calc_bg_snow, draw_bg_snow},            // snow effect
    { init_bg_star, calc_bg_star, draw_bg_star},            // starfield
    { init_bg_plasma, calc_bg_plasma, draw_bg_plasma},      // plasma
    { init_bg_matrix, calc_bg_matrix, draw_bg_matrix},      // matrix
    { init_bg_fire, calc_bg_fire, draw_bg_fire}             // fire
     
};


// foreground effects

myfunctions foreground[][3] = {
    { init_fg_cube, calc_fg_cube, draw_fg_cube}             // 3D cube
};


// number of our effects 
// why don't we use length()?
const int   BG_EFFECTNO=5,
            FG_EFFECTNO=1;

int         ACT_BG_EFFECT=3,
            ACT_FG_EFFECT=0;


// init all thingies
void init_all() {
    int i;
    initscreen();
    clear();
    clearalllayer(CLEARCHAR);

    // randomize clock charset design
    ACTDIGITDESIGN=rand() % MAXDIGITDESIGNS;
    // randomize clock color
    CLOCKCOLOR=rand() % 8;
    // get a random background effect
    ACT_BG_EFFECT = rand() % BG_EFFECTNO;
    //ACT_BG_EFFECT=0;
    // initialize background & foreground effects
    background[ACT_BG_EFFECT][0]();
    foreground[ACT_FG_EFFECT][0]();
        
}


int main(){
    system("stty raw -echo");
    hideCursor();
    // to store pressed keys
    char ch=0;
    bool showForeground=false;
    string btcprice;

    srand(GetMilliCount());

    // elapsed time counter in msec
    int nTimeElapsed =0;

    init_all();
    init_clock_digital();
    
    while(ch!=27 && ch!=113 && ch!=120) {
        // current millisec for proper FPS counting
        int nTimeStart = GetMilliCount();

        checktime();
        // if minute changed, reinit everything
        if (LAST_MINSTR[0] != ACT_MINSTR[0]) {
            init_all();
        }
     
        // get btc price
        string line;
        ifstream myfile ("price.txt");
        if (myfile.is_open())
        {
            getline (myfile,btcprice);
            myfile.close();
        }

        // calculate next background frame
        background[ACT_BG_EFFECT][1]();

        // put background frame to layers
        background[ACT_BG_EFFECT][2]();

        // draw the clock
        draw_clock_digital((SCREENX-(DIGITDESIGNS[ACTDIGITDESIGN].x*5)) /2 ,(SCREENY-DIGITDESIGNS[ACTDIGITDESIGN].y) /2);


        // foreground effects, try 3d cube if interested
        if (showForeground) {
            // calculate next foreground frame
            foreground[ACT_FG_EFFECT][1]();

            // put background frame to layers
            foreground[ACT_FG_EFFECT][2]();
        }

        // write out btc price
        stringxy (5, float (SCREENX /2 -3), float(SCREENY /2)+5, WRITECHAR, " $"+btcprice+" " );

        // merge all layers and draw to screen
        mergelayers();
        printscreen();


        // check pressed keys
        if (keyPressed()) {
            ch=getchar();
            switch (ch) {
                case 27:
                    getchar(); ch=getchar();
                    switch (ch) {
                        case 27:
                            cout << endl << "ESC" << ch << endl; 
                            exit(0);
                            break;
                        case 68:
                            cout << "Left";
                            break;
                        case 67:
                            cout << "Right";
                            break;
                    }
                    break;
                case 102:
                    showForeground=!showForeground;
                    init_all();
                    break;
            }
        }

        // save current minute
        LAST_MINSTR[0]=ACT_MINSTR[0];

        // get elapsed time in ms
        int nTimeElapsed = GetMilliSpan( nTimeStart );
        // wait some ms to have the needed FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(FPS2MILLISEC-nTimeElapsed));
    }	
    // restore terminal
    system("stty cooked echo");
    textReset();
    showCursor();
	return 0;
}
