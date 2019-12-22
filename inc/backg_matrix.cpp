const int   MATRIX_BGLAYER=0,
            MATRIX_FGLAYER=1;



short unsigned int  MATRIX_BGCOL=C_GREEN,
                    MATRIX_FGCOL=C_LGREEN;
int
                    MATRIX_MAXSPD=5,
                    MATRIX_MAXLEN=SCREENY / 2,
                    MATRIX_MINLEN=SCREENY / 5;

struct s_matrixchrs {
    int y=0;
    s_simplechar chr = { 32, MATRIX_FGCOL, 8, false, false, false};
    int spd=0;
    int counter=0;
    int len=1;
};

s_matrixchrs MATRIXCHRS[MAXX];

void matrix_newchar (int x) {
    MATRIXCHRS[x].chr={ (char) (rand() % 93 + 33), MATRIX_FGCOL, 8, false, false, false};
    MATRIXCHRS[x].spd=rand() % MATRIX_MAXSPD;
    MATRIXCHRS[x].y=0- rand() % SCREENY / 2;
    MATRIXCHRS[x].counter=0;
    MATRIXCHRS[x].len=rand() % (int) (SCREENY / 2) + (int) (SCREENY / 5) ;
}


void init_bg_matrix() {
    int x;
    clearlayer(MATRIX_BGLAYER, WRITECHAR);
    clearlayer(MATRIX_FGLAYER, WRITECHAR);
    for( x = 0; x < SCREENX; x++)
    {
        matrix_newchar (x);

    }
}

void calc_bg_matrix() {
    int x;
    s_simplechar mychr;
    for( x = 0; x < SCREENX; x++)
    {
        MATRIXCHRS[x].counter++;
        if (MATRIXCHRS[x].counter > MATRIXCHRS[x].spd) {
            MATRIXCHRS[x].counter=0;
            mychr={ (char) (rand() % 93 + 33), MATRIX_BGCOL, 8, false, false, false};
            charxy(MATRIX_FGLAYER, x, MATRIXCHRS[x].y, mychr  );
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