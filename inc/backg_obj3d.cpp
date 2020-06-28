// starfield background
const int   MAXOBJ3DTYPE=11,  // number of char types
            MAXOBJ3D=500,    // number of points
            MAXOBJ3DOBJECTS=6;  // number of our 3D objects to select from
            
int         MAXOBJ3DDIST=2,// max distance from center in world units
            MINOBJ3DDIST=1,
            OBJ3DLAYER=1;    // where to draw STAR

int OBJ3DOBJECT=0;

// STAR characters -> * + .
s_simplechar OBJ3DCHARS[MAXOBJ3DTYPE]={
    { 46, C_DGRAY, 8, false, false, true },
    { 46, C_DGRAY, 8, false, false, true },
    { 42, C_DGRAY,  8, false, false, true },
    { 42, C_DGRAY,  8, false, false, true },
    { 42, C_GRAY,  8, false, false, true },
    { 42, C_GRAY,  8, false, false, true },
    { 43, C_GRAY,  8, false, false, true },
    { 43, C_GRAY,  8, false, false, true },
    { 43, C_WHITE,  8, false, false, true },
    { 120, C_WHITE,  8, false, false, true },
    { 88, C_WHITE,  8, false, false, true },


};


int OBJ3DNEGPOS[2]={1,-1};

// char for clearing the screen
s_simplechar OBJ3DCLEAR = { 32, 0, 8, false, false, false};


// array to store the star data
s_3dcoord   OBJS3D[MAXOBJ3D],         // to store the original x,y,z coords
            OBJS3DCALC[MAXOBJ3D];     // store the rotated coords for every frame
                                        // didn't use the same array, because rounding errors will mess up the original coords quickly

// current angle of the camera
// in real: stars angle relative to starting pos (->OBJS3D array)
s_3dcoord OBJ3DCAM_ANGLE={ 0, 0, 0};

// offset for the camera center
// else 0,0 will be at top left corner
// could be handy for future camera movement
s_2dcoord OBJ3DCENTER={ 0, 0};

//main initialization
void init_bg_obj3d(){
    int i,j,x,y, circlepointsno, circleslicesno;
    // clear bg layers
    OBJ3DCENTER={ (int) SCREENX/2, (int) SCREENY/2};
    //OBJ3DCENTER={  0, 0};
    for (i=0; i<=1; i++) {
        clearlayer(i, OBJ3DCLEAR);
    }

    OBJ3DOBJECT=rand()%MAXOBJ3DOBJECTS;


    //OBJ3DOBJECT=5;
    switch (OBJ3DOBJECT) {
        case 0:     // sphere-like object
            MAXOBJ3DDIST=round(SCREENY/3*2);
            MINOBJ3DDIST=MAXOBJ3DDIST-1;
            for (i=0; i<MAXOBJ3D; i++) {

                // random cooord
                OBJS3D[i].x=((rand() % (MAXOBJ3DDIST-MINOBJ3DDIST)) + MINOBJ3DDIST) * OBJ3DNEGPOS[rand() % 2];
                OBJS3D[i].y=((rand() % (MAXOBJ3DDIST-MINOBJ3DDIST)) + MINOBJ3DDIST) * OBJ3DNEGPOS[rand() % 2];
                OBJS3D[i].z=((rand() % (MAXOBJ3DDIST-MINOBJ3DDIST)) + MINOBJ3DDIST) * OBJ3DNEGPOS[rand() % 2];
                // and rotated on random axis
                OBJS3D[i]=c3drotate(rand() % 3 +1, rand() % 360, OBJS3D[i]);
            } 
            break;
        case 1:     // plane
            MAXOBJ3DDIST=round(SCREENY*1.3);
            MINOBJ3DDIST=MAXOBJ3DDIST-1;
            for (i=0; i<MAXOBJ3D; i++) {

                OBJS3D[i].x=0;
                OBJS3D[i].y=(rand() % MAXOBJ3DDIST*2)-MAXOBJ3DDIST;
                OBJS3D[i].z=(rand() % MAXOBJ3DDIST*2)-MAXOBJ3DDIST;

            }
            break;
        case 2:     // ring
            MAXOBJ3DDIST=round(SCREENY/4*3);
            MINOBJ3DDIST=round(SCREENY/3);
            for (i=0; i<MAXOBJ3D; i++) {

                OBJS3D[i].x=((rand()%MINOBJ3DDIST) -MINOBJ3DDIST/2)   *OBJ3DNEGPOS[rand() % 2];

                OBJS3D[i].y=((rand() % (MAXOBJ3DDIST-MINOBJ3DDIST)) + MINOBJ3DDIST) * OBJ3DNEGPOS[rand() % 2];
                OBJS3D[i].z=((rand() % (MAXOBJ3DDIST-MINOBJ3DDIST)) + MINOBJ3DDIST) * OBJ3DNEGPOS[rand() % 2];
                OBJS3D[i]=c3drotate(1, rand() % 360, OBJS3D[i]);

            }
            break;

        case 3:     // sphere
            MAXOBJ3DDIST=round(SCREENY);
            MINOBJ3DDIST=MAXOBJ3DDIST-1;
            circleslicesno=6;
            circlepointsno=round(MAXOBJ3D/circleslicesno);
            for (i=0; i<circlepointsno; i++) {
                OBJS3D[i].x=MAXOBJ3DDIST*sin(i);
                OBJS3D[i].y=MAXOBJ3DDIST*cos(i);
                OBJS3D[i].z=0;
                for (j=1; j<circleslicesno; j++) {
                    OBJS3D[j*circlepointsno+i]=c3drotate(1, 180/circleslicesno*j, OBJS3D[i]);
                }
                /*
                OBJS3D[i]=c3drotate(1, rand() % 360, OBJS3D[i]);
                OBJS3D[i]=c3drotate(2, rand() % 360, OBJS3D[i]);
                OBJS3D[i]=c3drotate(3, rand() % 360, OBJS3D[i]);
                */
            } 

            break;    
        case 4:     // cube
            MAXOBJ3DDIST=round(SCREENY/4*3);
            MINOBJ3DDIST=MAXOBJ3DDIST-1;
            for (i=0; i<MAXOBJ3D; i++) {
                OBJS3D[i].x=-MAXOBJ3DDIST;

                OBJS3D[i].y=((rand() % MAXOBJ3DDIST*2)-MAXOBJ3DDIST)*OBJ3DNEGPOS[rand() % 2];
                OBJS3D[i].z=((rand() % MAXOBJ3DDIST*2)-MAXOBJ3DDIST)*OBJ3DNEGPOS[rand() % 2];
                OBJS3D[i]=c3drotate(rand() % 2 +2, (rand() % 4) *90, OBJS3D[i]);
            } 
            break;
        case 5:     // cube2
            MAXOBJ3DDIST=round(SCREENY/3*2);
            MINOBJ3DDIST=MAXOBJ3DDIST-1;
            for (i=0; i<MAXOBJ3D; i++) {
                OBJS3D[i].x=MAXOBJ3DDIST * OBJ3DNEGPOS[rand() % 2];

                OBJS3D[i].y=(rand() % MAXOBJ3DDIST) * OBJ3DNEGPOS[rand() % 2];
                OBJS3D[i].z=MAXOBJ3DDIST;
                OBJS3D[i]=c3drotate(rand() % 3 +1, (rand() % 4) *90, OBJS3D[i]);
                OBJS3D[i]=c3drotate(rand() % 3 +1, (rand() % 4) *90, OBJS3D[i]);
                OBJS3D[i]=c3drotate(rand() % 3 +1, (rand() % 4) *90, OBJS3D[i]);
            } 
            break;
    }


    // setup the clock digits' transparency
    CLOCKCHAR.transpbcol=false;
    CLOCKCHAR.transpcol=false;
    CLOCKCHAR.transpchr=false;
    AVOIDCLOCKCOLOR=0;
}

// calculate the new position of points
void calc_bg_obj3d() {
    int i;
    // rotate on each axis every point
    OBJ3DCAM_ANGLE.x+=1;
    OBJ3DCAM_ANGLE.y+=1;
    OBJ3DCAM_ANGLE.z+=1;
    for (i=0; i<MAXOBJ3D; i++) {
        OBJS3DCALC[i]=c3drotate(1, OBJ3DCAM_ANGLE.x, OBJS3D[i]);
        OBJS3DCALC[i]=c3drotate(2, OBJ3DCAM_ANGLE.y, OBJS3DCALC[i]);
        OBJS3DCALC[i]=c3drotate(3, OBJ3DCAM_ANGLE.z, OBJS3DCALC[i]);
    }    
}

//
void draw_bg_obj3d() {
    int i,x,y;
    // clear the layer
    clearlayer(OBJ3DLAYER, OBJ3DCLEAR);
    // put the things to layer
    for (i=0; i<MAXOBJ3D; i++) {
        //if (OBJS3DCALC[i].z<0) { // if its far from camera then draw
            // array index checks for OBJ3DCHARS[]
            int dist=(int)( (OBJS3DCALC[i].z+MAXOBJ3DDIST/2) / ((MAXOBJ3DDIST*2 / MAXOBJ3DTYPE)-1)  );
            if (dist<0) { dist=0;}
            if (dist>MAXOBJ3DTYPE-1) { dist=MAXOBJ3DTYPE-1;}
            // draw the point
            charxy(OBJ3DLAYER, OBJ3DCENTER.x+c3dto2d(OBJS3DCALC[i]).x, OBJ3DCENTER.y+c3dto2d(OBJS3DCALC[i]).y,
            OBJ3DCHARS[dist]);
        //}
    }

}
