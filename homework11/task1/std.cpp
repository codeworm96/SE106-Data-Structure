#include <iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i){
        int n;
        cin >> n;
        if (n % 2){
            cout << "Bob" << endl;
        } else {
            int cnt = 0;
            while(n % 2 == 0){
                n /= 2;
                ++cnt;
            }
            if (n > 1 || (cnt % 2 == 0)){
                cout << "Alice" << endl;
            }else{
                cout << "Bob" << endl;
            }
        }
    }
    return 0;
}

 
