/* written by Magnus Bartsch, ipoque GmbH
 * magnus.bartsch@ipoque.com
 */

#ifndef __IPOQUE_API_INCLUDE_FILE__
#error CANNOT INCLUDE THIS .H FILE, INCLUDE IPQ_API.H
#endif

typedef void *(*pace_malloc_t)( unsigned long size );
typedef void (*pace_free_t)( void *ptr );

typedef void *(*pace_ext_malloc_t)( unsigned long size,
                                    void *user_ptr );
typedef void (*pace_ext_free_t)( void *ptr,
                                 void *user_ptr );

typedef void *(*pace_realloc_t)( void *ptr, unsigned long size,
                                 void *memory_userptr );

typedef void *(*pace2_malloc)( u64 size,
                                 int thread_ID,
                                 void *user_ptr,
                                 int scope );
typedef void (*pace2_free)( void *ptr,
                              int thread_ID,
                              void *user_ptr,
                              int scope );
typedef void *(*pace2_realloc)( void *ptr,
                                u64 size,
                                int thread_ID,
                                void *user_ptr,
                                int scope );

typedef void *(*pace2_dlopen)( const char *filename, int flag, void *userptr );
typedef void *(*pace2_dlsym)( void *handle, const char *symbol, void *userptr );
typedef int (*pace2_dlclose)( void *handle, void *userptr );

struct pace2_old_mem_interface_wrapper {
    pace_ext_malloc_t malloc_callback;
    pace_ext_free_t free_callback;
    void *callback_userptr;
};

struct pace2_new_mem_interface_wrapper {
    pace2_malloc malloc_callback;
    pace2_free free_callback;
    void *callback_userptr;
};
