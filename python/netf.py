from netfilterqueue import NetfilterQueue
from scapy.all import * 
import os 
import threading 
import logging 

from curry import curry 

logging.basicConfig(level = logging.DEBUG, 
                    format = '(%(threadName)-10s) %(message)s', 
                    ) 

class MPLS(Packet): 
   name = "MPLS" 
   fields_desc =  [ BitField("label", 3, 20), 
                    BitField("cos", 0, 3), 
                    BitField("s", 1, 1), 
                    ByteField("ttl", 0)  ] 

   #bind_layers(Ether, MPLS, type=0x8847)


def print_and_accept(pkt): 
    print pkt
    o_pkt = IP(pkt.get_payload()) 
    o_pkt.show()
    print pkt.get_payload_len() 
    m = MPLS(label=0x9, cos = 0x3) 
    #new_pkt = IP(dst=o_pkt[IP].dst, src=o_pkt[IP].src, \
    #              proto=o_pkt[IP].proto,\
    #             tos=o_pkt[IP].tos)/m/pkt.get_payload()
    #new_pkt = o_pkt/Raw('Hello World')
    new_pkt = o_pkt/Raw(pkt.get_payload())
    #new_pkt = o_pkt/ICMP()
    send(new_pkt)

    pkt.drop()
    #   pkt.accept()




#nfqueue = NetfilterQueue()
#nfqueue.bind(1, print_and_accept) 

#try: 
#    nfqueue.run()
#except KeyboardInterrupt: 
#    print 

class NFQueue(threading.Thread): 
    _nfqueue = None 
    _queues = []
    _event_stop = None 

    def __init__(self, queues): 
        self._queues = queues
        self._nfqueue = NetfilterQueue() 
        self._event_stop = threading.Event()

    def handle_pkt(self, queue, pkt): 
        logging.debug('Queue %s pkt len %s content %s' %
                       (queue, pkt_get_payload_len(),  kt)) 
        if self._event_stop.isSet(): 
            return 

        o_pkt = IP(pkt.get_payload()) 
        o_pkt.show()
        m = MPLS(label=0x9, cos = 0x3) 
        #new_pkt = IP(dst=o_pkt[IP].dst, src=o_pkt[IP].src, \
        #              proto=o_pkt[IP].proto,\
        #             tos=o_pkt[IP].tos)/m/pkt.get_payload()
        #new_pkt = o_pkt/Raw('Hello World')
        new_pkt = o_pkt/Raw(pkt.get_payload())
        #new_pkt = o_pkt/ICMP()
        send(new_pkt)

        pkt.drop()
        #   pkt.accept()

    def run(self): 
        for i in queues: 
            self._nfqueue.bind(i, curry(handle_pkt, i))

        try: 
            self._nfqueue.run()
        except ValueError: 
            print "Completed New Configuration Comes In" 
            pass 
        except KeyboardInterrupt: 
            print 
      
    def cleanup(self): 
        for i in queues: 
            self._nfqueue.unbind()

    def stop(self): 
        self._event_stop.set() 
        self.cleanup() 
        raise ValueError('New Configuration Comes In') 

    def __call__(self): 
        run()

class TCManager(object): 
    _queues = []
    _nfq_thread = None  

    def __init__(self): 
        pass 

    def service_restart(self): 
        for i in self._queues: 
            print "queue number %s" % i 
        if _nfq_thread: 
            #need to call stop thread function 
            _nfq_thread.stop()
            print "stopped a thread " 
        self._nfq_thread = NFQueue()
        print "creating a thread" 
        self._nfq_thread.start() 


    def add_queue(self, queue_num): 
        self._queues.append(queue_num)
        #call service restart in order to make
        #the changes effective 
        self.service_restart() 


    def remove_queue(self, queue_num): 
        self._queues.remove(queue_num) 
        #call service restart in order to make
        #the changes effective 
        self.service_restart() 



if __name__ == "__main__":
    tc = TCManager()  
    tc.add_queue(1) 
    tc.add_queue(2) 

