#include <iostream>
#include <stack>

using namespace std;

int main()
{
    //init
    int n;  //n in description
    cin >> n;
    bool valid = true;  //consider the sequence is true
    int pending = 1;    //the next number for push
    stack<int> st;      //the stack
    //checking
    for (int i = 0; i < n; ++i){
        int cur;
        cin >> cur;
        while(st.empty()||((pending <= n)&&(st.top() != cur))){
            st.push(pending);
            ++pending;
        }//push until st.top() == cur or sequence exhausted

        if (!st.empty()&&(st.top() == cur)){ //ok for pop
            st.pop();
        }else{ //cannot match the output
            valid = false;
        }
    }
    //output
    if (valid){
        cout<<1;
    }else{
        cout<<0;
    }

    return 0;
}


