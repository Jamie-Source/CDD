/*! \mainpage Lab 2
    \author Jamie Hawthorne
    \date 29/10/2020
    \copyright This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 
               International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
    \brief An Implementation of Threads Using Semaphores
    Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>

/*! \fn void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay)
    \brief This function takes in the semaphore and the delay. the task one signals once it has fully printed out.

/*! displays a message first*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();
}

/*! \fn void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
    \brief This function takes in the semaphore and the delay. the task is signaled to run once task one is completed.
/*! displays a message second*/
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

/*! \fn int main(void)
    \brief Main function of the program, creates the two threads and the semaphore.
*/   
int main(void)
{
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  /**< Launch the threads  */
  int taskOneDelay=5;
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish */
  threadOne.join();
  threadTwo.join();
  return 0;
}
