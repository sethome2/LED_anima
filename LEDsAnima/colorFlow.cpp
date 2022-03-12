/*
 * @Author: sethome
 * @Date: 2022-03-13 00:51:33
 * @LastEditTime: 2022-03-13 01:34:53
 * @LastEditors: sethome
 * @Description: LEDsAnima: colorFlow file
 * @FilePath: \LED_anima\LEDsAnima\colorFlow.cpp
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

    class flow : public LEDsAnimaBase
    {
    private:
      //设定参数
      uint16_t length = 4; //流水的长度(从0数)
      float gradient = 1;  //步长（流水的速度）
      float MAX_V = 1;     //最大明度（通常是流水方向的第一个）
      float MIN_V = 0;     //最小明度（通常是流水方向的最后一个）

    private:
      //处理过程的中间变量（设定后需要重新计算）
      std::vector<RGB_info *>::iterator iter_endFlow; //流水尾部LED的指针

      std::vector<float> flow_V; //流水灯的各个明度值

      float gradientCount = 0; //步长不为1时的累计

      void reCal()
      {
        gradientCount = 0;

        if (LEDs != NULL) //当确定LED组存在时
        {
          iter_endFlow = LEDs->begin(); //重设迭代器

          gradient = (float)LEDs->size() / (float)frame; //重设步长

          flow_V.clear();
          flow_V.resize(length);
          for (int i = 0; i < length; i++)
            flow_V[i] = ((1.0f + i) / (float)length) * (MAX_V - MIN_V);
        }
      }

    public:
      flow()
      {
        setupFrame(defaultFrame * 5); //默认5秒播放完
        setupLength(4);               //默认4颗灯
      }
      ~flow() {}

      void initLEDs(std::vector<RGB_info *> *setLEDs)
      {
        LEDs = setLEDs;
        reCal();
      }
      void setupFrame(uint16_t setVal)
      {
        frame = setVal;
        reCal();
      }

      void setupMAX_V(float setVal)
      {
        MAX_V = setVal;
        reCal();
      }
      float getMAX_V() { return MAX_V; }

      void setupMIN_V(float setVal)
      {
        MIN_V = setVal;
        reCal();
      }
      float getMIN_V() { return MIN_V; }

      void setupLength(uint16_t setVal)
      {
        length = setVal;
        reCal();
      }
      uint16_t getLength() { return length; }

      void update()
      {
        //累计向前步长
        gradientCount += gradient;

        if (gradientCount > 1) //满足向前一步的条件（至少向前一位）
        {
          int step = (int)gradientCount; //强制转换取整，应对极端条件（向前走一步以上）
          gradientCount -= step;

          //流水灯队列前移
          for (int i = 0; i < step; i++)
          {
            ++iter_endFlow;
            if (iter_endFlow == LEDs->end()) //回到队头
              iter_endFlow = LEDs->begin();
          }
        }

        //将计算的灯组颜色信息写入
        auto iter = iter_endFlow;
        for (int i = 0; i < length; i++) //写入流水
        {
          //获取当前灯珠的HSV值
          HSV_info targetHSV;
          (*iter)->toHSV(targetHSV);

          targetHSV.V = flow_V[i];

          **iter = targetHSV;

          ++iter;
          if (iter == LEDs->end())
            iter = LEDs->begin();
        }
        while (iter != iter_endFlow) //将其他区域设为黑色
        {
          (*iter)->blank();

          ++iter;
          if (iter == LEDs->end())
            iter = LEDs->begin();
        }
      }

      void bindArgv(std::string setArgv)
      {
        jsonxx::json argv = jsonxx::json::parse(setArgv); //反序列化

        if (argv.find("frame") != argv.cend())
          setupFrame(argv["frame"].as_integer());

        else if (argv.find("length") != argv.cend())
          setupLength(argv["length"].as_integer());

        else if (argv.find("MAX_V") != argv.cend())
          setupMAX_V(argv["MAX_V"].as_float());

        else if (argv.find("MIN_V") != argv.cend())
          setupMIN_V(argv["MIN_V"].as_float());
      }

      //获取设置参数状态
      std::string argvInfo()
      {
        jsonxx::json argvList;
        argvList["frame"] = getFrame();
        argvList["length"] = getLength();
        argvList["MAX_V"] = getMAX_V();
        argvList["MIN_V"] = getMIN_V();

        return argvList.dump();
      }
    };
  }; // namspace LEDsAnimaList
};   // namspace LED_anima
