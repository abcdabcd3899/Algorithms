#include <iostream>
#include <vector>
#include <thread>
#include "pcqueue.hpp"

void producer(PCQueue<std::size_t>& queue)
{
    for (auto i = 0ul; i < WORK_PER_THREAD; ++i)
    {
        queue.push(i);
    }
}

void consumer(PCQueue<std::size_t>& queue)
{
    std::size_t pop_count{0};
    while (pop_count < WORK_PER_THREAD)
    {
        // pop() may return empty shared_ptr in the event queue is empty
        auto popdata = queue.pop();
        if (popdata)
        {
            ++pop_count;
        }
    }
}

int main(){
    std::cout << "PCQueue supports concurrent operations!" << std::endl;

    PCQueue<std::size_t> queue{};

    assert(queue.is_empty_unsafe());

    std::vector<std::thread> threads{};

    for (auto i = 0ul; i < N_WORKER_PAIRS; ++i){
        threads.emplace_back(producer, std::ref(queue));
        threads.emplace_back(consumer, std::ref(queue));
    }

    for (auto& t: threads){
        t.join();
    }
    std::cout << "PCQueue is end!" << std::endl;
    assert(queue.is_empty_unsafe());
    return 0;
}
