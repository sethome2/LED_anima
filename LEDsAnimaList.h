//2021-6-13 sethome

#pragma once

#define __LEDS_ANIMA_LIST_H__
#ifdef __LEDS_ANIMA_LIST_H__

#include "setting.h"

#include "BaseDataClass.h"
#include "ClassFactory.hpp"

#include "3dr_part./jsonxx/json.hpp"

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

      //获取动画的介绍
      std::string introduction(std::string language)
      {
        if (language == "zh-ch")
          return "流水灯，一小段亮起来的灯，跑在灯条区域上";
        return "A short section of lights running on the light bar area";
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

      //获取动画的介绍
      std::string introduction(std::string language)
      {
        if (language == "zh-ch")
          return "随机闪烁，每一个灯的亮灭都是随机的";
        return "Random flash(blink)";
      }
    };

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

      //获取动画的介绍
      std::string introduction(std::string language)
      {
        if (language == "zh-ch")
          return "根据区域内第一个灯的颜色，生成许多连续的不同颜色。";
        return "According to the color of the first light in the area, many consecutive different colors are generated.";
      }
    };
  }
}

#endif

//end of file
