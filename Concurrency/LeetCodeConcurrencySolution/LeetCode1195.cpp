#include <iostream>
#include <condition_variable>
#include <thread>

using namespace std;

class FizzBuzz
{
private:
    int n;
    int cur;
    mutex mtx;
    condition_variable cv;

public:
    FizzBuzz(int n) : n(n), cur(1) {}

    void fizz(function<void()> printFizz)
    {
        while (true)
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this]
                    { return cur > n || cur % 3 == 0 && cur % 5 != 0; });
            if (cur > n)
            {
                break;
            }
            printFizz();
            cur++;
            cv.notify_all();
        }
    }

    void buzz(function<void()> printBuzz)
    {
        while (true)
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this]
                    { return cur > n || cur % 3 != 0 && cur % 5 == 0; });
            if (cur > n)
            {
                break;
            }
            printBuzz();
            cur++;
            cv.notify_all();
        }
    }

    void fizzbuzz(function<void()> printFizzBuzz)
    {
        while (true)
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this]
                    { return cur > n || cur % 3 == 0 && cur % 5 == 0; });
            if (cur > n)
            {
                break;
            }
            printFizzBuzz();
            cur++;
            cv.notify_all();
        }
    }

    void number(function<void(int)> printNumber)
    {
        while (true)
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this]
                    { return cur > n || cur % 3 != 0 && cur % 5 != 0; });
            if (cur > n)
            {
                break;
            }
            printNumber(cur);
            cur++;
            cv.notify_all();
        }
    }
};

int main()
{
    FizzBuzz fizzBuzz(15);
    auto fizz = []
    { cout << "fizz" << endl; };
    auto buzz = []
    { cout << "buzz" << endl; };
    auto fizzbuzz = []
    { cout << "fizzbuzz" << endl; };
    auto number = [](int x)
    { cout << x << endl; };
    thread t1(&FizzBuzz::fizz, &fizzBuzz, fizz);
    thread t2(&FizzBuzz::buzz, &fizzBuzz, buzz);
    thread t3(&FizzBuzz::fizzbuzz, &fizzBuzz, fizzbuzz);
    thread t4(&FizzBuzz::number, &fizzBuzz, number);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
