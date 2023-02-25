#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class DiningPhilosophers
{
public:
    DiningPhilosophers()
    {
        for (int i = 0; i < 5; i++)
        {
            forks[i] = true;
        }
    }

    void wantsToEat(int philosopher,
                    std::function<void()> pickLeftFork,
                    std::function<void()> pickRightFork,
                    std::function<void()> eat,
                    std::function<void()> putLeftFork,
                    std::function<void()> putRightFork)
    {
        int leftFork = philosopher;
        int rightFork = (philosopher + 1) % 5;

        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this, leftFork, rightFork]
                { return forks[leftFork] && forks[rightFork]; });

        pickLeftFork();
        forks[leftFork] = false;
        pickRightFork();
        forks[rightFork] = false;

        eat();

        putLeftFork();
        forks[leftFork] = true;
        putRightFork();
        forks[rightFork] = true;

        lock.unlock();
        cv.notify_all();
    }

private:
    bool forks[5];
    std::mutex mtx;
    std::condition_variable cv;
};
