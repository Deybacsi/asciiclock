/*
 * If you have usual thin and tall rectangle characters, leave it on 2
 * 
 * If you have characters like a square with equal height and width, set it to 1
 * 
 * Or you can fine-tune it to any float value, if needed
 */
const float SCREEN_CHAR_ASPECT_RATIO=2;



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
// transparent means, the chars on layers below this will be visible
// othervise it will overwrite the lower layers' data
struct s_simplechar {
    char chr = 32;                  // character
    unsigned short int col = 0;     // color
    unsigned short int bcol  = 8;   // background color
    bool transpchr = true;          // character is transparent?
    bool transpcol = true;          // color is transparent?
    bool transpbcol= true;          // backgorund color is transparent?
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

// ANSI escape codes to print colors
const string COLORS[16] = { "0;30", "0;31", "0;32", "0;33", "0;34", "0;35", "0;36", "0;37", "1;30", "1;31", "1;32", "1;33", "1;34", "1;35", "1;36", "1;37" };
const string BCOLORS[9] = { "40", "41", "42", "43", "44", "45", "46", "47", "49" };

// the screen size will be there
int SCREENX, SCREENY;

// layers with chars & attributes
s_simplechar LAYER[MAXLAYERS+1][MAXX][MAXY];
s_simplechar FINAL[MAXX][MAXY];

// simple writing char for string outputs (for debug, etc)
s_simplechar WRITECHAR = { 32, 7, 8, false, false, false};
// simple transparent clear char
s_simplechar CLEARCHAR = { 32, 7, 8, true, true, true};


#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))
#define hideCursor() printf("\033[?25l");
#define showCursor() printf("\033[?25h");
#define textReset() printf("\033[0m");


// initialize screen
void initscreen(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    SCREENY= (w.ws_row > MAXY ) ? MAXY-1 : w.ws_row;
    SCREENX= (w.ws_col > MAXX ) ? MAXX-1 : w.ws_col;

}

// puts a char to x,y at given layer with simpechar formatting
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

// draws a line
void linexy (int layer, int x1, int y1, int x2, int y2, s_simplechar &simplechar ) {
    int x,y=0;
    float fx,fy=0;      // line angle
    int t=0;
    int kulx=x2-x1;     
    int kuly=y2-y1;

    // line is wide or tall?
    if (abs(kulx) >= abs(kuly)){
        fy= (float) (y2-y1) / (x2-x1) ;
        if (x1>x2) { t=x1; x1=x2; x2=t; t=y1; y1=y2; y2=t;}
        for (x=x1; x<=x2; x++) { charxy(layer, x, round(y1 + fy * (x-x1)), simplechar ); }

    } else {
        fx= (float) (x2-x1) / (y2-y1) ;
        if (y1>y2) { t=x1; x1=x2; x2=t; t=y1; y1=y2; y2=t; }

            for (y=y1; y<=y2; y++) { charxy(layer, round(x1 + fx * (y-y1)), y, simplechar ); }        

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

// fill all layers with char
void clearalllayer(s_simplechar simplechar) {
    int l;
    clearlayer(0, WRITECHAR);           // the 0. layer needs to be filled with non transparent chars, otherwise it will not rendered to the screen
    for (l=1; l< MAXLAYERS; l++) {      // others can be filled with anything
        clearlayer(l, simplechar);
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
        if ( y < SCREENY-1) { putchar(10); putchar(13); }
    }
    
}