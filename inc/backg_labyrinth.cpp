
const int LABLAYER=0;

//s_simplechar LABCLEAR = { 32, C_DGRAY, C_GRAY, false, false, false};
s_simplechar LABWALL =  { 35, C_LBLUE, C_BLUE, false, false, false};
s_simplechar LABEMPTY = { 32, C_DGRAY, C_BLACK, false, false, false};
s_simplechar LABPLAYER = { 111, C_LYELLOW, C_BLACK, false, false, false};
s_simplechar LABPLAYERWALKED = { 46, C_WHITE, C_BLUE, false, false, false};

struct s_direction {
    int x=0;
    int y=0;
};

s_direction DIRECTIONS[4]={
    {0,-1},
    {1,0},
    {0,1},
    {-1,0}
};

int DIRSELECTOR[4]= { 0, 1, 2, 3};

int LAB_PLAYERDIR=0;

s_2dcoord LAB_PLAYER = { 1,1 };


// recursive backtrack labyrinth generation
void labyrinth_grid(int x, int y) {
    int i;
    int freedirs=0;
    int direction=0;

    charxy(LABLAYER,x,y,LABEMPTY);

    // obtain a time-based seed:
    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    //shuffle (DIRSELECTOR.begin(), DIRSELECTOR.end(), std::default_random_engine(seed));
    int tmp,other;

    // shuffle the possible directions
    for (i=0; i<4; i++) {
        other=rand() % 4;
        tmp=DIRSELECTOR[i]; DIRSELECTOR[i]=DIRSELECTOR[other]; DIRSELECTOR[other]=tmp;
    }

    // count the directions what are free to go
    for (direction=0; direction<4; direction++) {
        if (x+DIRECTIONS[DIRSELECTOR[direction]].x*2>0 && x+DIRECTIONS[DIRSELECTOR[direction]].x*2<SCREENX && y+DIRECTIONS[DIRSELECTOR[direction]].y*2>0 && y+DIRECTIONS[DIRSELECTOR[direction]].y*2<SCREENY) {
            if (LAYER[LABLAYER][x+DIRECTIONS[DIRSELECTOR[direction]].x*2][y+DIRECTIONS[DIRSELECTOR[direction]].y*2].chr==LABWALL.chr) {
                freedirs++;
            }
        }
    }

    // if there are any unexplored directions
    if (freedirs>0) {
        // go through all directions (randomized before)
        for (direction=0; direction<4; direction++) {
            // if desired direction is OK to go
            if (LAYER[LABLAYER][x+DIRECTIONS[DIRSELECTOR[direction]].x*2][y+DIRECTIONS[DIRSELECTOR[direction]].y*2].chr==LABWALL.chr) {
                // remove the wall in that direction
                charxy(LABLAYER,x+DIRECTIONS[DIRSELECTOR[direction]].x,y+DIRECTIONS[DIRSELECTOR[direction]].y, LABEMPTY);
                // draw the clock
                //draw_clock_digital((SCREENX-(DIGITDESIGNS[ACTDIGITDESIGN].x*5)) /2 ,(SCREENY-DIGITDESIGNS[ACTDIGITDESIGN].y) /2);

                // draw the screen
                mergelayers();
                printscreen();
                // call again with the next step's coords
                labyrinth_grid(x+DIRECTIONS[DIRSELECTOR[direction]].x*2,y+DIRECTIONS[DIRSELECTOR[direction]].y*2);
            }
        }
    } else {    // if there's no way, then return back to the caller
        return;
    }
}

// initialize labyrinth
void init_bg_labyrinth() {
    int x,y;
    clearalllayer(CLEARCHAR);
    clearlayer(LABLAYER, LABWALL);
    LAB_PLAYER={1+rand() % (SCREENX-3), 1+rand() % (SCREENY-3)};
    //labyrinth_grid (1,1);
    labyrinth_grid (1+rand() % (SCREENX-3), 1+rand() % (SCREENY-3));
    for (x=0; x<SCREENX; x++) {
        charxy(LABLAYER,x,0,LABWALL);
        charxy(LABLAYER,x,SCREENY-1,LABWALL);
    }
    for (x=0; x<SCREENY; x++) {
        charxy(LABLAYER,0,x,LABWALL);
        charxy(LABLAYER,SCREENX-1,x,LABWALL);
    }


    CLOCKCHAR.transpbcol=false;
    CLOCKCHAR.transpcol=false;
    CLOCKCHAR.transpchr=false;
    // clock color can't be black
    AVOIDCLOCKCOLOR=LABWALL.bcol;
   
}


// calc next frame
void calc_bg_labyrinth() {
    int freedirs=0, direction=0;
    charxy(LABLAYER,LAB_PLAYER.x,LAB_PLAYER.y,LABPLAYERWALKED);

    // check directions
    for (direction=0; direction<4; direction++) {
        // if dir is inside of screen
        if (LAB_PLAYER.x+DIRECTIONS[direction].x>0 && LAB_PLAYER.x+DIRECTIONS[direction].x<SCREENX && LAB_PLAYER.y+DIRECTIONS[direction].y>0 && LAB_PLAYER.y+DIRECTIONS[direction].y<SCREENY) {
            // and is not explored yet
            if (LAYER[LABLAYER][LAB_PLAYER.x+DIRECTIONS[direction].x][LAB_PLAYER.y+DIRECTIONS[direction].y].chr== LABEMPTY.chr) {
                freedirs++;
            }
        }
    }
    // if there are unexplored directions
    if (freedirs>0) {
        do {
            LAB_PLAYERDIR=(LAB_PLAYERDIR+1) % 4;    // choose a direction

        } while (LAYER[LABLAYER][LAB_PLAYER.x+DIRECTIONS[LAB_PLAYERDIR].x][LAB_PLAYER.y+DIRECTIONS[LAB_PLAYERDIR].y].chr == LABPLAYERWALKED.chr); // what is not explored

    } else {    // if we are surrounded by already walked areas
        // and in this direction there's a wall
        if (LAYER[LABLAYER][LAB_PLAYER.x+DIRECTIONS[LAB_PLAYERDIR].x][LAB_PLAYER.y+DIRECTIONS[LAB_PLAYERDIR].y].chr == LABWALL.chr) {
            LAB_PLAYERDIR= rand() % 4;      // choose another dir
        }
    }

    // if in that direction there's no wall, then step there
    if (LAYER[LABLAYER][LAB_PLAYER.x+DIRECTIONS[LAB_PLAYERDIR].x][LAB_PLAYER.y+DIRECTIONS[LAB_PLAYERDIR].y].chr != LABWALL.chr ) {
        LAB_PLAYER.x=LAB_PLAYER.x+DIRECTIONS[LAB_PLAYERDIR].x;
        LAB_PLAYER.y=LAB_PLAYER.y+DIRECTIONS[LAB_PLAYERDIR].y;
    } 

    // draw our little explorer char
    charxy(LABLAYER,LAB_PLAYER.x,LAB_PLAYER.y,LABPLAYER);
     
}

// not used
void draw_bg_labyrinth() {

}