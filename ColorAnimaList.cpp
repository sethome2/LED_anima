/*
 * @Author: sethome
 * @Description: Define The ColorAnima Class Factory
 * @FilePath: \LED_anima\ColorAnimaList.cpp
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
//2021-5-31 sethome

#include "ColorAnimaList.h"

#include "ColorAnima/alwaysOn.cpp"
#include "ColorAnima/breath.cpp"
#include "ColorAnima/random.cpp"
#include "ColorAnima/randomRainbow.cpp"
#include "ColorAnima/rainbow.cpp"
#include "ColorAnima/colorFlow.cpp"
#include "ColorAnima/blink.cpp"

using namespace Reflection;

namespace LED_anima
{
  namespace ColorAnimaList
  {
    //反射类
    Reflection::classFactory animaFactory;

    //注册反射函数和对象
    REGISTER(alwaysOn, animaFactory);
    REGISTER(breath, animaFactory);
    REGISTER(random, animaFactory);
    REGISTER(randomRainbow, animaFactory);
    REGISTER(rainbow, animaFactory);
    REGISTER(colorFlow, animaFactory);
    REGISTER(blink, animaFactory);
  };
};
//end of file
