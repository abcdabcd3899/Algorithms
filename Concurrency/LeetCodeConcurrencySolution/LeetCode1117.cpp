class H2O {
 private:
  std::condition_variable cv;
  std::atomic<int> hydrogen_count;
  std::atomic<int> oxygen_count;

 public:
  H2O() : hydrogen_count(0), oxygen_count(0) {}

  void hydrogen(function<void()> releaseHydrogen) {
    while (hydrogen_count >= 2) {
      std::this_thread::yield();
    }
    ++hydrogen_count;
    if (hydrogen_count == 2 && oxygen_count == 1) {
      hydrogen_count = 0;
      oxygen_count = 0;
      cv.notify_all();
    }
    releaseHydrogen();
  }

  void oxygen(function<void()> releaseOxygen) {
    while (hydrogen_count < 2) {
      std::this_thread::yield();
    }
    ++oxygen_count;
    if (hydrogen_count == 2 && oxygen_count == 1) {
      hydrogen_count = 0;
      oxygen_count = 0;
      cv.notify_all();
    }
    releaseOxygen();
  }
};
