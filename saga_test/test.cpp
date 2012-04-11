#include <saga/saga.hpp>
#include<stdlib.h>
#include<string.h>
#include<sstream>
#include<string>
int main(int argc, char* argv[])
{
  try 
  {
    // create an "echo 'hello, world' job"
    saga::job::description jd,jd2;
    jd.set_attribute("Interactive", "True");
    jd2.set_attribute("Interactive", "True");
    jd.set_attribute("Executable", "/home/andrew/Saga_code/b");
    jd2.set_attribute("Executable", "/home/andrew/Saga_code/c");

  
//jd.set_vector_attribute("Arguments",args);
//jd2.set_vector_attribute("Arguments",args2);

    // connect to the local job service
    saga::job::service js("fork://localhost");
 saga::job::service js2("fork://localhost");

    // submit the job
    saga::job::job job = js.create_job(jd);
saga::job::job job2 = js2.create_job(jd2);
  
  job.run();
job2.run();

    //wait for the job to complete
    job.wait(-1);
job2.wait(-1);
  
    // print the job's output
    saga::job::istream output = job.get_stdout();
saga::job::istream output2 = job2.get_stdout();

std::string line;
    while ( ! std::getline (output, line).eof () )
    {
     std::cout << line << std::endl;
    }
        //std::cout<<output<<std::endl;

//std::cout<<"A="<<a<<std::endl;
    while ( ! std::getline (output2, line).eof () )
    {
     std::cout << line << std::endl;
    }
//int b=atoi(line.c_str());
//std::cout<<"B="<<b<<std::endl;
        //std::cout<<"A="<<a<<"B="<<b<<std::endl;
  } 

