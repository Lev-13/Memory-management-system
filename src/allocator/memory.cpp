#include <iostream>
using namespace std ;

struct Block{

    const int memonry_unit_size = 1 ;
    int startaddress ;
    int Size ;
    int Id ;
    bool flag ;
    Block* next ;
    Block* prev ;

    Block(){
        next = NULL ;
        prev = NULL ;
    }

    Block ( int stadd , int size , int id , bool hole ,  Block* n , Block* p ){
        startaddress = stadd ;
        Size = size ;
        Id = id ;
        flag = hole ;
        next = n ;
        prev = p ;
    } 

};

struct memory{

    Block* head ;
    int Id = 0 ;
    
    memory( int size ){
        head = new Block( 0 , size, 1 , 1 ,NULL  , NULL ) ;
        cout << "memory of size " << size << " created " << endl ;
    }

    void first_fit( int size ){
        
        bool found = 0 ;
        Block* node = head ;
        while( node != NULL && found == 0 ){

            if( node->Size >= size ){
                found = 1 ;
                Id++ ;
                node->Id = Id ;
                node->flag = 0 ;
                int extra = node->Size - size ;
                node->Size = size ;
                if( extra > 0 ){
                    Block * after = node->next ;
                    Block* left = new Block( node->startaddress + size , extra , 0 , 1 , after , node ) ;
                    node->next = left ;
                    if( after != NULL ) after->prev = left ;
                } 
            }

            node = node->next ;
        }
    
    }

    void best_fit( int size ){
        
    }

    void print_memory(){
        Block* node = head ;
        while( node != NULL ){
            
            if( node->flag){

            }
            else{

            }

            node = node->next ;
        }

    }



};