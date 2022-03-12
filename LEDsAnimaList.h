/*
 * @Author: sethome
 * @Date: 2021-09-25 01:26:25
 * @LastEditTime: 2022-03-13 01:31:47
 * @LastEditors: sethome
 * @Description: LEDs group Anima List
 * @FilePath: \LED_anima\LEDsAnimaList.h
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
//2021-6-13 sethome

#pragma once

#define __LEDS_ANIMA_LIST_H__
#ifdef __LEDS_ANIMA_LIST_H__

#include "setting.h"

// LED_anima headfile
#include "BaseDataClass.h"
#include "ClassFactory.hpp"

// 3rd lib
#include "3dr_part./jsonxx/json.hpp"

// C/C++ std lib 
#include "vector"
#include "string"
#include "cstdlib"

namespace LED_anima
{
  namespace LEDsAnimaList
  {
    extern Reflection::classFactory animaFactory;

    class LEDsAnimaBase
    {
    protected:
      std::vector<RGB_info *> *LEDs = NULL;
      uint16_t frame = defaultFrame;

    public:
      LEDsAnimaBase() {}
      ~LEDsAnimaBase() {} //不要主动释放leds里的LED序列

      //初始化
      virtual void initLEDs(std::vector<RGB_info *> *setLEDs) { LEDs = setLEDs; }

      //方便设定帧率时初始化
      virtual void setupFrame(uint16_t setVal) { frame = setVal; }
      const uint16_t getFrame() { return frame; }

      //更新区域内的LED的动画（颜色）
      virtual void update() {}

      //设置不同参数,使用json文件配置
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
