# stdx-chrono-timer-prototype

This is simple timer prototype for C++11 and later with no dependencies. 

## Usage

```cpp
#include "timer.hpp"

int main() {
  //this is timer with 1 sec interval and stops at main scope finishes or
  //explicitly call to t1.stop() func.
  stdx::chrono::timer t1(std::chrono::milliseconds(1000),[]{
    //callable func
    });
    
  //this is another style for create timer and connect and start
  stdx::chrono::timer t2;
  t2.set_interval(std::chrono::milliseconds(2000));
  t2.connect([]{
      //callable func
    });
  t2.start();
    
  //this is singleshot timer
  stdx::chrono::timer t3;
  t3.singleshot(std::chrono::milliseconds(1000),[]{
      //callable func
    });
      
  std::this_thread::sleep_for(std::chrono::seconds(10));
      
}
 
 ```
