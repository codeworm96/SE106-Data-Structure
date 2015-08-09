/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name: 张宇宁 
 * Student ID: 5140379063
 * This file is the starter project for the word ladder problem.
 * [TODO: extend the documentation]
 * A program to find the shortest word ladder between two words.
 * A word ladder is a connection from one word to anther formed by
 * changing one letter at a time with the constraint that at each
 * step the sequence of letters still forms a valid word.
 */

#include <iostream>
#include "lexicon.h"
#include "vector.h"
#include "queue.h"

const int NO_MORE_STEP = -1;  //represent that there is no more step before

struct LadderStep   //a key insight is that to record a ladder, we only need to restore the word 
                    //and keep track of the last step
{
    string str;     //the word
    int forward;    //last step
    //constructors
    LadderStep(const string & s, int fw):str(s), forward(fw){}
    LadderStep():str(""), forward(NO_MORE_STEP){}   //This is required to put in Vector
};

/* The function to solve the problem
 * Parameters:
 * start, dest => the two words to connect (MUST BE VALID WORDS)
 * dict        => Lexicon restores words
 * Return: The ladder / an empty Vector (when there is no solution)
 * No side effects
 */
Vector<string> find_ladder(const string & start, const string & dest, const Lexicon & dict)
{
    Vector<LadderStep> steps;  //keep answers
    Lexicon appeared;          //word that has appeared
    Queue<int> queue;          //the queue, saves the labels of steps

    //init
    steps.push_back(LadderStep(start,NO_MORE_STEP));
    appeared.add(start);
    queue.enqueue(0);
    int last = NO_MORE_STEP;   //the last step of the answer

    //main loop
    while(!queue.isEmpty()){
        int cur = queue.dequeue();

        if (steps[cur].str == dest) //arrives destination
        {
            last = cur;            //mark position
            break;
        }

        for (int i = 0; i < steps[cur].str.size(); ++i){
            for (char c = 'a'; c <= 'z'; ++c){           //generate all possible steps
                string next(steps[cur].str);
                next[i] = c;
                //A valid word that hasn't appeared yet?
                if (dict.contains(next)&& !appeared.contains(next)){
                    //enqueue
                    appeared.add(next);
                    steps.push_back(LadderStep(next, cur));
                    queue.enqueue(steps.size() - 1);
                }
            }
        }
    }

    Vector<string> tmp;       //the answer, reversed
    while(last != NO_MORE_STEP){       //has more steps?
        tmp.push_back(steps[last].str);
        last = steps[last].forward;    //go forward
    }

    //reverse to get the answer
    Vector<string> res;
    for (int i = tmp.size() - 1; i>=0; --i){
        res.push_back(tmp[i]);
    }

    return res;
}

int main()
{
    Lexicon dict("EnglishWords.dat");  //create a dictionary for reference
    
    string start;
    std::cout<<"Enter start word (RETURN to quit): ";
    std::getline(std::cin, start);
    while(start != ""){
        std::cout<<"Enter destination word: ";
        string dest;
        std::getline(std::cin, dest);

        Vector<string> res = find_ladder(start, dest, dict);

        //output
        if (!res.isEmpty()){    //found solution?
            std::cout<<res[0];  //the start word
            for (int i = 1; i < res.size(); ++i){
                std::cout<<" "<<res[i];
            }
        }
        std::cout<<std::endl;

        std::cout<<"Enter start word (RETURN to quit): ";
        std::getline(std::cin, start);
    }
    std::cout<<"Goodbye!"<<std::endl;
    return 0;
}
