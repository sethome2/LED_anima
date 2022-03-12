/*
 * @Author: sethome
 * @Description: Declaration and Define(their shouldn't in this) The ColorAnima Class
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

//2021-5-17 sethome

#pragma once

#define __COLORANIMALIST_H__
#ifdef __COLORANIMALIST_H__

#include "setting.h"

#include "BaseDataClass.h"
#include "ClassFactory.hpp"

//第三方库支持
#include "3dr_part./jsonxx/json.hpp"

//C&C++ library
#include "string"
#include "cstdlib"

namespace LED_anima
{
  namespace ColorAnimaList
  {
    //动画类反射
    extern Reflection::classFactory animaFactory;

    /**
     * @brief 基础类,所有的动画函数从此继承
     * @param 帧率  defaultFrame
     */
    class colorAnimaBase
    {
    protected:
      int frame = defaultFrame; //动画帧率

    public:
      RGB_info calRGB; //ColorAnima计算得出的颜色

      colorAnimaBase() {}
      ~colorAnimaBase() {}

      /**
       * @brief 获取和设定帧率 Get add Set Frame
       */
      virtual void setupFrame(uint16_t setVal) { this->frame = setVal; }
      const uint16_t getFrame() { return this->frame; }

      //获取下一帧的色彩数据
      virtual void update(RGB_info nowRGB) {} //更新数据

      //设置不同参数,使用json文件配置
      //我承认这有点蠢(这很蠢啊啊啊啊)
      virtual void bindArgv(std::string setArgv)
      {
        jsonxx::json argv = jsonxx::json::parse(setArgv); //反序列化

        if (argv.find("frame") != argv.cend())
          setupFrame(argv["frame"].as_integer());
      }

      //获取设置参数状态
      virtual std::string argvInfo()
      {
        jsonxx::json argvList;
        argvList["frame"] = getFrame();

        return argvList.dump();
      }
    };

  }
}

#endif

//end of file
