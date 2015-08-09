#include <iostream>
using namespace std;
int main()
{
    bool f[20000];
    for (int i = 1; i < 20000 ;++i){
        f[i] = false;
        for (int j = 2; j < i; ++j){
            if (i % j == 0 && !f[i - j]){
                f[i] = true;
            }
        }
    }
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i){
        int n;
        cin >> n;
        if (f[n]){
            cout << "Alice" << endl;
        }else{
            cout << "Bob" << endl;
        }
    }
    return 0;
}
