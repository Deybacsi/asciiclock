// basic digital clock digits

int ACTDIGITDESIGN=1;

const int MAXDIGITDESIGNS=2;

struct s_digitdesign {
    unsigned int x;
    unsigned int y;
};

s_digitdesign DIGITDESIGNS[MAXDIGITDESIGNS] = {
    { 8, 8},
    { 8, 8}
};

const string CLOCKDIGIT8X8[MAXDIGITDESIGNS][12][8]={
    {
        {
        "  xxxx  ",
        " xx  xx ",
        " xx xxx ",
        " xxx xx ",
        " xx  xx ",
        " xx  xx ",
        "  xxxx  ",
        "        " },
        {
        "   xx   ",
        "  xxx   ",
        " xxxx   ",
        "   xx   ",
        "   xx   ",
        "   xx   ",
        " xxxxxx ",
        "        " },
        {
        "  xxxx  ",
        " xx  xx ",
        "     xx ",
        "   xxx  ",
        "  xx    ",
        " xx  xx ",
        " xxxxxx ",
        "        " },
        {
        "  xxxx  ",
        " xx  xx ",
        "     xx ",
        "  xxxx  ",
        "     xx ",
        " xx  xx ",
        "  xxxx  ",
        "        " },
        {
        "    xxx ",
        "   xxxx ",
        "  xx xx ",
        " xx  xx ",
        " xxxxxxx",
        "     xx ",
        "    xxxx",
        "        " },
        {
        " xxxxxx ",
        " xx  xx ",
        " xx     ",
        " xxxxx  ",
        "     xx ",
        " xx  xx ",
        "  xxxx  ",
        "        " },
        {
        "  xxxx  ",
        " xx  xx ",
        " xx     ",
        " xxxxx  ",
        " xx  xx ",
        " xx  xx ",
        "  xxxx  ",
        "        " },
        {
        " xxxxxx ",
        " xx  xx ",
        "     xx ",
        "    xx  ",
        "   xx   ",
        "   xx   ",
        "   xx   ",
        "        " },
        {
        "  xxxx  ",
        " xx  xx ",
        " xx  xx ",
        "  xxxx  ",
        " xx  xx ",
        " xx  xx ",
        "  xxxx  ",
        "        " },
        {
        "  xxxx  ",
        " xx  xx ",
        " xx  xx ",
        "  xxxxx ",
        "     xx ",
        " xx  xx ",
        "  xxxx  ",
        "        " },
        {
        "        ",
        "   xx   ",
        "   xx   ",
        "        ",
        "   xx   ",
        "   xx   ",
        "        ",
        "        " },
        {
        "        ",
        "        ",
        "        ",
        "        ",
        "        ",
        "        ",
        "        ",
        "        " }
    },
    {
        {
        " xxxxxx ",
        " xx  xx ",
        " xx  xx ",
        " xx  xx ",
        " xx  xx ",
        " xx  xx ",
        " xxxxxx ",
        "        " },
        {
        "     xx ",
        "     xx ",
        "     xx ",
        "     xx ",
        "     xx ",
        "     xx ",
        "     xx ",
        "        " },
        {
        " xxxxxx ",
        "     xx ",
        "     xx ",
        " xxxxxx ",
        " xx     ",
        " xx     ",
        " xxxxxx ",
        "        " },
        {
        " xxxxxx ",
        "     xx ",
        "     xx ",
        "  xxxxx ",
        "     xx ",
        "     xx ",
        " xxxxxx ",
        "        " },
        {
        " xx  xx ",
        " xx  xx ",
        " xx  xx ",
        " xxxxxx ",
        "     xx ",
        "     xx ",
        "     xx ",
        "        " },
        {
        " xxxxxx ",
        " xx     ",
        " xx     ",
        " xxxxxx ",
        "     xx ",
        "     xx ",
        " xxxxxx ",
        "        " },
        {
        " xxxxxx ",
        " xx     ",
        " xx     ",
        " xxxxxx ",
        " xx  xx ",
        " xx  xx ",
        " xxxxxx ",
        "        " },
        {
        " xxxxxx ",
        "     xx ",
        "     xx ",
        "     xx ",
        "     xx ",
        "     xx ",
        "     xx ",
        "        " },
        {
        " xxxxxx ",
        " xx  xx ",
        " xx  xx ",
        " xxxxxx ",
        " xx  xx ",
        " xx  xx ",
        " xxxxxx ",
        "        " },
        {
        " xxxxxx ",
        " xx  xx ",
        " xx  xx ",
        " xxxxxx ",
        "     xx ",
        "     xx ",
        " xxxxxx ",
        "        " },
        {
        "        ",
        "   xx   ",
        "   xx   ",
        "        ",
        "   xx   ",
        "   xx   ",
        "        ",
        "        " },
        {
        "        ",
        "        ",
        "        ",
        "        ",
        "        ",
        "        ",
        "        ",
        "        " }
    }    
};