#include <bits/stdc++.h>
#define line vector<pair<int, int>>
using namespace std;

int x, y;
int flag = 0;
float f = 0.001;

int Roundoff(float num)
{ // printf(" num = %f, number = %d \n", num, int(num));

    if ((num - int(num)) >= 0.5)
        return int(num) + 1;
    else
        return int(num);
}

void BLD(int x1, int y1, int x2, int y2, line* l1)
{
    int delx, dely, i, p;
    int incx, incy, inc1, inc2;
    int x = x1, y = y1;

    delx = x2 - x1;
    dely = y2 - y1;

    if (delx < 0)
        delx = -delx;
    if (dely < 0)
        dely = -dely;

    incx = 1;
    if (x2 < x1)
        incx = -1;

    incy = 1;
    if (y2 < y1)
        incy = -1;

    if (delx == 0)
    {
        for (i = 0; y != y2; i++)
        {
            (*l1).push_back(make_pair(x, y));
            y += incy;
        }
    }
    else if (delx >= dely)
    {
        (*l1).push_back(make_pair(x, y));
        p = 2 * dely - delx;
        inc1 = 2 * (dely - delx);
        inc2 = 2 * dely;

        for (i = 0; x != x2 || y != y2; i++)
        {
            if (p >= 0)
            {
                y += incy;
                p += inc1;
            }
            else
                p += inc2;

            x += incx;
            (*l1).push_back(make_pair(x, y));
        }
    }
    else
    {
        (*l1).push_back(make_pair(x, y));
        p = 2 * delx - dely;
        inc1 = 2 * (delx - dely);
        inc2 = 2 * delx;

        for (i = 0; x != x2 || y != y2; i++)
        {
            if (p >= 0)
            {
                x += incx;
                p += inc1;
            }
            else
                p += inc2;

            y += incy;
            (*l1).push_back(make_pair(x, y));
        }
    }

}
