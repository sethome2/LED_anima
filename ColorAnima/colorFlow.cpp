/*
 * @Author: sethome
 * @Date: 2022-03-13 00:35:03
 * @LastEditTime: 2022-03-13 00:39:22
 * @LastEditors: sethome
 * @Description: ColorAnima: colorFlow file
 * @FilePath: \LED_anima\ColorAnima\colorFlow.cpp
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

    //色彩流？
    //思路：增加HSV的H色相实现
    //可设定的参数：无
    class colorFlow : public colorAnimaBase
    {
    private:
      float gradient;
      HSV_info nowHSV;

    public:
      colorFlow()
      {
        setupFrame(defaultFrame * 5);
        nowHSV.red();
      }
      ~colorFlow() {}

      void setupFrame(uint16_t setVal)
      {
        frame = setVal;
        gradient = 360.0f / frame;
      }

      void update(RGB_info nowRGB)
      {
        nowHSV.H += gradient;
        if (nowHSV.H >= 360.0f)
          nowHSV.H = 0;

        nowHSV.toRGB(calRGB);
      }
    };

  }; // namespace ColorAnimaList
};   // namespace LED_anima
