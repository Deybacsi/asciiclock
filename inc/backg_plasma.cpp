// simple plasma effect
//
// main method from:
// https://github.com/leonardo-ono/JavaOldPlasmaEffectTest/blob/master/src/oldplasmaeffecttest/OldPlasmaEffectTestPanel.java


int         
            plasma_time=0,
            PLASMACOLOR=0;

const int   PLASMALAYER     =1,             // where to draw effect - layer no
            MAXPLASMACHARS  =10,            // number of chars to draw
            MAXPLASMACOLORS =2;             // number of colorsets

// precalculated sin & cos datas to speed up things
// 0..360 needed, else there will be a horizontal & vertcical "crack"
float sn[361], cs[361];

// _.,oxOX

s_simplechar PLASMACHARS[MAXPLASMACOLORS][MAXPLASMACHARS]={
    {
        { 32,  1,  8, false, false, false },    // dummy char 0 is for nothing
        { 46,  C_YELLOW,  8, false, false, true },
        { 43,  C_YELLOW,  8, false, false, true },
        { 120, C_YELLOW, 8, false, false, true },

        { 120, C_LGREEN, 8, false, false, true },
        { 88,  C_LGREEN, 8, false, false, true },
        { 120, C_LGREEN, 8, false, false, true },

        { 120, C_YELLOW, 8, false, false, true },
        { 43,  C_YELLOW,  8, false, false, true },
        { 46,  C_YELLOW,  8, false, false, true }
    },    
    {
        { 32,  1,  8, false, false, false },    // dummy char 0 is for nothing
        { 46,  C_BLUE,  8, false, false, true },
        { 43,  C_BLUE,  8, false, false, true },
        { 120, C_BLUE, 8, false, false, true },

        { 120, C_LBLUE, 8, false, false, true },
        { 88,  C_LBLUE, 8, false, false, true },
        { 120, C_LBLUE, 8, false, false, true },

        { 120, C_BLUE, 8, false, false, true },
        { 43,  C_BLUE,  8, false, false, true },
        { 46,  C_BLUE,  8, false, false, true }
    }          
};

/*
s_simplechar PLASMACHARS[MAXPLASMACHARS]={
    { 32,  1,  8, false, false, false },    // dummy char 0 is for nothing
    { 95,  C_BLUE,  8, false, false, true },
    { 46,  C_YELLOW,  8, false, false, true },
    { 120, C_GREEN, 8, false, false, true },
    { 88,  C_LGREEN, 8, false, false, true },
    { 120, C_GREEN, 8, false, false, true },  
    { 46,  C_YELLOW,  8, false, false, true },
    { 95,  C_BLUE,  8, false, false, true },          
};
*/

// initialize effect
void init_bg_plasma(){
    int i,c;
    // precalc the sin&cos datas
    for (i=0; i<=360; i++) {
        sn[i]=sin(i * PI/180);
        cs[i]=cos(i * PI/180);
    }
    plasma_time=0;
    CLOCKCHAR.transpbcol=false;
    CLOCKCHAR.transpcol=false;
    CLOCKCHAR.transpchr=false;
    PLASMACOLOR=rand() % MAXPLASMACOLORS;
}

// calc next frame
void calc_bg_plasma() {
    int x,y,c;
    clearlayer(0,PLASMACHARS[PLASMACOLOR][0]);
    clearlayer(PLASMALAYER,PLASMACHARS[PLASMACOLOR][0]);
    
    plasma_time++;

    for (y=0; y<=SCREENY; y++) {
        for (x=0; x<=SCREENX; x++) {

                double t = plasma_time* 0.2;
                double k = (t + y) * 0.02;
                double v1 = 10 + 10 * sin(0.075 * (x * sin(k) + (y*2) * cos(k * 2)));
                double v2 = 10 + 10 * sin(0.055 * (x * cos(k * 3) + (y*2) * sin(k * 4)));
                double v3 = 10 + 10 * cos((t + (y*2)) * 0.04);
                double v4 = 10 + 10 * sin((t + x) * 0.04);
                double v5 = 10 + 10 * sin(k + sqrt(v3 + v4));
                double v6 = (v1 + v2 + v5) / 3;
                c = (int) v6 % MAXPLASMACHARS;


            charxy(PLASMALAYER, x, y, PLASMACHARS[PLASMACOLOR][c]);
        }
    }
}

void draw_bg_plasma() {
}

