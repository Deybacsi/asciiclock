// starfield background


const int   MAXSTAR=200,    // number of stars
            MAXSTARSPD=2,       // number of star speed types - 0 1 2
            STARLAYER=1;    // where to draw STAR





// STAR characters -> . + *
s_simplechar STARCHARS[3]={
    { 42, C_WHITE,  8, false, false, true },
    { 43, C_GRAY,  8, false, false, true },
    { 46, C_DGRAY, 8, false, false, true }
};

// char for clearing the screen
s_simplechar STARCLEAR = { 32, 0, 8, false, false, false};

// max ground STAR "density"
const int   MAXSTARBG=5;    

// generic STAR structure
struct s_star{
    unsigned int x=0;
    unsigned int y=0;
    unsigned int spd=0;
    unsigned int spdcounter=0;
};

// array to store the star data
s_star STARS[MAXSTAR];


// create a new star in random position at top of the screen with random speed
void calc_new_star(int i) {
    STARS[i].x=0;
    STARS[i].y=rand() % SCREENY;
    STARS[i].spd=rand() % (MAXSTARSPD+1);
}

//main initialization
void init_bg_star(){
    int i,x,y;
    // clear bg layers
    for (i=0; i<=1; i++) {
        clearlayer(i, STARCLEAR);
    }
    // generate new stars
    for (i=0; i<MAXSTAR; i++) {
        calc_new_star(i);
        STARS[i].x=rand() % SCREENX;   // give them initial x coords instead of left of the screen
    } 
    CLOCKCHAR.transpbcol=false;
    CLOCKCHAR.transpcol=true;
    CLOCKCHAR.transpchr=true;
    // clock color can't be black
    AVOIDCLOCKCOLOR=0;
}


// calculate the new position of STARS
void calc_bg_star() {
    int i;
    for (i=0; i<MAXSTAR; i++) {
        // increase the STARflake's counter (simulates the speed)
        STARS[i].spdcounter++;
        
        // if counter hits the spd -> move STARflake
        if (STARS[i].spdcounter > STARS[i].spd ) { 
            STARS[i].spdcounter=0;
            STARS[i].x++;      // go down :)
            
            // if it reaches the bottom of the screen
            if (STARS[i].x > SCREENX ) {
                // generate a star at left
                calc_new_star(i);
            } 

        }
        
    }    
}

//
void draw_bg_star() {
    int i,x,y;
    // clear the layer
    clearlayer(STARLAYER, STARCLEAR);
    // put the flakes to layer
    for (i=0; i<MAXSTAR; i++) {
        charxy(1, STARS[i].x, STARS[i].y, STARCHARS[STARS[i].spd] );
    }

}








