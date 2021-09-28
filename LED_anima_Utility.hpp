/*
 * @Author: sethome
 * @Description: In User Settings Edit
 * @FilePath: \LED_anima\LED_anima_Utility.hpp
 */
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
//2021-5-18 sethome

#define __LED_ANIMA_UTILITY_H__
#ifdef  __LED_ANIMA_UTILITY_H__

//比较大小的宏定义（色域转换函数用）
#define THREE_MAX(a, b, c) (a > b ? (a > c ? a : c) : (b > c ? b : c)) //输出三个数中最大数
#define THREE_MIN(a, b, c) (a > b ? (b > c ? c : b) : (a > c ? c : a)) //输出三个数中最小数

namespace LED_anima
{
  namespace utility
  {
    //释放内存
    template <typename MemoryPoint>
    bool freeMemory(MemoryPoint p)
    {
      if (p != NULL)
      {
        delete p;
        p = NULL;
        return true;
      }
      return false;
    }
  }
}
#endif

//end of file
