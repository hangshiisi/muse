import os 
import time 
import iptc

from flask import Flask 
from flask import request 

class policy_rule(object):
    '''
      class to manipulate policy rules 
    '''

    def __init__(self): 
        self._name = None
        self._rule = None 

    def create_rule(self, src, dst, action, qnum = 1):
         
        rule = iptc.Rule()
        target = iptc.Target(rule, action)
        #target.set_parameter('queue-num', 2)
        
        rule.target = target
        
        rule.src = src
        rule.dst = dst 
    
        chain = iptc.Chain(iptc.Table(iptc.Table.FILTER), "INPUT")
        chain.insert_rule(rule) 
        return 


    def create_rule(self, src, dst, action, qnum = 1):
         
        rule = iptc.Rule()
        target = iptc.Target(rule, action)
        #target.set_parameter('queue-num', 2)
        
        rule.target = target
        
        rule.src = src
        rule.dst = dst 
    
        chain = iptc.Chain(iptc.Table(iptc.Table.FILTER), "INPUT")
        chain.delete_rule(rule) 
        return 

     
    def create_rule_cmd(self, src, dst, action, qnum = 1):

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
         
        cmd = 'sudo iptables -A INPUT '

        cmd += '--src ' + src + ' ' 
        cmd += '--dst ' + dst + ' '

        cmd += '-j NFQUEUE ' 
        cmd += '--queue-num ' + str(qnum) + ' '

        print "command is " + cmd 
        os.system(cmd) 
        return  

    def delete_rule_cmd(self, src, dst, action, qnum = 1):
        cmd = 'sudo iptables -D INPUT '

        cmd += '--src ' + src + ' ' 
        cmd += '--dst ' + dst + ' '

        cmd += '-j NFQUEUE ' 
        cmd += '--queue-num ' + str(qnum) + ' '

        print "command is " + cmd 
        os.system(cmd) 
        return 

def rule_manipulation():

    prule = policy_rule() 

    prule.create_rule_cmd("172.1.1.1", "172.1.2.1", "NFQUEUE", 2) 
    #prule.create_rule("172.1.1.1", "172.1.2.1", "QUEUE", 2) 

    #time.sleep(3)
    os.system('sudo iptables -L -n')  

    prule.delete_rule_cmd("172.1.1.1", "172.1.2.1", "NFQUEUE", 2) 
    os.system('sudo iptables -L -n')  
    print "hello world ends" 
    return 


app = Flask(__name__)
prule = policy_rule() 

@app.route("/")
def hello():
    return "Hello World!"

@app.route('/policy/rule/<int:rule_num>', \
           methods = ['GET', 'POST', 'DELETE'])
def handle_policy_rule(rule_num): 
    print 'policy num %s ' % rule_num 
    print 'request method is %s ' % request.method 

    data = request.get_json() 

    app.logger.debug('Info %s ' % data)
    if request.method == 'POST': 
        print 'handling post'
    elif request.method == 'DELETE': 
        print 'handling deletion'
    else:
        print 'handling get'

    return 'request method is %s %s ' % (request.method, rule_num)





if __name__ == "__main__":
    app.debug = True 
    app.run(host='0.0.0.0')



