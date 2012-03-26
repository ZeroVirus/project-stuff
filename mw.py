from threading import Thread
import time

class Master(object):
    def __init__(self):
        self._max_=max;
        self.worker = [];
		
    def returnTotal(self):
        return self.worker;

    def work(self, id):
        self.worker.append("Hello World from Thread "+str(id));
        print "Thread "+str(id)+" timestamp: "+str(time.clock());
		
class Worker(Thread):
    def __init__(self, master, id):
        Thread.__init__(self);
        self._master_= master;
        self._id_ = id;
		
    def run(self):
        self._master_.work(self._id_);


		
w = Master();
workers = [];
for i in range(0,5):
    workers.append(Worker(w,i));
    workers[i].start();

time.sleep(.0001);
print;
print "[Printing Final Array]";
print w.returnTotal();