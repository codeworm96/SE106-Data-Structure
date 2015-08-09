#include <fstream>
#include <cstdlib>
#define N 500
#define INF 0x3FFFFFFF
using namespace std;
int a[N][N];
int to_ans(int x)
{
    if (x == INF){ // no path
        return -1;
    }else{
        return x;
    }
}
int main()
{
    srand(time(0));
    ofstream input_file("dijk.in");
    input_file << 499 <<endl;
    int m = 0;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            if (i == j){
                a[i][j] = 0;
            }else{
                if (rand()%2){
                    a[i][j] = rand()%1000;
                    ++m;
                }else{
                    a[i][j] = INF;
                }
            }
        }
    }
    input_file << m <<endl;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            if (i != j && a[i][j]!=INF){
                input_file << i << " " << j << " " << a[i][j] <<endl;
            }
        }
    }
    for (int k = 0; k < N; ++k){
        for (int i = 0; i < N; ++i){
            for (int j = 0; j < N; ++j){
                if (a[i][k] + a[k][j] < a[i][j]){
                    a[i][j] = a[i][k] + a[k][j];
                }
            }
        }
    }

    ofstream out("dijk.out");
    for (int i = 0; i < N; ++i){
        out << to_ans(a[0][i]) << " ";
    }

    return 0;
}
