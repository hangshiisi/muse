/*
 * basic_reassembly.c
 *
 *  Created on: 23 Jul 2014
 *
 */

#include <stdlib.h>
#include <string.h>
#ifdef WIN32
#include <winsock2.h>
#endif
#include "basic_reassembly.h"

u8 br_add_data(struct reassembly_flow_data *rfd, u32 seq, const u8* data, u64 data_len, u8 direction, u8 is_tcp_syn)
{
    u8 reassembly_init_flow = 0;

    if (NULL == rfd) {
        return 1;
    }

    // direction has to be 0 or 1
    if (1 < direction) {
        return 1;
    }

    if (NULL == rfd->buf[direction]) {
        rfd->buf[direction] = malloc(data_len);
        if (NULL == rfd->buf[direction]) {
            return 1;
        }
        rfd->bufsize[direction] = data_len;

        if (is_tcp_syn && 0 == data_len) {
            rfd->base_seq[direction] = seq + 1;
            reassembly_init_flow = 1;
        } else {
            rfd->base_seq[direction] = seq;
        }
    }

    // there is a lost or reordered packet
    if (!reassembly_init_flow && (seq != rfd->base_seq[direction] + rfd->data_length[direction])) {
        return 1;
    }

    if (rfd->bufsize[direction] < rfd->data_length[direction] + data_len) {
        u8 *new_data = realloc(rfd->buf[direction], rfd->data_length[direction] + data_len);

        rfd->bufsize[direction] = rfd->data_length[direction] + data_len;
        rfd->buf[direction] = new_data;
    }

    memcpy(rfd->buf[direction] + rfd->data_length[direction], data, data_len);

    rfd->data_length[direction] += data_len;

    return 0;
}

u8 br_remove_data(struct reassembly_flow_data *rfd, u64 data_length[2])
{
    if (NULL == rfd) {
        return 1;
    }

    if (NULL == rfd->buf[0] || NULL == rfd->buf[1]) {
        return 1;
    }

    if (data_length[0] > rfd->data_length[0] || data_length[1] > rfd->data_length[1]) {
        return 1;
    }

    if (data_length[0] > 0) {
        memmove(rfd->buf[0], rfd->buf[0] + data_length[0], rfd->data_length[0] - data_length[0]);
        rfd->data_length[0] -= data_length[0];
        rfd->base_seq[0] += data_length[0];
    }

    if (data_length[1] > 0) {
        memmove(rfd->buf[1], rfd->buf[1] + data_length[1], rfd->data_length[1] - data_length[1]);
        rfd->data_length[1] -= data_length[1];
        rfd->base_seq[1] += data_length[1];
    }

    return 0;
}

u8 br_destroy_data(struct reassembly_flow_data *rfd)
{
    if (NULL == rfd) {
        return 1;
    }

    if (NULL != rfd->buf[0]) {
        free(rfd->buf[0]);
    }

    if (NULL != rfd->buf[1]) {
        free(rfd->buf[1]);
    }
    return 0;
}

