// Copyright 2021 alexgiving

#include "TimedDoor.h"
#include <iostream>

int main() {
  TimedDoor door(5);
  try {
    door.lock();
    door.throwState();
  }
  catch(std::string message) {
    std::cout << message;
  }

  return 0;
}
