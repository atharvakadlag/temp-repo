#include <bits/stdc++.h>
using namespace std;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

class Point;
class Line;
class ClippingWindow;

class Point
{
public:
    int x, y;

    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};

class ClippingWindow
{
public:
    int x_min, x_max, y_min, y_max;
    ClippingWindow(int _x_min, int _y_min, int _x_max, int _y_max)
    {
        x_min = _x_min;
        x_max = _x_max;
        y_min = _y_min;
        y_max = _y_max;
    }

    int get_outcode(Point p)
    {
        int x = p.x;
        int y = p.y;
        int outcode = INSIDE;
        if (x < x_min)
        {
            outcode |= LEFT;
        }
        if (x > x_max)
        {
            outcode |= RIGHT;
        }
        if (y < y_min)
        {
            outcode |= BOTTOM;
        }
        if (y > y_max)
        {
            outcode |= TOP;
        }

        return outcode;
    }

    bool contains(Point p)
    {
        int z = this->get_outcode(p);
        return z == 0;
    }
};

class Line
{
public:
    Point start = Point(0, 0);
    Point end = Point(0, 0);

    Line(int x1, int y1, int x2, int y2)
    {
        start = Point(x1, y1);
        end = Point(x2, y2);
    }

    Line(Point _start, Point _end)
    {
        start = _start;
        end = _end;
    }

    bool cohen_clip(ClippingWindow clip)
    {
        int outcode1 = clip.get_outcode(start);
        int outcode2 = clip.get_outcode(end);

        bool accepted = false;

        while (true)
        {
            if (clip.contains(start) && clip.contains(end))
            {
                accepted = true;
                break;
            }
            else if (clip.get_outcode(start) & clip.get_outcode(end))
            {
                break;
            }
            else
            {
                int x, y;
                int outer_outcode = outcode1 == 0 ? outcode2 : outcode1;
                if (outer_outcode & TOP)
                {
                    x = start.x + (end.x - start.x) * (clip.y_max - start.y) / (end.y - start.y);
                    y = clip.y_max;
                }
                else if (outer_outcode & BOTTOM)
                {
                    x = start.x + (end.x - start.x) * (clip.y_min - start.y) / (end.y - start.y);
                    y = clip.y_min;
                }
                else if (outer_outcode & RIGHT)
                {
                    y = start.y + (end.y - start.y) * (clip.x_max - start.x) / (end.x - start.x);
                    x = clip.x_max;
                }
                else if (outer_outcode & LEFT)
                {
                    y = start.y + (end.y - start.y) * (clip.x_min - start.x) / (end.x - start.x);
                    x = clip.x_min;
                }

                if (outer_outcode == outcode1)
                {
                    start.x = x;
                    start.y = y;
                    outcode1 = clip.get_outcode(start);
                }
                else
                {
                    end.x = x;
                    end.y = y;
                    outcode2 = clip.get_outcode(end);
                }
            }
        }

        return accepted;
    }
};