/*
 * @Author: sethome
 * @Date: 2022-03-13 00:51:05
 * @LastEditTime: 2022-03-13 01:34:47
 * @LastEditors: sethome
 * @Description: LEDsAnima: flow file
 * @FilePath: \LED_anima\LEDsAnima\flow.cpp
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

#include "LEDsAnimaList.h"

namespace LED_anima
{
  namespace LEDsAnimaList
  {

    //色彩流
    //从第一个灯开始，按照一定的比例变换出七彩
    //可设定的参数：帧率
    class colorFlow : public LEDsAnimaBase
    {
    private:
      float gradient = 1;

    public:
      colorFlow() { setupFrame(defaultFrame * 5); }
      ~colorFlow() {}

      void setupFrame(uint16_t setVal)
      {
        frame = setVal;
        gradient = frame / 360.0;
      }

      void initLEDs(std::vector<RGB_info *> *setLEDs)
      {
        LEDs = setLEDs;
      }

      void update()
      {
        HSV_info nowHSV;
        (*(LEDs->begin()))->toHSV(nowHSV);

        for (auto iter = (LEDs->begin() + 1); iter != LEDs->end(); ++iter)
        {
          nowHSV.H += gradient;
          if (nowHSV.H >= 360.0f) //利用强制类型转换减去超出360的部分
            nowHSV.H -= static_cast<int>(nowHSV.H);

          nowHSV.toRGB(**iter);
        }
      }
    };

  }; // namspace LEDsAnimaList
};   // namspace LED_anima
