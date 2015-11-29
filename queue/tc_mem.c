#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h> 
#include <unistd.h> 
#include <memory.h> 

#include "tc_mem.h" 

static void 
set_bitmap(bitmap_t b, int i) 
{
    b[i / 8] |= 1 << (i & 7);
}

static void 
unset_bitmap(bitmap_t b, int i) 
{
    b[i / 8] &= ~(1 << (i & 7));
}

static int 
get_bitmap(bitmap_t b, int i) 
{
    return b[i / 8] & (1 << (i & 7)) ? 1 : 0;
}

static bitmap_t 
get_start_bitmap(unsigned char *shr_mem, 
                 unsigned int max_num) 
{
    unsigned char *start = shr_mem; 

    start += max_num * sizeof (mz_record_t);
    start += sizeof (mz_shr_data_hdr_t);

    return start;
}

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

int 
tc_create_memory_store(mz_mem_store_handle_t *handle, 
                       int max_num, 
                       key_t key)
{ 
    int shmid;
    char *shm;
    unsigned int mem_size;
    mz_shr_data_hdr_t *hdr; 

    assert(handle); 
    mem_size = get_size_shr_mem_total(max_num);
    printf("create memory size %d \n", mem_size); 

    /*
     * Create the segment.
     */
    if ((shmid = shmget (key, mem_size, 
                         IPC_CREAT | 0666)) < 0) {
        perror ("shmget");
        exit (1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat (shmid, NULL, 0)) == (char *) -1) {
        perror ("shmat");
        exit (1);
    }

    bzero(shm, mem_size);
  
    handle->max_num = max_num; 
    handle->shm_id = shmid; 
    handle->key = key; 
    handle->mem_size = mem_size; 

    handle->mem_start = shm; 
    handle->data_start = shm; 
    handle->header_start = get_start_shr_mem_header(shm, 
                                  max_num); 
    handle->bitmap_start = get_start_bitmap(shm, max_num); 

    hdr = (mz_shr_data_hdr_t *)handle->header_start; 

    hdr->max_num = max_num; 
    INIT_LIST_HEAD(&hdr->head);   
    
    return 0; 
}  

int 
tc_destroy_memory_store(mz_mem_store_handle_t *handle) 
{
    // need to have a way to detash shared memory 
    // TBD 

    return 0; 
} 

void *tc_alloc_memory_record(mz_mem_store_handle_t *handle) 
{
    bitmap_t bm;
    int i;

    assert(handle); 
    bm = handle->bitmap_start;
    printf("nm address is %p %p \n", bm, 
           handle->mem_start);
    for (i = 0; i < handle->max_num; i++) {
        if (get_bitmap(bm, i) == 0) {
            set_bitmap(bm, i);
            printf("return nodes at %d \n", i);
            return handle->mem_start + sizeof(mz_record_t) * i;
        }
    }

    return NULL; 
} 


void 
tc_free_memory_record(mz_mem_store_handle_t *handle, 
                      void *node) 
{ 
    bitmap_t bm;
    int i;

    assert(handle); 
    bm = handle->bitmap_start;
    i = ((unsigned char *)node - (unsigned char *) 
         handle->mem_start) / sizeof(mz_record_t);

    //TODO, remove from the list 
    unset_bitmap(bm, i);
 
    return; 
} 

struct list_head *
tc_get_mem_head(mz_mem_store_handle_t *handle) 
{
    struct list_head *hdr = NULL; 
    mz_shr_data_hdr_t *data_hdr = NULL; 
 
    if (handle) { 
        data_hdr = handle->header_start; 
        hdr = &(data_hdr->head);
    } 
    
    return hdr;          
} 

int tc_mem_test ()
{
  char c;
  int shmid;
  key_t key;
  char *shm;
  int i = 0; 
 
  unsigned int max_num = 1024; 
  unsigned int mem_size; 
  mz_shr_data_hdr_t *hdr; 
  mz_record_t *node; 
  mz_mem_store_handle_t hdl; 
   

  /*
   * We'll name our shared memory segment
   * "5678".
   */
  key = 5678;
  memset(&hdl, 0, sizeof(hdl)); 

  if (0 != tc_create_memory_store(&hdl, 
                                  max_num, 
                                  key)) { 
      perror("Error in creating mem store. \n"); 
      exit(-1); 
  } 

  assert(hdl.max_num == max_num); 
  assert(hdl.key == key); 
        
  printf("setting deadbeeft %d mem_size %d \n", 
         hdl.max_num, mem_size); 

  node = (mz_record_t *)shm;     
  for (i = 0; i < max_num; i++) { 
      printf("setting at %p \n", &node[i]); 
      //node[i].f1 = i; 
      //node[i].f2 = i + 1; 
  } 

  for (i = 0; i < max_num; i++) { 
      node = tc_alloc_memory_record(&hdl); 
      assert(node != NULL); 
      //assert(node->f1 == i); 
      //assert(node->f2 == i + 1);    
  } 

  node = tc_alloc_memory_record(&hdl); 
  assert(node == NULL); 
 
  /*
   * Finally, we wait until the other process 
   * changes the first character of our memory
   * to '*', indicating that it has read what 
   * we put there.
   */
  while (hdr->max_num !=0) { 
      printf("sleep 5 seconds more \n"); 
      sleep (5);
  } 

  printf("max is set to 0 right now, all done\n"); 

  exit (0);
}

