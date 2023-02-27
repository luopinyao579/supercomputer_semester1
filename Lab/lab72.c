#include <iostream>
#include <vector>
#include <omp.h>
#define N 4

using namespace std;

struct Params 
{
    vector<vector<int>> matx;
    int index;
    double result;
};

double determinant_3x3(vector<vector<int>> m)
{
    double Z;
    Z = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) - m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2]) +
        m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
    return Z;
}
double determinant_4x4(vector<vector<int>> matx)
{
    double Y;
    vector<vector<int>> D1 = 
    {
            {matx[1][1], matx[1][2], matx[1][3]},
            {matx[2][1], matx[2][2], matx[2][3]},
            {matx[3][1], matx[3][2], matx[3][3]}
    };
    vector<vector<int>> D2 = 
    {
            {matx[1][0], matx[1][2], matx[1][3]},
            {matx[2][0], matx[2][2], matx[2][3]},
            {matx[3][0], matx[3][2], matx[3][3]}
    };
    vector<vector<int>> D3 = 
    {
            {matx[1][0], matx[1][1], matx[1][3]},
            {matx[2][0], matx[2][1], matx[2][3]},
            {matx[3][0], matx[3][1], matx[3][3]}
    };
    vector<vector<int>> D4 = 
    {
            {matx[1][0], matx[1][1], matx[1][2]},
            {matx[2][0], matx[2][1], matx[2][2]},
            {matx[3][0], matx[3][1], matx[3][2]}
    };
    Y= matx[0][0] * determinant_3x3(D1) - matx[0][1] * determinant_3x3(D2) +
        matx[0][2] * determinant_3x3(D3) - matx[0][3] * determinant_3x3(D4);
    return Y;
}

double determinant(vector<vector<int>> matx, int n) 
{
    int temp;
    for (auto& row : matx) {
        for (int j = 0; j < row.size(); ++j) {
            temp = row[n];
            row[n] = row[row.size() - 1];
            row[row.size() - 1] = temp;
        }
    }
    return determinant_4x4(matx);
}

int main() 
{
    double delta, result[N], x[N];

    // Create a matrix 5x5.
    vector<vector<int>> matx = 
    {
            {1, 2, 5, 8, 15},
            {2, 4, 3, 1, 0},
            {7, 7, 2, 5, 4},
            {7, 6, 3, 4, 20}
    };

    delta = determinant_4x4(matx);

    if (delta == 0) {
        cout << "key elements of the value =0, we can't calculat this problem.\n";
        return 0;
    }

    printf("key elements of the value=: %f\n", delta);

    // Calculate the required values
#pragma omp parallel for
    for (int i = 0; i < N; ++i) 
    {
        result[i] = determinant(matx, i);
    }

#pragma omp parallel for
    for (int i = 0; i < N; ++i) 
    {
        x[i] = result[i] / delta;
    }
    printf("x1 = %f\nx2 = %f\nx3 = %f\nx4 = %f\n", x[0], x[1], x[2], x[3]);
    return 0;
}
