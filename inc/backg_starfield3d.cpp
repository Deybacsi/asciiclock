// starfield background

const int   MAXSTAR3D=500,    // number of stars
            MAXSTAR3DTYPE=17,  // number of star types
            MAXSTAR3DDIST=100,// max distance from center in world units
            MINSTAR3DDIST=10,
            STAR3DLAYER=1;    // where to draw STAR

// STAR characters -> * + .
s_simplechar STAR3DCHARS[MAXSTAR3DTYPE]={
    { 32, C_DGRAY, 8, false, false, true },
    { 46, C_DGRAY, 8, false, false, true },
    { 42, C_DGRAY,  8, false, false, true },
    { 42, C_GRAY,  8, false, false, true },
    { 43, C_GRAY,  8, false, false, true },
    { 43, C_WHITE,  8, false, false, true },
    { 120, C_WHITE,  8, false, false, true },
    { 88, C_WHITE,  8, false, false, true },
    { 88, C_WHITE,  8, false, false, true },

    { 46, C_DGRAY, 8, false, false, true },  // these will never appear, because we don't draw anything that has z>0
    { 42, C_DGRAY,  8, false, false, true },
    { 42, C_GRAY,  8, false, false, true },
    { 43, C_GRAY,  8, false, false, true },
    { 43, C_WHITE,  8, false, false, true },
    { 120, C_WHITE,  8, false, false, true },
    { 88, C_WHITE,  8, false, false, true },
    { 88, C_WHITE,  8, false, false, true }
};


int NEGPOS[2]={1,-1};

// char for clearing the screen
s_simplechar STAR3DCLEAR = { 32, 0, 8, false, false, false};


// array to store the star data
s_3dcoord   STARS3D[MAXSTAR3D],         // to store the original x,y,z coords
            STARS3DCALC[MAXSTAR3D];     // store the rotated coords for every frame
                                        // didn't use the same array, because rounding errors will mess up the original coords quickly

// current angle of the camera
// in real: stars angle relative to starting pos (->STARS3D array)
s_3dcoord CAM_ANGLE={ 0, 0, 0};

// offset for the camera center
// else 0,0 will be at top left corner
// could be handy for future camera movement
s_2dcoord STAR3DCENTER={ 0, 0};

//main initialization
void init_bg_star3d(){
    int i,x,y;
    // clear bg layers
    STAR3DCENTER={ (int) SCREENX/2, (int) SCREENY/2};
    //STAR3DCENTER={  0, 0};
    for (i=0; i<=1; i++) {
        clearlayer(i, STAR3DCLEAR);
    }
    // generate new stars
    for (i=0; i<MAXSTAR3D; i++) {
        // random cooord
        STARS3D[i].x=((rand() % (MAXSTAR3DDIST-MINSTAR3DDIST)) + MINSTAR3DDIST) * NEGPOS[rand() % 2];
        STARS3D[i].y=((rand() % (MAXSTAR3DDIST-MINSTAR3DDIST)) + MINSTAR3DDIST) * NEGPOS[rand() % 2];
        STARS3D[i].z=((rand() % (MAXSTAR3DDIST-MINSTAR3DDIST)) + MINSTAR3DDIST) * NEGPOS[rand() % 2];
        // and rotated on random axis
        STARS3D[i]=c3drotate(rand() % 3 +1, rand() % 360, STARS3D[i]);
    } 

    // setup the clock digits' transparency
    CLOCKCHAR.transpbcol=false;
    CLOCKCHAR.transpcol=false;
    CLOCKCHAR.transpchr=false;
    AVOIDCLOCKCOLOR=0;
}

// calculate the new position of STARS
void calc_bg_star3d() {
    int i;
    // rotate on each axis every star
    CAM_ANGLE.x+=1;
    CAM_ANGLE.y+=1;
    CAM_ANGLE.z+=1;
    for (i=0; i<MAXSTAR3D; i++) {
        STARS3DCALC[i]=c3drotate(1, CAM_ANGLE.x, STARS3D[i]);
        STARS3DCALC[i]=c3drotate(2, CAM_ANGLE.y, STARS3DCALC[i]);
        STARS3DCALC[i]=c3drotate(3, CAM_ANGLE.z, STARS3DCALC[i]);
    }    
}

//
void draw_bg_star3d() {
    int i,x,y;
    // clear the layer
    clearlayer(STAR3DLAYER, STAR3DCLEAR);
    // put the flakes to layer
    for (i=0; i<MAXSTAR3D; i++) {
        if (STARS3DCALC[i].z<0) { // if its far from camera then draw
            // array index schecks for STAR3DCHARS[]
            int dist=(int)( (STARS3DCALC[i].z+MAXSTAR3DDIST) / ((MAXSTAR3DDIST*2 / MAXSTAR3DTYPE)-1)  );
            if (dist<0) { dist=0;}
            if (dist>MAXSTAR3DTYPE-1) { dist=MAXSTAR3DTYPE-1;}
            // draw the star
            charxy(STAR3DLAYER, STAR3DCENTER.x+c3dto2d(STARS3DCALC[i]).x, STAR3DCENTER.y+c3dto2d(STARS3DCALC[i]).y,
            STAR3DCHARS[dist]);
        }
    }

}
