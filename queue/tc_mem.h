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

typedef enum { 
    TC_FO_ENUM_MUSE    = 0, 
    TC_FO_ENUM_FW      = 1, 
    TC_FO_ENUM_OPERA   = 2, 
    TC_FO_ENUM_OPENWRT = 3, 
    TC_FO_ENUM_QOS     = 4, 
    TC_FO_ENUM_MAX     = 5, 
} mz_fo_enum_e; 

#define FO_NUM                  TC_FO_ENUM_MAX
#define FO_DATA_SIZE            32

typedef enum { 
    MZ_TC_MEM_MODE_RO = 0, 
    MZ_TC_MEM_MODE_RW = 1, 
} mz_tc_mem_mode_e; 

typedef unsigned char* bitmap_t;

typedef struct mz_fo_data_t_ { 
    unsigned char fo_data[FO_DATA_SIZE]; 
} mz_fo_data_t;  

typedef struct mz_record_t_
{
    struct list_head list_member;

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

    unsigned char *mem_start; // start of shared memory 
    unsigned char *data_start; //start of recrord data
    unsigned char *header_start; //start of meta data
    unsigned char *bitmap_start; //start of bitmap  

} mz_shr_data_hdr_t;

typedef struct mz_mem_store_handle_ { 
    int max_num; 	//from user, max number of records 
    
    void *mem_start; // start of shared memory 
    void *data_start; //start of recrord data
    void *header_start; //start of meta data
    void *bitmap_start; //start of bitmap  

    int shm_id; //shared memory id 
    int mem_size; //size of shared memory 
    key_t key; //key for this shared memory 
} mz_mem_store_handle_t; 


/* 
 * TC memory API 
 */ 

 /* Server Specific API */ 
int tc_create_memory_store(mz_mem_store_handle_t *handle, 
                           int max_num, 
                           key_t key); 

int tc_destroy_memory_store(mz_mem_store_handle_t *handle); 


void *tc_alloc_memory_record(mz_mem_store_handle_t *handle); 

void tc_free_memory_record(mz_mem_store_handle_t *handle, 
                           void *node); 
/* Rule API */
int tc_attach_fo_to_record(mz_mem_store_handle_t *handle, 
                           mz_record_t *node, 
                           mz_fo_enum_e fo_type, 
                           void *fo_data, 
                           unsigned int len); 

void *tc_get_fo_from_record(mz_mem_store_handle_t *handle, 
                            mz_record_t *node, 
                            mz_fo_enum_e fo_type); 

int tc_detach_fo_from_record(mz_mem_store_handle_t *handle, 
                             mz_record_t *node, 
                             mz_fo_enum_e fo_type); 



/* Server or Client API */ 
struct list_head *tc_get_mem_head(mz_mem_store_handle_t *handle); 

mz_record_t *tc_get_memory_record_by_index(mz_mem_store_handle_t *handle, 
                                           int index);

mz_record_t *tc_get_memory_record_by_rule_num(mz_mem_store_handle_t *handle, 
                                              int rule_num);

typedef int (*tc_walk_callback)(mz_record_t *ndoe, void *data) ; 


int tc_walk_all_record(mz_mem_store_handle_t *handle, tc_walk_callback cb, 
                       void *data); 


/* Client Specific API */ 
int tc_open_memory_store(mz_mem_store_handle_t *handle, 
                         key_t key); 

int tc_close_memory_store(mz_mem_store_handle_t *handle, 
                          key_t key); 



#endif 

