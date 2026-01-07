#ifndef CLI_HPP
#define CLI_HPP
#include <iostream>
#include "../cache/cache.hpp"
#include "../virtual memory/virtual.hpp"
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
        virtual_memory *vmem = NULL ; 

        while( getline(cin, cmd) ){
            
            cout << "------------------" << endl ;
            cout << "Command given: "<< cmd << endl ;
            if( cmd == "exit" ){
                cout << "End" << endl ;
                break; 
            }
            
            vector < string > split = Split( cmd ) ;

            

            if( split[ 0 ] == "init" && split[ 1 ] == "memory" ){
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
                cout << "Allocated memory " << stoi( split [ 1 ] ) << endl ;
            }


            if( split[ 0 ] == "free" ){
                cout << "free reached" << endl ;
                memory->free_memory( stoi(  split[ 1 ] ) ) ;
            }


            if( split[ 0 ] == "dump" ){
                cout << "dump reached " << endl ;
                memory->print_memory() ;
            }
            
            if (split[0] == "stats") {
                cout << "\n========== SYSTEM STATISTICS ==========" << endl;
                
                if (memory != NULL) {
                    cout << "[Allocator Statistics]" << endl;
                    memory->stats() ;  
                }

                if (vmem != NULL) {
                    cout << "\n[Virtual Memory Statistics]" << endl;
                    vmem->stats_report() ; 
                }

                if (l1_cache != NULL) {
                    cout << "\n[L1 Cache Statistics]" << endl;
                    cout << "  Hits: " << l1_cache->hits << " | Misses: " << l1_cache->misses 
                        << " | Ratio: " << l1_cache->hit_ratio() * 100 << "%" << endl;
                }

                if (l2_cache != NULL) {
                    cout << "\n[L2 Cache Statistics]" << endl;
                    cout << "  Hits: " << l2_cache->hits << " | Misses: " << l2_cache->misses 
                        << " | Ratio: " << l2_cache->hit_ratio() * 100 << "%" << endl;
                }
                cout << "=======================================\n" << endl;
            }

            if( split[ 0 ] == "init" && split[ 1]  == "cache" ){
                
                cout << "cache reached" << endl ;
                int Size ;
                int Block_size ;
                int associativity ;
                
                if( split[ 2 ] == "1" ){

                    // cout << "Enter Cache size" << endl ;
                    Size = stoi( split[ 3 ] ) ;

                    // cout << "Enter Block Size " << endl ;
                    Block_size = stoi( split[ 4 ] ) ;

                    // cout << "Enter associativity" << endl ;
                    associativity = stoi( split [ 5 ] )  ;

                    l1_cache = new cachelevel( Size , Block_size , associativity , memory ) ;

                }
                if( split[ 2 ] == "2" ){
                    
                    // cout << "Enter Cache size" << endl ;
                    Size = stoi( split[ 3 ] ) ;

                    // cout << "Enter Block Size " << endl ;
                    Block_size = stoi( split[ 4 ] ) ;

                    // cout << "Enter associativity" << endl ;
                    associativity = stoi( split [ 5 ] )  ;

                    l2_cache = new cachelevel( Size , Block_size , associativity , memory ) ;

                }

            }

            if( split[ 0 ] == "init" && split[ 1 ] == "vmem" ){
                
            cout << "Virtual is initiallisze " << endl ;
                int v_size = stoi(split[2]);
                int p_size = stoi(split[3]);
                int pg_size = stoi(split[4]);
                vmem = new virtual_memory(v_size, p_size, pg_size) ;

            }
            
            if (split[0] == "read") {
                int va = stoi(split[1]);
                int pa = va;

                cout << "\n--- Memory Access Log ---" << endl;
                cout << "Virtual Address: " << va << endl;

                if (vmem != NULL) {
                    pa = vmem->translate(va);
                    cout << "[Step 2] Translation: VPN " << (va / vmem->page_size) 
                        << " -> Frame " << (pa / vmem->page_size) << " (PA: " << pa << ")" << endl;
                } else {
                    cout << "Virtual Memory disabled. PA = VA." << endl;
                }

                cout << "Probing Cache Hierarchy..." << endl;
                if (l1_cache != NULL && l1_cache->read(pa)) {
                    cout << "  >> L1 Cache: HIT" << endl;
                } 
                else {
                    cout << "  >> L1 Cache: MISS" << endl;
                    if (l2_cache != NULL && l2_cache->read(pa)) {
                        cout << "  >> L2 Cache: HIT" << endl;
                        l1_cache->insert( pa ) ; 
                    } 
                    else {
                        cout << "  >> L2 Cache: " << (l2_cache ? "MISS" : "DISABLED") << endl;
                        cout << "Accessing Physical RAM..." << endl;
                        if (l2_cache != NULL) l2_cache->insert(pa);
                        if (l1_cache != NULL) l1_cache->insert(pa);
                    }
                }
            }

            
            cout << "------------------" << endl ;

        }


    }
    

};

#endif