const int   FIRELAYER     =1,             // where to draw effect - layer no
            MAXFIRECHARS  =23,            // number of chars to draw
            MAXFIRECOLORS =2;             // number of colorsets
            
int MAXFIRERANDOM = 0; 


int FIREBUFFER[2][MAXY][MAXX];

// char for clearing the screen
s_simplechar FIRECLEAR = { 32, 0, 8, false, false, false};



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

void copy_back_buffer() {
    int i,j;
    for (i=1; i<=SCREENY; i++) {
        for (j=1; j<=SCREENX; j++) {
            FIREBUFFER[0][i][j]=FIREBUFFER[1][i][j];
        }
    }
}

void init_buffer() {
    int i,j;
    for (i=0; i<SCREENY; i++) {
        for (j=0; j<SCREENX; j++) {
            FIREBUFFER[0][i][j]=0;
            FIREBUFFER[1][i][j]=0;
        }
    }
}

void draw_fire_random() {
    int x,y;
    x=float(rand() % SCREENX);
    y=float(SCREENY-rand() % SCREENY/4);
    FIREBUFFER[0][y][x]=MAXFIRECHARS;
}


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
}

void calc_bg_fire() {
    int x,y;
    int average=0;
    copy_back_buffer();
    draw_random_bottom();
    draw_fire_random();
    for (y=1; y<=SCREENY; y++) {
        for (x=1; x<=SCREENX-1; x++) {
            average=floor( (FIREBUFFER[0][y-1][x]+FIREBUFFER[0][y][x-1]+FIREBUFFER[0][y][x]+FIREBUFFER[0][y][x+1]+FIREBUFFER[0][y+1][x]) / 5 );
            if (average>MAXFIRECHARS) { average=MAXFIRECHARS; }
            FIREBUFFER[1][y-1][x]=average;
            charxy(FIRELAYER,x,y,FIRECHARS[0][FIREBUFFER[1][y][x]]);
        }
    } 
    


    for (x=0; x<=SCREENX; x++ ) {
        charxy(FIRELAYER,x,SCREENY-1,FIRECHARS[0][FIREBUFFER[1][SCREENY-1][x]]);
    }

}


void draw_bg_fire() {
}

