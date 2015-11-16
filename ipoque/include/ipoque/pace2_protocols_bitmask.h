/********************************************************************************/
/**
 ** \file       pace2_protocols_bitmask.h
 ** \brief      PACE 2 protocol bitmask definition.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_PROTOCOLS_BITMASK_H
#define PACE2_PROTOCOLS_BITMASK_H

/* Includes *********************************************************************/
#include "pace2_protocols.h"

/* Public Types *****************************************************************/
#define PACE2_PROTOCOLS_BITMASK_LENGTH 4

/**
 * @brief Structure contains the bitmask representation of PACE 2 protocols
 */
typedef struct {
    u64 bitmask[PACE2_PROTOCOLS_BITMASK_LENGTH]; /**!< Array to hold the protocol bitmask. */
} PACE2_protocols_bitmask;

/**
 * @brief Union combining the protocol bitmask and the structural representation of protocols.
 */
typedef union {
    PACE2_protocols_struct protocols; /**!< Structural representation of protocols */
    PACE2_protocols_bitmask bitmask; /**!< Bitmask representing protocols. */
} PACE2_protocols_mask;


/* Public Macros ****************************************************************/

/**
 * @brief Convert a given 8 bit value to a bitmask.
 *
 * @param[out]  bmask   Destination bitmask which is used to store the value.
 *                      Has to a variable of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 * @param[in]   value   8 bit value which will be converted to a bitmask.
 */
#define PACE2_PROTOCOLS_SAVE_AS_BITMASK(bmask,value)                \
{                                                                   \
    (bmask).bitmask[0] = 0;                                         \
    (bmask).bitmask[1] = 0;                                         \
    (bmask).bitmask[2] = 0;                                         \
    (bmask).bitmask[3] = 0;                                         \
    (bmask).bitmask[(value) >> 6] = (((u64)1)<<((value) & 0x3F));   \
}

/**
 * @brief Compares to bitmasks and returns 1 if they suit each other.
 *
 * @param[in]   a   First bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 * @param[in]   b   Second bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 */
#define PACE2_PROTOCOLS_BITMASK_MATCH(a,b) (((a).bitmask[0]) == ((b).bitmask[0]) &&     \
                                            ((a).bitmask[1]) == ((b).bitmask[1]) &&     \
                                            ((a).bitmask[2]) == ((b).bitmask[2]) &&     \
                                            ((a).bitmask[3]) == ((b).bitmask[3]))

/**
 * @brief Checks if the bitmask a contains the bitmask b.
 *
 * @param[in]   a   The bitmask which is checked whether it contains another bitmask.
 *                  Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 * @param[in]   b   The bitmask which is used to check whether another bitmask contains it.
 *                  Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 */
#define PACE2_PROTOCOLS_BITMASK_CONTAINS_BITMASK(a,b)  ((((a).bitmask[0] & (b).bitmask[0]) == (b).bitmask[0]) &&    \
                                                        (((a).bitmask[1] & (b).bitmask[1]) == (b).bitmask[1]) &&    \
                                                        (((a).bitmask[2] & (b).bitmask[2]) == (b).bitmask[2]) &&    \
                                                        (((a).bitmask[3] & (b).bitmask[3]) == (b).bitmask[3]))

/**
 * @brief Checks if the bitmask a does not contain the bitmask b.
 *
 * @param[in]   a   The bitmask which is checked whether it does not contain another bitmask.
 *                  Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 * @param[in]   b   The bitmask which is used to check whether another bitmask does not contain it.
 *                  Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 */
#define PACE2_PROTOCOLS_BITMASK_NOT_CONTAINS_BITMASK(a,b)  ((~((a).bitmask[0])) & ((b).bitmask[0]) ||   \
                                                            (~((a).bitmask[1])) & ((b).bitmask[1]) ||   \
                                                            (~((a).bitmask[2])) & ((b).bitmask[2]) ||   \
                                                            (~((a).bitmask[3])) & ((b).bitmask[3]))

/**
 * @brief Adds a given bitmask b to the bitmask a. Uses a logical or to merge the bitmasks.
 *
 * @param[in]   a   Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 * @param[in]   b   Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 */
#define PACE2_PROTOCOLS_BITMASK_ADD(a,b)    \
{                                           \
    (a).bitmask[0] |= (b).bitmask[0];       \
    (a).bitmask[1] |= (b).bitmask[1];       \
    (a).bitmask[2] |= (b).bitmask[2];       \
    (a).bitmask[3] |= (b).bitmask[3];       \
}

/**
 * @brief Uses a logical and to merge the bitmasks a and b. The result is stored in a.
 *
 * @param[in]   a   Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 * @param[in]   b   Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 */
#define PACE2_PROTOCOLS_BITMASK_AND(a,b)    \
{                                           \
    (a).bitmask[0] &= (b).bitmask[0];       \
    (a).bitmask[1] &= (b).bitmask[1];       \
    (a).bitmask[2] &= (b).bitmask[2];       \
    (a).bitmask[3] &= (b).bitmask[3];       \
}

/**
 * @brief Deletes a given bitmask b from the bitmask a.
 *
 * @param[in]   a   Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 * @param[in]   b   Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 */
#define PACE2_PROTOCOLS_BITMASK_DEL(a,b)    \
{                                           \
    (a).bitmask[0] &= ~((b).bitmask[0]);    \
    (a).bitmask[1] &= ~((b).bitmask[1]);    \
    (a).bitmask[2] &= ~((b).bitmask[2]);    \
    (a).bitmask[3] &= ~((b).bitmask[3]);    \
}

/**
 * @brief Copies the value of bitmask b to bitmask a.
 *
 * @param[in]   a   Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 * @param[in]   b   Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 */
#define PACE2_PROTOCOLS_BITMASK_SET(a,b)    \
{                                           \
    (a).bitmask[0] = (b).bitmask[0];        \
    (a).bitmask[1] = (b).bitmask[1];        \
    (a).bitmask[2] = (b).bitmask[2];        \
    (a).bitmask[3] = (b).bitmask[3];        \
}

/**
 * @brief Resets the value bitmask a to zero.
 *
 * @param[in]   a   Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 */
#define PACE2_PROTOCOLS_BITMASK_RESET(a)    \
{                                           \
    ((a).bitmask[0]) = 0;                   \
    ((a).bitmask[1]) = 0;                   \
    ((a).bitmask[2]) = 0;                   \
    ((a).bitmask[3]) = 0;                   \
}

/**
 * @brief Sets all bits of bitmask a to 1.
 *
 * @param[in]   a   Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 */
#define PACE2_PROTOCOLS_BITMASK_SET_ALL(a)      \
{                                               \
    ((a).bitmask[0]) = 0xFFFFFFFFFFFFFFFFULL;   \
    ((a).bitmask[1]) = 0xFFFFFFFFFFFFFFFFULL;   \
    ((a).bitmask[2]) = 0xFFFFFFFFFFFFFFFFULL;   \
    ((a).bitmask[3]) = 0xFFFFFFFFFFFFFFFFULL;   \
}

/**
 * @brief Adds a given 8 bit value to a bitmask.
 *
 * @param[out]  bmask   Destination bitmask to which the value has to be added.
 *                      Has to a variable of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 * @param[in]   value   8 bit value which will be added to the bitmask.
 */
#define PACE2_ADD_PROTOCOL_TO_BITMASK(bmask,value)                  \
{                                                                   \
    (bmask).bitmask[(value) >> 6] |= (((u64)1)<<((value) & 0x3F));  \
}

/**
 * @brief Deletes a given 8 bit value from a bitmask.
 *
 * @param[out]  bmask   Destination bitmask from which the value has to be deleted.
 *                      Has to a variable of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 * @param[in]   value   8 bit value which will be deleted from the bitmask.
 */
#define PACE2_DEL_PROTOCOL_FROM_BITMASK(bmask,value)                \
{                                                                   \
    (bmask).bitmask[(value) >> 6] &= ~(((u64)1)<<((value) & 0x3F)); \
}

/**
 * @brief Checks whether the bitmask contains the given 8 bit value.
 *
 * @param[out]  bmask   The bitmask which is checked whether it contains the value.
 *                      Has to a variable of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 * @param[in]   value   8 bit value which is used to check whether the bitmask contains it.
 */
#define PACE2_COMPARE_PROTOCOL_TO_BITMASK(bmask,value) ((bmask).bitmask[(value) >> 6] & (((u64)1)<<((value) & 0x3F)))

/**
 * @brief Checks whether all bits of the bitmask are set to zero.
 *
 * @param[in]   a   Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 */
#define PACE2_PROTOCOLS_BITMASK_IS_ZERO(a) ((a).bitmask[0] == 0 &&  \
                                            (a).bitmask[1] == 0 &&  \
                                            (a).bitmask[2] == 0 &&  \
                                            (a).bitmask[3] == 0)

/**
 * @brief Checks if the bitmask a contains the complement of bitmask b.
 *
 * @param[in]   a   The bitmask which is checked whether it contains the complement.
 *                  Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 * @param[in]   b   The bitmask which is used to check whether another bitmask contains its complement.
 *                  Bitmask of type @ref PACE2_protocols_bitmask "PACE2_protocols_bitmask".
 */
#define PACE2_PROTOCOLS_BITMASK_CONTAINS_NEGATED_BITMASK(a,b) ((((a).bitmask[0] & ~(b).bitmask[0]) == ~(b).bitmask[0]) &&   \
                                                               (((a).bitmask[1] & ~(b).bitmask[1]) == ~(b).bitmask[1]) &&   \
                                                               (((a).bitmask[2] & ~(b).bitmask[2]) == ~(b).bitmask[2]) &&   \
                                                               (((a).bitmask[3] & ~(b).bitmask[3]) == ~(b).bitmask[3]))

#endif /* PACE2_PROTOCOLS_BITMASK_H */
