#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<string, string> Rule;
const int MAX_DEP = 10;
const int NO_ANSWER = MAX_DEP + 1;

int ans = NO_ANSWER;
string start;
string dest;
vector<Rule> rules;
vector<string> st;
bool have_more_dep;

bool dfs(const string & start, int depth, int begin, int maxdep)
{
    //hit the border
    if (depth > maxdep){
        //it's possible to lessen the border
        have_more_dep = true;
        return false;
    }
    if (start == dest){
        //found
        return true;
    }

    st[depth] = start;

    //try all rules
    for(int i = 0; i < rules.size(); ++i){
        size_t pos = max(begin - int(rules[i].first.size()) + 1, 0); //a cut not necessary to search from the begin
                                                                     //just after last modification
        while(true){
            pos = start.find(rules[i].first, pos);
            if(pos != string::npos){//found substr
                string t(start);
                //apply trans
                t.replace(pos, rules[i].first.size(), rules[i].second);
                vector<string>::iterator head(st.begin());
                vector<string>::iterator last(st.begin()+(depth + 1));
                if(find(head, last , t) == last){ //not appeared
                    if (dfs(t, depth + 1, pos, maxdep)){ 
                        return true;
                    }
                }
                ++pos;
            }else{
                break;
            }
        }
    }
    return false;
}

int main()
{
    //input
    ifstream fin("convert.in");
    fin >> start >> dest;
    string a, b;
    while (fin >> a >> b){
        rules.push_back(Rule(a, b));
    }
    //work, iterative deepen
    st.resize(MAX_DEP + 1);
    //try depth 0,1,2..10
    for (int i = 0; i <= MAX_DEP; ++i){
        have_more_dep = false;
        if (dfs(start, 0, 0, i)){
            //found answer!
            ans = i;
            break;
        }
        if (!have_more_dep){//no use to deepen
            break;
        }
    }

    //output
    ofstream fout("convert.out");
    if (ans < NO_ANSWER){
        fout << ans << endl;
    }else{
        fout << "NO ANSWER" <<endl;
    }
    return 0;
}
    

    
