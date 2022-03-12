/*
 * @Author: sethome
 * @Date: 2022-03-12 20:50:55
 * @LastEditTime: 2022-03-13 00:39:32
 * @LastEditors: sethome
 * @Description: ColorAnima: breath file
 * @FilePath: \LED_anima\ColorAnima\breath.cpp
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
     * @brief 呼吸灯  breath Light
     * @extran param 最大/最小明亮度 Max&Min V
     * @work 转为HSV色域后进行操作V明亮值，再转换为RGB色域
     */
    class breath : public colorAnimaBase
    {
    private:
      bool flag = true; //呼吸灯变量变暗的判断

      float MAX_V = 0.5;    //设定的最大明亮值
      float MIN_V = 0.0001; //设定最小的明度值
      float V = 0;          //计算的V值
      float gradient;       //颜色改变速率

      //计算梯度
      void calGradient() { gradient = (MAX_V - MIN_V) / frame; }

    public:
      //默认5秒一次呼吸 default anima play in 5s
      breath() { setupFrame(defaultFrame * 2.5f); }
      ~breath() {}

      void setupFrame(uint16_t setVal)
      {
        frame = setVal;
        calGradient();
      }

      //设定最大明亮度
      void setupMAX_V(float setVal)
      {
        if (setVal < 0.01) //限制最大亮度的V值的最小值
          setVal = 0.01;
        else if (setVal > 1.0) //防止溢出
          setVal = 1.0;

        MAX_V = setVal;
        calGradient();
      }
      float getMAX_V() { return MAX_V; }

      //设定最小明亮度
      void setupMIN_V(float setVal)
      {
        if (setVal < 0.0001) //限制小亮度的V值的最小值
          setVal = 0.0001;
        else if (setVal >= MIN_V) //防止溢出
          setVal = MIN_V;

        MIN_V = setVal;
        calGradient();
      }
      float getMIN_V() { return MIN_V; }

      //更新函数
      void update(RGB_info nowRGB)
      {
        if (flag) //确定亮度变化方向
        {
          V += gradient;
          if (V >= MAX_V) //防止溢出
          {
            V = MAX_V;
            flag = false;
          }
        }
        else
        {
          V -= gradient;
          if (V <= MIN_V) //防止溢出
          {
            V = MIN_V;
            flag = true;
          }
        }

        //进行一次色域转换
        HSV_info nowHSV = nowRGB;

        nowHSV.V = V;
        calRGB = nowHSV;
      }

      //设定最大明亮度和帧率
      void bindArgv(std::string setArgv)
      {
        jsonxx::json argv = jsonxx::json::parse(setArgv); //序列化

        if (argv.find("frame") != argv.cend())
          setupFrame(argv["frame"].as_integer());

        else if (argv.find("setMIN_V") != argv.cend())
          setupMIN_V(argv["setMIN_V"].as_float());

        else if (argv.find("setMAX_V") != argv.cend())
          setupMAX_V(argv["setMAX_V"].as_float());
      }

      //获取设置参数状态
      std::string argvInfo()
      {
        jsonxx::json argvList;
        argvList["frame"] = getFrame();
        argvList["MAX_V"] = getMAX_V();
        argvList["MIN_V"] = getMIN_V();

        return argvList.dump();
      }
    };
    
  }; // namespace ColorAnimaList
};   // namespace LED_anima