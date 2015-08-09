#include <iostream>
using namespace std;

const int MAXL = 20000000;  //max # of elements to sort

int n;//# of elements
int a[MAXL];//array to sort
//int tmp[MAXL];//the auxiliary space
//do not need the auxiliary array any more

void swap(int & x, int & y)
{
    int t(x);
    x = y;
    y = t;
}

void reverse(int l, int r) //reverse a[l,r)
{
    int i = l;
    int j = r - 1;
    while (i < j){
        swap(a[i], a[j]);
        ++i;
        --j;
    }
}

void merge(int l, int m, int r)//merge a[l,m) and a[m,r), see readme for more infomation
{
    int i = l;
    int j = m;
    while ((i != j) && (j != r)){
        while ((i != j) && (a[i] <= a[j])){
            ++i;
        }
        int k = j;
        while ((j != r) && (a[j] < a[i])){
            ++j;
        }
        reverse(i, k);
        reverse(k, j);
        reverse(i, j);
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

