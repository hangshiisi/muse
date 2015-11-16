#include "pace2_netfilter.h"

#include <stddef.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

static int pace2_netfilter_handle_packet( struct nfq_q_handle * const qh,
                                           struct nfgenmsg * const nfmsg,
                                           struct nfq_data * const nfad,
                                           void * const int_user_data )

{
    struct timeval tv;
    int payload_len;
    const void * payload;
    uint64_t packet_id;
    struct pace2_netfilter * const netfilter = int_user_data;

    if ( netfilter == NULL ) return 0;

    static int ( * const nfq_get_payload_ptr )( struct nfq_data *nfad, char **data ) = ( void * )nfq_get_payload;

    const struct nfqnl_msg_packet_hdr * const nfq_ph = nfq_get_msg_packet_hdr( nfad );

    if ( nfq_ph == NULL ) {
        fprintf( stderr, "nfq_get_msg_packet_hdr() failed.\n");
        return 0;
    }

    packet_id = ntohl( nfq_ph->packet_id );

    if ( ( payload_len = nfq_get_payload_ptr( nfad, ( char ** )&payload ) ) < 0 ) {
        fprintf( stderr, "nfq_get_payload() failed.\n" );
        return 0;
    }

    if ( gettimeofday( &tv, NULL ) != 0 ) {
        fprintf( stderr, "Timer error, could not read time from computer.\n" );
        return 0;
    }

    if ( payload_len > 0 ) {
        netfilter->callback( &tv, payload, payload_len, &packet_id, 3, netfilter->user_data );
    }

    return 0;
}

char pace2_netfilter_initialize( struct pace2_netfilter * const netfilter ,
                                  pace2_netfilter_callback_t callback,
                                  void * const user_data )
{
    if ( netfilter == NULL || callback == NULL ) return 0;

    netfilter->callback = callback;
    netfilter->user_data = user_data;

    {
        netfilter->nfq_h = nfq_open();

        if ( netfilter->nfq_h == NULL ) {
	        fprintf( stderr, "Could not initalize iptables userspace hook.\n" );
            return 0;
        }

        if ( nfq_unbind_pf( netfilter->nfq_h, AF_INET ) < 0 ||
             nfq_unbind_pf( netfilter->nfq_h, AF_INET6 ) < 0 ||
             nfq_bind_pf( netfilter->nfq_h, AF_INET ) < 0 ||
             nfq_bind_pf( netfilter->nfq_h, AF_INET6 ) < 0 ) {

            fprintf( stderr, "nfq_unbind_pf() / nfq_bind_pf() failed: Run as root and unload the \"ip_queue\" module.\n" );
            return 0;
        }

        netfilter->nfq_q_h = nfq_create_queue( netfilter->nfq_h, 0, pace2_netfilter_handle_packet, netfilter );

        if ( netfilter->nfq_q_h == NULL ) {
            fprintf( stderr, "nfq_create_queue() failed.\n" );
            return 0;
        }

        if ( nfq_set_mode( netfilter->nfq_q_h, NFQNL_COPY_PACKET, IPQ_BUFSIZE ) < 0) {
            fprintf( stderr, "nfq_set_mode() failed.\n" );
            return 0;
        }

        /* increase the NFQ socket receive buffer size to avoid failed reads due to a full buffer */
        nfnl_rcvbufsiz( nfq_nfnlh( netfilter->nfq_h ), IPQ_SOCKET_BUFFER_SIZE );

        return 1;
    }

    fprintf( stderr, "Netfilter not supported.\n");

    return 0;
}

void pace2_netfilter_exit( struct pace2_netfilter * const netfilter )
{
    if ( netfilter == NULL ) return;

    netfilter->callback = NULL;
    netfilter->user_data = NULL;

    if ( netfilter->nfq_q_h != NULL ) nfq_destroy_queue( netfilter->nfq_q_h );
    if ( netfilter->nfq_h != NULL ) nfq_close( netfilter->nfq_h );

}


void pace2_netfilter_packet_loop( struct pace2_netfilter * const netfilter, const uint8_t * const running )
{
    if ( netfilter->nfq_q_h != NULL ) {
        while ( *running ) {
            static char nfq_buf[IPQ_BUFSIZE];
            int status;

            if ( ( status = recv( nfq_fd( netfilter->nfq_h ), nfq_buf, IPQ_BUFSIZE, 0 ) ) >= 0 ) {
                nfq_handle_packet( netfilter->nfq_h, nfq_buf, status );
                continue;
            }

            if ( status < 0 && errno == ENOBUFS ) {
                fprintf(stderr, "Losing packets.\n");
                continue;
            }
        }
    }

}

void pace2_netfilter_set_verdict( struct pace2_netfilter * const netfilter,
                                   const uint64_t packet_id,
                                   const uint32_t verdict )
{
    if ( netfilter == NULL ) return;

    nfq_set_verdict( netfilter->nfq_q_h, packet_id, verdict, 0, NULL );

}
