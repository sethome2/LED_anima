/*
 * @Author: sethome
 * @Date: 2022-03-13 00:51:24
 * @LastEditTime: 2022-03-13 01:34:50
 * @LastEditors: sethome
 * @Description: LEDsAnima: randomRlash file
 * @FilePath: \LED_anima\LEDsAnima\randomFlash.cpp
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

    class randomFlash : public LEDsAnimaBase
    {
    private:
      uint16_t countFrame = 1; //计时

      std::vector<uint8_t> status; //存储亮灭的状态
      uint8_t randSingleStatus()   //随机计算bool值（其实效率应该还可以再优化一下）
      {
        return (rand() % 2);
      }

    public:
      randomFlash() { setupFrame(defaultFrame); }
      ~randomFlash() {}

      void initLEDs(std::vector<RGB_info *> *setLEDs)
      {
        LEDs = setLEDs;
        status.resize(LEDs->size(), 0);
      }

      void update()
      {
        countFrame++;

        //达到设定帧率，更新状态数组
        if (countFrame >= frame)
        {
          for (int i = 0; i < status.size(); i++)
            status[i] = randSingleStatus();

          countFrame = 1;
        }

        //将状态写入灯组
        auto iter_status = status.begin();
        for (auto iter_LEDs : *LEDs)
        {
          if (*iter_status)
            iter_LEDs->blank();

          iter_status++;
        }
      }

      void bindArgv(std::string setArgv)
      {
        jsonxx::json argv = jsonxx::json::parse(setArgv); //反序列化

        if (argv.find("frame") != argv.cend())
          setupFrame(argv["frame"].as_integer());
      }
    };

  }; // namspace LEDsAnimaList
};   // namspace LED_anima
