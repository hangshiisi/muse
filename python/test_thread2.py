import time
from thread2 import Thread 

def f(): 
    try: 
        while True: 
            time.sleep(1) 
    finally: 
        print "outta here" 

#t = Thread(target = f) 
#t.start()
#t.isAlive()

#t.terminate()
#t.join()
#t.isAlive()


