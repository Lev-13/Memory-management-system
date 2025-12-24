#include <iostream>
#include "../allocator/memory.hpp"
#include <vector>
#include <string>
using namespace std ;

struct cli{

    vector < string > Split ( string &s )
    {

            vector < string > result ;
            string temp = "" ;
            for( auto a : s ){
                if( a == ' ' ){
                    if( temp.size() ) result.push_back( temp ) ;
                    temp = "" ;
                }
                else{
                    temp += a ;
                }
            }
            
            if( temp.size() ) result.push_back( temp ) ;

            return result ;

    }

    void run(){
        string cmd ;
        cout << "> " ;
        
        int allocator = 1 ;
        Memory* memory = NULL ;

        while( getline( cin , cmd ) ){
            
            if( cmd == "exit" ){
                cout << "Exiting..." << endl ;
                break; 
            }
            
            vector < string > split = Split( cmd ) ;

            if( split[ 0 ] == "init" & split[ 1 ] == "memory" ){
                memory = new Memory( stoi( split[ 2 ] ) ) ;
            }
            if( split[ 0 ] == "set" ){
                if( split[ 2 ][ 0 ] == 'f' ) allocator = 1 ;
                if( split[ 2 ][ 0 ] == 'b' ) allocator = 2 ;
                if( split[ 2 ][ 0 ] == 'w' ) allocator = 3 ;   
            }
            if( split[ 0 ] == "malloc" ){
                if( allocator == 1 ) memory->first_fit( stoi( split[ 1 ] ) ) ;
                if( allocator == 2 ) memory->best_fit( stoi( split[ 1 ] ) ) ;
                if( allocator == 3 ) memory->worst_fit( stoi( split[ 1 ] ) ) ;
            }
            if( split[ 0 ] == "free" ){
                memory->free_memory( stoi(  split[ 1 ] ) ) ;
            }
            if( split[ 0 ] == "dump" ){
                memory->print_memory() ;
            }
            if( split[ 0 ] == "stats" ){
                memory->stats() ;
            }
        }


    }
    

};