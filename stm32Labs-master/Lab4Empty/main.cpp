//#include <cstdint>            //for int types such as uint32_t
#include "gpioaregisters.hpp" //for Gpioa
#include "rccregisters.hpp"   //for RCC
#include "tim2registers.hpp"   //for SPI2
#include "nvicregisters.hpp"  //for NVIC
#include "tim5registers.hpp" //For TIM5
using namespace std ;



extern "C"
{
int __low_level_init(void)
{
  //3
  RCC::CR::HSION::On::Set(); 
  while(!RCC::CR::HSIRDY::Ready::IsSet());
  {
  }
  RCC::CFGR::SW::Hsi::Set();
  while(!RCC::CFGR::SWS::Hsi::IsSet());
  {
  }
  
  //4
  RCC::APB1ENR::TIM5EN::Enable::Set();
  //5
  RCC::AHB1ENR::GPIOAEN::Enable::Set();
  //6
  GPIOA::MODER::MODER5::Output::Set();
  
  //8
  TIM5::PSC::Write(15999);
  TIM5::ARR::Write(2000);
  //9
  NVIC::ISER1::Write(1 << 18);
  //10
  TIM5::CR1::URS::Overflow::Set();
  TIM5::DIER::UIE::Value1::Set() ;
  TIM5::CR1::CEN::Enable::Set();
  return 1;
}
}
template <typename Port, std::uint32_t pinNum>
struct Led //Realizacia perecluchenia cherez Toggle
{
  static void Toggle()
  {
    Port::ODR::Toggle(1<<pinNum);
  }
};

int main()
{
  for(;;)
  {
  }
  
  return 0 ;
}

