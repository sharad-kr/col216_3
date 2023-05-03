
#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <fstream>
#include <exception>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <bits/stdc++.h>

using namespace std;



int BLOCKSIZE ;
int L1_SIZE ;
int L1_ASSSOC; 
int L2_SIZE ;
int L2_ASSOC ;










struct cache{
    int index_size_l1 = L1_SIZE/(BLOCKSIZE*L1_ASSOC);
    int index_size_l2 = L2_SIZE/(BLOCKSIZE*L2_ASSOC);    
    // vector<vector<int>> tag_l1(index_size_l1,{-1});
    // vector<vector<int>> tag_l2(index_size_l2,{-1});
    // vector<vector<int>> data_l1(index_size_l1,{-1});
    // vector<vector<int>> data_l2(index_size_l2,{-1});
    vector<vector<int>> tag1;
	vector<vector<int>> tag2;
    vector<vector<int>> data1;
	vector<vector<int>> data2;
	vector<vector<int>>lru_l1;
	vector<vector<int>>lru_l2;
    
    void make_array(int index_size,int assoc, int value , vector<vector<int>> vec){
        for (int i = 0 ; i<index_size; i++){
    vector<int> t;
    for (int j=0 ; j< assoc ; j++){
        t.push_back(value);

    }
    vec.push_back(t);
}
    }

        
    make_array(index_size_l1,L1_ASSOC,0,lru_l1);
    make_array(index_size_l2,L2_ASSOC,0,lru_l2);
    make_array(index_size_l1,L1_ASSOC,0,data1);
    make_array(index_size_l2,L2_ASSOC,0,data2);
    make_array(index_size_l1,L1_ASSOC,-1,tag1);
    make_array(index_size_l2,L2_ASSOC,-1,tag2);

    vector<vector<string>> commands;
    int l1_read;
    int l1_read_miss;
    int l1_wrt;
    int l1_wrt_miss;
    int l1_miss_rate;
    int l1_wrtbk;
    int l2_read;
    int l2_read_miss;
    int l2_wrt;
    int l2_wrt_miss;
    int l2_miss_rate;
    int l2_wrtbk;


    cache(ifstream &files){
            constructCommands(file);
    }


    void constructCommands(ifstream &file)
        {
            string line;
            while (getline(file, line))
                parseCommand(line);
            file.close();
        }
    void parseCommand(string line)
        {
        vector<string> command ;
        boost::tokenizer<boost::char_separator<char>> tokens(line, boost::char_separator<char>(" \t"));
        for (auto&s : tokens){
            command.push_back(s);}

        commands.push_back(command);
        }

    void executeCommands(){
        for(int i = 0 ; i < commands.size() ; i++){
            if(commands[i][0]=='r'){
                read_req_l1(commands[i]);
            }
            else{
                write_req_l1(commands[i]);
            }
        }
    }

    bool isTag(vector<vector<int>> tag_list , int tag, int index){
        bool result = false;
        for(int i = 0;i<tag_list[index].size();i++){
            if(tag_list[index][i]==tag){
                result = true;
                break;
            }
        }
        return result;

    }




    void write_req_l1(vector<string> commander){
            int address = stoi(commander[1],nullptr,16);
            int offset = address % BLOCKSIZE;
            // int index_size_l1 = size/(BLOCKSIZE*L1_ASSOC);
            int index_l1 = (address/BLOCKSIZE) % index_size_l1;
            int tag_l1 = (address % BLOCKSIZE) % index_size_l1;
                


    }
    
    
    

    void read_req_l1(vector<string> commander)
        {
            int address = stoi(commander[1],nullptr,16);
            int offset = address % BLOCKSIZE;
            // int index_size_l1 = size/(BLOCKSIZE*L1_ASSOC);
            int index_l1 = (address/BLOCKSIZE) % index_size_l1;
            int tag_l1 = (address % BLOCKSIZE) % index_size_l1;


        }

};




int main(int argc, char *argv[]){



    if (argc !=7) {
        std:: cerr << "Please provide all the arguments!\n";
        return 0;
    }
    else{
    ifstream file(argv[6]);
    int BLOCKSIZE = stoi(argv[1]);
    int L1_SIZE = stoi(argv[2]);
    int L1_ASSSOC = stoi(argv[3]);
    int L2_SIZE = stoi(argv[4]);
    int L2_ASSOC = stoi(argv[5]);

    cache *cac;
    if (file.is_open()){
    	cac = new cache(file);
    	}
    	cac->executeCommands();
    return 0;
    }
}





    





