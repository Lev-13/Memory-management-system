#include <iostream>
#include <vector>
#include <deque>
#include "../cache/cache.hpp"
using namespace std ;

struct PageTableEntry
{   
    int frame_num = -1 ;
    bool valid = false ;
    int last_allocated = -1 ;
};

struct frame{

    bool occupied = 0 ;
    int page_num = -1 ;
    int data ;

};

class PageTable{
public:
    vector < PageTableEntry > table ;
    int page_size ;
    int num_pages ;

    PageTable( int mem_size , int pg_size ){

        page_size = pg_size ;
        num_pages = mem_size / pg_size ;
        table.resize( num_pages ) ;
    }



};


struct virtual_memory{

    int page_size ;
    int vmem_size ;

    int pmem_size ;
    int num_frames ;
    
    PageTable page_table ; 
    deque < int > lru_queue ;
    vector < frame > ram ;

    virtual_memory( int vmem , int pmem , int page )
    : page_table(vmem, page)
    {
        vmem_size = vmem ;
        pmem_size = pmem ;
        page_size = page ;
        num_frames = pmem_size / page_size ;
        ram.resize( num_frames ) ;
    }

    int translate(int virtual_address) {

        int vpn = virtual_address / page_size ;
        // vpn -> virtual page number
        int offset = virtual_address % page_size ;

        if (!page_table.table[vpn].valid) {
            return handle_page_fault( vpn , offset ) ; 
        }

        int f_num = page_table.table[vpn].frame_num ;

        for( auto it = lru_queue.begin() ; it != lru_queue.end() ; it++ ){
            
            if( *it == f_num ){
                lru_queue.erase( it );
                lru_queue.push_back( f_num ) ;
                break; 
            }

        }
        

        return (page_table.table[vpn].frame_num * page_size) + offset;

    } 

    int handle_page_fault( int vpn , int offset ){

        bool empty_frame = 0 ;

        int target_frame = -1 ;


        for( int i = 0 ; i < num_frames ; i++ ){
            if( ram [ i ].occupied == 0 ){
                target_frame = i ;
                empty_frame = 1 ;
            }
        }

        if( !empty_frame ){

            target_frame = lru_queue.front() ;
            lru_queue.pop_front() ;

            int target_frame_page_num = ram[ target_frame ].page_num ;
            page_table.table[ target_frame_page_num ].frame_num = -1 ;
            page_table.table[ target_frame_page_num ].valid = false ;


        }

        ram[ target_frame ].occupied = 1 ;
        ram[ target_frame ].page_num = vpn ;

        page_table.table[ vpn ].frame_num = target_frame ;
        page_table.table[ vpn ].valid = true ;

        lru_queue.push_back( target_frame ) ;

        return target_frame * page_size + offset ;
    }

    

};


