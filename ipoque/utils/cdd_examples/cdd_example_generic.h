/********************************************************************************/
/**
 ** \file       cdd_example_generic.h
 ** \brief      PACE 2 file for generic information of Custom Defined Decoder.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef CDD_EXAMPLE_GENERIC_H
#define CDD_EXAMPLE_GENERIC_H

/* Includes *********************************************************************/
#include <string.h>
#include <pace2.h>

/* Public Macros ****************************************************************/
#define NUMBER_OF_CDD           4
#define NUMBER_OF_CDD_EVENTS    1
#define NUMBER_OF_CDC           1

/* used unique ID's to distinguish CDD's */
#define CDD_DOCTYPE_ID          0
#define CDD_HTTP_ID             1
#define CDD_AMAZON_ID           2
#define CDD_USERPASS_ID         3

/* used unique event ID's to distinguish events of CDD's */
#define CDD_DOCTYPE_EVENT_ID    0
#define CDD_HTTP_EVENT_ID       1
#define CDD_AMAZON_EVENT_ID     2
#define CDD_USERPASS_EVENT_ID   3

#define CDC_AMAZON_ID           0

/* Public Types *****************************************************************/

/* Structure to define flow user data of the class event CDD */
struct cdd_class_flow_user_data {
    struct ipd_charset_string username;
};

/* Union to combine all flow user data definitions */
union cdd_flow_user_data {
    uint8_t cdc_matched;
    struct cdd_class_flow_user_data class_data;
};

#endif /* CDD_EXAMPLE_GENERIC_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
