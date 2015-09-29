from flask import request
from flask import Flask 
import os 
import unittest
import tempfile 
import tr 


class trTestCase(unittest.TestCase): 
    def setUp(self): 
        print 'Inside Setup' 
        self.app = tr.app.test_client()

    def tearDown(self): 
        print 'Insde tearDown' 

    def test_empty_url(self): 
        rv = self.app.get('/')
        assert 'Hello World!' in rv.data 

    def test_create_url(self): 
        data = dict(
                src='172.16.1.1', 
                dst='172.16.2.1', 
                action='NFQUEUE', 
                queue_num='2')
        rv = self.app.post('/policy/rule/10', data, 
                follow_redirects = True)
        print data 
        assert 'request method is POST' in rv.data 

        

if __name__ == '__main__':
    unittest.main() 
    print 'hello world' 












