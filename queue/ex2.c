#include <netinet/in.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <stdio.h>

int handler(struct nfq_q_handle *myQueue, struct nfgenmsg *msg, struct nfq_data *pkt,   void *cbData) {
    int id = 0;
    struct nfqnl_msg_packet_hdr *header;

    if( header = nfq_get_msg_packet_hdr(pkt) )
        id = ntohl(header->packet_id);

    unsigned char *pktData;

    int len = nfq_get_payload(pkt, &pktData);

    printf("data[ %d ]:\n", len);

    int i;
    for (i = 0; i < len; i++)
        printf("%2d 0x%02x %3d %c\n", i, pktData[i], pktData[i], pktData[i]);

    printf("\n");

    return nfq_set_verdict(myQueue, id, NF_ACCEPT, len, pktData);
}

int main(int argc, char **argv) {
    struct nfq_handle *nfqHandle;
    struct nfq_q_handle *myQueue;
    struct nfnl_handle *netlinkHandle;

    int fd, res;
    char buf[4096];

    // queue connection
    if (!(nfqHandle = nfq_open())) {
        perror("Error in nfq_open()");
        return(-1);
    }

    // bind this handler
    if (nfq_bind_pf(nfqHandle, AF_INET) < 0) {
        perror("Error in nfq_bind_pf()");
        return(1);
    }

    // define a handler
    if (!(myQueue = nfq_create_queue(nfqHandle, 0, &handler, NULL))) {
        perror("Error in nfq_create_queue()");
        return(1);
    }

    // turn on packet copy mode
    if (nfq_set_mode(myQueue, NFQNL_COPY_PACKET, 0xffff) < 0) {
        perror("Could not set packet copy mode");
        return(1);
    }

    netlinkHandle = nfq_nfnlh(nfqHandle);
    fd = nfnl_fd(netlinkHandle);

    while ((res = recv(fd, buf, sizeof(buf), 0)) && res >= 0)
        nfq_handle_packet(nfqHandle, buf, res);

    nfq_destroy_queue(myQueue);
    nfq_close(nfqHandle);

    return 0;
}

