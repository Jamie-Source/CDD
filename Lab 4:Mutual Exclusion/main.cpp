/*!   \mainpage Lab 4
      \author Jamie Hawthorne
      \date 10/11/2020
      \copyright This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 
               International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
      \brief An Implementation of Mutual Exclusion using Semaphores
              Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions
*/


#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;

/*!   \fn void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates)
      \brief This function takes in the semaphore and number of numbers. it then loops through until each numbers has come in and shared variable updates each time.

*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){

 
  for(int i=0;i<numUpdates;i++){
    firstSem->Wait();
    //UPDATE SHARED VARIABLE HERE!
    sharedVariable++;
    firstSem->Signal();
  }

}

/*!   \fn int main(void)
      \brief Main function of this program. creates and calls two threads and semaphores. 

*/
int main(void){
  std::vector<std::thread> vt(num_threads);
/*!
      \brief here we are setting value of the first semaphore as one as we called wait before signal in order for code to function. withouth this the semaphore would go negative and be blocked!
*/ 
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore(1));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
