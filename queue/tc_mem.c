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
#include <signal.h> 


#include "tc_mem.h" 


static mz_mem_store_handle_t *g_tc_test_hdl = NULL; 


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
    // need to have a way to detach shared memory 
    assert(handle); 
    if (shmdt(handle->mem_start) == -1) { 
        perror("error in detach memory"); 
        return -1; 
    } 

    if (shmctl(handle->shm_id, IPC_RMID, 0) == -1) { 
        perror("error in free memory"); 
        return -1; 
    } 
 
    return 0; 
} 

void *
tc_alloc_memory_record(mz_mem_store_handle_t *handle) 
{
    bitmap_t bm;
    int i;
    unsigned *start = NULL; 

    assert(handle); 
    bm = handle->bitmap_start;

    //    printf("nm address is %p %p \n", bm, 
    //       handle->mem_start);
    for (i = 0; i < handle->max_num; i++) {
        if (get_bitmap(bm, i) == 0) {
            set_bitmap(bm, i);
            // printf("return nodes at %d \n", i);
            
            start = handle->mem_start + sizeof(mz_record_t) * i;
            bzero(start, sizeof(mz_record_t)); 
            return start; 
        }
    }

    return start; 
} 

mz_record_t *
tc_get_memory_record_by_index(mz_mem_store_handle_t *handle, int index) 
{
    bitmap_t bm;

    assert(handle); 
    bm = handle->bitmap_start;
    //printf("nm address is %p %p \n", bm, 
    //       handle->mem_start);

    if (get_bitmap(bm, index) != 0) {
        // printf("retrieve nodes at %d \n", index);
        return handle->mem_start + sizeof(mz_record_t) * index;
    }

    return NULL; 
} 

mz_record_t *
tc_get_memory_record_by_rule_num(mz_mem_store_handle_t *handle, int rule_num) 
{

    struct list_head *fo_list, *iter; 
    mz_record_t *node = NULL; 

    fo_list = tc_get_mem_head(handle); 

    __list_for_each(iter, fo_list) { 
        node = list_entry(iter, mz_record_t, list_member); 
        assert(node != NULL); 
        if (node->rule_num == rule_num) { 
            return node; 
        } 
    } 

  return node; 
}



int tc_walk_all_record(mz_mem_store_handle_t *handle, tc_walk_callback cb, 
                       void *data)
{ 
    struct list_head *fo_list, *iter; 
    mz_record_t *node = NULL; 
    int rc = 0; 

    fo_list = tc_get_mem_head(handle); 

    __list_for_each(iter, fo_list) { 
        node = list_entry(iter, mz_record_t, list_member); 
        assert(node != NULL); 
        
        if (cb) { 
            rc = cb(node, data); 
            if (rc != 0) { 
                 break; 
            }
        }
    } 

    return rc; 
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


int 
tc_attach_fo_to_record(mz_mem_store_handle_t *handle, 
                       mz_record_t * node, 
                       mz_fo_enum_e fo_type, 
                       void *fo_data, 
                       unsigned int len)
{
    if (handle == NULL || node == NULL) { 
        return -1; //invalid argument 
    }  

    if (len != FO_DATA_SIZE) { 
        return -1; //invalid argument 
    }

    memcpy(&(node->fo_data[fo_type]), fo_data, FO_DATA_SIZE); 

    return 0; 
}

void *
tc_get_fo_from_record(mz_mem_store_handle_t *handle, 
                      mz_record_t *node, 
                      mz_fo_enum_e fo_type)
{ 

    if (handle == NULL || node == NULL) { 
        return NULL; //invalid argument 
    }  

    return &(node->fo_data[fo_type]); 
}

int 
tc_detach_fo_from_record(mz_mem_store_handle_t *handle, 
                         mz_record_t * node, 
                         mz_fo_enum_e fo_type)
{ 
    if (handle == NULL || node == NULL) { 
        return -1; //invalid argument 
    }  

    memset(&(node->fo_data[fo_type]), 0, FO_DATA_SIZE); 

    return 0; 
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


static void 
tc_sig_handler(int sig) 
{ 
     printf("Got signal %d \n", sig); 
     if (g_tc_test_hdl) { 
         printf("Cleaning up tc memory store \n"); 
         tc_destroy_memory_store(g_tc_test_hdl); 
     }

     exit(EXIT_SUCCESS); 
}

/* below function is test codes 
 * to show function usages 
 */ 
int tc_mem_test ()
{
    int shmid;
    key_t key;
    char *shm;
    int i = 0; 
 
    unsigned int max_num = 1024; 
    mz_record_t *node = NULL; 
    mz_mem_store_handle_t hdl = {0} ; 
    struct list_head *fo_list, *iter;  

    g_tc_test_hdl = &hdl; 
    if (signal(SIGINT, tc_sig_handler) == SIG_ERR) { 
        perror("Error setting signal handler"); 
        exit(-1); 
    }


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
  
    fo_list = tc_get_mem_head(&hdl); 
   
  printf("setting deadbeeft %d \n", hdl.max_num); 

  for (i = 0; i < max_num; i++) { 
      node = tc_alloc_memory_record(&hdl); 
      assert(node != NULL); 
      node->rule_num = i; 
      node->queue_num = i + 1;    
      node->app_info = i + 2;    
      INIT_LIST_HEAD(&node->list_member);
      list_add(&node->list_member, fo_list);    
  } 

  node = tc_alloc_memory_record(&hdl); 
  assert(node == NULL); 
 
  for (i = 0; i < max_num; i++) { 
      node = tc_get_memory_record_by_index(&hdl, i); 
      assert(node != NULL); 
      assert(node->rule_num == i); 
      assert(node->queue_num == i + 1);    
      assert(node->app_info == i + 2);    
  } 

  
  __list_for_each(iter, fo_list) { 
      node = list_entry(iter, mz_record_t, list_member); 
      assert(node != NULL); 
      assert(node->queue_num == node->rule_num + 1); 
      assert(node->app_info == node->rule_num + 2);   
  } 


  /*
   * Finally, we wait until the other process 
   * changes the first character of our memory
   * to '*', indicating that it has read what 
   * we put there.
   */
  while (hdl.max_num !=0) { 
      printf("sleep waiting for max_num to be cleared\n"); 
      sleep (5);
  } 

  printf("max is set to 0 right now, all done\n"); 
  tc_destroy_memory_store(&hdl); 

  exit (0);
}

