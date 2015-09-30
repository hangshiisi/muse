from netfilterqueue import NetfilterQueue
from scapy.all import * 
import os 

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
    #new_pkt = IP(dst=o_pkt[IP].dst, src=o_pkt[IP].src, proto=o_pkt[IP].proto,\
    #             tos=o_pkt[IP].tos)/m/pkt.get_payload()
    #new_pkt = o_pkt/Raw('Hello World')
    new_pkt = o_pkt/Raw(pkt.get_payload())
    #new_pkt = o_pkt/ICMP()
    send(new_pkt)

    pkt.drop()
    #   pkt.accept()




nfqueue = NetfilterQueue()
nfqueue.bind(1, print_and_accept) 

try: 
    nfqueue.run()
except KeyboardInterrupt: 
    print 



