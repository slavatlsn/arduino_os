#include <Graphics.h>

ProgressBar::ProgressBar()
{
  x1 = 0;
  x2 = 0;
  y1 = 0;
  y2 = 0;
}

ProgressBar::ProgressBar(int x_1, int y_1, int x_2, int y_2)
{
  x1 = x_1;
  x2 = x_2;
  y1 = y_1;
  y2 = y_2;
}

void ProgressBar::setProgress(int pr)
{
  progress = pr;
}

void ProgressBar::render(LiquidCrystal lcd, String type)
{
  if(type == "horizontal")
  {
    int l = abs(x2 - x1) + 1;
    int n = round(l * progress / 100);
    float x = l * progress / 100.0 - n;
    int k = round(5 * x);
    lcd.createChar(1, one_line);
    lcd.createChar(2, two_lines);
    lcd.createChar(3, three_lines);
    lcd.createChar(4, four_lines);
    lcd.createChar(5, five_lines);
    for(int i = 0; i < abs(y2 - y1) + 1; i++)
    {
      lcd.setCursor(x1, y1 + i);
      for(int j = 0; j < n; j++) lcd.write(byte(5));
      if(k != 0) lcd.write((byte)k);
      if(k == 0) 
      {
       lcd.setCursor(x1 + n, y1 + i);
       for(int x = n; x < l; x++) lcd.print(" ");
      } 
      else
      {
        lcd.setCursor(x1 + n + 1, y1 + i);
        for(int x = n + 1; x < l; x++) lcd.print(" "); 
      }
    }
  }
  else if(type == "vertical")
  {
    int h = abs(y2 - y1) + 1;
    int n = round(h * progress / 100);
    float x = h * progress / 100.0 - n;
    int k = round(8 * x) - 1;
    lcd.createChar(0, one_line_v);
    lcd.createChar(1, two_lines_v);
    lcd.createChar(2, three_lines_v);
    lcd.createChar(3, four_lines_v);
    lcd.createChar(4, five_lines_v);
    lcd.createChar(5, six_lines_v);
    lcd.createChar(6, seven_lines_v);
    lcd.createChar(7, eight_lines_v);
    for(int i = 0; i < abs(x2 - x1) + 1; i++)
    {
      for(int j = 0; j < n; j++) 
      {
        lcd.setCursor(x1 + i, y2 - j);
        lcd.write((byte)7);
      }
      lcd.setCursor(x1 + i, y2 - n);
      if(k != -1) lcd.write((byte)k);
      if(k == -1) 
      {
       for(int x = n; x < h; x++)
       {
         lcd.setCursor(x1 + i, y2 - x);
         lcd.print(" ");
       }
      } 
      else
      {
        for(int x = n + 1; x < h; x++)
        {
         lcd.setCursor(x1 + i, y2 - x);
         lcd.print(" ");
        } 
      }
    }
  }
}

void ProgressBar::erase(LiquidCrystal lcd)
{
  for(int i = 0; i < abs(x2 - x1) + 1; i++)
    {
      for(int j = 0; j < abs(y2 - y1) + 1; j++) 
      {
        lcd.setCursor(x1 + i, y1 + j);
        lcd.print(" "); 
      }
    }  
}

//----------------------------------------------------------------------------------------------------------------

Text::Text(int x_1, int y_1, int x_2, int y_2) 
{
  x1 = 0;
  x2 = 0;
  y1 = 0;
  y2 = 0;
}

Text::Text(int x_1, int y_1, int x_2, int y_2) 
{
  x1 = x_1;
  x2 = x_2;
  y1 = y_1;
  y2 = y_2;
}

void Text::setText(String str)
{
  int n = (abs(y2 - y1) + 1) * (abs(x2 - x1) + 1);
  text = str;
  int k = round(str.length() / n) + 1;
  if(str.length() < n) for(int i = 0; i < n - str.length(); i++) text = text + " "; else for(int i = 0; i < n * k - str.length(); i++) text = text + " ";
}

void Text::render(LiquidCrystal lcd, int shift)
{
  String text2;
  if(shift == 0) text2 = text; else text2 = text.substring(shift, text.length()) + text.substring(0, shift);
  int l = abs(x2 - x1) + 1;
  int j = y1;
  for(int i = 0; i < text2.length(); i++)
  {
     String sym = text2.substring(i, i + 1);
     if(x1 + i - l * (j - y1) <= x2) 
     {
     lcd.setCursor(x1 + i - l * (j - y1), j);
     lcd.print(sym);
     }
     else
     {
        if(j < y2) 
        {
          j++; 
          lcd.setCursor(x1 + i - l * (j - y1), j);
          lcd.print(sym);
        }
     }
  }
}

void Text::erase(LiquidCrystal lcd)
{
  int l = abs(x2 - x1) + 1;
  int h = abs(y2 - y1) + 1;
  for(int i = 0; i < h; i++)
  {
    for(int j = 0; j < l; j++)
    {
      lcd.setCursor(x1 + j, y1 + i);
      lcd.print(" ");
    }
  }
}

//----------------------------------------------------------------------------------------------------------------

Selector::Selector(int x_1, int y_1, int x_2, int y_2, int n, String* var)
{
  arr = var;
  x1 = x_1;
  x2 = x_2;
  y1 = y_1;
  y2 = y_2;
  s = n;
}

void Selector::setPos(int p)
{
  if(p >= 0 && p < s) pos = p;
}

void Selector::render(LiquidCrystal lcd, int shift)
{
  Text text(x1, y1, x2, y1);
  text.setText(arr[pos]);
  text.render(lcd, shift);
}

void Selector::erase(LiquidCrystal lcd)
{
  for(int i = x1; i < x2 + 1; i++)
  {
    for(int j = y1; j < y2 + 1; j++)
    {
      lcd.setCursor(j, i);
      lcd.print(" ");
    }
  }
}

//----------------------------------------------------------------------------------------------------------------

Bitmap::Bitmap(int (*dots)[2], int n, int x1, int y1, int x2, int y2)
{
  _dots = dots;
  _x1 = x1;
  _y1 = y1;
  _y2 = y2;
  _x2 = x2;
  _n = n;
}

void Bitmap::render(LiquidCrystal lcd)
{
  int a = 0;
  int cols = abs(_x1 - _x2) + 1;
  int rows = abs(_y1 - _y2) + 1;
  if(rows*cols <= 8)
  {
    for(int i = 0; i < rows; i++)
    {
      for(int j = 0; j < cols; j++)
      {
        const byte variants[5] =
        {
          0b10000,
          0b01000,
          0b00100,
          0b00010,
          0b00001
        };
      
        byte chunk[8] 
        {
          0b00000,
          0b00000,
          0b00000,
          0b00000,
          0b00000,
          0b00000,
          0b00000,
          0b00000
        };
        int xmin = j*5;
        int xmax = (j+1)*5;
        int ymin = (rows-i-1)*8;
        int ymax = (rows-i)*8;
        for(int k = 0; k < _n; k++)
        {
          if((_dots[k][0] > xmin) && (_dots[k][1] > ymin) && (_dots[k][0] <= xmax) && (_dots[k][1] <= ymax)) 
          {
            chunk[8 - _dots[k][1] + ymin] += variants[_dots[k][0] - xmin - 1];
          }
        }
        lcd.createChar(a, chunk);
        lcd.setCursor(j, i);
        lcd.write((byte)a);
        a++;
      }
    }
  }
}

void Selector::erase(LiquidCrystal lcd)
{
  for(int i = x1; i < x2 + 1; i++)
  {
    for(int j = y1; j < y2 + 1; j++)
    {
      lcd.setCursor(j, i);
      lcd.print(" ");
    }
  }
}
