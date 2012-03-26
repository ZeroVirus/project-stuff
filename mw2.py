import os
import math 

#Simple MasterWorker Application using fork(). 
#Given string s, the program reverses the first two char in string
#Continue doing so on until it reaches end of string.
#If the len(s) is odd, then the last character's position remains the same.
#No need for locking mechanism

def worker(prev,next):
    rev = next+prev; #Reverse the two char string
    return rev;

def master(s):
    final=[]; #Array to collect processes' work
    iter = int(math.floor(len(s)/2)); 
    for i in range(0,iter):
        nworker = os.fork(); #Forks a new process
        pids = (os.getpid(), nworker) #Gets PID of the created process
        print "parent: %d, child: %d" % pids 
        final.append(worker(s[i*2],s[i*2+1])); #Collects the result     
    
    if(len(s)%2==1):
       final.append(s[len(s)-1]); #Appends the last char is len(s) is odd

    return final;
                        
if __name__ == "__main__":
    s="";
    stringarr = master("ONPNRATIEIS"); 
    
    for i in range(0,len(stringarr)):  #Techically master's work. Turns the collected work into printable answer. 
        s+=stringarr[i];

    print s;
