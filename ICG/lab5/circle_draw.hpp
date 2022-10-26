#include <bits/stdc++.h>
#define circle vector<pair<int, int>>
#define point pair<int, int>
using namespace std;

circle MCD(int x_center, int y_center, int r) {
    circle c1;

    int x = r, y = 0;
    c1.push_back(point(x, y));
    
    int P  = 1-r;
    while (x>y) {
        y++;

        if (P < 0) {
            // x = x;
            P = P + 2*y + 1; 
        } else {
            x = x - 1;
            P = P + 2*y - 2*x + 1;
        }
        c1.push_back(point(x, y));
    }
    // for (int i = c1.size() - 2; i >= 0; i--) {
    //     c1.push_back(point(c1[i].second, c1[i].first));
    // }
    // for (int i = c1.size() - 2; i >= 0; i--) {
    //     cout << "phase 3 " << -1*c1[i].first << " " << c1[i].second << endl; 
    //     c1.push_back(point(-1*c1[i].first, c1[i].second));
    // }
    // for (int i = c1.size() - 2; i >= 0; i--) {
    //     c1.push_back(point(c1[i].first, -c1[i].second));
    // }

    for (int i = 0; i < c1.size(); i++) {
        c1[i] = point(c1[i].first+x_center, -c1[i].second+y_center);
    }
    // reverse(c1.begin(), c1.end());
    return c1;
}
