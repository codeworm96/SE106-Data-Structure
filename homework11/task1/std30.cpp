#include <iostream>
using namespace std;

bool check(int n)
{
    bool res = false;
    for (int i = 2; i < n; ++i){
        if (n % i == 0 && !check(n - i)){
            res = true;
        }
    }
    return res;
}

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i){
        int n;
        cin >> n;
        if (check(n)){
            cout << "Alice" << endl;
        }else{
            cout << "Bob" << endl;
        }
    }
    return 0;
}
