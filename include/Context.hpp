#include "Common.hpp"
#include "ThreadSafeQueue.hpp"

class Context
{
  public:
    Context()
      : exec(true)
    {
      std::cout << "start\n";
    }

    ~Context()
    {
      exec = false;

      std::cout << "end\n";

      for(auto& worker : _pool)
      {
	if(worker.joinable())
	{
	  worker.join();
	}
      }
    }
    
    void run()
    {
      _pool.resize(std::thread::hardware_concurrency() - 2 );

      for(auto& worker : _pool )
      {
	worker = std::thread(&Context::work, this);
      }

    }

    void post(const std::function<void(void)>& task)
    {
      _work.push(task);

    }
  private:

    void work()
    {
      while(exec)
      {
	auto task = _work.wait_and_pop();
	if( task )
	{
	  (*task)();
	}
      }
    }

  private:

    bool exec;

    std::vector<std::thread> _pool;
    ThreadSafeQueue<std::function<void(void)>> _work;

};
