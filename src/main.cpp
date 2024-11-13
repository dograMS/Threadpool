#include "Context.hpp"
#include <chrono>

int main(int argc, char *argv[])
{
  Context threadpool;

  for(int i = 1; i < 10; i++)
  {
    threadpool.post([i](){
	std::cout << "work - " << i << "\n";
	});
  }
  
  threadpool.run();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return 0;
}
