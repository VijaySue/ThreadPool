#include <iostream>
#include <vector>
#include <chrono>
#include "ThreadPool.h"

int main()
{

    ThreadPool pool(4);                                                  // create thread pool with 4 worker threads
    std::vector< std::future<int> > results;

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(pool.enqueue([i] {                          // enqueue and store future
            std::cout << "hello " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "world " << i << std::endl;
            return i * i;
            })
        );
    }

    for (auto&& result : results) std::cout << result.get() << ' ';     // get result from future
    std::cout << '\n';

    return 0;
}
