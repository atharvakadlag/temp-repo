#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

float x1[5] = {1.0, 0.7, 1.2, 0.7, 1.2};
float w1[12] = {0.5, 1.5, 0.8, 0.9, -1.7, 1.6, 0.5, 1.5, 0.8, 0.9, -1.7, 1.6};
float w2[12] = {0.8, 0.2, -1.6, 1.2, 2.1, -0.2, 0.8, 0.2, -1.6, 1.2, 2.1, -0.2,};

float x[15000];

float _true[15000];
float loss[5000];
float layer1[15000];
float layer2[15000];

int main() {
    for (int i = 0; i < 36000; i++) {
        w1[i] = int(w1[i])%10/10;
        w2[i] = int(w2[i])%10/10;
    }
    for (int i = 0; i < 15000; i++) {
        x[i] = int(x[i])%10/10;
    }

    int iter;
    for (iter = 0; iter < 5000; iter++) {

        for (int i = 0; i < 15000; i++) {
            float sum = 0;
            for (int j = 0; j < 36000; j++) {
                sum += x[i] * w1[j];
            }
            layer1[i] = sum;
        }

        for (int i = 0; i < 15000; i++) {
            float sum = 0;
            for (int j = 0; j < 36000; j++) {
                sum += layer1[i] * w2[j];
            }
            layer2[i] = sum;
        }

    }
}
