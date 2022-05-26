#include <Graphics.h>

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

void ProgressBar::eraze(LiquidCrystal lcd)
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

void Text::eraze(LiquidCrystal lcd)
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

Selector::Selector(int x_1, int y_1, int x_2, int y_2, int n, String* var)
{
  arr = var;
  x1 = x_1;
  x2 = x_2;
  y1 = y_1;
  y2 = y_2;
  s = n;
  h = abs(y2 - y1) + 1;
  l = abs(x2 - y2);
  visible = new int [h];
  for(int i = 0; i < h; i++) visible[i] = i;
}

void Selector::setPos(int p)
{
  if(p >= 0 && p < s) 
  {
    int delta = pos - p;
    if((delta == 1) && (pos == visible[0])) 
    {
      for(int i = 0; i < sizeof(visible); i++) visible[i] = visible[i] - delta;
    }
    if((delta == -1) && (pos == visible[sizeof(visible)-1])) 
    {
      for(int i = 0; i < sizeof(visible); i++) visible[i] = visible[i] - delta;
    }
    pos = p;
  }
}

void Selector::render(LiquidCrystal lcd, int* shifts)
{
  for(int i = 0; i < h; i++)
  {
    lcd.setCursor(x1, y1 + i);
    if(pos == visible[i]) lcd.print(">"); else lcd.print(" ");
    for(int j = 0; j < l; j++)
    {
     lcd.print(arr[visible[i]].substring(j, j + 1)); 
    }
  }
}

void Selector::eraze(LiquidCrystal lcd)
{
  for(int i = 0; i < h; i++)
  {
    for(int j = 0; j < l+1; j++)
    {
      lcd.setCursor(j, i);
      lcd.print(" ");
    }
  }
}
