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
#include "inc/clock_digital.h"
#include "inc/clock_analog.cpp"

#include "inc/backg_snow.cpp"

int main()
{	int ch;


    printf("\033[=2h");
    initscreen();
    
    printf("%d x %d", SCREENX, SCREENY);
    clear();
    s_simplechar proba = { 65, 2 ,1, false, false, false };
    s_simplechar proba2 = { (char) 219, 2 ,4, false, false, false };
    s_simplechar proba3 = { 67, 2 ,5, false, false, false };
    s_simplechar proba4 = { 68, 3 ,8, false, false, false };
    
    //clearlayer(3, proba);


    LAYER[1][0][0]=proba;
    LAYER[2][10][10]=proba2;
    LAYER[3][20][20]=proba3;
    LAYER[4][30][30]=proba4;

    //printf("%d",LAYER[4][20][20].chr);
    //getchar();

    init_bg_snow();


    
    do {
        int nTimeStart = GetMilliCount();


        checktime();

        calc_bg_snow();
        draw_bg_snow();

        stringxy(4, 12,12 , proba4, ACT_TIMESTR[0]);


        
        //stringxy(4, 12,15 , proba4, to_string(nTimeElapsed));
        
        mergelayers();

        printscreen();

        gotoxy(10,3);
        printf("%d:%d:%s", ACT_HOUR[0], ACT_MIN[0],inttostr2(ACT_SEC[0]).c_str());
        printf("%s", ACT_TIMESTR[0].c_str());




        int nTimeElapsed = GetMilliSpan( nTimeStart );
        std::this_thread::sleep_for(std::chrono::milliseconds(FPS2MILLISEC-nTimeElapsed));
    } while ( cin.peek() != EOF );	



	return 0;
}
