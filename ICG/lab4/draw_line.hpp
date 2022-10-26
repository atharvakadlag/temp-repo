#include "bits/stdc++.h"

using namespace std;

vector<pair<int, int>> DDA(int x1, int y1, int x2, int y2) {
    /*
    Returns vector of points in form (x, y)
    */
    vector<pair<int, int>> line_points;

    float slope = (float)(y1 - y2)/(x1 - x2);
    if (slope >= 1) {
        if (y1 > y2) {
            int y_temp = y1;
            y1 = y2;
            y2 = y_temp;

            int x_temp = x1;
            x1 = x2;
            x2 = x_temp;
        }

        int y_prev = y1;
        float x_prev_f = x1;
        while (y_prev <= y2) {
            int x_prev = round(x_prev_f);
            // cout << count << " " << x_prev_f << " " << x_prev << " " << y_prev << "\n";
            line_points.push_back(make_pair(x_prev, y_prev));
            y_prev = y_prev + 1;
            x_prev_f = x_prev_f + 1/slope;
        }
    } else {
        if (x1 > x2) {
            int x_temp = x1;
            x1 = x2;
            x2 = x_temp;

            int y_temp = y1;
            y1 = y2;
            y2 = y_temp;
        }

        int x_prev = x1;
        float y_prev_f = y1;
        while (x_prev <= x2) {
            int y_prev = round(y_prev_f);
            line_points.push_back(make_pair(x_prev, y_prev));
            x_prev = x_prev + 1;
            y_prev_f = y_prev_f + slope;
        }
    }

    return line_points;
}

vector<pair<int, int>> BLD(int x1, int y1, int x2, int y2) {
    /*
    Returns vector of points in form (x, y)
    */

    vector<pair<int, int>> line_points;

    float slope = (float)(y1 - y2)/(x1 - x2);
    cout << slope << endl;
    if (slope <= 1) {
        if (x1 > x2) {
            int x_temp = x1;
            x1 = x2;
            x2 = x_temp;

            int y_temp = y1;
            y1 = y2;
            y2 = y_temp;
        }

        int delx = x2 - x1;
        int dely = y2 - y1;

        int fac1 = 2*dely;
        int fac2 = 2*dely - 2*delx;

        int P0 = 2*dely - delx;

        int x_prev = x1;
        int y_prev = y1;
        int Pk = P0;
        while (x_prev <= x2) {
            if (Pk <= 0) {
                line_points.push_back(make_pair(x_prev, y_prev));
                x_prev += 1;
                Pk += fac1;
            }
            if (Pk > 0) {
                line_points.push_back(make_pair(x_prev, y_prev));
                x_prev += 1;
                y_prev += 1;
                Pk += fac2;
            }
        }
    } else {
        x1 *= -1;
        x2 *= -1;
        cout << "hello\n";
        vector<pair<int, int>> line_points = BLD(x1, y1, x2, y2);

        for (int i = 0; i < line_points.size(); i++) {
            line_points[i].first *= -1;
        }
    }

    return line_points;
}
