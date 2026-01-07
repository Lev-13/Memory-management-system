#ifndef CACHE_HPP
#define CACHE_HPP
#include <iostream>
#include <vector>
#include <deque>
#include "../allocator/memory.hpp"
#include <cmath>
using namespace std;



struct cacheline{

    int tag ;
    int data ;

    cacheline( int t , int d ){
        tag = t ;
        data = d ; 
    }

};

struct cachelevel{

    int Size ;
    int Blocksize ;
    int associativity ;

    int hits = 0 ;
    int misses = 0 ;

    Memory* memory  ;

    int sets ;
    int offset_bits ;
    int set_bits ;

    
    vector < deque < cacheline > > cache ;

    cachelevel( int size , int bsize , int associ , Memory* mem ){
        
        Size = size ;
        Blocksize = bsize ;
        associativity = associ ;
        sets = ( Size  / ( associativity * Blocksize ) ) ;
        cache.resize( sets ) ;
        memory = mem ;
        offset_bits = log2( Blocksize ) ;
        set_bits = log2( sets ) ;

    }

    void insert( int address ){

        int offset = ( address & ( ( 1 << offset_bits ) - 1 ) ) ;
        int set = (address >> offset_bits) & ( ( 1 << set_bits ) - 1) ;

        int tag = address >> ( offset_bits + set_bits ) ;

        if( cache[ set ].size() == associativity ){
            cache[ set ].pop_back() ;
        }
        cacheline to_insert( tag , 0 ) ;
        cache[ set ].push_front(  to_insert ) ;

        cout << address << " inserted at " << set << endl ;

    }


    bool read( int address ){
        int offset = ( address & ( ( 1 << offset_bits ) - 1 ) ) ;
        int set = (address >> offset_bits) & ( ( 1 << set_bits ) - 1) ;

        int tag = address >> ( offset_bits + set_bits ) ;
        bool found = 0 ;

        for (auto it = cache[set].begin(); it != cache[set].end(); ++it) 
        {
            cout << "*" << endl ;
            if (it->tag == tag) {
                cacheline hit_line = *it;
                cache[set].erase(it);
                cache[set].push_front(hit_line);
                found = 1 ;
                break ;
            }
        }

        if( found ) hits ++ ;
        else misses ++ ;
        return found ;
    }

    void cache_flush( int address ){

        int set = (address >> offset_bits) & ( ( 1 << set_bits ) - 1) ;

        int tag = address >> ( offset_bits + set_bits ) ;

        deque<cacheline> *row = &cache[set];
		for (auto it = row->begin(); it != row->end(); it++) {
			if (it->tag == tag) {
				row->erase(it);
				return;
			}
		}

    }

    double hit_ratio(){
        if( hits + misses == 0 ) return 0.0 ;
        
        return ( double )hits / ( hits + misses ) ;
    }

    



};

#endif