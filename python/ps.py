from multiprocessing import Process

import os

def info(title): 
    print(title)
    print('module name', __name__)
    print('parent processes', os.getppid()) 
    print('process id', os.getpid()) 


def f(name): 
    info('function f')
    print('hello', name)
    while True: 
        pass

if __name__ == '__main__':
    info('main line')
    f = Process(target=f, args=('bob',))
    f.start()
    print f.is_alive() 
    f.terminate()
    f.join()
    print f.is_alive() 



