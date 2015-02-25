#include <iostream>
#include <thread>
 
void foo() 
{
  std::cout<<"foo"<<std::endl;
}

void bar(int x)
{
  for (int i=0;i<x;i++)
    std::cout<<"bar"<<std::endl;
}

int main() 
{
  std::cout<<"# of concurrent threads supported by hardware: "<<std::thread::hardware_concurrency()<<std::endl;

  std::thread first (foo);     // spawn new thread that calls foo()
  std::thread second (bar,5);  // spawn new thread that calls bar(5)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
}
