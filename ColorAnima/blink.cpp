/*
 * @Author: sethome
 * @Date: 2022-03-13 00:35:09
 * @LastEditTime: 2022-03-13 00:39:42
 * @LastEditors: sethome
 * @Description: ColorAnima: blink file
 * @FilePath: \LED_anima\ColorAnima\blink.cpp
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

    //闪烁
    //可设定的参数：亮和暗的时间
    class blink : public colorAnimaBase
    {
    private:
      uint16_t countFrame = 1;
      uint16_t openMinFrame = defaultFrame * 3;

    public:
      blink() { setupFrame(defaultFrame * 6); }
      ~blink() {}

      void setupFrame(uint16_t setVal) //防止闪瞎眼
      {
        if (setVal <= 10)
          frame = 10;
        else
          frame = setVal;

        openMinFrame = frame / 2;
      }

      void update(RGB_info nowRGB)
      {
        if (countFrame <= openMinFrame)
          calRGB = nowRGB;
        else
        {
          calRGB.blank();
          if (countFrame >= frame) //抵达目标帧率后刷新
          {
            countFrame = 1; //重置计数
            return;
          }
        }
        countFrame++; //每次+1
      }

      //设定
      void bindArgv(std::string setArgv)
      {
        jsonxx::json argv = jsonxx::json::parse(setArgv);

        if (argv.find("frame") != argv.cend())
          setupFrame(argv["frame"].as_integer()); //这个一定要在前面，因为设定时会重置整体帧率

        else if (argv.find("openMinFrame") != argv.cend())
          openMinFrame = argv["openMinFrame"].as_integer();
      }
    };
  }; // namespace ColorAnimaList
};   // namespace LED_anima
