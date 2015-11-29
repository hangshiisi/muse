#define _GNU_SOURCE

#ifndef TC_MEM_HS_
#define TC_MEM_HS_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h> 
#include <unistd.h> 
#include <memory.h> 

#include "list.h" 

#define FO_NUM 			5 
#define FO_DATA_SIZE 		32
typedef unsigned char* bitmap_t;

typedef struct mz_fo_data_t_ { 
    unsigned char fo_data[FO_DATA_SIZE]; 
} mz_fo_data_t;  

typedef struct mz_record_t_
{
    int rule_num; //from orchestrator
    int queue_num;//from orchestrator, and L3/L4 classification 
    int app_info; // from DPI 
    mz_fo_data_t fo_data[FO_NUM]; //feature opaque data 
} mz_record_t;

/* 
 * layout of the fields: 
 * 1) array of records 
 *       mz_record_t * max_num 
 *    below is fixed size, more fields can be added 
 * 2) maximum number of records (max_num) 
 * 3) header of data structure (doubly linked list) 
 * 4) bitmap for the records (array) 
 */
typedef struct mz_shr_data_hdr_
{
    struct list_head head;		//list head to keep all nodes  
    unsigned int max_num;		//max of records 
} mz_shr_data_hdr_t;

typedef struct mz_mem_store_handle_ { 
    int max_num; 	//from user, max number of records 
    
    unsigned char *mem_start; // start of shared memory 
    unsigned char *data_start; //start of recrord data
    unsigned char *header_start; //start of meta data
    unsigned char *bitmap_start; //start of bitmap  
} mz_mem_store_handle_t; 

int tc_create_memory_store(mz_mem_store_handle_t *handle, 
                           int max_num); 

int tc_destroy_memory_store(mz_mem_store_handle_t *handle); 

void *tc_alloc_memory_record(mz_mem_store_handle_t *handle); 
void tc_free_memory_record(mz_mem_store_handle_t *handle, 
                           void *node); 


static unsigned int
get_size_shr_mem_total (int max_num)
{
  unsigned int total = 0;

  total += max_num * sizeof (mz_record_t);

  total += sizeof (mz_shr_data_hdr_t);

  total += (max_num + 7) / sizeof (unsigned char);

  return total;
}

static unsigned char * 
get_start_shr_mem_header(unsigned char *shr_mem, 
                         unsigned int max_num) { 
    unsigned char *start = shr_mem; 

    start += max_num * sizeof (mz_record_t);

    return start;
} 

#endif 

