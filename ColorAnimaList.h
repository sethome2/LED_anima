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

#include "3dr_part./jsonxx/json.hpp"

#include "string"
#include "cstdlib"

namespace LED_anima
{
  namespace ColorAnimaList
  {
    //动画类反射
    extern Reflection::classFactory animaFactory;

    //基础类,所有的动画函数从此继承
    class colorAnimaBase
    {
    protected:
      int frame = defaultFrame; //动画帧率

    public:
      RGB_info calRGB; //下一帧的数据

      colorAnimaBase() {}
      ~colorAnimaBase(){};

      //方便设定帧率时初始化的内容设定
      virtual void setupFrame(uint16_t setVal) { frame = setVal; }
      const uint16_t getFrame() { return this->frame; }

      //获取下一帧的色彩数据
      virtual void update(RGB_info nowRGB) {} //更新数据

      //设置不同参数,使用json文件配置
      //我承认这有点蠢
      virtual void bindArgv(std::string setArgv)
      {
        jsonxx::json argv = jsonxx::json::parse(setArgv); //反序列化

        if (argv.find("frame") != argv.cend())
          setupFrame(argv["frame"].as_integer());
      }

      //获取动画的介绍
      virtual std::string introduction(std::string language)
      {
        if (language == "zh-ch")
          return "未定义";
        return "Undefine.";
      }

      //获取设置参数状态
      virtual std::string argvInfo()
      {
        jsonxx::json argvList;
        argvList["frame"] = getFrame();

        return argvList.dump();
      }
    };

    //常量动画
    //就是一直亮
    //可设定的参数：无
    class alwaysOn : public colorAnimaBase
    {
    public:
      alwaysOn(){};
      ~alwaysOn(){};

      void update(RGB_info nowRGB){calRGB = nowRGB;}

      //获取介绍
      std::string introduction(std::string language)
      {
        if (language == "zh-ch")
          return "常亮，你设置什么颜色就亮什么颜色。";
        return "Always bright, whatever color you set to brighten whatever color.";
      }
    };

    //呼吸灯
    //思路：转为HSV色域后进行操作V明亮值，再转换为RGB色域
    //可设定的参数：最大/最小明亮度，帧率
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
      //默认5秒一次呼吸
      breath() { setupFrame(defaultFrame * 2.5f); }
      ~breath() {}

      //设定帧率
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

      //获取介绍
      std::string introduction(std::string language)
      {
        if (language == "zh-ch")
          return "呼吸灯，可以设定最大和最小明亮度。";
        return "Breathing light, you can set the maximum and minimum brightness(Value)";
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

    //随机亮
    //随机利用随机数生成RGB值
    //可设定的参数：帧率
    class random : public colorAnimaBase
    {
    private:
      uint16_t countFrame = 1;

    public:
      random() { setupFrame(defaultFrame * 2); }
      ~random() {}

      void setupFrame(uint16_t setVal)
      {
        frame = setVal;

        countFrame = frame; //下次调用时强制刷新
      }
      //更新函数
      void update(RGB_info nowRGB)
      {
        if (countFrame >= frame)
        {
          //预留功能限制随机区域
          //uint32_t randColor = rand() % 0xFFFFFF;
          calRGB.RGB(rand() % 0xFFFFFF);
          countFrame = 1;
        }
        countFrame++;
      }

      //获取介绍
      std::string introduction(std::string language)
      {
        if (language == "zh-ch")
          return "随机颜色，(´･ω･`)。";
        return "random color.(´･ω･`)";
      }
    };

    //随机的彩虹色
    //可设定的参数：帧率
    class randomRainbow : public colorAnimaBase
    {
    private:
      uint16_t countFrame = 1;

    public:
      randomRainbow() { setupFrame(defaultFrame * 2); }
      ~randomRainbow() {}

      void setupFrame(uint16_t setVal)
      {
        frame = setVal;

        countFrame = frame; //下次调用时强制刷新
      }
      //更新函数
      void update(RGB_info nowRGB)
      {
        if (countFrame >= frame)
        {
          uint32_t randColor = rand() % 7 + 1;
          switch (randColor)
          {
          case 1:
            calRGB.red();
            break;
          case 2:
            calRGB.orange();
            break;
          case 3:
            calRGB.yellow();
            break;
          case 4:
            calRGB.green();
            break;
          case 5:
            calRGB.blue();
            break;
          case 6:
            calRGB.cyanblue();
            break;
          case 7:
            calRGB.purple();
            break;
          }
          countFrame = 1;
          return;
        }
        countFrame++;
      }

      //获取介绍
      std::string introduction(std::string language)
      {
        if (language == "zh-ch")
          return "随机彩虹色！";
        return "Random rainbow color!";
      }
    };

    //按照顺序点亮的彩虹色
    //可设定的参数：帧率
    class rainbow : public colorAnimaBase
    {
    private:
      uint16_t countFrame = 1;
      uint8_t color = 1;

    public:
      rainbow() { setupFrame(defaultFrame * 5); }
      ~rainbow() {}

      void update(RGB_info nowRGB)
      {
        if (countFrame >= frame) //抵达目标帧率后刷新
        {
          if (color == 7) //回到一开始的红色
            color = 1;
          else
            color++;

          switch (color)
          {
          case 1:
            calRGB.red();
            break;
          case 2:
            calRGB.orange();
            break;
          case 3:
            calRGB.yellow();
            break;
          case 4:
            calRGB.green();
            break;
          case 5:
            calRGB.blue();
            break;
          case 6:
            calRGB.cyanblue();
            break;
          case 7:
            calRGB.purple();
            break;
          }

          countFrame = 1; //重置计数
          return;
        }
        countFrame++; //每次+1
      }

      //获取介绍
      std::string introduction(std::string language)
      {
        if (language == "zh-ch")
          return "呼吸灯，可以设定最大和最小明亮度。";
        return "Breathing light, you can set the maximum and minimum brightness(Value)";
      }
    };

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

      //获取介绍
      std::string introduction(std::string language)
      {
        if (language == "zh-ch")
          return "按次序排列的彩虹颜色。";
        return "Rainbow colors in order.";
      }
    };

    //闪烁
    //可设定的参数：亮和暗的时间
    class blink : public colorAnimaBase
    {
    private:
      uint16_t countFrame = 1;
      uint16_t openMinFrame = defaultFrame * 3;

    public:
      blink() { setupFrame(defaultFrame * 6); }
      ~blink() {}

      void setupFrame(uint16_t setVal) //防止闪瞎眼
      {
        if (setVal <= 10)
          frame = 10;
        else
          frame = setVal;

        openMinFrame = frame / 2;
      }

      void update(RGB_info nowRGB)
      {
        if (countFrame <= openMinFrame)
          calRGB = nowRGB;
        else
        {
          calRGB.blank();
          if (countFrame >= frame) //抵达目标帧率后刷新
          {
            countFrame = 1; //重置计数
            return;
          }
        }
        countFrame++; //每次+1
      }

      //设定
      void bindArgv(std::string setArgv)
      {
        jsonxx::json argv = jsonxx::json::parse(setArgv);

        if (argv.find("frame") != argv.cend())
          setupFrame(argv["frame"].as_integer()); //这个一定要在前面，因为设定时会重置整体帧率

        else if (argv.find("openMinFrame") != argv.cend())
          openMinFrame = argv["openMinFrame"].as_integer();
      }

      //获取介绍
      std::string introduction(std::string language)
      {
        if (language == "zh-ch")
          return "闪烁，像小星星一样。";
        return "Blink,like a litter star.";
      }
    };
  }
}

#endif

//end of file