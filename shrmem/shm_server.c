#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h> 
#include <unistd.h> 

// #define SHMSZ     27

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

unsigned int
get_size_shr_mem_total (int max_num)
{
  unsigned int total = 0;

  total += max_num * sizeof (mz_record_t);

  total += sizeof (mz_shr_data_hdr_t);

  total += (max_num + 7) / sizeof (unsigned char);

  return total;
}

unsigned char * 
get_start_shr_mem_header(unsigned char *shr_mem, 
                         unsigned int max_num) { 
    unsigned char *start = shr_mem; 

    start += max_num * sizeof (mz_record_t);

    return start;
} 

void set_bitmap(bitmap_t b, int i) {
    b[i / 8] |= 1 << (i & 7);
}

void unset_bitmap(bitmap_t b, int i) {
    b[i / 8] &= ~(1 << (i & 7));
}

int get_bitmap(bitmap_t b, int i) {
    return b[i / 8] & (1 << (i & 7)) ? 1 : 0;
}

bitmap_t get_start_bitmap(unsigned char *shr_mem, 
                          unsigned int max_num) {
    unsigned char *start = shr_mem; 

    start += max_num * sizeof (mz_record_t);
    start += sizeof (mz_shr_data_hdr_t);

    return start;
}

/* 
 * better to encapsulate details of max_num 
 */ 
void *alloc_mz_node(unsigned char *shr_mem, 
                    unsigned int max_num) { 
    bitmap_t bm; 
    int i; 
    
    bm = get_start_bitmap(shr_mem, max_num); 
    for (i = 0; i < max_num; i++) { 
	if (get_bitmap(bm, i) == 0) { 
            set_bitmap(bm, i); 
            return shr_mem + sizeof(mz_record_t) * (i - 1); 
        } 
    } 

    return NULL; 
}

void free_mz_node(unsigned char *shr_mem, 
                  unsigned int max_num, 
                  void *node) { 
    bitmap_t bm; 
    int i; 
    
    bm = get_start_bitmap(shr_mem, max_num); 
    i = ((unsigned char *)node - shr_mem)/sizeof(mz_record_t); 

    unset_bitmap(bm, i); 

    return; 
}  

int main ()
{
  char c;
  int shmid;
  key_t key;
  char *shm;
  
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
  hdr = (mz_shr_data_hdr_t *)get_start_shr_mem_header(shm, max_num); 
  assert(hdr); 

  hdr->max_num = max_num; 
  hdr->next = (void *) 0xDEAD; 
  hdr->prev = (void *) 0xBEEF; 

  node = (mz_record_t *)shm;     
  for (int i = 0; i < max_num; i++) { 
      node[i].f1 = i; 
      node[i].f2 = i + 1; 
  } 


  /*
   * Finally, we wait until the other process 
   * changes the first character of our memory
   * to '*', indicating that it has read what 
   * we put there.
   */
  while (hdr->max_num !=0)
    sleep (1);

  exit (0);
}

