#include "TimePoint.h"

#include <cstdlib>
#include <iostream>
#include <cmath>

int main() {
  TimePoint time1, time2, clock;

  time1.Input();
  time2.Input();

  std::cout<<"\ngetters:" << time1.GetHours()<< ' '<< time1.GetMinutes() << ' ' << time1.GetSeconds()<<"\n";

  time1.SetHours(13);
  time1.SetMinutes(14);
  time1.SetSeconds(15);
  time1.Output();

  std::cout << "\n\nsumma:"; (time1+time2).Output();
  std::cout << "rasnost:"; (time1-time2).Output();

  std::cout << "\nbolshe:"; 
  if (time1>time2)
    std::cout<<"1";
  else
    std::cout<<0;

  std::cout << "\nmenshe:"; 
  if (time1<time2)
    std::cout<<"1";
  else
    std::cout<<0;

    std::cout << "\nravno::"; 
  if (time1==time2)
    std::cout<<"1";
  else
    std::cout<<0;

  std::cout << "\n\nTimes of day:" << time1.TimesOfDay();
  std::cout << "\nenter clock ";
  clock.Input();
  std::cout<<"Will ring today?\n"<<time1.WillRingToday(clock)<<"\n";
  (time1.GetAlarmTime(clock)).Output();

}
