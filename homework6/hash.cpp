#include <fstream>
#include "hash.h"
using namespace std;

int a[MAX_N];    //array
int h[MAX_SIZE]; //hash table

int main()
{
    int n, m, pos;
    //pos: position of m

    //input
    ifstream fin("hash.in");
    fin>>n>>m;
    for (int i = 0; i < n; ++i){
        fin>>a[i];
        if (a[i] == m){
            pos = i;
        }
    }
    //init hast table
    for (int i = -n; i <= n ; ++i){
        h[OFFEST + i] = 0;
    }
    //counting on the first part
    int cnt = 0;    //(# of elem < m) - (# of elem > m)
    for (int i = pos; i >= 0; --i){
        if (a[i] > m){
            --cnt;
        }
        if (a[i] < m){
            ++cnt;
        }
        ++h[OFFEST + cnt];
    }
    //counting on the second part
    int ans = 0;
    cnt = 0;
    for (int i = pos; i < n; ++i){
        if (a[i] > m){
            --cnt;
        }
        if (a[i] < m){
            ++cnt;
        }
        ans += h[OFFEST - cnt];  //sum the matching pairs
    }
    //output
    ofstream fout("hash.out");
    fout<<ans<<endl;
    return 0;
}



