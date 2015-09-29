import iptc

class policy_rule(object):
    '''
      class to manipulate policy rules 
    '''

    def __init__(self): 
        self._name = None
        self._rule = None 

    def create_rule(self, src, dst, action, queue_num = 1):
         
	rule = iptc.Rule()
	target = iptc.Target(rule, action)
#	target.set_parameter(queue_num, 2)
        
	rule.target = target
        
        rule.src = src
        rule.dst = dst 
	
	chain = iptc.Chain(iptc.Table(iptc.Table.FILTER), "INPUT")
	chain.insert_rule(rule) 
         

'''
rule = iptc.Rule()
rule.protocol = "tcp" 
rule.target = iptc.Target(rule, "DROP")
match = iptc.Match(rule, "state")
chain = iptc.Chain(iptc.Table(iptc.Table.FILTER), "INPUT")
match.state = "RELATED,ESTABLISHED"
rule.add_match(match)
chain.insert_rule(rule) 
'''
prule = policy_rule() 

prule.create_rule("172.1.1.1", "172.1.2.1", "NFQUEUE", 2) 
#prule.create_rule("172.1.1.1", "172.1.2.1", "QUEUE", 2) 


print "hello world ends" 



