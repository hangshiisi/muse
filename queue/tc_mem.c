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

/* 
 * better to encapsulate details of max_num 
 */ 
void *alloc_mz_node(unsigned char *shr_mem, 
                    unsigned int max_num) 
{ 
    bitmap_t bm; 
    int i; 
    
    bm = get_start_bitmap(shr_mem, max_num); 
    printf("nm address is %p %p \n", bm, shr_mem); 
    for (i = 0; i < max_num; i++) { 
	if (get_bitmap(bm, i) == 0) { 
            set_bitmap(bm, i); 
            printf("return nodes at %d \n", i); 
            return shr_mem + sizeof(mz_record_t) * i; 
        } 
    } 

    return NULL; 
}

void free_mz_node(unsigned char *shr_mem, 
                  unsigned int max_num, 
                  void *node) 
{ 
    bitmap_t bm; 
    int i; 
    
    bm = get_start_bitmap(shr_mem, max_num); 
    i = ((unsigned char *)node - shr_mem)/sizeof(mz_record_t); 

    unset_bitmap(bm, i); 

    return; 
}  

int tc_mem ()
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
   
  mem_size = get_size_shr_mem_total(max_num); 

  /*
   * We'll name our shared memory segment
   * "5678".
   */
  key = 5678;
  
  /*
   * Create the segment.
   */
  if ((shmid = shmget (key, mem_size, IPC_CREAT | 0666)) < 0)
    {
      perror ("shmget");
      exit (1);
    }

  /*
   * Now we attach the segment to our data space.
   */
  if ((shm = shmat (shmid, NULL, 0)) == (char *) -1)
    {
      perror ("shmat");
      exit (1);
    }

  /*
   * Now put some things into the memory for the
   * other process to read.
   */
  memset(shm, 0, mem_size);
  bzero(shm, mem_size); 

  /*  
  unsigned char *ch = (unsigned char *)shm; 
  for (int i = 0; i < mem_size; i++) { 
       printf("i value is %d mem_size %d %d\n", 
              i, mem_size, ch[i]); 
       assert(ch[i] == (unsigned char)0); 
  } */ 
            
  hdr = (mz_shr_data_hdr_t *)get_start_shr_mem_header(shm, max_num); 
  assert(hdr); 


  hdr->max_num = max_num; 
  INIT_LIST_HEAD(&hdr->head);   
  printf("setting deadbeeft %p mem_size %d \n", 
         hdr, mem_size); 

  node = (mz_record_t *)shm;     
  for (i = 0; i < max_num; i++) { 
      printf("setting at %p \n", &node[i]); 
      //node[i].f1 = i; 
      //node[i].f2 = i + 1; 
  } 

  for (i = 0; i < max_num; i++) { 
      node = alloc_mz_node(shm, max_num); 
      assert(node != NULL); 
      //assert(node->f1 == i); 
      //assert(node->f2 == i + 1);    
  } 

  node = alloc_mz_node(shm, max_num); 
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

int 
tc_create_memory_store(mz_mem_store_handle_t *handle, 
                           int max_num)
{ 
 
    return 0; 
}  

int 
tc_destroy_memory_store(mz_mem_store_handle_t *handle) 
{ 

    return 0; 
} 

void *tc_alloc_memory_record(mz_mem_store_handle_t *handle) 
{ 

    return NULL; 
} 


void tc_free_memory_record(mz_mem_store_handle_t *handle, 
                           void *node) 
{ 
    return; 
} 



