/*
MIT License

Copyright (c) 2021 sethome

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
// 2021-5-17 sethome

#pragma once

#define __BASEDATACLASS_H__
#ifdef __BASEDATACLASS_H__

#include "stdint.h"

namespace LED_anima
{
  //向前声明
  class RGB_info;
  class HSV_info;

  //单个HSV信息
  class HSV_info
  {
  public:
    float H = 0;        // 0-360
    float S = 0, V = 0; // 0-1

  public:
    HSV_info();
    HSV_info(RGB_info setVal);

    ~HSV_info();

    void HSV(float setH, float setS, float setV);

    void toRGB(RGB_info &RGB);

    inline HSV_info operator+(const HSV_info other_color)
    {
      HSV_info mix_color;
      mix_color.H = (this->H + other_color.H) / 2.0f;
      mix_color.S = (this->S + other_color.S) / 2.0f;
      mix_color.V = (this->V + other_color.V) / 2.0f;
      return mix_color;
    }
    void operator=(RGB_info other_color);

    //基本颜色
    void red() { this->HSV(0, 1, 1); }
    void green() { this->HSV(120, 1, 1); }
    void blue() { this->HSV(240, 1, 1); }
    void yellow() { this->HSV(60, 1, 1); }
    void purple() { this->HSV(272.7, 1, 1); }
    void cyanblue() { this->HSV(210, 1, 1); }
    void orange() { this->HSV(38.8, 0, 0); }
    void blank() { this->HSV(0, 0, 0); }
  };

  //单个灯珠RGB信息
  class RGB_info
  {
  public:
    unsigned char A = 255, R = 0, G = 0, B = 0;

  public:
    RGB_info();
    RGB_info(HSV_info setVal);

    ~RGB_info();

    uint32_t RGB();

    void RGB(uint32_t RGB)
    {
      B = static_cast<uint32_t>(RGB);
      G = static_cast<uint32_t>(RGB) >> 8;
      R = static_cast<uint32_t>(RGB) >> 16;
    }

    void toHSV(HSV_info &HSV);

    inline RGB_info operator+(const RGB_info other_color)
    {
      RGB_info mix_color;
      mix_color.R = (static_cast<uint16_t>(this->R) + static_cast<uint16_t>(other_color.R)) / 2;
      mix_color.G = (static_cast<uint16_t>(this->G) + static_cast<uint16_t>(other_color.G)) / 2;
      mix_color.B = (static_cast<uint16_t>(this->B) + static_cast<uint16_t>(other_color.B)) / 2;
      return mix_color;
    }
    void operator=(HSV_info other_color);

    //基本颜色
    void red() { this->RGB(0xFF0000); }
    void green() { this->RGB(0x00FF00); }
    void blue() { this->RGB(0x0000FF); }
    void yellow() { this->RGB(0xFFFF00); }
    void purple() { this->RGB(0x8B00FF); }
    void cyanblue() { this->RGB(0x007FFF); }
    void orange() { this->RGB(0xFFA500); }
    void blank() { this->RGB(0x000000); }
  };
}

#endif
// end of file
