    import os
    import math

    #Simple MasterWorker Application using fork().
    #Given string s, the program reverses the first two char in string
    #And so on until it reaches end of string.
    #If the len(s) is odd, then the last character's position remains the same.


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
        input = raw_input('Enter a string to reverse\n');
        while(input==""): #Waits until input is valid
            pass;
        stringarr = master(input);
        for i in range(0,len(stringarr)):
            s+=stringarr[i];

        print s;


