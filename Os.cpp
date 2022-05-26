#include <Os.h>

Os::Os()
{
  n = 0;
  apps = {};
  app_list = {};
}

void Os::app(String name, void(*pointer)())
{
  void (**newapps) = new void*[n + 1];
  String (*app_list_new) = new String[n + 1];
  for(int i = 0; i < n; i++) newapps[i] = apps[i];
  for(int i = 0; i < n; i++) app_list_new[i] = app_list[i];
  newapps[n] = pointer;
  app_list_new[n] = name;
  n++;
  delete[] apps;
  delete[] app_list;
  app_list = app_list_new;
  apps = newapps;
}

void Os::run_app(String name)
{
  int index = -1;
  for(int i = 0; i < n; i++) if(app_list[i] == name) index = i;
  if(index != -1) apps[index]();
} 
