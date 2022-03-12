/*
 * @Author: sethome
 * @Date: 2022-03-13 00:15:12
 * @LastEditTime: 2022-03-13 00:38:13
 * @LastEditors: sethome
 * @Description: ColorAnima: random file
 * @FilePath: \LED_anima\ColorAnima\random.cpp
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
    /**
     * @brief 随机颜色🎲 randomColor🎲
     * @extra param
     * @todo Limit Random Area
     */
    class random : public colorAnimaBase
    {
    private:
      uint16_t countFrame;

    public:
      random() { setupFrame(defaultFrame * 2); }
      ~random() {}

      void setupFrame(uint16_t setVal)
      {
        frame = setVal;

        countFrame = frame; //下次调用时强制刷新
      }

      //更新函数
      void update(RGB_info nowRGB)
      {
        if (countFrame >= frame)
        {
          //预留功能限制随机区域
          // uint32_t randColor = rand() % 0xFFFFFF;
          calRGB.RGB(rand() % 0xFFFFFF);
          countFrame = 1;
        }
        countFrame++;
      }
    };

  }; // namespace ColorAnimaList
};   // namespace LED_anima