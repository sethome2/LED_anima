/*
 * @Author: sethome
 * @Date: 2022-03-12 20:39:53
 * @LastEditTime: 2022-03-13 00:18:30
 * @LastEditors: Please set LastEditors
 * @Description: ColorAnima: AlwaysOn file
 * @FilePath: \LED_anima\ColorAnima\alwaysOn.c
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
     * @brief 保持一种颜色 Keep a Color
     * @extran param 无
     */
    class alwaysOn : public colorAnimaBase
    {
    public:
      alwaysOn(){};
      ~alwaysOn(){};

      void update(RGB_info nowRGB) { calRGB = nowRGB; }
    };

  }; // namespace ColorAnimaList
};   // namespace LED_anima
