#pragma once

#include <string>

class TimePoint {
public:
  TimePoint();
  TimePoint(int h, int m, int s);

  int ToSeconds() const;

  int GetHours() const;
  int GetMinutes() const;
  int GetSeconds() const;

  void SetHours(int h);
  void SetMinutes(int m);
  void SetSeconds(int s);

  void Input();
  void Output() const;

  TimePoint operator+(const TimePoint& other) const;
  TimePoint operator-(const TimePoint& other) const;

  bool operator>(const TimePoint& other) const;
  bool operator<(const TimePoint& other) const;
  bool operator>=(const TimePoint& other) const;
  bool operator<=(const TimePoint& other) const;
  bool operator==(const TimePoint& other) const;
  bool operator!=(const TimePoint& other) const;

  std::string TimesOfDay() const;
  TimePoint GetAlarmTime(const TimePoint& alarm) const;
  bool WillRingToday(const TimePoint& alarm) const;

private:
  int hours_;
  int minutes_;
  int seconds_;

  void Proverka(int h, int m, int s) const;
};