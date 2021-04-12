// Copyright 2021 alexgiving

#include "TimedDoor.h"
#include <string>

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& _door) : door(_door) {
  this->door = _door;
}

void DoorTimerAdapter::Timeout() {
  Timer timer{};
  timer.tregister(this->door.getTime(), this);
  TimedDoor::DoorTimeOut();
}

TimedDoor::TimedDoor(int _time) {
  iTimeout = _time;
  opened = false;
  adapter = new DoorTimerAdapter(*this);
}

bool TimedDoor::isDoorOpened() {
  return opened;
}

int TimedDoor::getTime() const {
  return iTimeout;
}

void TimedDoor::lock() {
  opened = false;
}

void TimedDoor::unlock() {
  opened = true;
  adapter->Timeout();
}

void TimedDoor::DoorTimeOut() {
  throw static_cast<std::string>("close the door!");
}

void TimedDoor::throwState() {
  if (!opened)
    throw static_cast<std::string>("the door is closed!");
  if (opened)
    throw static_cast<std::string>("the door is opened!");
}

void Timer::sleep(int _time) {
  time_t start = time(nullptr);
  while (time(nullptr) - start < _time) {}
}

void Timer::tregister(int _time, TimerClient* _client) {
  client = _client;
  sleep(_time);
}