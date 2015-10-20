#!/usr/bin/env python 

import os 
import time 
import iptc
import thread 
import cmd 
import logging 


from flask import Flask 
from flask import request 
from flask import jsonify 
from flask import make_response 

from netf import TCManager

logging.basicConfig(level = logging.DEBUG,
                    format = '(%(threadName)-10s) %(message)s',
                    )

policy_db = dict() 
tc_mgr = TCManager() 

class PolicyRule(object):
    '''
      class to manipulate policy rules 
    '''

    def __init__(self, tc_mgr=None): 
        self._name = None
        self._rule = None 
        self._tc_mgr = tc_mgr

    def create_rule(self, src, dst, action, qnum = 1):
         
        rule = iptc.Rule()
        target = iptc.Target(rule, action)
        #target.set_parameter('queue-num', 2)
        
        rule.target = target
        
        rule.src = src
        rule.dst = dst 
    
        chain = iptc.Chain(iptc.Table(iptc.Table.FILTER), "FORWARD")
        chain.insert_rule(rule)
        if self._tc_mgr: 
            self._tc_mgr.add_queue(int(qnum)) 
 
        return 


    def delete_rule(self, src, dst, action, qnum = 1):
         
        rule = iptc.Rule()
        target = iptc.Target(rule, action)
        #target.set_parameter('queue-num', 2)
        
        rule.target = target
        
        rule.src = src
        rule.dst = dst 
    
        chain = iptc.Chain(iptc.Table(iptc.Table.FILTER), "FORWARD")
        chain.delete_rule(rule) 
        if self._tc_mgr: 
            self._tc_mgr.remove_queue(int(qnum)) 
        return 

     
    def create_rule_cmd(self, src, dst, action, qnum = 1, 
                        position = 1):

        '''
        rule = iptc.Rule()
        rule.protocol = "tcp" 
        rule.target = iptc.Target(rule, "DROP")
        match = iptc.Match(rule, "state")
        chain = iptc.Chain(iptc.Table(iptc.Table.FILTER), "FORWARD")
        match.state = "RELATED,ESTABLISHED"
        rule.add_match(match)
        chain.insert_rule(rule) 
        '''
         
        cmd = 'sudo iptables -A FORWARD '

        cmd += '--src ' + src + ' ' 
        cmd += '--dst ' + dst + ' '

        cmd += '-j NFQUEUE ' 
	#print "type str is %s " % type(qnum) 

        cmd += '--queue-num ' + str(qnum) + ' '

        print "command is " + cmd 
        os.system(cmd) 
        if self._tc_mgr: 
            self._tc_mgr.add_queue(int(qnum)) 
 
        return  

    def delete_rule_cmd(self, src, dst, action, qnum = 1):
        cmd = 'sudo iptables -D FORWARD '

        cmd += '--src ' + src + ' ' 
        cmd += '--dst ' + dst + ' '

        cmd += '-j NFQUEUE ' 
        cmd += '--queue-num ' + str(qnum) + ' '

        print "command is " + cmd 
        os.system(cmd) 
        if self._tc_mgr: 
            self._tc_mgr.remove_queue(int(qnum)) 
        return 

def rule_manipulation():

    prule = PolicyRule(tc_mgr) 

    prule.create_rule_cmd("172.1.1.1", "172.1.2.1", "NFQUEUE", 2) 
    #prule.create_rule("172.1.1.1", "172.1.2.1", "QUEUE", 2) 

    #time.sleep(3)
    os.system('sudo iptables -L -n')  

    prule.delete_rule_cmd("172.1.1.1", "172.1.2.1", "NFQUEUE", 2) 
    os.system('sudo iptables -L -n')  
    print "hello world ends" 
    return 

class ShellEnabled(cmd.Cmd):

    last_output = ''

    def do_shell(self, line):
        "Run a shell command"
        print "running shell command:", line
        output = os.popen(line).read()
        print output
        self.last_output = output
        return 

    def do_echo(self, line):
        """
        Print the input, replacing '$out' with the output 
        of the last shell command
        """
        # Obviously not robust
        print line.replace('$out', self.last_output)
        return 

    def do_create(self, rule):
        """
        Create Policy Rule
        """
        print "the line is " + rule  
        l = rule.split() 
        if len(l) < 1 or len(l) % 2 == 0: 
            print "input needs to have odd number" 
            return 

        if l[0] != 'rule': 
            print "only rule creation is supported " 
            return 

        # some default values 
        src = '172.1.1.1'
        dst = '172.1.2.1'
        action = 'NFQUEUE'
        queue_num = 2 
       
        for k,v in zip(l[1::2], l[2::2]): 
            print "%s = %s " % (k, v) 
            if k == 'src': 
                src = v
            elif k == 'dst':
                dst = v
            elif k == 'action': 
                action = v
            elif k == 'queue_num': 
                queue_num = v 
            else: 
                print "unsupported parameter"
                return 

        prule = PolicyRule(tc_mgr) 
        prule.create_rule_cmd(src, dst, action, queue_num) 
        return 

    def do_delete(self, rule):
        """
        Delete Policy Rule
        """
        print "the line is " + rule  
        l = rule.split() 
        if len(l) < 1 or len(l) % 2 == 0: 
            print "input needs to have odd number" 
            return 

        if l[0] != 'rule': 
            print "only rule creation is supported " 
            return 

        # some default values 
        src = '172.1.1.1'
        dst = '172.1.2.1'
        action = 'NFQUEUE'
        queue_num = 2 
       
        for k,v in zip(l[1::2], l[2::2]): 
            print "%s = %s " % (k, v) 
            if k == 'src': 
                src = v
            elif k == 'dst':
                dst = v
            elif k == 'action': 
                action = v
            elif k == 'queue_num': 
                queue_num = v 
            else: 
                print "unsupported parameter"
                return 

        prule = PolicyRule(tc_mgr) 
        prule.delete_rule_cmd(src, dst, action, queue_num) 
        return 

    def do_show(self, rule):
        """
        Show Policy Rule
        """
        print "the line is " + rule  
        l = rule.split() 
        if len(l) > 2: 
            print "input needs to have one number" 
            return 

        if l[0] != 'rule': 
            print "only rule display is supported " 
            return 

        cmd1 = 'iptables -L -n -v '
        output = os.popen(cmd1).read()
        print '#'*40
        print output

        cmd1 = 'iptables -t nat -L -n -v '
        output = os.popen(cmd1).read()
        print '#'*40
        print output
        return 

    def do_flush(self, line):
        """
        list the queues  
        """
        print "flushing the rules " + line  
        l = line.split() 
        if len(l) > 1: 
            print "input needs to have one number" 
            return 
	policy_flush_rules() 
	return 
        
    def do_queue(self, line):
        """
        list the queues  
        """
        print "the line is " + line  
        l = line.split() 
        if len(l) > 2: 
            print "input needs to have one number" 
            return 

        if l[0] != 'list': 
            print "only queue list is supported " 
            return 

	queues = tc_mgr.get_queue() 
	print "queue numbers are: %s " % queues 
	for q in queues: 
	    print "queue %s details: %s" % (q, policy_db[str(q)]) 
        return 
       

    def do_exit(self, line):
        """
        exit the application 
        """
        return True

    def do_EOF(self, line):
        """
        Ctrl+D to exit
        """
        return True

app = Flask(__name__)

@app.route("/")
def hello():
    return "Hello World!"


@app.errorhandler(404)
def not_found(error): 
    return make_response(
            jsonify({'error':'Not Found'}), 
                    404) 


@app.route('/policy/rules/<int:rule_num>', \
           methods = ['POST'])
def policy_rule_create(rule_num): 
    if not request.json: 
        abort(400)

    print 'policy num %s ' % rule_num 
    print 'request method is %s ' % request.method 

    print 'AB1 the request json data is %s ' % request.data


    #app.logger.debug('Info %s ' % data)
    src = request.json.get('src', '192.168.1.1') 
    dst = request.json.get('dst', '192.168.2.1')
    action = request.json.get('action', 'ACCEPT')
    queue_num = request.json.get('queue_num', 0)

    prule.create_rule_cmd(src, dst, action, queue_num) 
    policy_db[rule_num] = request.get_json() 

    return jsonify({'result':policy_db[rule_num]}), 201 



@app.route('/policy/rules/<int:rule_num>', \
           methods = ['DELETE'])
def policy_rule_delete(rule_num): 
    if not request.json: 
        abort(400)

    print 'policy num %s ' % rule_num 
    print 'request method is %s ' % request.method 

    print 'AB1 the request json data is %s ' % request.data


    #app.logger.debug('Info %s ' % data)
    src = request.json.get('src', '192.168.1.1') 
    dst = request.json.get('dst', '192.168.2.1')
    action = request.json.get('action', 'ACCEPT')
    queue_num = request.json.get('queue_num', 0)

    policy_db.pop(rule_num, None)
    prule.delete_rule_cmd(src, dst, action, queue_num) 

    return jsonify(policy_db), 201 


@app.route('/policy/rules', methods = ['GET'])
def policy_rule_get_all(): 
    return jsonify(policy_db) 

def policy_flush_rules(): 
    os.system('iptables -F -t nat')
    os.system('iptables -F -t filter') 



@app.route('/policy/rules/<int:rule_num>', \
           methods = ['GET'])
def policy_rule_get_one(rule_num): 
    rule = [ v for k, v in policy_db.iteritems() \
                if k == rule_num]
    print str(rule) 

    return jsonify({'result':rule}) 

def start_web_server(): 
    app.run(debug=True, use_reloader=False, host='0.0.0.0')



if __name__ == "__main__":
    logging.debug("Starting Services and Shell, please wait")
    thread.start_new_thread(start_web_server, ())
    time.sleep(2)
    logging.debug("Shell started")
    logging.debug("Only limited commands are supported")

    ShellEnabled().cmdloop() 

# while True: 
#        time.sleep(1)
#        pass




