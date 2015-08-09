#include <fstream>
using namespace std;

const int MAX_N = 150000;
const int MAX_SIZE = 300000;
const int OFFEST = 150000;

int a[MAX_N];
int n, m;

bool check(int l, int r)
{
    if ((r - l + 1)%2==0)
      return false;
    bool f = false;
    int less = 0;
    int greater = 0;
    for (int i = l; i <= r ; ++i){
        if (a[i] < m)
            ++less;
        if (a[i] == m)
            f = true;
        if (a[i] > m)
            ++greater;
    }
    return (f&&(less==greater));
}

int main()
{
    //input
    ifstream fin("hash.in");
    fin>>n>>m;
    for (int i = 0; i < n; ++i){
        fin>>a[i];
    }
    int ans = 0;
    for (int i = 0; i < n; ++i){
        for (int j = i; j < n; ++j){
            if (check(i,j)){
                ++ans;
            }
        }
    }
    ofstream fout("hash.ans");
    fout<<ans<<endl;
    return 0;
}



