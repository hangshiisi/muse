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


typedef unsigned char* bitmap_t;

typedef struct mz_record_t_
{
  int f1;
  int f2;
  char f[100];
} mz_record_t;

/* 
 * layout of the fields: 
 * 1) array of records 
 *    below is fixed size, more fields can be added 
 * 2) maximum number of records (max_num) 
 * 3) header of data structure (doubly linked list) 
 * 4) bitmap for the records (array) 
 */

typedef struct mz_shr_data_hdr_
{
  void *next, *prev;		//replace it with list_head later 
  unsigned int max_num;		//max of records 
} mz_shr_data_hdr_t;

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

