//
// Created by Sergey on 21.11.2019.
//

#ifndef REGISTERS_INTERRUPTHANDLER_HPP
#define REGISTERS_INTERRUPTHANDLER_HPP


#include "tim2registers.hpp"  //for TIM2
#include "tim5registers.hpp" 
#include "gpiocregisters.hpp"  //for TIM2
#include "gpioaregisters.hpp"

class InterruptHandler {
  public:
    static void DummyHandler() { for(;;) {} }
    static void Timer2Handler()
    {
      if (TIM2::SR::UIF::UpdatePending::IsSet())
      {
        TIM2::SR::UIF::NoUpdate::Set();
        GPIOC::ODR::Toggle(1 << 8) ;
      }
    }
    //7
    static void Timer5Handler()
    {
      if (TIM5::SR::UIF::UpdatePending::IsSet())
      {
        TIM5::SR::UIF::NoUpdate::Set();
    GPIOA::ODR::Toggle(1 << 5) ;
      }
    }
};

#endif //REGISTERS_INTERRUPTHANDLER_HPP
