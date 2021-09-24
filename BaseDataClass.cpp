//2021-5-28 sethome

//LED_anima Lib
#include "BaseDataClass.h"

//C++ STD Lib
#include "cmath"

//比较大小的宏定义（色域转换函数用）
#define THREE_MAX(a, b, c) (a > b ? (a > c ? a : c) : (b > c ? b : c)) //输出三个数中最大数
#define THREE_MIN(a, b, c) (a > b ? (b > c ? c : b) : (a > c ? c : a)) //输出三个数中最小数

using namespace LED_anima;


HSV_info::HSV_info(){};
HSV_info::HSV_info(RGB_info setVal) { setVal.toHSV(*this); }

/**
 * @description: HSV_info析构函数
 */
HSV_info::~HSV_info(){};

/**
 * @description: 设定HSV颜色参数
 * @param: H色相 S饱和度 V明度
 * @return: N/a 
 */
void HSV_info::HSV(float setH, float setS, float setV)
{
  H = setH;
  S = setS;
  V = setV;
}

//@brief 色域颜色转换
//@param 接受转换结果变量
void HSV_info::toRGB(RGB_info &RGB)
{
  int h_i = floor(this->H / 60.0f);
  float f = (this->H / 60.0f) - h_i;
  float V_by255 = this->V * 255.0f;

  float p = V_by255 * (1.0f - this->S);
  float q = V_by255 * (1.0f - f * this->S);
  float t = V_by255 * (1.0f - (1.0f - f) * this->S);

  switch (h_i)
  {
  case 0:
    RGB.R = V_by255;
    RGB.G = t;
    RGB.B = p;
    return;
  case 1:
    RGB.R = q;
    RGB.G = V_by255;
    RGB.B = p;
    return;
  case 2:
    RGB.R = p;
    RGB.G = V_by255;
    RGB.B = t;
    return;
  case 3:
    RGB.R = p;
    RGB.G = q;
    RGB.B = V_by255;
    return;
  case 4:
    RGB.R = t;
    RGB.G = p;
    RGB.B = V_by255;
    return;
  case 5:
    RGB.R = V_by255;
    RGB.G = p;
    RGB.B = q;
    return;
  }
}
void HSV_info::operator=(RGB_info other_color)
{
  other_color.toHSV(*this);
}

RGB_info::RGB_info() {}
RGB_info::RGB_info(HSV_info setVal) { setVal.toRGB(*this); }

RGB_info::~RGB_info() {}

uint32_t RGB_info::RGB()
{
  return (static_cast<uint32_t>(R) << 16) + (static_cast<uint32_t>(G) << 8) + (static_cast<uint32_t>(B));
}

void RGB_info::toHSV(HSV_info &HSV)
{
  float r = this->R / 255.0f, g = this->G / 255.0f, b = this->B / 255.0f;

  float imax = THREE_MAX(r, g, b);
  float imin = THREE_MIN(r, g, b);
  float diff = imax - imin;

  HSV.V = imax;

  if (diff == 0.0f)
  {
    HSV.S = 0;
    HSV.H = 0;
  }
  else
  {
    HSV.S = diff / imax;

    if (r == imax)
    {
      HSV.H = 60.0f * (g - b) / diff;
      if (r == imax && g < b)
        HSV.H += 360;
      return;
    }
    else if (g == imax)
    {
      HSV.H = 60.0f * (b - r) / diff + 120;
      return;
    }
    else
      HSV.H = 60.0f * (r - g) / diff + 240;
  }
}

void RGB_info::operator=(HSV_info other_color)
{
  other_color.toRGB(*this);
}
//end of file