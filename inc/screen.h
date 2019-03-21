int SCREENX, SCREENY;

// frames / sec
const int   FPS=25,
            FPS2MILLISEC=1000/FPS;

// number of layers
const short MAXLAYERS = 5;

// initial values for SCREEN arrays
const int   MAXX = 200;
const int   MAXY = 200;


// common definitions

// the simple char type
struct s_simplechar {
    char chr = 32;
    unsigned short int col = 0;
    unsigned short int bcol  = 8;
    bool transpchr = true;
    bool transpcol = true;
    bool transpbcol= true;
};

// color code constants
const int   C_BLACK   = 0,
            C_RED     = 1,
            C_GREEN   = 2,
            C_YELLOW  = 3,
            C_BLUE    = 4,
            C_MAGENTA = 5,
            C_CYAN    = 6,
            C_GRAY    = 7,

            C_DGRAY   = 8,
            C_LRED    = 9,
            C_LGREEN  = 10,
            C_LYELLOW = 11,
            C_LBLUE   = 12,
            C_LMAGENTA= 13,
            C_LCYAN   = 14,
            C_WHITE  = 15,

            C_BGTRANS = 8;  // default transparent bg color -> 49m

// ANSI ascape codes to print colors
const string COLORS[16] = { "0;30", "0;31", "0;32", "0;33", "0;34", "0;35", "0;36", "0;37", "1;30", "1;31", "1;32", "1;33", "1;34", "1;35", "1;36", "1;37" };
const string BCOLORS[9] = { "40", "41", "42", "43", "44", "45", "46", "47", "49" };


// layers with chars & attributes
s_simplechar LAYER[MAXLAYERS+1][MAXX][MAXY];
s_simplechar FINAL[MAXX][MAXY];

// simple writing char for string outputs (for debug, etc)
s_simplechar WRITECHAR = { 32, 2, 8, false, false, false};

// temporary counters for effects, if needed
int     INT_COUNTER[3]  = { 0, 0, 0 };
float   FLOAT_COUNTER[3]= { 0, 0, 0 };

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))


// initialize screen
void initscreen(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    SCREENY= (w.ws_row > MAXY ) ? MAXY-1 : w.ws_row;
    SCREENX= (w.ws_col > MAXX ) ? MAXX-1 : w.ws_col;

}

// puts a char to x,y at given layer
void charxy(int layer, int x, int y, s_simplechar &simplechar) {
    if ( x >= 0 && x <= SCREENX && y >= 0 && y<=SCREENY ) {
        LAYER[layer][x][y]=simplechar;
    }
}

// puts a string to x,y at given layer
// simplechar = format 
void stringxy(int layer, int x, int y, s_simplechar &simplechar, string s ) {
    int i;
    for (i=0; i<s.length(); i++) {
        simplechar.chr=s[i];
        charxy(layer, x+i, y, simplechar);
    }

}

// fill a layer with char
void clearlayer(int layer, s_simplechar &simplechar) {
    int x,y;
    for (y=0; y<=SCREENY; y++) {
        for (x=0; x<=SCREENX; x++) {
            LAYER[layer][x][y]=simplechar;
        }
    }
}

// merge all the layers from bottom to top - 0->MAXLAYERS
void mergelayers(){
    int l,x,y;
    for (l=0; l<=MAXLAYERS; l++) {
        for (y=0; y<=SCREENY; y++) {
            for (x=0; x<=SCREENX; x++) {
                FINAL[x][y].chr = LAYER[l][x][y].transpchr  ? FINAL[x][y].chr  : LAYER[l][x][y].chr;
                FINAL[x][y].col = LAYER[l][x][y].transpcol  ? FINAL[x][y].col  : LAYER[l][x][y].col;
                FINAL[x][y].bcol= LAYER[l][x][y].transpbcol ? FINAL[x][y].bcol : LAYER[l][x][y].bcol;
            }
        }
    }
}

// print out the final image to screen
void printscreen() {
    int x,y;
    gotoxy(0,0);
    for (y=0; y<SCREENY; y++) {
        for (x=0; x<SCREENX; x++) {
            printf("\033[%s;%sm", COLORS[FINAL[x][y].col].c_str(), BCOLORS[FINAL[x][y].bcol].c_str() );
            putchar(FINAL[x][y].chr);
        
        }
        if ( y < SCREENY-1) putchar(10) ;
    }
    
}