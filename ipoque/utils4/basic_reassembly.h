/*
 * basic_reassembly.h
 *
 *  Created on: 23 Jul 2014
 *
 */

#ifndef BASIC_REASSEMBLY_H
#define BASIC_REASSEMBLY_H


#include <pace2.h>

struct reassembly_flow_data {
    /* the current size of every buffer per direction */
    u64 bufsize[2];
    /* length of stored data per direction */
    u64 data_length[2];
    /* the seq of the first byte stored per direction */
    u32 base_seq[2];
    /* the pointer to the allocated memory per direction */
    u8 *buf[2];
};

/**
 * adds data of a (tcp) packet to the reassembled memory area
 * @param rfd reassembly to add data to
 * @param seq sequence number of current chunk
 * @param data pointer to payload
 * @param data_len legth of payload
 * @param direction direction of payload
 * @param is_tcp_syn enables special handling of tcp syn requests (increases seq without data)
 * @return 0 on success; !=0 on error
 */
u8 br_add_data(struct reassembly_flow_data *rfd, u32 seq, const u8* data, u64 data_len, u8 direction, u8 is_tcp_syn);

/**
 * removes given number of bytes from the beginning of the reassembled memory
 * @param rfd reassembly to remove data from
 * @param data_len number of bytes to remove from each direction
 * @return 0 on success; !=0 on error
 */
u8 br_remove_data(struct reassembly_flow_data *rfd, u64 data_length[2]);

/**
 * destroys a reassembly and frees memory
 * @param rfd reassembly to destroy
 * @return 0 on success; !=0 on error
 * @note reassembly itself has to be freed on the outside
 */
u8 br_destroy_data(struct reassembly_flow_data *rfd);

#endif /* BASIC_REASSEMBLY_H_ */
