/* written by klaus degner, ipoque GmbH
 * klaus.degner@ipoque.com
 */
/* OSDPI-START */
#ifndef __IPOQUE_API_INCLUDE_FILE__
#error CANNOT INCLUDE THIS .H FILE, INCLUDE IPQ_API.H
#endif

#ifndef __IPQ_MACROS_H__
#define __IPQ_MACROS_H__

#ifdef __cplusplus
extern "C" {
#endif

#if IPOQUE_MAX_SUPPORTED_PROTOCOLS >= 320

#    error "IPOQUE: Not more than 320 protocols supported!"

#elif IPOQUE_MAX_SUPPORTED_PROTOCOLS >= 256
    typedef struct ipoque_protocol_bitmask_struct {
        u64 bitmask[5];
    } ipoque_protocol_bitmask_struct_t;
#   define IPOQUE_PROTOCOL_BITMASK struct ipoque_protocol_bitmask_struct

#elif IPOQUE_MAX_SUPPORTED_PROTOCOLS >= 192

	typedef struct ipoque_protocol_bitmask_struct {
		u64 bitmask[4];
	} ipoque_protocol_bitmask_struct_t;
#   define IPOQUE_PROTOCOL_BITMASK struct ipoque_protocol_bitmask_struct

#elif IPOQUE_MAX_SUPPORTED_PROTOCOLS >= 128
	typedef struct ipoque_protocol_bitmask_struct {
		u64 bitmask[3];
	} ipoque_protocol_bitmask_struct_t;
#define IPOQUE_PROTOCOL_BITMASK struct ipoque_protocol_bitmask_struct

#elif IPOQUE_MAX_SUPPORTED_PROTOCOLS >= 64
	typedef struct ipoque_protocol_bitmask_struct {
		u64 bitmask[2];
	} ipoque_protocol_bitmask_struct_t;
#define IPOQUE_PROTOCOL_BITMASK struct ipoque_protocol_bitmask_struct

#else

#define IPOQUE_PROTOCOL_BITMASK u64

#endif


#if IPOQUE_MAX_SUPPORTED_PROTOCOLS < 64


#define IPOQUE_CONVERT_PROTOCOL_TO_BITMASK(p) ( ((IPOQUE_PROTOCOL_BITMASK)1) << (p) )
#define IPOQUE_SAVE_AS_BITMASK(bitmask,value) (bitmask)=(((IPOQUE_PROTOCOL_BITMASK)1)<<(value))
#define IPOQUE_BITMASK_COMPARE(a,b)	((a) & (b))
#define IPOQUE_BITMASK_MATCH(x,y)	((x) == (y))

// all protocols in b are also in a
#define IPOQUE_BITMASK_CONTAINS_BITMASK(a,b)	(((a) & (b)) == (b))
#define IPOQUE_BITMASK_NOT_CONTAINS_BITMASK(a,b) ((~a) & (b))

#define IPOQUE_BITMASK_ADD(a,b)	(a)|=(b)
#define IPOQUE_BITMASK_AND(a,b)	(a)&=(b)
#define IPOQUE_BITMASK_DEL(a,b) (a)=((a) & (~(b)))
#define IPOQUE_BITMASK_SET(a,b)	(a)=(b)
#define IPOQUE_PROTOCOL_BITMASK_NONE			((IPOQUE_PROTOCOL_BITMASK)0)

#define IPOQUE_ADD_PROTOCOL_TO_BITMASK(bmask,value) IPOQUE_BITMASK_ADD(bmask,IPOQUE_CONVERT_PROTOCOL_TO_BITMASK(value))
#define IPOQUE_DEL_PROTOCOL_FROM_BITMASK(bmask,value) IPOQUE_BITMASK_DEL(bmask,IPOQUE_CONVERT_PROTOCOL_TO_BITMASK(value))

#define IPOQUE_COMPARE_PROTOCOL_TO_BITMASK(bmask,value) IPOQUE_BITMASK_COMPARE(bmask,IPOQUE_CONVERT_PROTOCOL_TO_BITMASK(value))


#define IPOQUE_BITMASK_RESET(a)		(a) = 0
#define IPOQUE_BITMASK_SET_ALL(a)	(a) = ((IPOQUE_PROTOCOL_BITMASK)0xFFFFFFFFFFFFFFFFULL)


#define IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_STRING	"%llu"
#define IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_VALUE(bm)	(bm)
// you can use a printf(IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_STRING,

#define IPOQUE_BITMASK_IS_ZERO(a) ( (a) == 0 )

#define IPOQUE_BITMASK_CONTAINS_NEGATED_BITMASK(a,b) ((a) & ~(b) == ~(b))

#elif IPOQUE_MAX_SUPPORTED_PROTOCOLS < 128

#define IPOQUE_SAVE_AS_BITMASK(bmask,value)						\
	{										\
	(bmask).bitmask[0] = 0;								\
	(bmask).bitmask[1] = 0;								\
	(bmask).bitmask[(value) >> 6] = (((u64)1)<<((value) & 0x3F));			\
	}

#define IPOQUE_BITMASK_COMPARE(a,b)	(((a).bitmask[0]) & ((b).bitmask[0]) || ((a).bitmask[1]) & ((b).bitmask[1]))

#define IPOQUE_BITMASK_MATCH(a,b)	(((a).bitmask[0]) == ((b).bitmask[0]) && ((a).bitmask[1]) == ((b).bitmask[1]))

// all protocols in b are also in a
#define IPOQUE_BITMASK_CONTAINS_BITMASK(a,b)	((((a).bitmask[0] & (b).bitmask[0]) == (b).bitmask[0]) && (((a).bitmask[1] & (b).bitmask[1]) == (b).bitmask[1]))
#define IPOQUE_BITMASK_NOT_CONTAINS_BITMASK(a,b)  ((~((a).bitmask[0])) & ((b).bitmask[0]) || ((~(a).bitmask[1])) & ((b).bitmask[1]))


#define IPOQUE_BITMASK_ADD(a,b)		{(a).bitmask[0] |= (b).bitmask[0]; (a).bitmask[1] |= (b).bitmask[1];}
#define IPOQUE_BITMASK_AND(a,b)		{(a).bitmask[0] &= (b).bitmask[0]; (a).bitmask[1] &= (b).bitmask[1];}
#define IPOQUE_BITMASK_DEL(a,b) 	{(a).bitmask[0] = (a).bitmask[0] & (~((b).bitmask[0]));(a).bitmask[1] = (a).bitmask[1] & ( ~((b).bitmask[1]));}

#define IPOQUE_BITMASK_SET(a,b)		{(a).bitmask[0] = ((b).bitmask[0]); (a).bitmask[1] = (b).bitmask[1];}

#define IPOQUE_BITMASK_RESET(a)		{((a).bitmask[0]) = 0; ((a).bitmask[1]) = 0;}
#define IPOQUE_BITMASK_SET_ALL(a)		{((a).bitmask[0]) = 0xFFFFFFFFFFFFFFFFULL; ((a).bitmask[1]) = 0xFFFFFFFFFFFFFFFFULL;}

/* this is a very very tricky macro *g*,
 * the compiler will remove all shifts here if the protocol is static...
 */
#define IPOQUE_ADD_PROTOCOL_TO_BITMASK(bmask,value)					\
	{(bmask).bitmask[(value) >> 6] |= (((u64)1)<<((value) & 0x3F));}		\

#define IPOQUE_DEL_PROTOCOL_FROM_BITMASK(bmask,value)								\
	{(bmask).bitmask[(value) >> 6] = (bmask).bitmask[(value) >> 6] & (~(((u64)1)<<((value) & 0x3F)));}	\

#define IPOQUE_COMPARE_PROTOCOL_TO_BITMASK(bmask,value)					\
	((bmask).bitmask[(value) >> 6] & (((u64)1)<<((value) & 0x3F)))			\


#define IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_STRING	"%16llX , %llX"
#define IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_VALUE(bm)	(bm).bitmask[0] , (bm).bitmask[1]

#define IPOQUE_BITMASK_IS_ZERO(a) ( (a).bitmask[0] == 0 && (a).bitmask[1] == 0)

#define IPOQUE_BITMASK_CONTAINS_NEGATED_BITMASK(a,b) ((((a).bitmask[0] & ~(b).bitmask[0]) == ~(b).bitmask[0]) && (((a).bitmask[1] & ~(b).bitmask[1]) == ~(b).bitmask[1]))

#elif IPOQUE_MAX_SUPPORTED_PROTOCOLS < 192

#define IPOQUE_SAVE_AS_BITMASK(bmask,value)           \
  {                   \
  (bmask).bitmask[0] = 0;               \
  (bmask).bitmask[1] = 0;               \
  (bmask).bitmask[2] = 0;               \
  (bmask).bitmask[(value) >> 6] = (((u64)1)<<((value) & 0x3F));     \
}

#define IPOQUE_BITMASK_COMPARE(a,b) (((a).bitmask[0]) & ((b).bitmask[0]) || ((a).bitmask[1]) & ((b).bitmask[1]) || ((a).bitmask[2]) & ((b).bitmask[2]))

#define IPOQUE_BITMASK_MATCH(a,b) (((a).bitmask[0]) == ((b).bitmask[0]) && ((a).bitmask[1]) == ((b).bitmask[1]) && ((a).bitmask[2]) == ((b).bitmask[2]))

// all protocols in b are also in a
#define IPOQUE_BITMASK_CONTAINS_BITMASK(a,b)  ((((a).bitmask[0] & (b).bitmask[0]) == (b).bitmask[0]) && (((a).bitmask[1] & (b).bitmask[1]) == (b).bitmask[1]) && (((a).bitmask[2] & (b).bitmask[2]) == (b).bitmask[2]))
#define IPOQUE_BITMASK_NOT_CONTAINS_BITMASK(a,b)  ((~((a).bitmask[0])) & ((b).bitmask[0]) || ((~(a).bitmask[1])) & ((b).bitmask[1]) || ((~(a).bitmask[2])) & ((b).bitmask[2]))


#define IPOQUE_BITMASK_ADD(a,b)   {(a).bitmask[0] |= (b).bitmask[0]; (a).bitmask[1] |= (b).bitmask[1]; (a).bitmask[2] |= (b).bitmask[2];}
#define IPOQUE_BITMASK_AND(a,b)   {(a).bitmask[0] &= (b).bitmask[0]; (a).bitmask[1] &= (b).bitmask[1]; (a).bitmask[2] &= (b).bitmask[2];}
#define IPOQUE_BITMASK_DEL(a,b)   {(a).bitmask[0] = (a).bitmask[0] & (~((b).bitmask[0])); (a).bitmask[1] = (a).bitmask[1] & ( ~((b).bitmask[1])); (a).bitmask[2] = (a).bitmask[2] & (~((b).bitmask[2]));}

#define IPOQUE_BITMASK_SET(a,b)   {(a).bitmask[0] = ((b).bitmask[0]); (a).bitmask[1] = (b).bitmask[1]; (a).bitmask[2] = (b).bitmask[2];}

#define IPOQUE_BITMASK_RESET(a)   {((a).bitmask[0]) = 0; ((a).bitmask[1]) = 0; ((a).bitmask[2]) = 0;}
#define IPOQUE_BITMASK_SET_ALL(a)   {((a).bitmask[0]) = 0xFFFFFFFFFFFFFFFFULL; ((a).bitmask[1]) = 0xFFFFFFFFFFFFFFFFULL; ((a).bitmask[2]) = 0xFFFFFFFFFFFFFFFFULL;}

/* this is a very very tricky macro *g*,
  * the compiler will remove all shifts here if the protocol is static...
 */
#define IPOQUE_ADD_PROTOCOL_TO_BITMASK(bmask,value)         \
  {(bmask).bitmask[(value) >> 6] |= (((u64)1)<<((value) & 0x3F));}    \

#define IPOQUE_DEL_PROTOCOL_FROM_BITMASK(bmask,value)               \
  {(bmask).bitmask[(value) >> 6] = (bmask).bitmask[(value) >> 6] & (~(((u64)1)<<((value) & 0x3F)));}  \

#define IPOQUE_COMPARE_PROTOCOL_TO_BITMASK(bmask,value)         \
  ((bmask).bitmask[(value) >> 6] & (((u64)1)<<((value) & 0x3F)))      \


#define IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_STRING  "%llu , %llu , %llu"
#define IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_VALUE(bm) (bm).bitmask[0] , (bm).bitmask[1] , (bm).bitmask[2]

#define IPOQUE_BITMASK_IS_ZERO(a) ( (a).bitmask[0] == 0 && (a).bitmask[1] == 0 && (a).bitmask[2] == 0)

#define IPOQUE_BITMASK_CONTAINS_NEGATED_BITMASK(a,b) ((((a).bitmask[0] & ~(b).bitmask[0]) == ~(b).bitmask[0]) && (((a).bitmask[1] & ~(b).bitmask[1]) == ~(b).bitmask[1]) && (((a).bitmask[2] & ~(b).bitmask[2]) == ~(b).bitmask[2]))

#elif IPOQUE_MAX_SUPPORTED_PROTOCOLS < 256

#    define IPOQUE_SAVE_AS_BITMASK(bmask,value)	\
	{											\
		(bmask).bitmask[0] = 0;					\
		(bmask).bitmask[1] = 0;					\
		(bmask).bitmask[2] = 0;											\
		(bmask).bitmask[3] = 0;											\
		(bmask).bitmask[(value) >> 6] = (((u64)1)<<((value) & 0x3F));	\
	}

#    define IPOQUE_BITMASK_COMPARE(a,b) (((a).bitmask[0]) & ((b).bitmask[0]) || ((a).bitmask[1]) & ((b).bitmask[1]) || ((a).bitmask[2]) & ((b).bitmask[2]) || ((a).bitmask[3]) & ((b).bitmask[3]))

#    define IPOQUE_BITMASK_MATCH(a,b) (((a).bitmask[0]) == ((b).bitmask[0]) && ((a).bitmask[1]) == ((b).bitmask[1]) && ((a).bitmask[2]) == ((b).bitmask[2]) && ((a).bitmask[3]) == ((b).bitmask[3]))

// all protocols in b are also in a
#    define IPOQUE_BITMASK_CONTAINS_BITMASK(a,b)  ((((a).bitmask[0] & (b).bitmask[0]) == (b).bitmask[0]) && (((a).bitmask[1] & (b).bitmask[1]) == (b).bitmask[1]) && (((a).bitmask[2] & (b).bitmask[2]) == (b).bitmask[2]) && (((a).bitmask[3] & (b).bitmask[3]) == (b).bitmask[3]))
#    define IPOQUE_BITMASK_NOT_CONTAINS_BITMASK(a,b)  ((~((a).bitmask[0])) & ((b).bitmask[0]) || ((~(a).bitmask[1])) & ((b).bitmask[1]) || ((~(a).bitmask[2])) & ((b).bitmask[2]) || ((~(a).bitmask[3])) & ((b).bitmask[3]))

#    define IPOQUE_BITMASK_ADD(a,b)   {(a).bitmask[0] |= (b).bitmask[0]; (a).bitmask[1] |= (b).bitmask[1]; (a).bitmask[2] |= (b).bitmask[2]; (a).bitmask[3] |= (b).bitmask[3];}
#    define IPOQUE_BITMASK_AND(a,b)   {(a).bitmask[0] &= (b).bitmask[0]; (a).bitmask[1] &= (b).bitmask[1]; (a).bitmask[2] &= (b).bitmask[2]; (a).bitmask[3] &= (b).bitmask[3];}
#    define IPOQUE_BITMASK_DEL(a,b)   {(a).bitmask[0] &= ~((b).bitmask[0]); (a).bitmask[1] &=  ~((b).bitmask[1]); (a).bitmask[2] &= ~((b).bitmask[2]); (a).bitmask[3] &= ~((b).bitmask[3]);}

#    define IPOQUE_BITMASK_SET(a,b)   {(a).bitmask[0] = (b).bitmask[0]; (a).bitmask[1] = (b).bitmask[1]; (a).bitmask[2] = (b).bitmask[2]; (a).bitmask[3] = (b).bitmask[3];}

#    define IPOQUE_BITMASK_RESET(a)   {((a).bitmask[0]) = 0; ((a).bitmask[1]) = 0; ((a).bitmask[2]) = 0; ((a).bitmask[3]) = 0;}
#    define IPOQUE_BITMASK_SET_ALL(a)   {((a).bitmask[0]) = 0xFFFFFFFFFFFFFFFFULL; ((a).bitmask[1]) = 0xFFFFFFFFFFFFFFFFULL; ((a).bitmask[2]) = 0xFFFFFFFFFFFFFFFFULL; ((a).bitmask[3]) = 0xFFFFFFFFFFFFFFFFULL;}

/* this is a very very tricky macro *g*,
  * the compiler will remove all shifts here if the protocol is static...
 */
#    define IPOQUE_ADD_PROTOCOL_TO_BITMASK(bmask,value)				  \
	{(bmask).bitmask[(value) >> 6] |= (((u64)1)<<((value) & 0x3F));}  \

#    define IPOQUE_DEL_PROTOCOL_FROM_BITMASK(bmask,value)               \
	{(bmask).bitmask[(value) >> 6] &= ~(((u64)1)<<((value) & 0x3F));}	\

#    define IPOQUE_COMPARE_PROTOCOL_TO_BITMASK(bmask,value)         \
	((bmask).bitmask[(value) >> 6] & (((u64)1)<<((value) & 0x3F)))	\


#    define IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_STRING  "%llu , %llu , %llu, %llu"
#    define IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_VALUE(bm) (bm).bitmask[0] , (bm).bitmask[1] , (bm).bitmask[2] , (bm).bitmask[3]

#    define IPOQUE_BITMASK_IS_ZERO(a) ( (a).bitmask[0] == 0 && (a).bitmask[1] == 0 && (a).bitmask[2] == 0 && (a).bitmask[3] == 0)

#    define IPOQUE_BITMASK_CONTAINS_NEGATED_BITMASK(a,b) ((((a).bitmask[0] & ~(b).bitmask[0]) == ~(b).bitmask[0]) && (((a).bitmask[1] & ~(b).bitmask[1]) == ~(b).bitmask[1]) && (((a).bitmask[2] & ~(b).bitmask[2]) == ~(b).bitmask[2]) && (((a).bitmask[3] & ~(b).bitmask[3]) == ~(b).bitmask[3]))


#else /* <320 protocols */

#    define IPOQUE_SAVE_AS_BITMASK(bmask,value)                         \
    {                                                                   \
        (bmask).bitmask[0] = 0;                                         \
        (bmask).bitmask[1] = 0;                                         \
        (bmask).bitmask[2] = 0;                                         \
        (bmask).bitmask[3] = 0;                                         \
        (bmask).bitmask[4] = 0;											\
        (bmask).bitmask[(value) >> 6] = (((u64)1)<<((value) & 0x3F));	\
    }

#    define IPOQUE_BITMASK_COMPARE(a,b) (((a).bitmask[0]) & ((b).bitmask[0]) || \
                                         ((a).bitmask[1]) & ((b).bitmask[1]) || \
                                         ((a).bitmask[2]) & ((b).bitmask[2]) || \
                                         ((a).bitmask[3]) & ((b).bitmask[3]) || \
                                         ((a).bitmask[4]) & ((b).bitmask[4]))

#    define IPOQUE_BITMASK_MATCH(a,b) (((a).bitmask[0]) == ((b).bitmask[0]) && \
                                       ((a).bitmask[1]) == ((b).bitmask[1]) && \
                                       ((a).bitmask[2]) == ((b).bitmask[2]) && \
                                       ((a).bitmask[3]) == ((b).bitmask[3]) && \
                                       ((a).bitmask[4]) == ((b).bitmask[4]))

// all protocols in b are also in a
#    define IPOQUE_BITMASK_CONTAINS_BITMASK(a,b)  ((((a).bitmask[0] & (b).bitmask[0]) == (b).bitmask[0]) && \
                                                   (((a).bitmask[1] & (b).bitmask[1]) == (b).bitmask[1]) && \
                                                   (((a).bitmask[2] & (b).bitmask[2]) == (b).bitmask[2]) && \
                                                   (((a).bitmask[3] & (b).bitmask[3]) == (b).bitmask[3]) && \
                                                   (((a).bitmask[4] & (b).bitmask[4]) == (b).bitmask[4]))

#    define IPOQUE_BITMASK_NOT_CONTAINS_BITMASK(a,b)  ((~((a).bitmask[0])) & ((b).bitmask[0]) || \
                                                       (~((a).bitmask[1])) & ((b).bitmask[1]) || \
                                                       (~((a).bitmask[2])) & ((b).bitmask[2]) || \
                                                       (~((a).bitmask[3])) & ((b).bitmask[3]) || \
                                                       (~((a).bitmask[4])) & ((b).bitmask[4]))

#    define IPOQUE_BITMASK_ADD(a,b) { (a).bitmask[0] |= (b).bitmask[0]; \
                                      (a).bitmask[1] |= (b).bitmask[1]; \
                                      (a).bitmask[2] |= (b).bitmask[2]; \
                                      (a).bitmask[3] |= (b).bitmask[3]; \
                                      (a).bitmask[4] |= (b).bitmask[4]; }

#    define IPOQUE_BITMASK_AND(a,b) { (a).bitmask[0] &= (b).bitmask[0]; \
                                      (a).bitmask[1] &= (b).bitmask[1]; \
                                      (a).bitmask[2] &= (b).bitmask[2]; \
                                      (a).bitmask[3] &= (b).bitmask[3]; \
                                      (a).bitmask[4] &= (b).bitmask[4]; }

#    define IPOQUE_BITMASK_DEL(a,b) { (a).bitmask[0] &= ~((b).bitmask[0]); \
                                      (a).bitmask[1] &= ~((b).bitmask[1]); \
                                      (a).bitmask[2] &= ~((b).bitmask[2]); \
                                      (a).bitmask[3] &= ~((b).bitmask[3]); \
                                      (a).bitmask[4] &= ~((b).bitmask[4]); }

#    define IPOQUE_BITMASK_SET(a,b) { (a).bitmask[0] = (b).bitmask[0]; \
                                      (a).bitmask[1] = (b).bitmask[1]; \
                                      (a).bitmask[2] = (b).bitmask[2]; \
                                      (a).bitmask[3] = (b).bitmask[3]; \
                                      (a).bitmask[4] = (b).bitmask[4]; }

#    define IPOQUE_BITMASK_RESET(a) { ((a).bitmask[0]) = 0; ((a).bitmask[1]) = 0; ((a).bitmask[2]) = 0; \
                                      ((a).bitmask[3]) = 0; ((a).bitmask[4]) = 0; }

#    define IPOQUE_BITMASK_SET_ALL(a) { ((a).bitmask[0]) = 0xFFFFFFFFFFFFFFFFULL; \
                                        ((a).bitmask[1]) = 0xFFFFFFFFFFFFFFFFULL; \
                                        ((a).bitmask[2]) = 0xFFFFFFFFFFFFFFFFULL; \
                                        ((a).bitmask[3]) = 0xFFFFFFFFFFFFFFFFULL; \
                                        ((a).bitmask[4]) = 0xFFFFFFFFFFFFFFFFULL;}

/* this is a very very tricky macro *g*,
 * the compiler will remove all shifts here if the protocol is static...
 */
#    define IPOQUE_ADD_PROTOCOL_TO_BITMASK(bmask,value)				  \
    {(bmask).bitmask[(value) >> 6] |= (((u64)1)<<((value) & 0x3F));}  \

#    define IPOQUE_DEL_PROTOCOL_FROM_BITMASK(bmask,value)               \
    {(bmask).bitmask[(value) >> 6] &= ~(((u64)1)<<((value) & 0x3F));}	\

#    define IPOQUE_COMPARE_PROTOCOL_TO_BITMASK(bmask,value)         \
    ((bmask).bitmask[(value) >> 6] & (((u64)1)<<((value) & 0x3F)))	\


#    define IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_STRING  "%llu, %llu, %llu, %llu, %llu"
#    define IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_VALUE(bm) (bm).bitmask[0], (bm).bitmask[1], (bm).bitmask[2], \
                                                          (bm).bitmask[3], (bm).bitmask[4]

#    define IPOQUE_BITMASK_IS_ZERO(a) ((a).bitmask[0] == 0 && (a).bitmask[1] == 0 && (a).bitmask[2] == 0 && \
                                       (a).bitmask[3] == 0 && (a).bitmask[4] == 0)

#    define IPOQUE_BITMASK_CONTAINS_NEGATED_BITMASK(a,b) ((((a).bitmask[0] & ~(b).bitmask[0]) == ~(b).bitmask[0]) && \
                                                          (((a).bitmask[1] & ~(b).bitmask[1]) == ~(b).bitmask[1]) && \
                                                          (((a).bitmask[2] & ~(b).bitmask[2]) == ~(b).bitmask[2]) && \
                                                          (((a).bitmask[3] & ~(b).bitmask[3]) == ~(b).bitmask[3]) && \
                                                          (((a).bitmask[4] & ~(b).bitmask[4]) == ~(b).bitmask[4]))
#endif

#define IPQ_PARSE_PACKET_LINE_INFO(ipoque_struct,packet)                        \
                        if (packet->packet_lines_parsed_complete != 1) {        \
                                ipq_parse_packet_line_info(ipoque_struct);      \
                        }                                                       \

#define IPQ_PARSE_REQUEST_URL(ipoque_struct)												\
						if (ipoque_struct->packet.request_line_parsed_complete != 1) {		\
							ipq_parse_request_url(ipoque_struct);							\
						}																	\

/* OSDPI-END */

/* macros for user defined protocols */

#define IPOQUE_IS_USER_DEFINED_PROTOCOL(protocol_number) ((protocol_number) > IPOQUE_LAST_IMPLEMENTED_PROTOCOL)

#ifdef IPOQUE_PACE_API_MK1

	/* NOTE: This macro only works correctly if no CDP offset has been set */
#define IPOQUE_GET_USER_DEFINED_PROTOCOL_NUMBER(protocol_number) ((protocol_number) - IPOQUE_LAST_IMPLEMENTED_PROTOCOL)

#endif

/* OSDPI-START */
#ifdef __cplusplus
}
#endif
#endif
/* OSDPI-END */
