#include "time_calendar.hpp"
#include "config.hpp"

Time_calendar::Time_calendar() {}

Time_calendar::~Time_calendar() {}

void Time_calendar::tick() {
    seconds++;
    
    if(!(seconds%60) && seconds) {
      minutes++;
      seconds=0;
    }
    
    if(!(minutes%60) && minutes) {
      hours++;
      minutes=0;
    }
    
    if(!(hours%24) && hours) {
      days++;
      hours=0;
    }

    int leap_year = 0;
    if((years%400==0 || (years%4==0 && years%100!=0)) && months==1) {
      leap_year = 1;
    }

    if(!(days%day_count[months] + leap_year) && days) {
      months++;
      days=0;
    }
    
    if(!(months%12) && months) {
      years++;
      months=0;
    }
}

String Time_calendar::time_date() {
    String time_date_str;

    time_date_str += String(years);
    time_date_str += ":";
    time_date_str += String(months);
    time_date_str += ":";
    time_date_str += String(days);
    time_date_str += ":";
    time_date_str += String(hours);
    time_date_str += ":";
    time_date_str += String(minutes);
    time_date_str += ":";
    time_date_str += String(seconds);

    return time_date_str;
}

bool Time_calendar::changed() {
  bool changed = seconds != prev_seconds;
  prev_seconds = seconds;
  return changed;
}

void Time_calendar::set_time(int hours, int minutes, int seconds) {
  this->hours = hours;
  this->minutes = minutes;
  this->seconds = seconds;
}
void Time_calendar::set_date(int year, int month, int day) {
  years = year;
  months = month;
  days = day;
}