/*! \mainpage Lab 3
    \author Jamie Hawthorne
    \date 30/10/2020
    \copyright This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 
               International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
    \brief An Implementation of a Rendezvous using Semaphores
    Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <chrono>

/*! \fn void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay)
    \brief This code takes in 2 sempahores 1 set to signal and wait. the first one signals onece the thread arrives and sets second to wait until first arrives
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task One has arrived! "<< std::endl;
  //THIS IS THE RENDEZVOUS POINT!
  firstSem->Signal();
  secondSem->Wait();
  std::cout << "Task One has left!"<<std::endl;
}
/*! \fn void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay)
    \brief This code is the opposit to the one above now the second semaphor has signaled it has arrived and first is now set to wait
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task Two has arrived "<<std::endl;
  //THIS IS THE RENDEZVOUS POINT!wedw
  secondSem->Signal();
  firstSem->Wait();
  std::cout << "Task Two has left "<<std::endl;
}

/*! \fn int main(void)
    \brief This is the main function for this code. it creats the semaphores and sets the delays. it also calls task one and two.
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> sem2( new Semaphore);
  int taskOneDelay=5;
  int taskTwoDelay=1;
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem1,sem2,taskTwoDelay);
  threadTwo=std::thread(taskOne,sem1,sem2,taskOneDelay);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
