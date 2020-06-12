// basic digital clock


// layer to draw clock
const int CLOCKLAYER=2;

// color of clock
int CLOCKCOLOR=0;

// color what can't be chosen during random color selection
// background effects can change it -> and it's advised to do so
int AVOIDCLOCKCOLOR=0;

s_simplechar CLOCKCHAR = { 32, 1, 2, true, true, false };

// char for clearing the screen
s_simplechar CLOCKCLEAR = { 32, 0, 8, true, true, true};



// : between hour and min - on/off
bool colon;

void init_clock_digital() {
    // randomize clock charset design
    ACTDIGITDESIGN=rand() % MAXDIGITDESIGNS;
    // randomize clock color
    do {
        CLOCKCOLOR=rand() % 8;
    } while (CLOCKCOLOR == AVOIDCLOCKCOLOR || CLOCKCOLOR == 0);
};

void draw_clock_digit(int layer, int px, int py, int digit, s_simplechar chr ) {
    int x,y;
    int dx=DIGITDESIGNS[ACTDIGITDESIGN].x;
    int dy=DIGITDESIGNS[ACTDIGITDESIGN].y;
    for (y=0; y<dy; y++) {
        for (x=0; x<dx; x++) {
            if ( CLOCKDIGIT8X8[ACTDIGITDESIGN][digit][y][x] == 120) {
                charxy(layer, px+x, py+y, CLOCKCHAR);
            } else {
                //charxy(CLOCKLAYER, 10+x, 12+y, CLOCKCLEAR);
            }
        }
    }
}

void draw_clock_digital(int cx, int cy) {
    int digit,x,y,dx,dy;
    CLOCKCHAR.bcol=CLOCKCOLOR;
    dx=DIGITDESIGNS[ACTDIGITDESIGN].x;
    dy=DIGITDESIGNS[ACTDIGITDESIGN].y;
    clearlayer(CLOCKLAYER,CLOCKCLEAR);
    for (digit=0; digit<2; digit++) {
        draw_clock_digit(CLOCKLAYER, cx+(digit*dx),cy, ACT_TIMESTR[0][digit]-48,CLOCKCHAR);
    }
    if (!(LAST_TIMESTR[0] == ACT_TIMESTR[0] )) {
        colon= !colon;
    }
    if (colon) {
        draw_clock_digit(CLOCKLAYER, cx+(2*dx),cy, 10,CLOCKCHAR);
    }
    for (digit=2; digit<4; digit++) {
        draw_clock_digit(CLOCKLAYER, cx+dx+(digit*dx),cy, ACT_TIMESTR[0][digit]-48,CLOCKCHAR);
    }
    LAST_TIMESTR[0] = ACT_TIMESTR[0];
};