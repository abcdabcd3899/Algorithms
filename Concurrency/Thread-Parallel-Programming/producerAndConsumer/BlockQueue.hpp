#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
template <typename T, typename Container = std::queue<T>>
class ThreadQueue
{
public:
    using container_type           = Container;
    using value_type               = typename Container::value_type;
    using reference                = typename Container::reference;
    using const_reference          = typename Container::const_reference;
    using size_type                = typename Container::size_type;
    using mutex_type               = std::mutex;
    using condition_variable_type  = std::condition_variable;
private:
    Container                queue_;
    mutable mutex_type       mutex_;
    condition_variable_type  cond_;

public:
    ThreadQueue() = default;
    ThreadQueue( const ThreadQueue & ) = delete;
    ThreadQueue &operator=( const ThreadQueue & ) = delete;
    void pop( reference elem )
    {
        std::unique_lock<mutex_type> lock( mutex_ );
        cond_.wait( lock, [this]() {  return !queue_.empty();  } );
        elem = std::move( queue_.front() );
        queue_.pop();
    }
    bool try_pop( reference elem )
    {
        std::unique_lock<mutex_type> lock( mutex_ );
        if( queue_.empty() ) {
            return false;
        }
        elem = std::move( queue_.front() );
        queue_.pop();
        return true;
    }

    bool empty() const
    {
        std::lock_guard<mutex_type> lock( mutex_ );
        return queue_.empty();
    }

    size_type size() const
    {
        std::lock_guard<mutex_type> lock( mutex_ );
        return queue_.size();
    }

    void push( const value_type &elem )
    {
        {
            std::lock_guard<mutex_type> lock( mutex_ );
            queue_.push( elem );
        }
        cond_.notify_one();
    }
    void push( value_type &&elem )
    {
        {
            std::lock_guard<mutex_type> lock( mutex_ );
            queue_.push( std::move( elem ) );
        }
        cond_.notify_one();
    }
};


// Testing Code
#include "ThreadQueue.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <thread>
using namespace std;
ThreadQueue<string> messageQueue;
mutex print_mtx;
void provider( int product_num, int wait_seconds )
{
    for( int i = 0; i < product_num; ++i )
    {
        string message( "Message-" );
        message.append( to_string( i ) );
        messageQueue.push( message );
        this_thread::sleep_for( chrono::seconds( wait_seconds ) );
    }
    lock_guard<mutex> guard( print_mtx );
    cout << "All works done!" << endl;
}
void consumer( int consumer_id )
{
    while( true )
    {
        string message;
        messageQueue.pop( message );
        {
            lock_guard<mutex> guard( print_mtx );
            cout << "consumer-" << consumer_id << " receive: " << message << endl;
        }
    }
}
int main()
{
    thread pvi{ provider, 10, 1 };
    thread csm1{ consumer, 1 };
    thread csm2{ consumer, 2 };
    pvi.join();
    csm1.join();
    csm2.join();

    return 0;
}
