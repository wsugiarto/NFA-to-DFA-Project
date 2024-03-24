// g++ -Wall -pedantic -g -O0 -std=c++11 -o NFA NFAtoDFA.cpp 
#include <string>
#include <vector>
#include <tuple>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;
void NFAtoDFA(vector<tuple<string, int, vector<string>>> NFA, string start, vector<string> accepts){

    unordered_set<string> DFAStates; // Store all the DFA states
    vector<tuple<string,int,vector<string>>> DFA; // Store all DFA transitions
    for(auto tuple: NFA){
        DFAStates.insert(get<0>(tuple));
    }
    vector<string> zeroTrans;
    vector<string> oneTrans;
    tuple<string, int, vector<string>> toAdd0;
    tuple<string, int, vector<string>> toAdd1;
    //Creating transitions for the single node sets
    for(string state: DFAStates){ 
        zeroTrans = {};
        oneTrans = {};
        for(auto tuple: NFA){
            if(get<0>(tuple) == state){
                if(get<1>(tuple) == 0){
                    zeroTrans = get<2>(tuple);

                }
                else{
                    oneTrans = get<2>(tuple);
                }
            }
        toAdd0 = make_tuple(state, 0, zeroTrans);
        DFA.push_back(toAdd0);
        toAdd1 = make_tuple(state, 1, oneTrans);
        DFA.push_back(toAdd1);
        

        }
    }
    ///*
    int size = DFA.size();
    int count = 0;
    string states = "";
    vector<string> zeroTrans2;
    vector<string> oneTrans2;
    tuple<string, int, vector<string>> Add0;
    tuple<string, int, vector<string>> Add1;

    //Inserting states where we have more than one node in a set ex. {q1q2}
    for(auto tuple: DFA){ //Iterate through our current transitions to find these such states
        if(count >= size){ 
            break;
        }
        count++;
        if(get<2>(tuple).size() > 1){
            states = "";
            zeroTrans2 = {};
            oneTrans2 = {};
            for(string state: get<2>(tuple)){ // making string for such state
                if(states.find(state) != 2){
                    states += state;
                }
                for(auto transition: DFA){ // We want to find the transitions for these individual states to add to our new transitions
                    if(get<0>(transition) == state){
                        if(get<1>(transition) == 0){
                            for(string item: get<2>(transition)){
                                if(find(zeroTrans2.begin(), zeroTrans2.end(), item) == zeroTrans2.end()){
                                    zeroTrans2.push_back(item);
                                } 
                            }
                            

                        }
                        else{
                            for(string item: get<2>(transition)){
                                if(find(oneTrans2.begin(), oneTrans2.end(), item) == oneTrans2.end()){
                                    oneTrans2.push_back(item);
                                }
                            }
                        }
                    }
                }
            }
            DFAStates.insert(states);
            Add0 = make_tuple(states, 0, zeroTrans2);
            DFA.push_back(Add0);
            Add1 = make_tuple(states, 1, oneTrans2);
            DFA.push_back(Add1);

        }
    }

    //Printing all information starts here
    cout << "Original NFA transitions:" << endl;
    for(auto trans: NFA){
        for(auto st: get<2>(trans)){
            cout << get<0>(trans) << " " << get<1>(trans) << " " <<  st << ""<< endl;
        }
        
    }
    cout << "Start State:  " << start << endl;
    cout << "Accept States: " << endl; 

    for(auto acc : accepts){
        cout << acc << endl;
    }
    //*/
    cout << "DFA List Of Transitions" << endl;
    string states2 = "";
    int counter = 0; 
    
    //Printing Segment
    for(auto tuple: DFA){
        if(get<0>(tuple).length() == 2){
            states2 = "";
            for(string state: get<2>(tuple)){
                states2 += state;
            }
            if(counter == 4 || counter == 5){
                cout<< "{" << get<0>(tuple) << "}" << " " << get<1>(tuple) << " {" <<  states2 << "}"<< endl;
            }
            if(counter == 5){
                counter = -1;
            }
            counter++;
            
            
        }

        else{
            states2 = "";
            for(string state: get<2>(tuple)){
                states2 += state;
            }
            if(counter == 2 || counter == 3){
                cout<< "{" << get<0>(tuple) << "}" << " " << get<1>(tuple) << " {" <<  states2 << "}"<< endl;
            }
            if(counter == 3){
                counter = -1;
            }
            counter++;
            
        }
        
    }
    //Null set 
    bool useNull = false;
    for(auto tuple: DFA){
        if(get<2>(tuple).size() == 0){
            useNull = true;
            break;
        }
    }
    if(useNull){
        cout<< "{}" << " " << "0" << " {}"<< endl;
        cout<< "{}" << " " << "1" << " {}"<< endl;
    }
    

    cout << "Start State: " << start << endl;
    
    //Get the accept states by combining states if necessary
    vector<string> DFAaccepts;
    for(auto acceptStates: accepts){
        for(auto States: DFAStates ){
            if(boost::algorithm::contains(States, acceptStates)){
                DFAaccepts.push_back(States);
            }
        }
    }
    cout << "Accept States: " << endl;

    for(string items: DFAaccepts){
        cout << items << endl;
    }
    

}

int main(){
    vector<tuple<string, int, vector<string>>> NFA;
    vector<string> va{"q1"};
    tuple<string, int, vector<string>> a = make_tuple("q0", 1, va);
    vector<string> vb{"q1", "q2"};
    tuple<string, int, vector<string>> b = make_tuple("q1", 0, vb);
    vector<string> vc{"q1"};
    tuple<string, int, vector<string>> c = make_tuple("q1", 1, vc);
    NFA.push_back(a);
    NFA.push_back(b);
    NFA.push_back(c);
    vector<string> acceptstates;
    acceptstates.push_back("q2");
    NFAtoDFA(NFA, "q0", acceptstates);
}
