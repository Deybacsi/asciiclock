const int   MATRIX_BGLAYER=0,
            MATRIX_FGLAYER=1;



short unsigned int  MATRIX_BGCOL=C_GREEN,
                    MATRIX_FGCOL=C_LGREEN;
int
                    MATRIX_MAXSPD=5,
                    MATRIX_MAXLEN=SCREENY / 2,
                    MATRIX_MINLEN=SCREENY / 5;

// for the background string lines
struct s_matrixchrs {
    int y=0;        // y coord of line
    s_simplechar chr = { 32, MATRIX_FGCOL, 8, false, false, false};
    int spd=0;      // speed of line
    int counter=0;  // counter for speed calc
    int len=1;      // length of line
};

// every column on screen has one string line
s_matrixchrs MATRIXCHRS[MAXX];

// generate a new line
void matrix_newchar (int x) {
    MATRIXCHRS[x].chr={ (char) (rand() % 93 + 33), MATRIX_FGCOL, 8, false, false, false};
    MATRIXCHRS[x].spd=rand() % MATRIX_MAXSPD;
    MATRIXCHRS[x].y=0- rand() % SCREENY / 2;    // always start with a negative number -> it will start above the screen, and flows down from there
    MATRIXCHRS[x].counter=0;
    MATRIXCHRS[x].len=rand() % (int) (SCREENY / 2) + (int) (SCREENY / 5) ;
}

// bg effect init
void init_bg_matrix() {
    int x;
    // clear background layers
    clearlayer(MATRIX_BGLAYER, WRITECHAR);
    clearlayer(MATRIX_FGLAYER, WRITECHAR);
    for( x = 0; x < SCREENX; x++)
    {
        matrix_newchar (x);
    }
        // clock color can't be black
    AVOIDCLOCKCOLOR=0;
}

// calculating next frame
void calc_bg_matrix() {
    int x;
    s_simplechar mychr;

    // go through horizontally
    for( x = 0; x < SCREENX; x++)
    {
        // inc the sp counter, and check if > spd
        MATRIXCHRS[x].counter++;
        if (MATRIXCHRS[x].counter > MATRIXCHRS[x].spd) {
            MATRIXCHRS[x].counter=0;
            // choose a new char and draw it
            mychr={ (char) (rand() % 93 + 33), MATRIX_BGCOL, 8, false, false, false};
            charxy(MATRIX_FGLAYER, x, MATRIXCHRS[x].y, mychr  );
            // delete the chars at the end of the lines
            s_simplechar CLRCHAR={ 32, 7, 8, false, false, false};
            charxy(MATRIX_FGLAYER, x, MATRIXCHRS[x].y-MATRIXCHRS[x].len, CLRCHAR );

            MATRIXCHRS[x].chr={ (char) (rand() % 93 + 33), MATRIX_FGCOL, 8, false, false, false};
            
            MATRIXCHRS[x].y++;
            if (MATRIXCHRS[x].y-MATRIXCHRS[x].len > SCREENY ) {
                matrix_newchar (x);
            }
        }
    }

    

}

void draw_bg_matrix() {
    int x;
    //clearlayer(MATRIX_FGLAYER, WRITECHAR);
    for( x = 0; x < SCREENX; x++)
    {
        charxy(MATRIX_FGLAYER, x, MATRIXCHRS[x].y, MATRIXCHRS[x].chr);
    }
}