import os 
import thread 
import time 

from flask import Flask 
from flask import request 
from flask import jsonify 
from flask import make_response 


app = Flask(__name__)


@app.route("/")
def hello():
    return "Hello World!"


@app.errorhandler(404)
def not_found(error): 
    return make_response(
            jsonify({'error':'Not Found'}), 
                    404) 

# example of handling post request 
#
@app.route('/rules/<int:rule_num>', \
           methods = ['POST'])
def rule_create(rule_num): 
    if not request.json: 
        abort(400)

    print 'policy num %s ' % rule_num 
    print 'request method is %s ' % request.method 
    print 'AB1 the request json data is %s ' % request.data

    #app.logger.debug('Info %s ' % data)
    queue_num = request.json.get('queue_num', 0)


    return jsonify({'result':'success'}), 200 



@app.route('/rules/<int:rule_num>', \
           methods = ['DELETE'])
def policy_rule_delete(rule_num): 
    if not request.json: 
        abort(400)

    print 'policy num %s ' % rule_num 
    print 'request method is %s ' % request.method 
    print 'AB1 the request json data is %s ' % request.data


    #app.logger.debug('Info %s ' % data)
    queue_num = request.json.get('queue_num', 0)


    return jsonify({'result':'success'}), 200 


@app.route('/rules', methods = ['GET'])
def policy_rule_get_all(): 
    return jsonify({'result':'success'}), 200 

def start_web_server(): 
    app.run(debug=True, port=9999, use_reloader=False, 
            host='0.0.0.0')



if __name__ == "__main__":
    thread.start_new_thread(start_web_server, ())
    print "Hello world after app.run"
    while True: 
        time.sleep(1)
        pass




