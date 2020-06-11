const int   FIRELAYER     =1,             // where to draw effect - layer no
            MAXFIRECHARS  =23,            // number of chars to draw
            MAXFIRECOLORS =2;             // number of colorsets
            
int MAXFIRERANDOM = 0; 

// framebuffers for calculations
int FIREBUFFER[2][MAXY][MAXX];

// char for clearing the screen
s_simplechar FIRECLEAR = { 32, 0, 8, false, false, false};


// character definitions for fire effect
s_simplechar FIRECHARS[MAXFIRECOLORS][MAXFIRECHARS]={
    {
        { 32,  1,  8, false, false, false },    // dummy char 0 is for nothing
        { 32,  0,  8, false, false, false },
        { 32,  0,  8, false, false, false },
        { 32,  0,  8, false, false, false },
        { 32,  0,  8, false, false, false },

        { 46,  C_DGRAY,  8, false, false, true},
        { 43,  C_RED,  8, false, false, true},
        { 120,  C_YELLOW,  8, false, false, true},
        { 88,  C_YELLOW,  8, false, false, true },
        { 120,  C_LYELLOW,  8, false, false, true },
        { 88, C_LYELLOW, 8, false, false, true },
        { 120, C_LGREEN, 8, false, false, true },
        { 88,  C_LGREEN, 8, false, false, true },
        { 120, C_WHITE, 8, false, false, true },
        { 88,  C_WHITE, 8, false, false, true },
        { 120, C_WHITE, 8, false, false, true },
        { 88, C_WHITE, 8, false, false, true },
        { 120, C_WHITE,  8, false, false, true },
        { 88,  C_WHITE,  8, false, false, true },
        { 88,  C_WHITE,  8, false, false, true },
        { 88,  C_WHITE,  8, false, false, true },
        { 88,  C_WHITE,  8, false, false, true },
        { 88,  C_WHITE,  8, false, false, true }



    },    
    {
        { 32,  1,  8, false, false, false },    // dummy char 0 is for nothing
        { 46,  C_BLUE,  8, false, false, true },
        { 43,  C_BLUE,  8, false, false, true },
        { 120, C_BLUE, 8, false, false, true },

        { 43, C_LBLUE, 8, false, false, true },
        { 88,  C_LBLUE, 8, false, false, true },
        { 43, C_LBLUE, 8, false, false, true },

        { 120, C_BLUE, 8, false, false, true },
        { 43,  C_BLUE,  8, false, false, true },
        { 46,  C_BLUE,  8, false, false, true }
    }          
};

// copy buffer1 -> buffer0
void copy_back_buffer() {
    int i,j;
    for (i=1; i<=SCREENY; i++) {
        for (j=1; j<=SCREENX; j++) {
            FIREBUFFER[0][i][j]=FIREBUFFER[1][i][j];
        }
    }
}

// clear our 2 initial framebuffers
void init_buffer() {
    int i,j;
    for (i=0; i<SCREENY; i++) {
        for (j=0; j<SCREENX; j++) {
            FIREBUFFER[0][i][j]=0;
            FIREBUFFER[1][i][j]=0;
        }
    }
}

// draws random flame points to buffer, feels more realistic
void draw_fire_random() {
    int x,y;
    x=float(rand() % SCREENX);
    y=float(SCREENY-rand() % SCREENY/4);
    FIREBUFFER[0][y][x]=MAXFIRECHARS;
}

// generates random chars at the bottom of buffer0
// this feeds the fire
void draw_random_bottom() {
    int i;
    for (i=0; i<=SCREENX; i++) {
        FIREBUFFER[0][SCREENY][i]=rand() % MAXFIRECHARS;
    }

}

//main initialization
void init_bg_fire(){
    init_buffer();
    MAXFIRERANDOM = float(SCREENX * SCREENY / 20);
    clearlayer(FIRELAYER, FIRECLEAR);
    // clock color can't be black
    AVOIDCLOCKCOLOR=0;
}

// calc next frame & draw to given layer
void calc_bg_fire() {
    int x,y;
    int average=0;
    // copy the last frame from buf1 to buf0
    copy_back_buffer();
    draw_random_bottom();
    draw_fire_random();

    // average every pixel in buf0 with its neighbors, and put it to buf1 one row above
    for (y=1; y<=SCREENY; y++) {
        for (x=1; x<=SCREENX-1; x++) {
            average=floor( (FIREBUFFER[0][y-1][x]+FIREBUFFER[0][y][x-1]+FIREBUFFER[0][y][x]+FIREBUFFER[0][y][x+1]+FIREBUFFER[0][y+1][x]) / 5 );
            if (average>MAXFIRECHARS) { average=MAXFIRECHARS; }
            FIREBUFFER[1][y-1][x]=average;
            // draw to screen instantly
            charxy(FIRELAYER,x,y,FIRECHARS[0][FIREBUFFER[1][y][x]]);
        }
    } 
    // draw out the bottom line
    for (x=0; x<=SCREENX; x++ ) {
        charxy(FIRELAYER,x,SCREENY-1,FIRECHARS[0][FIREBUFFER[1][SCREENY-1][x]]);
    }

}

// not needed
void draw_bg_fire() {

}

