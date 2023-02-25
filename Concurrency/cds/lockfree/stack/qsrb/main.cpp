// This stack relies on the existence of quiscent states in order to reclaim nodes.

#include <iostream>
#include <vector>
#include <future>

#include "stack.hpp"

constexpr static auto const N_PRODUCERS = 2ul;
constexpr static auto const N_CONSUMERS = 2ul;

constexpr static auto const WORK_PER_THREAD = 100ul;

std::size_t producer(stack<std::size_t>& s)
{
    std::size_t pushed{0};
    for (auto i = 0ul; i < WORK_PER_THREAD; ++i)
    {
        s.push(i);
        ++pushed;
    }

    return pushed;
}

std::size_t consumer(stack<std::size_t>& s)
{
    std::size_t popped{0};
    for (auto i = 0ul; i < WORK_PER_THREAD; ++i)
    {
        auto result = s.pop();
        ++popped;
    }

    return popped;
}

int main(){
    using results_t = std::vector<std::future<std::size_t>>;

    stack<std::size_t> s{};

    assert(s.is_empty_unsafe());

    results_t producer_results{};
    for (auto i = 0ul; i < N_PRODUCERS; ++i)
    {
        producer_results.emplace_back(
                std::async(std::launch::async, producer, std::ref(s)));
    }

    results_t consumer_results{};
    for (auto i = 0ul; i < N_CONSUMERS; ++i)
    {
        consumer_results.emplace_back(
                std::async(std::launch::async, consumer, std::ref(s)));
    }

    for (auto& fut : producer_results)
    {
        assert(fut.get() == WORK_PER_THREAD);
    }

    for (auto& fut : consumer_results)
    {
        assert(fut.get() == WORK_PER_THREAD);
    }

    // drain the stack contents
    std::shared_ptr<std::size_t> popped{};
    do
    {
        popped = s.pop();
    } while (popped);

    assert(s.is_empty_unsafe());
    return 0;
}