// Copyright 2024 GOTHAM Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

// refer to: https://rigtorp.se/spinlock/

#include <atomic>
#include <iostream>

class SpinLock {
 public:
  void lock() {
    while (lock_.exchange(true, std::memory_order_acquire)) {
    }
  }
  void unlock() { lock_.store(false, std::memory_order_release); }

 private:
  std::atomic_bool lock_ = {false};
};

int main(int argc, char** argv) { return 0; }
