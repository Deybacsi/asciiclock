
time_t TIMENOW;

const int MAXTIMEZONES=1;

int ACT_HOUR[MAXTIMEZONES],
    ACT_MIN[MAXTIMEZONES],
    ACT_SEC[MAXTIMEZONES];

// string for actual time - "HHMMSS"
string  ACT_TIMESTR[MAXTIMEZONES],
        ACT_MINSTR[MAXTIMEZONES]; // "HHMM"

// for comparing the last timestring
// if LAST_TIMESTR != ACT_TIMESTR -> second changed
string  LAST_TIMESTR[MAXTIMEZONES],
        LAST_MINSTR[MAXTIMEZONES];



// get milliseconds time
// http://www.firstobject.com/getmillicount-milliseconds-portable-c++.htm

int GetMilliCount()
{
  // Something like GetTickCount but portable
  // It rolls over every ~ 12.1 days (0x100000/24/60/60)
  // Use GetMilliSpan to correct for rollover
  timeb tb;
  ftime( &tb );
  int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
  return nCount;
}

int GetMilliSpan( int nTimeStart )
{
  int nSpan = GetMilliCount() - nTimeStart;
  if ( nSpan < 0 )
    nSpan += 0x100000 * 1000;
  return nSpan;
}



// convert int to 2 char string with leading 0 if necessary
string inttostr2(int i) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << i;
    std::string s = ss.str();
    return s;
}

void checktime() {
    TIMENOW = time(0);
    tm *ltm = localtime(&TIMENOW);
    ACT_HOUR[0]=ltm->tm_hour;
    ACT_MIN[0]=ltm->tm_min;
    ACT_SEC[0]=ltm->tm_sec;
    ACT_TIMESTR[0]=inttostr2(ACT_HOUR[0])+inttostr2(ACT_MIN[0])+inttostr2(ACT_SEC[0]);
    ACT_MINSTR[0]=inttostr2(ACT_HOUR[0])+inttostr2(ACT_MIN[0]);
}

// return the count of chars available to read
int keyPressed() {
    int i;
    ioctl(0, FIONREAD, &i);
    return i; 
}

