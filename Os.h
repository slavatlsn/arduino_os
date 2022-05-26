#pragma once
#include <Arduino.h>

class Os
{
  public:
  Os();
  int n;
  void** (**apps)();
  String* app_list;
  void app(String name, void(*pointer)());
  void run_app(String name);
};
