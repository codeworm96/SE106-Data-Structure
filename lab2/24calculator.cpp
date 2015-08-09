#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>

using namespace std;
typedef vector<int> VecInt;
const double EPS = 1e-8;

VecInt cards;          //four cards
vector<VecInt> perm;   //all permutation of cards
vector<VecInt> op_seq; //all possible operators sequences
//auxilary spaces;
VecInt perm_work(4);
VecInt op_work(3);
//--

//generate all possible operators sequences
void make_op_seq(int cnt, int choice)
{
    if (cnt == 0){//a new one
        op_seq.push_back(op_work);
        return;
    }
    //try all possibilities
    for (int i = 0; i < choice; ++i){
        op_work[cnt - 1] = i;
        //generate the left
        make_op_seq(cnt - 1, choice);
    }
}

//helper for generate permutations
void make_perm_helper(int cnt, int n)
{
    if (cnt < 0){ //a new one
        perm.push_back(perm_work);
        return;
    }
    //try all choices
    for (int i = 0; i < n; ++i){
        bool found = false;
        for (int j = cnt + 1; j < n; ++j){
            if (perm_work[j] == i){
                found = true;
                break;
            }
        }
        //valid
        if (!found){
            perm_work[cnt] = i;
            //try left
            make_perm_helper(cnt - 1, n);
        }
    }
}

//generate all permutation
void make_perm(int n)
{
    make_perm_helper(n - 1, n);
}

//convert card to int
int card2int(const string & s)
{
    if (s.size() == 1){
        char c = s[0];
        if (c >= '1' && c <= '9'){
            return (c - '0');
        }
        if (c == 'J')
            return 11;
        if (c == 'Q')
            return 12;
        if (c == 'K')
            return 13;
        throw runtime_error("invalid card");
    }else{
        if (s == string("10")){
            return 10;
        }
        throw runtime_error("invalid card");
    }
}

//convert int to card
string int2card(int x)
{
    if (x >= 1 && x <= 9){
        string res;
        res += char(x + '0');
        return res;
    }
    switch(x){
        case 10:
            return string("10");
        case 11:
            return string("J");
        case 12:
            return string("Q");
        case 13:
            return string("K");
        default:
            throw runtime_error("invalid parameter");
    }
}

//operators:
//0:a+b
//1:a-b
//2:b-a
//3:a*b
//4:a/b
//5:b/a
double calc(double a, double b, int op)
{
    switch(op){
        case 0:
            return a+b;
            break;
        case 1:
            return a-b;
            break;
        case 2:
            return b-a;
            break;
        case 3:
            return a*b;
            break;
        case 4:
            if (abs(b) < EPS){//check for divide 0
                throw runtime_error("divide by 0");
            }
            return a/b;
            break;
        case 5:
            if (abs(a) < EPS){//check for divide 0
                throw runtime_error("divide by 0");
            }
            return b/a;
            break;
    }
}


bool check(const VecInt & perm, const VecInt & op_seq)
    try{
        double xs = cards[perm[0]];
        for (int i = 0; i < 3 ; ++i){
            xs = calc(xs,cards[perm[1 + i]],op_seq[i]);
        }
        return (abs(xs - 24) < EPS);
    }catch(...){
        return false;
    }

//check for ( op ) op ( op )
bool check2(const VecInt & perm, const VecInt & op_seq)
    try{
        double xs = calc(calc(cards[perm[0]],cards[perm[1]],op_seq[0]),calc(cards[perm[2]],cards[perm[3]],op_seq[2]),op_seq[1]);
        return (abs(xs - 24) < EPS);
    }catch(...){
        return false;
    }

string build(string a, string b, int op)
{
    string xs;
    switch(op){
        case 0:
            xs = a + " + " + b;
            break;
        case 1:
            xs = a + " - " + b;
            break;
        case 2:
            xs = b + " - " + a;
            break;
        case 3:
            xs = a + " * " + b;
            break;
        case 4:
            xs = a + " / " + b;
            break;
        case 5:
            xs = b + " / " + a;
            break;
    }
    xs = "( " + xs + " )";
    return xs;
}


//build output string
string build_exp(const VecInt & perm, const VecInt & op_seq)
{
    string xs = int2card(cards[perm[0]]);
    for (int i = 0; i < 3 ; ++i){
        xs = build(xs,int2card(cards[perm[1 + i]]),op_seq[i]);
    }
    return xs;
}

//build for ( op ) op ( op )
string build_exp2(const VecInt & perm, const VecInt & op_seq)
{
    return build(build(int2card(cards[perm[0]]),int2card(cards[perm[1]]),op_seq[0]),
                 build(int2card(cards[perm[2]]),int2card(cards[perm[3]]),op_seq[2]),op_seq[1]);
}

int main()
{ 
    //input
    ifstream fin("24calculator.in");
    for (int i = 0; i < 4; ++i){
        string t;
        fin >> t;
        cards.push_back(card2int(t));
    }

    //init
    make_perm(4);
    make_op_seq(3, 6);
    //try all permutation / operation pairs
    bool found = false;
    string ans;
    for (int i = 0; !found && i < perm.size(); ++i){
        for (int j = 0; !found && j < op_seq.size(); ++j){
            if (check(perm[i], op_seq[j])){
                found = true;
                ans = build_exp(perm[i], op_seq[j]);
            }
            if (check2(perm[i], op_seq[j])){
                found = true;
                ans = build_exp2(perm[i], op_seq[j]);
            }
        }
    }

    //output
    ofstream fout("24calculator.out");
    if (found){
        fout << ans << endl;
    }else{
        fout << "NO ANSWER" <<endl;
    }

    return 0;
}


