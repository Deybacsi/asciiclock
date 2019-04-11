
const int FG_CUBE_LAYER=4;

s_simplechar CUBECHAR={ 32, 2, 1, true, false, false};
s_simplechar CUBECLR={ 32, 2, 1, true, true, true};

s_2dcoord CUBECENTER={ 0, 0};

const int CUBEEDGE=20;

// default cube coordinates in world units
s_3dcoord CUBE_DEF[8]={
    {-CUBEEDGE,-CUBEEDGE, CUBEEDGE},
    { CUBEEDGE,-CUBEEDGE, CUBEEDGE},
    { CUBEEDGE, CUBEEDGE, CUBEEDGE},
    {-CUBEEDGE, CUBEEDGE, CUBEEDGE},

    {-CUBEEDGE,-CUBEEDGE,-CUBEEDGE},
    { CUBEEDGE,-CUBEEDGE,-CUBEEDGE},
    { CUBEEDGE, CUBEEDGE,-CUBEEDGE},
    {-CUBEEDGE, CUBEEDGE,-CUBEEDGE},
};

// current angle of the cube
s_3dcoord CUBE_ANGLES={ 0, 0, 0};

// cube rotated coords for the current frame
s_3dcoord CUBE[8];


void init_fg_cube() {
     CUBECENTER={ (int) SCREENX/2, (int) SCREENY/2};
     //CUBECENTER= {0,0}
;}

void calc_fg_cube() {
    int i;
    CUBE_ANGLES.x+=3;
    CUBE_ANGLES.y+=3;
    CUBE_ANGLES.z+=3;
    for (i=0; i<8; i++) {
        CUBE[i]=c3drotate(1, CUBE_ANGLES.x, CUBE_DEF[i]);
        CUBE[i]=c3drotate(2, CUBE_ANGLES.y, CUBE[i]);
        CUBE[i]=c3drotate(3, CUBE_ANGLES.z, CUBE[i]);
    }
    

}

void draw_fg_cube() {
    int i;
    s_2dcoord c2dcoords;
    
    clearlayer(FG_CUBE_LAYER, CUBECLR);

    for (i=1; i<4; i++) {
        linexy( FG_CUBE_LAYER,
            CUBECENTER.x+c3dto2d(CUBE[i-1]).x, CUBECENTER.y+c3dto2d(CUBE[i-1]).y,
            CUBECENTER.x+c3dto2d(CUBE[i  ]).x, CUBECENTER.y+c3dto2d(CUBE[i  ]).y, CUBECHAR);
    }
    linexy( FG_CUBE_LAYER,
        CUBECENTER.x+c3dto2d(CUBE[3]).x, CUBECENTER.y+c3dto2d(CUBE[3]).y,
        CUBECENTER.x+c3dto2d(CUBE[0]).x, CUBECENTER.y+c3dto2d(CUBE[0]).y, CUBECHAR);

    for (i=5; i<8; i++) {
        linexy( FG_CUBE_LAYER,
            CUBECENTER.x+c3dto2d(CUBE[i-1]).x, CUBECENTER.y+c3dto2d(CUBE[i-1]).y,
            CUBECENTER.x+c3dto2d(CUBE[i  ]).x, CUBECENTER.y+c3dto2d(CUBE[i  ]).y, CUBECHAR);
    }
    linexy( FG_CUBE_LAYER,
        CUBECENTER.x+c3dto2d(CUBE[7]).x, CUBECENTER.y+c3dto2d(CUBE[7]).y,
        CUBECENTER.x+c3dto2d(CUBE[4]).x, CUBECENTER.y+c3dto2d(CUBE[4]).y, CUBECHAR);



    
    for (i=0; i<4; i++) {
        linexy( FG_CUBE_LAYER,
            CUBECENTER.x+c3dto2d(CUBE[i  ]).x, CUBECENTER.y+c3dto2d(CUBE[i  ]).y,
            CUBECENTER.x+c3dto2d(CUBE[i+4]).x, CUBECENTER.y+c3dto2d(CUBE[i+4]).y, CUBECHAR);
    }
    

     for (i=0; i<5; i++) {
        charxy( FG_CUBE_LAYER,
            CUBECENTER.x+c3dto2d(CUBE[i  ]).x, CUBECENTER.y+c3dto2d(CUBE[i  ]).y, CUBECHAR);
        }
    
        linexy( FG_CUBE_LAYER,
            CUBECENTER.x+c3dto2d(CUBE[0]).x, CUBECENTER.y+c3dto2d(CUBE[0]).y,
            CUBECENTER.x+c3dto2d(CUBE[4]).x, CUBECENTER.y+c3dto2d(CUBE[4]).y, CUBECHAR);


    stringxy (5, 2, 2, WRITECHAR, to_string(c3dto2d(CUBE[0]).x) );
    stringxy (5, 2, 3, WRITECHAR, to_string(c3dto2d(CUBE[0]).y) );

    stringxy (5, 2, 5, WRITECHAR, to_string(c3dto2d(CUBE[4]).x) );
    stringxy (5, 2, 6, WRITECHAR, to_string(c3dto2d(CUBE[4]).y) );

    //linexy( FG_CUBE_LAYER, c3dto2d(CUBE[0]).x, c3dto2d(CUBE[0]).y, c3dto2d(CUBE[2]).x,c3dto2d(CUBE[2]).y, CUBECHAR);
}