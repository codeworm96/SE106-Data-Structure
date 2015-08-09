#include <iostream>
#include <vector>

//generator the succeeding element in the result vector
int succ(std::vector<int>::iterator & it1, std::vector<int>::iterator & it2,
        const std::vector<int>::iterator & en1, const std::vector<int>::iterator & en2)
{
    if (it1 == en1){
        return *it2++;
    }
    if (it2 == en2){
        return *it1++;
    }
    if (*it1 < *it2){
        return *it1++;
    }else{
        return *it2++;
    }
}

double median_helper(std::vector<int>::iterator & it1, std::vector<int>::iterator & it2,
                const std::vector<int>::iterator & en1, const std::vector<int>::iterator & en2,
                int size, int count)
{
    if (size%2 == 0){
        int t1 = succ(it1, it2, en1, en2);//take the head of the left result vector
        if (count == (size / 2 - 1)){//one of the median?
            int t2 = succ(it1, it2, en1, en2);//get the next
            return (t1 + t2) / 2.0;//return the average
        }
        return median_helper(it1, it2, en1, en2, size, count + 1);//recur on the left
    }else{
        int t = succ(it1, it2, en1, en2);
        if (count == size / 2){//the median?
            return t;
        }
        return median_helper(it1, it2, en1, en2, size, count + 1);
    }
}

double median(std::vector<int> v1, std::vector<int> v2)
{
    std::vector<int>::iterator it1, it2;
    it1 = v1.begin();
    it2 = v2.begin();
    return median_helper(it1, it2, v1.end(), v2.end(), v1.size() + v2.size(), 0);
}

int main()
{
    std::vector<int> v1;
    std::vector<int> v2;
    //input
    while (std::cin){
        int t;
        std::cin>>t;
        if(std::cin){
            v1.push_back(t);
        }
    }//v1
    std::cin.clear();
    char c;
    std::cin>>c;      //the ,
    while (std::cin){
        int t;
        std::cin>>t;
        if(std::cin){
            v2.push_back(t);
        }
    }//v2

    std::cout<<median(v1, v2)<<std::endl;
    return 0;
}


