import os 
import time 
import iptc

from flask import Flask 
from flask import request 
from flask import jsonify 
from flask import make_response 

policy_db = dict() 

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


    def delete_rule(self, src, dst, action, qnum = 1):
         
        rule = iptc.Rule()
        target = iptc.Target(rule, action)
        #target.set_parameter('queue-num', 2)
        
        rule.target = target
        
        rule.src = src
        rule.dst = dst 
    
        chain = iptc.Chain(iptc.Table(iptc.Table.FILTER), "INPUT")
        chain.delete_rule(rule) 
        return 

     
    def create_rule_cmd(self, src, dst, action, qnum = 1, 
                        position = 1):

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

    policy_db[rule_num] = request.get_json() 

    return jsonify(policy_db), 201 



@app.route('/policy/rules/<int:rule_num>', \
           methods = ['DELETE'])
def policy_rule_delete(rule_num): 
    if not request.json: 
        abort(400)

    print 'policy num %s ' % rule_num 
    print 'request method is %s ' % request.method 

    print 'AB1 the request json data is %s ' % request.data

    data = request.data
    print 'iAB2 the request json data is %s ' % data 
    #dataDict = json.loads(data)
    json.dumps(data)


    #app.logger.debug('Info %s ' % data)
    src = request.json.get('src', '192.168.1.1') 
    dst = request.json.get('dst', '192.168.2.1')
    action = request.json.get('action', 'ACCEPT')
    queue_num = request.json.get('queue_num', 0)

    policy_db.pop(rule_num, None)

    return jsonify(policy_db), 201 


@app.route('/policy/rules', methods = ['GET'])
def policy_rule_get_all(): 
    return jsonify(policy_db) 



@app.route('/policy/rules/<int:rule_num>', \
           methods = ['GET'])
def policy_rule_get_one(rule_num): 
    rule = [ v for k, v in policy_db.iteritems() \
                if k == rule_num]

    print str(rule) 

    return jsonify({'result':rule}) 



if __name__ == "__main__":
    app.debug = True 
    app.run(host='0.0.0.0')



