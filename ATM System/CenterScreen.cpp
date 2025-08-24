#include "CenterScreen.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

using namespace std;

CenterScreen::CenterScreen() : width(0)
{
   width = getConsoleWidth();
}
CenterScreen::~CenterScreen()
{
    //dtor
}

int CenterScreen::getConsoleWidth(){
#ifdef _WIN32
    /*
    stdoutputhandle = handle / access to the console/terminal screen where output is displayed
    csbi = includes: total rows & columns, current cursor position, text attributes, visible window portion
    srWindow = small rect: top, left, right, bottom
    csbi.srWindow.Right - csbi.srWindow.Left + 1  = result is inclusive (counted) both ends
    */

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        return columns;
    } else {
        return 120; // fallback
    }
#else
    /*
    winsize = csbi similar
    ioctl = stdoutputhandle similar
    ==0 return success
    */

    struct winsize w;
    if (isatty(STDOUT_FILENO) && ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        return w.ws_col;
    } else {
        return 120; // fallback
    }
#endif
}

int CenterScreen::getWidth(){
    return width;
}

//like margin: auto in web
void CenterScreen::positionCenter(const string &text) {
    /*
    static_cast<int>(text.length()) = gets text length and convert into signed(negative) int if unsigned(positive) int is too large
    (consoleWidth - textLength) / 2 = number of spaces left after texts and split by two evenly (left n right)
    if (padding < 0) padding = 0; = safety net, uncentered, if text is longer than the console/terminal
    */

    int padding=(width - static_cast<int>(text.length())) / 2;
    if (padding < 0) padding = 0;
    cout<<string(padding, ' ')<<text;
}
