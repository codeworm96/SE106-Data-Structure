#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
    int n = 9000;
    srand((unsigned)time(0));
    cout<<n<<endl;
    for(int i = n;i>0;--i){
        cout<<rand()%10000000<<' ';
    }
    return 0;
}
