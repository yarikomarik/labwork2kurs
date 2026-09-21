#include "TimePoint.h"

#include <cstdlib>
#include <iostream>

TimePoint::TimePoint() : hours_(0), minutes_(0), seconds_(0) {}

TimePoint::TimePoint(int h, int m, int s) {
  Proverka(h, m, s);
  hours_ = h;
  minutes_ = m;
  seconds_ = s;
}

void TimePoint::Proverka(int h, int m, int s) const {
  if (h == 24 && m == 0 && s == 0) {
    return;
  }
  if (h < 0 || h > 23) {
    std::cout << "invalid hours";
    std::exit(1);
  }
  if (m < 0 || m > 59) {
    std::cout << "invalid minutes";
    std::exit(1);
  }
  if (s < 0 || s > 59) {
    std::cout << "invalid seconds";
    std::exit(1);
  }
}

int TimePoint::ToSeconds() const {
  return hours_ * 60 * 60 + minutes_ * 60 + seconds_;
}

int TimePoint::GetHours() const {
  return hours_;
}

int TimePoint::GetMinutes() const {
  return minutes_;
}

int TimePoint::GetSeconds() const {
  return seconds_;
}

void TimePoint::SetHours(int h) {
  Proverka(h, minutes_, seconds_);
  hours_ = h;
}

void TimePoint::SetMinutes(int m) {
  Proverka(hours_, m, seconds_);
  minutes_ = m;
}

void TimePoint::SetSeconds(int s) {
  Proverka(hours_, minutes_, s);
  seconds_ = s;
}

void TimePoint::Input() {
  int h, m, s;
  std::cout << "print hours, minutes, seconds:";
  std::cin >> h >> m >> s;
  Proverka(h, m, s);
  hours_ = h;
  minutes_ = m;
  seconds_ = s;
}

void TimePoint::Output() const {
  if (hours_ < 10) {
    std::cout << '0' << hours_ << ':';
  } else {
    std::cout << hours_ << ':';
  }
  if (minutes_ < 10) {
    std::cout << '0' << minutes_ << ':';
  } else {
    std::cout << minutes_ << ':';
  }
  if (seconds_ < 10) {
    std::cout << '0' << seconds_ << std::endl;
  } else {
    std::cout << seconds_ << std::endl;
  }
}

TimePoint TimePoint::operator+(const TimePoint& other) const {
  int h = hours_ + other.hours_;
  int m = minutes_ + other.minutes_;
  int s = seconds_ + other.seconds_;

  m = m + s / 60;
  s = s % 60;
  h = h + m / 60;
  m = m % 60;

  return TimePoint(h, m, s);
}

TimePoint TimePoint::operator-(const TimePoint& other) const {
  int h = hours_ - other.hours_;
  int m = minutes_ - other.minutes_;
  int s = seconds_ - other.seconds_;

  if (s < 0) {
    --m;
    s += 60;
  }
  if (m < 0) {
    --h;
    m += 60;
  }
  return TimePoint(h, m, s);
}

bool TimePoint::operator>(const TimePoint& other) const {
  return ToSeconds() > other.ToSeconds();
}

bool TimePoint::operator<(const TimePoint& other) const {
  return ToSeconds() < other.ToSeconds();
}

bool TimePoint::operator>=(const TimePoint& other) const {
  return ToSeconds() >= other.ToSeconds();
}

bool TimePoint::operator<=(const TimePoint& other) const {
  return ToSeconds() <= other.ToSeconds();
}

bool TimePoint::operator==(const TimePoint& other) const {
  return ToSeconds() == other.ToSeconds();
}

bool TimePoint::operator!=(const TimePoint& other) const {
  return ToSeconds() != other.ToSeconds();
}

std::string TimePoint::TimesOfDay() const {
  TimePoint night(5, 59, 59);
  TimePoint morning(11, 59, 59);
  TimePoint day(17, 59, 59);

  if (*this <= night) {
    return "night";
  }
  if (*this <= morning) {
    return "morning";
  }
  if (*this <= day) {
    return "day";
  }
  return "evening";
}

TimePoint TimePoint::GetAlarmTime(const TimePoint& alarm) const {
  if (*this <= alarm) {
    return alarm - *this;
  }
  return TimePoint(24, 0, 0) - *this + alarm;
}

bool TimePoint::WillRingToday(const TimePoint& alarm) const {
  return *this <= alarm;
}