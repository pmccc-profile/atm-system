#ifndef CENTERSCREEN_H
#define CENTERSCREEN_H

#include <string>

using namespace std;

class CenterScreen
{
    public:
        CenterScreen();
        ~CenterScreen();

        int getConsoleWidth();
        int getWidth();
        void positionCenter(const string &text);

    private:
        int width;
};

#endif // CENTERSCREEN_H
