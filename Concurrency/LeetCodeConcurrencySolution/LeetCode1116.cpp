class ZeroEvenOdd
{
private:
    int n;
    std::mutex mtx;
    std::condition_variable cv_zero, cv_odd, cv_even;
    int state; // 0 for zero, 1 for odd, 2 for even

public:
    ZeroEvenOdd(int n) : n(n), state(0) {}

    // printNumber(x) outputs "x", where x is an integer.
    void zero(std::function<void(int)> printNumber)
    {
        for (int i = 1; i <= n; i++)
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv_zero.wait(lock, [this]
                         { return state == 0; });
            printNumber(0);
            state = (i % 2 == 1) ? 1 : 2;
            cv_odd.notify_one();
            cv_even.notify_one();
        }
    }

    void even(std::function<void(int)> printNumber)
    {
        for (int i = 2; i <= n; i += 2)
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv_even.wait(lock, [this]
                         { return state == 2; });
            printNumber(i);
            state = 0;
            cv_zero.notify_one();
        }
    }

    void odd(std::function<void(int)> printNumber)
    {
        for (int i = 1; i <= n; i += 2)
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv_odd.wait(lock, [this]
                        { return state == 1; });
            printNumber(i);
            state = 0;
            cv_zero.notify_one();
        }
    }
};
