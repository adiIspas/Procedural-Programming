#include <iostream>

using namespace std;

int main()
{
    int M, N, P;
     M = 5;
    N = 7;
    P = 3;
    //int A[2][2] = {1,2,3,4}, B[2][2] = {5,6,7,8}, C[2][2] = {0,0,0,0};
    int A[M][P], B[P][N], C[M][N] = {0};
    int x = 1;
    int operatii1, operatii2, operatii3;
    operatii1 = operatii2 = operatii3 = 0;

    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            A[i][j] = B[i][j] = i + 1;

    for (int i = 0; i < M; ++i) {
            operatii1++;
        for (int j = 0; j < N; ++j) {
            operatii2++;
            for (int k = 0; k < P; ++k) {
                operatii3++;
                //cout << i << " " << j << " | " << x << ": " << A[i][k] << " " << B[k][j] << endl;
                x++;
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++)
            cout << C[i][j] << " ";
        cout << endl;
    }
        cout<<"Done!\n " << operatii1 << " " << operatii2 << " " << operatii3;

    return 0;
}
