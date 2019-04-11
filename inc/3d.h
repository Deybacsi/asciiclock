// z center coords in world's unit
// orf eg a usual object should be ~20 units (like the cube)
float   izx=100,
        izy=100;

// radians for angle calculations
float   rad=3.1415926535/180;

struct s_2dcoord {
    int x = 0;
    int y = 0;
};

struct s_3dcoord {
    float x = 0;
    float y = 0;
    float z = 0;
};

s_2dcoord c3dto2d(s_3dcoord c3d) {
    float   zzx=(float) c3d.z/izx,
            zzy=(float) c3d.z/izy;
    s_2dcoord coords={0,0};
    coords.x=round( c3d.x+0.0 + (zzx * (c3d.x) ) );
    coords.y=round( c3d.y+0.0 + (zzy * (c3d.y) ) )/SCREEN_CHAR_ASPECT_RATIO;
    return coords;
}

// rotate on an axis with an angle
// axis 1: x, 2:y, 3:z
s_3dcoord c3drotate(int axis, int angle, s_3dcoord c3d) {
    s_3dcoord coords={0,0,0};
    switch (axis) {
        case 1:
            coords.x=c3d.x;
            coords.y=round( c3d.y*cos(angle*rad)+c3d.z*sin(angle*rad));
            coords.z=round(-c3d.y*sin(angle*rad)+c3d.z*cos(angle*rad));
        break;

        case 2:
            coords.x=round(-c3d.z*sin(angle*rad)+c3d.x*cos(angle*rad));
            coords.y=c3d.y;
            coords.z=round( c3d.z*cos(angle*rad)+c3d.x*sin(angle*rad));
        break;
        case 3:
            coords.x=round(-c3d.x*sin(angle*rad)+c3d.y*cos(angle*rad));
            coords.y=round( c3d.x*cos(angle*rad)+c3d.y*sin(angle*rad));
            coords.z=c3d.z;
        break;
    }
    return coords;
}


// 0,46875