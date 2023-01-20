#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

class Text
{
  public:
    int x1, x2, y1, y2;
    String text;
    Text();
    Text(int x_1, int y_1, int x_2, int y_2);
    void setText(String str);
    void render(LiquidCrystal lcd, int shift);
    void erase(LiquidCrystal lcd);
};

class ProgressBar
{
  public:
    int progress;
    int x1, x2, y1, y2;
    const byte one_line[8] 
    {
     0b10000,
     0b10000,
     0b10000,
     0b10000,
     0b10000,
     0b10000,
     0b10000,
     0b10000
    };

    const byte two_lines[8] 
    {
     0b11000,
     0b11000,
     0b11000,
     0b11000,
     0b11000,
     0b11000,
     0b11000,
     0b11000
    };

    const byte three_lines[8] 
    {
     0b11100,
     0b11100,
     0b11100,
     0b11100,
     0b11100,
     0b11100,
     0b11100,
     0b11100
    };

    const byte four_lines[8] 
    {
     0b11110,
     0b11110,
     0b11110,
     0b11110,
     0b11110,
     0b11110,
     0b11110,
     0b11110
    };

    const byte five_lines[8] 
    {  
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111
    };

    const byte one_line_v[8] 
    {  
     0b00000,
     0b00000,
     0b00000,
     0b00000,
     0b00000,
     0b00000,
     0b00000,
     0b11111
    };  

    const byte two_lines_v[8] 
    {  
     0b00000,
     0b00000,
     0b00000,
     0b00000,
     0b00000,
     0b00000,
     0b11111,
     0b11111
    };  

    const byte three_lines_v[8] 
    {  
     0b00000,
     0b00000,
     0b00000,
     0b00000,
     0b00000,
     0b11111,
     0b11111,
     0b11111
    };  

    const byte four_lines_v[8] 
    {  
     0b00000,
     0b00000,
     0b00000,
     0b00000,
     0b11111,
     0b11111,
     0b11111,
     0b11111
    };  

    const byte five_lines_v[8] 
    {  
     0b00000,
     0b00000,
     0b00000,
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111
    };  

    const byte six_lines_v[8] 
    {  
     0b00000,
     0b00000,
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111
    };    

    const byte seven_lines_v[8] 
    {  
     0b00000,
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111
    };  

    const byte eight_lines_v[8] 
    {  
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111,
     0b11111
    };                
    ProgressBar();
    ProgressBar(int x_1, int y_1, int x_2, int y_2);
    void setProgress(int pr);
    void render(LiquidCrystal lcd, String type);
    void erase(LiquidCrystal lcd);
};

class Selector
{
  public:
  int pos;
  int x1, x2, y1, y2, s;
  String* arr;
  Selector(int x_1, int y_1, int x_2, int y_2, int n, String* var);
  void setPos(int p);
  void render(LiquidCrystal lcd, int shift);
  void erase(LiquidCrystal lcd);
};

class Bitmap
{
  public:
    Bitmap(int (*dots)[2], int n, int x1, int y1, int x2, int y2);
    void render(LiquidCrystal lcd);
    void erase(LiquidCrystal lcd);
  private:  
    int (*_dots)[2];
    int _x1, _x2, _y1, _y2, _n;  
};
