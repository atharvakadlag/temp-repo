#include<bits/stdc++.h>

#define parabola vector<pair<int, int>>
#define point pair<int, int>
using namespace std;

parabola MP_PARABOLA(int x_vertex, int y_vertex, int a) {
    parabola p1;

    int x = 0, y = 0;
    p1.push_back(point(x+x_vertex, y+y_vertex));
    
    int P  = 1 - 2*a;
    while (y <= a) {
        x++;

        if (P < 0) {
            // x = x;
            P = P + 2*x + 1; 
        } else {
            y++;
            P = P + 2*x + 1 - 4*a;
        }

        p1.push_back(point(x+x_vertex, y+y_vertex));
        p1.push_back(point(-x+x_vertex, y+y_vertex));
    }

    P = 2*a - 4;
    int count = 700;
    while (count--) {
        y++;

        if (P > 0) {
            P = P - 4*a;
        } else {
            x++;
            P = P + 2*x - 4*a;
        }

        p1.push_back(point(x+x_vertex, y+y_vertex));
        p1.push_back(point(-x+x_vertex, y+y_vertex));
    }
    return p1;
}
