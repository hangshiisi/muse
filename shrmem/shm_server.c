#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ     27

typedef struct mz_record_t_
{
  int f1;
  int f2;
  char f[100];
} mz_record_t;

/* 
 * sequences of the fields: 
 * 1) maximum number of records (max_num) 
 * 2) header of data structure (doubly linked list) 
 *    above is fixed size, more fields can be added 
 * 3) bitmap for the records (array) 
 * 4) array of records 
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


int main ()
{
  char c;
  int shmid;
  key_t key;
  char *shm, *s;

  /*
   * We'll name our shared memory segment
   * "5678".
   */
  key = 5678;

  /*
   * Create the segment.
   */
  if ((shmid = shmget (key, SHMSZ, IPC_CREAT | 0666)) < 0)
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
  s = shm;

  for (c = 'a'; c <= 'z'; c++)
    *s++ = c;
  *s = NULL;

  /*
   * Finally, we wait until the other process 
   * changes the first character of our memory
   * to '*', indicating that it has read what 
   * we put there.
   */
  while (*shm != '*')
    sleep (1);

  exit (0);
}

