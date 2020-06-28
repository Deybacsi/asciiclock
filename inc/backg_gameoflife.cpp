const int GOF_LAYER=0;

// for some slowdown 
int gof_counter=0;

s_simplechar GOFLIVE = { 79, C_LBLUE, C_BLACK, false, false, false};
s_simplechar GOFDEAD = { 32, C_GRAY, C_BLACK, false, false, false};

s_2dcoord GOF_NEIGHBOURS[8] = {
     { -1,-1 },{ 0,-1 },{ +1,-1 },
     { -1, 0 },         { +1, 0 },
     { -1,+1 },{ 0,+1 },{ +1,+1 }
};

void init_bg_gof() {
    int x,y;
    clearalllayer(CLEARCHAR);
    clearlayer(GOF_LAYER, GOFDEAD);
    
    for (y=0; y<=SCREENY; y++) {
        for (x=0; x<=SCREENX; x++) {
            charxy(GOF_LAYER,x,y,rand() % 2 -1 ? GOFLIVE : GOFDEAD);
        }
    }
    
    /*
    for (y=20; y<=SCREENY-20; y++) {
        for (x=20; x<=SCREENX-20; x++) {
            charxy(GOF_LAYER,x,y,rand() % 2 -1 ? GOFLIVE : GOFDEAD);
        }
    }
    */
    x=20; y=20;
                                        charxy(GOF_LAYER,x,y-1, GOFLIVE ); charxy(GOF_LAYER,x+1,y-1, GOFLIVE );
    charxy(GOF_LAYER,x-1,y, GOFLIVE );  charxy(GOF_LAYER,x,y, GOFLIVE );
                                        charxy(GOF_LAYER,x,y+1, GOFLIVE );

    x=60; y=20;
    charxy(GOF_LAYER,x-1,y-1, GOFLIVE ); charxy(GOF_LAYER,x,y-1, GOFLIVE );
    charxy(GOF_LAYER,x-1,y, GOFLIVE );  charxy(GOF_LAYER,x,y, GOFLIVE );

    gof_counter=0;
}

void calc_bg_gof() {
    int x,y,i,neighbors;
    bool cellalive;
    gof_counter++;
    if (gof_counter % 2 != 0) { return; }

    clearlayer(GOF_LAYER+1, GOFDEAD);
    
    for (y=0; y<=SCREENY; y++) {
        for (x=0; x<=SCREENX; x++) {
            neighbors=0; cellalive=false;
            for (i=0; i<8; i++) {
                if (LAYER[GOF_LAYER][x+GOF_NEIGHBOURS[i].x][y+GOF_NEIGHBOURS[i].y].chr == GOFLIVE.chr) {
                    neighbors++;
                }
            }
            if (LAYER[GOF_LAYER][x][y].chr == GOFLIVE.chr && (neighbors==2 || neighbors==3) ) {cellalive = true; }
            //if (neighbors<2) { cellalive = false;}                  // Any live cell with fewer than two live neighbours dies, as if by underpopulatio
            //if (neighbors==2 || neighbors==3 ) { cellalive = true;} // Any live cell with two or three live neighbours lives on to the next generation
            //if (neighbors>3) { cellalive = false;}                  // Any live cell with more than three live neighbours dies, as if by overpopulation
            if (neighbors==3 && LAYER[GOF_LAYER][x][y].chr == GOFDEAD.chr) { cellalive = true;}
                                                                    // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction

            charxy(GOF_LAYER+1,x,y, cellalive ? GOFLIVE : GOFDEAD) ;    
        }
    }  
    for (y=0; y<=SCREENY; y++) {
        for (x=0; x<=SCREENX; x++) {  
            LAYER[GOF_LAYER][x][y]=LAYER[GOF_LAYER+1][x][y]; 
        }
    }
    
}

void draw_bg_gof() {
    
}