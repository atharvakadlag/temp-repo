#include <bits/stdc++.h>
using namespace std;

const int INSIDE = 0;  // 0000
const int LEFT = 1;    // 0001
const int RIGHT = 2;   // 0010
const int BOTTOM = 4;  // 0100
const int TOP = 8;     // 1000

class Point;
class Line;
class ClippingWindow;

class Point {
   public:
    int x, y;

    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }

    friend ostream& operator<<(ostream& ss, const Point& p) {
        return ss << "(" << p.x << ", " << p.y << ")";
    }

    bool get_location(Point a, Point b) {
        int x1 = a.x;
        int y1 = a.y;
        int x2 = b.x;
        int y2 = b.y;
        if (((x2 - x1) * (y - y1) - (y2 - y1) * (x - x1)) < 0) {
            return false;
        }
        return true;
    }

    static Point get_intersection(Point p1, Point p2, Point e1, Point e2) {
        // Line AB represented as a1x + b1y = c1
        double a = p2.y - p1.y;
        double b = p1.x - p2.x;
        double c = a * (p1.x) + b * (p1.y);
        // Line CD represented as a2x + b2y = c2
        double a1 = e2.y - e1.y;
        double b1 = e1.x - e2.x;
        double c1 = a1 * (e1.x) + b1 * (e1.y);
        double det = a * b1 - a1 * b;
        if (det == 0) {
            return Point(INT_MAX, INT_MAX);
        } else {
            double x = (b1 * c - b * c1) / det;
            double y = (a * c1 - a1 * c) / det;
            return Point(x, y);
        }
    }
};

class ClippingWindow {
   public:
    vector<Point> coordinates;
    ClippingWindow(vector<Point> _coordinates) {
        this->coordinates = _coordinates;
    }

    bool contains(Point p) {
        vector<Point> polygon_loop = coordinates;
        polygon_loop.push_back(polygon_loop[0]);
        for (int i = 1; i < polygon_loop.size(); i++) {
            if (!p.get_location(polygon_loop[i - 1], polygon_loop[i])) {
                return false;
            }
        }
        return true;
    }
};

class Polygon {
   public:
    vector<Point> coordinates;
    Polygon(vector<Point> _coordinates) {
        this->coordinates = _coordinates;
    }

    void suth_clip(ClippingWindow clip) {
        vector<Point> clip_loop = clip.coordinates;
        clip_loop.push_back(clip_loop[0]);
        vector<Point> polygon_loop = coordinates;
        polygon_loop.push_back(polygon_loop[0]);

        for (int i = 1; i < clip_loop.size(); i++) {
            Point e1 = clip_loop[i - 1];
            Point e2 = clip_loop[i];
            cout << "Going for edge " << e1.x << ", " << e1.y << " " << e2.x << ", " << e2.y << endl;
            vector<Point> clippedPolygon;
            for (int j = 1; j < polygon_loop.size(); j++) {
                Point p1 = polygon_loop[j - 1];
                Point p2 = polygon_loop[j];
                // cout << "\tGoing for point " << p1.x << ", " << p1.y << " " << p2.x << ", " << p2.y << endl;

                bool p1_isleft = p1.get_location(e1, e2);
                bool p2_isleft = p2.get_location(e1, e2);

                if (p1_isleft && p2_isleft) {
                    // cout << "\t\tboth left adding " << p1.x << ", " << p1.y << endl;
                    clippedPolygon.push_back(p1);
                } else if (!(p1_isleft || p2_isleft)){
                    // cout << "\t\tboth right - skip\n";
                } else {
                    // find intersection between p1, p2, and e1, e2
                    Point intersection = Point::get_intersection(p1, p2, e1, e2);
                    cout << "\t\t\t adding intersection " << intersection.x << ", " << intersection.y << endl;
                    if (!p1_isleft && p2_isleft) {
                        clippedPolygon.push_back(intersection);
                    } else if (p1_isleft && !p2_isleft) {
                        clippedPolygon.push_back(p1);
                        clippedPolygon.push_back(intersection);
                        cout << "\t\t\tadding p1 " << p1.x << ", " << p1.y << endl;
                        // apend intersection and poitn
                    }
                }
            }
            for (auto i: clippedPolygon) {
                cout << i << endl;
            }
            polygon_loop = clippedPolygon;
            polygon_loop.push_back(polygon_loop[0]);
        }
        polygon_loop.pop_back();
        this->coordinates = polygon_loop;
    }
};

// class Line
// {
// public:
//     Point start = Point(0, 0);
//     Point end = Point(0, 0);

//     Line(int x1, int y1, int x2, int y2)
//     {
//         start = Point(x1, y1);
//         end = Point(x2, y2);
//     }

//     Line(Point _start, Point _end)
//     {
//         start = _start;
//         end = _end;
//     }

//     bool cohen_clip(ClippingWindow clip)
//     {
//         int outcode1 = clip.get_outcode(start);
//         int outcode2 = clip.get_outcode(end);

//         bool accepted = false;

//         while (true)
//         {
//             if (clip.contains(start) && clip.contains(end))
//             {
//                 accepted = true;
//                 break;
//             }
//             else if (clip.get_outcode(start) & clip.get_outcode(end))
//             {
//                 break;
//             }
//             else
//             {
//                 int x, y;
//                 int outer_outcode = outcode1 == 0 ? outcode2 : outcode1;
//                 if (outer_outcode & TOP)
//                 {
//                     x = start.x + (end.x - start.x) * (clip.y_max - start.y) / (end.y - start.y);
//                     y = clip.y_max;
//                 }
//                 else if (outer_outcode & BOTTOM)
//                 {
//                     x = start.x + (end.x - start.x) * (clip.y_min - start.y) / (end.y - start.y);
//                     y = clip.y_min;
//                 }
//                 else if (outer_outcode & RIGHT)
//                 {
//                     y = start.y + (end.y - start.y) * (clip.x_max - start.x) / (end.x - start.x);
//                     x = clip.x_max;
//                 }
//                 else if (outer_outcode & LEFT)
//                 {
//                     y = start.y + (end.y - start.y) * (clip.x_min - start.x) / (end.x - start.x);
//                     x = clip.x_min;
//                 }

//                 if (outer_outcode == outcode1)
//                 {
//                     start.x = x;
//                     start.y = y;
//                     outcode1 = clip.get_outcode(start);
//                 }
//                 else
//                 {
//                     end.x = x;
//                     end.y = y;
//                     outcode2 = clip.get_outcode(end);
//                 }
//             }
//         }

//         return accepted;
//     }
// };