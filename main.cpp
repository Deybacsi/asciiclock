#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "inc/common.h"
#include "inc/screen.h"


int main()
{	int ch;



    initscreen();
    
    printf("%d x %d", SCREENX, SCREENY);
    clear();
    //LAYER[4][20][20].chr=65;
    mergelayers();

    printscreen();
    
    getchar();			



	return 0;
}
