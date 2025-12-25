#include <iostream>
#include "../cache/cache.hpp"
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
        cachelevel* l1_cache = NULL ;
        cachelevel* l2_cache = NULL ;

        while( getline( cin , cmd ) ){
            
            if( cmd == "exit" ){
                cout << "End" << endl ;
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
                cout << "Allocator set" << endl ;   
            }
            if( split[ 0 ] == "malloc" ){
                if( allocator == 1 ) memory->first_fit( stoi( split[ 1 ] ) ) ;
                if( allocator == 2 ) memory->best_fit( stoi( split[ 1 ] ) ) ;
                if( allocator == 3 ) memory->worst_fit( stoi( split[ 1 ] ) ) ;
                cout << "Allocated memory" << endl ;
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

            if( split[ 0 ] == "init" && split[ 1]  == "cache" ){
                string s ;
                
                int Size ;
                int Block_size ;
                int associativity ;
                
                if( split[ 2 ] == "1" ){

                    cout << "Enter Cache size" << endl ;
                    getline( cin , s ) ;
                    Size = stoi( s ) ;

                    cout << "Enter Block Size " << endl ;
                    getline( cin , s ) ;
                    Block_size = stoi( s ) ;

                    cout << "Enter associativity" << endl ;
                    getline( cin , s ) ;
                    associativity = stoi ( s ) ;

                    l1_cache = new cachelevel( Size , Block_size , associativity , memory ) ;

                }
                if( split[ 2 ] == "2" ){
                    
                    cout << "Enter Cache size" << endl ;
                    getline( cin , s ) ;
                    Size = stoi( s ) ;

                    cout << "Enter Block Size " << endl ;
                    getline( cin , s ) ;
                    Block_size = stoi( s ) ;

                    cout << "Enter associativity" << endl ;
                    getline( cin , s ) ;
                    associativity = stoi ( s ) ;

                    l2_cache = new cachelevel( Size , Block_size , associativity , memory ) ;

                }

            }
            
            if( split[ 0 ] == "read" ){

                int address = stoi( split[ 1 ] ) ;

                if( l1_cache != NULL ){
                    if( l1_cache->read( address ) ){
                        cout << "Found in l1 cache" << endl ;
                    }
                    else{
                        if( l2_cache != NULL ){
                            if( l2_cache->read( address ) ){
                                cout << "Found in l2 cache" << endl ; 
                            }
                        }
                        else{
                            cout << "Found in memory" << endl ;
                        }
                    }
                }
                else{
                    if( l2_cache != NULL ){
                        if( l2_cache->read( address ) ){
                            cout << "Found in l2 cache" << endl ; 
                        }
                    }
                    else{
                        cout << "Found in memory" << endl ;
                    }
                }

            }

        }


    }
    

};