// manipulating the screen layers

int SCREENX, SCREENY;

// number of layers
const short MAXLAYERS = 4;

// initial values for SCREEN arrays
const int   MAXX = 200;
const int   MAXY = 200;

// layers with chars & attributes
s_simplechar LAYER[MAXLAYERS][MAXX][MAXY];
s_simplechar FINAL[MAXX][MAXY];


#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))



// initialize screen
void initscreen(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    SCREENY=w.ws_row;
    SCREENX=w.ws_col;

}


void mergelayers(){
    int l,x,y;
    for (l=0; l<=0; l++) {
        for (x=0; x<=SCREENX; x++) {
            for (y=0; y<=SCREENY; y++) {
                FINAL[x][y]=LAYER[l][x][y];
                
            }
        }
    }
}




void printscreen() {
    int x,y;
    for (y=0; y<SCREENY; y++) {
        for (x=0; x<SCREENX; x++) {
            putchar(65);
            //FINAL[x][y]
            
        }
    }
    
}