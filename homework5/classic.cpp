#include <iostream>
using namespace std;

const int MAXL = 20000000;  //max # of elements to sort

int n;//# of elements
int a[MAXL];//array to sort
int tmp[MAXL];//the auxiliary space

void merge(int l, int m, int r)//merge a[l,m) and a[m,r)
{
    int k = l;
    int i = l;
    int j = m;
    //both are non-empty
    while ((i != m) && (j != r)){
        if (a[i] <= a[j]){ //Note: "=" for stability
            tmp[k] = a[i];
            ++i;
            ++k;
        }else{
            tmp[k] = a[j];
            ++j;
            ++k;
        }
    }
    //The second exhausted
    while (i != m){
        tmp[k] = a[i];
        ++i;
        ++k;
    }
    //The first exhausted
    while (j != r){
        tmp[k] = a[j];
        ++j;
        ++k;
    }
    //moving the merged part back
    for (int i = l; i < r; ++i){
        a[i] = tmp[i];
    }
}

void sort(int l, int r)//sorting a[l,r)
{
    //of size 0 or 1
    if (l + 1 >= r){
        return;
    }
    //otherwise, split it, sort each and merge
    int m = (l + r) / 2;
    sort(l, m);
    sort(m, r);
    merge(l, m, r);
}

int main()
{
    //read in
    cin >> n;
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }

    sort(0, n);

    //output
    for (int i = 0; i < n; ++i){
        cout << a[i] <<endl;
    }
    return 0;
}

