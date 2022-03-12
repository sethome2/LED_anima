/*
 * @Author: sethome
 * @Date: 2022-03-13 00:34:54
 * @LastEditTime: 2022-03-13 00:40:20
 * @LastEditors: sethome
 * @Description: ColorAnima: rainbow file
 * @FilePath: \LED_anima\ColorAnima\rainbow.cpp
 */

/*
MIT License

Copyright (c) 2022 sethome

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

#include "ColorAnimaList.h"

namespace LED_anima
{
  namespace ColorAnimaList
  {
    //按照顺序点亮的彩虹色
    //可设定的参数：帧率
    class rainbow : public colorAnimaBase
    {
    private:
      uint16_t countFrame = 1;
      uint8_t color = 1;

    public:
      rainbow() { setupFrame(defaultFrame * 5); }
      ~rainbow() {}

      void update(RGB_info nowRGB)
      {
        if (countFrame >= frame) //抵达目标帧率后刷新
        {
          if (color == 7) //回到一开始的红色
            color = 1;
          else
            color++;

          switch (color)
          {
          case 1:
            calRGB.red();
            break;
          case 2:
            calRGB.orange();
            break;
          case 3:
            calRGB.yellow();
            break;
          case 4:
            calRGB.green();
            break;
          case 5:
            calRGB.blue();
            break;
          case 6:
            calRGB.cyanblue();
            break;
          case 7:
            calRGB.purple();
            break;
          }

          countFrame = 1; //重置计数
          return;
        }
        countFrame++; //每次+1
      }
    };
  }; // namespace ColorAnimaList
};   // namespace LED_anima
