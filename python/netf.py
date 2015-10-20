from netfilterqueue import NetfilterQueue
from scapy.all import * 
from curry import curry 
import os 
import logging 
import multiprocessing 
import traceback 

logger = logging.getLogger('MuseTC')
hdlr = logging.FileHandler('/var/log/MuseTC.log')
formatter = logging.Formatter('%(asctime)s-%(levelname)s-(%(threadName)-10s) %(message)s')
hdlr.setFormatter(formatter)
logger.addHandler(hdlr)
logger.setLevel(logging.DEBUG)

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
        logger.debug('Queue %s pkt len %s content %s' %
                       (queue, pkt.get_payload_len(), pkt)) 

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
            logger.debug("STOPPPED due to invalid configuration ")
            self.cleanup()
        except KeyboardInterrupt: 
            logger.debug("STOPPPED due to user keyboard input ")  
            self.cleanup()
        except: 
            logger.debug("STOPPPED due to user keyboard input ")  
            self.cleanup()
      
    def cleanup(self): 
        logger.debug("packet handler cleaning up ") 
        self._nfqueue.unbind()

    def stop(self): 
        logger.debug("packet handler stopped ") 
        self.cleanup()

class TCManager(object): 
    _queues = []
    _nfq_thread = None  

    def __init__(self): 
        #for line in traceback.format_stack(): 
        #    print line.strip() 
	
        #logger.debug("TC Packet Manager Invoked")  
        pass 

    def service_restart(self): 
        logger.debug("queue thread alive and number are %s, %s" %  
                       (self._nfq_thread == None, self._queues))
        if self._nfq_thread: 
            logger.debug("previous queue aliveness %s ", 
                        self._nfq_thread.is_alive()) 

        if self._nfq_thread and self._nfq_thread.is_alive(): 
            #need to call stop thread function 
            logger.debug("Updating packet handler with new configuration " )
            self._nfq_thread.terminate()
            self._nfq_thread.join()
        else: 
            logger.debug("Creating packet handler with new configuration")
        self._nfq_thread = NFQueue(self._queues)
        self._nfq_thread.start() 

    def add_queue(self, queue_num): 
        if queue_num in self._queues: 
	    logger.debug("queue %s is already there" % queue_num) 
	    return 

        self._queues.append(queue_num)
        #call service restart in order to make
        #the changes effective 
        self.service_restart() 

    def remove_queue(self, queue_num): 
        self._queues.remove(queue_num) 
        #call service restart in order to make
        #the changes effective 
        self.service_restart() 

    def get_queue(self): 
        #return queue info
        return self._queues 

if __name__ == "__main__":
    tc = TCManager()  
    tc.add_queue(900) 
    tc.add_queue(900) 
    tc.add_queue(2) 
    tc.add_queue(3) 
    tc.remove_queue(2) 

    print "current queue is %s " % tc.get_queue()

    while True: 
        pass

