#include <netinet/in.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h> 
#include <assert.h> 

#include "list.h" 

LIST_HEAD(ctxt_head); 

typedef struct muse_context_ { 
      struct list_head list_member;

      /* nflink handler information */ 
      struct nfq_handle *nfqHandle;
      struct nfq_q_handle *myQueue;
      struct nfnl_handle *netlinkHandle;

      /* user specific information */ 
      unsigned int queue_num; 
      unsigned int rule_num; 
} muse_context_t; 

muse_context_t *ctxt_add_node(struct list_head *head, unsigned int queue_num, 
                    unsigned int rule_num)
{
    muse_context_t *fooPtr = malloc(sizeof(muse_context_t));
    assert(fooPtr != NULL);

    // need to check if it is there arleady
    // in a separate function 
    memset(fooPtr, 0, sizeof(muse_context_t)); 
    fooPtr->queue_num = queue_num;
    fooPtr->rule_num = rule_num; 
    INIT_LIST_HEAD(&fooPtr->list_member);
    list_add(&fooPtr->list_member, head);
    return fooPtr; 
}

void ctxt_display_all(struct list_head *head)
{
    struct list_head *iter;
    muse_context_t *objPtr;

    __list_for_each(iter, head) {
        objPtr = list_entry(iter, muse_context_t, list_member);
        printf("%u ", objPtr->queue_num);
        printf("%u ", objPtr->rule_num);
    }
    printf("\n");
}

void ctxt_delete_all(struct list_head *head)
{
    struct list_head *iter;
    muse_context_t *objPtr;

  redo:
    __list_for_each(iter, head) {
        objPtr = list_entry(iter, muse_context_t, list_member);
        list_del(&objPtr->list_member);
        free(objPtr);
        goto redo;
    }
}


int ctxt_find_first_and_delete(unsigned int rule_num, 
                               struct list_head *head)
    
{
    struct list_head *iter;
    muse_context_t *objPtr;

    __list_for_each(iter, head) {
        objPtr = list_entry(iter, muse_context_t, list_member);
        if(objPtr->rule_num == rule_num) {
            list_del(&objPtr->list_member);
            free(objPtr);
            return 1;
        }
    }

    return 0;
}

int handler(struct nfq_q_handle *myQueue, struct nfgenmsg *msg, 
            struct nfq_data *pkt, void *cbData) {
    int id = 0;
    struct nfqnl_msg_packet_hdr *header;
    muse_context_t *ctxt = cbData; 
    unsigned char *pktData;
    int i;

    assert(ctxt != NULL); 

    if( header = nfq_get_msg_packet_hdr(pkt) )
        id = ntohl(header->packet_id);

    int len = nfq_get_payload(pkt, &pktData);

    printf("thread %u queue %u data[ %d ]:\n", 
           ctxt->rule_num, ctxt->queue_num, len);

    for (i = 0; i < len; i++)
        printf("%2d 0x%02x %3d %c\n", i, pktData[i], pktData[i], pktData[i]);

    printf("\n");

    return nfq_set_verdict(myQueue, id, NF_ACCEPT, len, pktData);
}

int create_nfq_queue(muse_context_t *ctxt) 
{ 
    assert(ctxt != NULL); 

    // queue connection
    if (!(ctxt->nfqHandle = nfq_open())) {
        perror("Error in nfq_open()");
        return(-1);
    }

    // bind this handler
    if (nfq_bind_pf(ctxt->nfqHandle, AF_INET) < 0) {
        perror("Error in nfq_bind_pf()");
        return(1);
    }

    // define a handler
    if (!(ctxt->myQueue = nfq_create_queue(ctxt->nfqHandle, ctxt->queue_num, 
                                     &handler, 
                                     ctxt))) {
        perror("Error in nfq_create_queue()");
        return(1);
    }

    // turn on packet copy mode
    if (nfq_set_mode(ctxt->myQueue, NFQNL_COPY_PACKET, 0xffff) < 0) {
        perror("Could not set packet copy mode");
        return(1);
    }

    //this field might not be needed 
    ctxt->netlinkHandle = nfq_nfnlh(ctxt->nfqHandle);

    return 0; 
}

int destroy_nfq_queue(muse_context_t *ctxt) 
{ 
    assert(ctxt); 
    nfq_destroy_queue(ctxt->myQueue);
    nfq_close(ctxt->nfqHandle);
} 

/* 
 * loop through all active queues and handle
 * those that have packets arriving 
 */ 
int servce_all_queues(struct list_head *head) 
{ 
    // loop through all list members 
    // add then into the set via FD_SET


    // monitor all queues 
    // once data is available, handles the 
    // queues and go back to monitor next 
    // set of requets 


} 

int main(int argc, char **argv) 
{
    struct nfq_handle *nfqHandle;
    struct nfq_q_handle *myQueue;
    struct nfnl_handle *netlinkHandle;

    int fd, res;
    char buf[4096];
    
    muse_context_t *node1, *node2; 

    node1 = ctxt_add_node(&ctxt_head, 1, 100);  
    node2 = ctxt_add_node(&ctxt_head, 2, 200);  

    //create a few queues 
    if (0 != create_nfq_queue(node1)) { 
        perror("invoking create queue failure"); 
        return -1; 
    } 

    if (0 != create_nfq_queue(node2)) { 
        perror("invoking create queue failure"); 
        return -1; 
    } 

    //run the scheduler 
    //netlinkHandle = nfq_nfnlh(nfqHandle);
    // or use fd = nfq_fd(node->nfqHandle); 
    fd = nfnl_fd(node1->netlinkHandle);

    while ((res = recv(fd, buf, sizeof(buf), 0)) && res >= 0)
        nfq_handle_packet(node1->nfqHandle, buf, res);

    //destroy those queues 
    destroy_nfq_queue(node1); 
    destroy_nfq_queue(node2); 

    if (1) { 
        return 0; 
    } 


    /////////////////////////////////////////////
    /////////////////////////////////////////////
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

