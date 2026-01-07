#ifndef MEMORY_HPP
#define MEMORY_HPP
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

struct Memory{

    Block* head ;
    int Id = 0 ;
    
    Memory( int size ){
        head = new Block( 0 , size, 1 , 1 ,NULL  , NULL ) ;
        cout << "memory of size " << size << " created " << endl ;
    }

    void first_fit( int size ){
        
        bool found = 0 ;
        Block* node = head ;
        while( node != NULL && found == 0 ){

            if( node->Size >= size && node->flag == 1 ){
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

        if( found == 0 ){
            cout << "memory not available"  << endl ;
        }
    
    }

    void best_fit( int size ){
        Block *node = head ;
        Block* found = NULL ;

        while( node != NULL ){
            if( node->Size >= size && node->flag == 1 ){
                if( found == NULL ){
                    found = node ;
                }
                else{
                    if( found ->Size > node->Size ) found = node ;
                }
            }
            node = node->next ;
        }
        if( found == NULL ){
            cout << "memory not available"  << endl ;
        }
        else{
            node = found ;
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

    }

    void worst_fit( int size ){
        Block *node = head ;
        Block* found = NULL ;

        while( node != NULL ){
            if( node->Size >= size && node->flag == 1 ){
                if( found == NULL ){
                    found = node ;
                }
                else{
                    if( found ->Size < node->Size ) found = node ;
                }
            }
            node = node->next ;
        }
        if( found == NULL ){
            cout << "memory not available"  << endl ;
        }
        else{
            node = found ;
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

    }


    void print_memory(){
        Block* node = head ;
        while( node != NULL ){
            
            if( node->flag){
                cout << "Free memory from: " << node->startaddress << " to: " << node->startaddress + node->Size - 1 << endl ;
            }
            else{
                cout << "Memory alloted from: " << node->startaddress << " to: " << node->startaddress + node->Size - 1 << " to user with ID: " << node->Id << endl ; 
            }   

            node = node->next ;
        }

    }


    void free_memory( int id ){
        Block* node = head ;
        bool found = 0 ;

        while( node != NULL && found == 0 ){
            if( node->Id == id ){
                found = 1 ;
                node->flag = 1 ;
                Block* after = node->next ;
                Block* before = node->prev ;
                if( after != NULL && after->flag == 1 ){
                    node->next = after->next ;
                    node->Size += after->Size ;
                    if( after->next != NULL ) after->next->prev = node ;
                    delete after ;
                }
                if( before != NULL && before->flag == 1 ){
                    before->Size += node->Size ;
                    before->next = node->next ;
                    if( node->next != NULL ) node->next->prev = before ;
                    delete node ;
                    break ;
                }
            }
            node = node->next ;
        }

        if( found == 0 ){
            cout << "No memory block with Id: " << id << " found" << endl ;
        }

    }

    void stats(){

        int total_free = 0;
        int largest_free = 0;
        int total_memory = 0;
        Block* node = head;
        while(node != NULL)
        {
            if(node->flag) 
            {
                total_free += node->Size;
                if(node->Size > largest_free) largest_free = node->Size;
            }
            total_memory += node->Size;
            node = node->next ;
        }

        cout << "Total memory " << total_memory << endl ;
        cout << "Free memory " << total_free << endl ;
        cout << "Allocated memory " << total_memory - total_free << endl ;
        cout << "External Fragmentation " << ( 1 - ( largest_free / total_free ) ) * 100 << endl ; 
    
    }


};

#endif