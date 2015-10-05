from netfilterqueue import NetfilterQueue
from scapy.all import * 
import os 
import logging 
import multiprocessing 

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

class StopThread(StopIteration): pass 

class NFQueue(multiprocessing.Process): 
    _nfqueue = None 
    _queues = []

    def __init__(self, queues): 
        self._queues = queues
        self._nfqueue = NetfilterQueue() 
        super(NFQueue, self).__init__()

    def handle_pkt(self, queue, pkt): 
        logging.debug('Queue %s pkt len %s content %s' %
                       (queue, pkt.get_payload_len(), pkt)) 
        print 'Getting a packet ' 

        o_pkt = IP(pkt.get_payload()) 
        m = MPLS(label=0x9, cos = 0x3) 
        #new_pkt = IP(dst=o_pkt[IP].dst, src=o_pkt[IP].src, \
        #              proto=o_pkt[IP].proto,\
        #             tos=o_pkt[IP].tos)/m/pkt.get_payload()
        #new_pkt = o_pkt/Raw('Hello World')
        new_pkt = o_pkt/Raw('FFFFFF'+ pkt.get_payload())
        #new_pkt = o_pkt/ICMP()
        send(new_pkt)
        new_pkt.show()

        pkt.drop()
        #   pkt.accept()

    def run(self): 
        for i in self._queues: 
            self._nfqueue.bind(i, curry(self.handle_pkt, i))

        try: 
            self._nfqueue.run()
        except ValueError: 
            print "STOPPPED V Completed New Configuration Comes In" 
            self.cleanup()
        except KeyboardInterrupt: 
            print "STOPPPED K Completed New Configuration Comes In" 
            self.cleanup()
        except: 
            print "OTHER STOPPPED Completed New Configuration Comes In" 
            pass 
      
    def cleanup(self): 
        print "inside clean up " 
        self._nfqueue.unbind()

    def stop(self): 
        print "done Got a stop signal here" 
        self.cleanup()


class TCManager(object): 
    _queues = []
    _nfq_thread = None  

    def __init__(self): 
        pass 

    def service_restart(self): 
        for i in self._queues: 
            print "queue number %s" % i 
        print self._nfq_thread
        if self._nfq_thread: 
           print self._nfq_thread.is_alive() 

        if self._nfq_thread and self._nfq_thread.is_alive(): 
            #need to call stop thread function 
            print "stopped a thread " 
            self._nfq_thread.terminate()
            print "prepare to wait for join a thread " 
            self._nfq_thread.join()
            print "done prepare to wait for join a thread " 
        print "creating a thread" 
        self._nfq_thread = NFQueue(self._queues)
        self._nfq_thread.start() 
        print "done creating a thread" 

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
    tc.add_queue(3) 
    while True: 
        pass

