//2021-6-12 sethome

#pragma once

#define __AREA_HPP__
#ifdef __AREA_HPP__

#include "vector"
#include "string"

#include "LED_anima_Utility.h"
#include "ColorAnimaList.h"
#include "LEDsAnimaList.h"

#include "3dr_part./jsonxx/json.hpp"

namespace LED_anima
{
  class area
  {
  private:
    std::vector<RGB_info *> LEDs; //存储区域内的LED灯组

    std::vector<ColorAnimaList::colorAnimaBase *> colorAnima; //颜色动画函数指针
    std::vector<LEDsAnimaList::LEDsAnimaBase *> LEDsAnima;    //灯组动画函数指针

  private:
    //获取动画函数
    ColorAnimaList::colorAnimaBase *getColorAnima(std::string name)
    {
      return static_cast<ColorAnimaList::colorAnimaBase *>(ColorAnimaList::animaFactory.getClassByName(name));
    }
    LEDsAnimaList::LEDsAnimaBase *getLEDsAnima(std::string name)
    {
      return static_cast<LEDsAnimaList::LEDsAnimaBase *>(LEDsAnimaList::animaFactory.getClassByName(name));
    }

  public:
    RGB_info setColor; //设定的颜色

  public:
    area() {} //do nothings
    area(RGB_info *firstLED_ptr, std::string jsonStr)
    {
      bindArgv(firstLED_ptr, jsonStr);
    }
    ~area()
    {
      //释放所有动画函数
      for (int i = colorAnima.size(); i >= 0; i--)
      {
        ColorAnimaList::colorAnimaBase *anima = colorAnima[i];
        colorAnima.pop_back();
        utility::freeMemory(anima);
      }
      for (int i = LEDsAnima.size(); i >= 0; i--)
      {
        LEDsAnimaList::LEDsAnimaBase *anima = LEDsAnima[i];
        LEDsAnima.pop_back();
        utility::freeMemory(anima);
      }
    }

    //设定参数
    void bindArgv(RGB_info *firstLED_ptr, std::string jsonStr)
    {
      jsonxx::json areaData = jsonxx::json::parse(jsonStr);

      //添加LED_id序列
      const auto &LED_id = areaData["LED_id"].as_array();
      for (uint16_t i = 0; i < LED_id.size(); i++)
        addLED(firstLED_ptr + LED_id[i].as_integer());

      //添加设定颜色
      setColor.RGB(areaData["setColor"].as_integer());

      //添加色彩动画序列
      for (auto iter : areaData["anima"]["color"])
        addColorAnima((iter).value()["name"].as_string(), (iter).value()["argv"].dump());

      //添加灯组动画序列
      if (areaData["anima"].find("LEDs") != areaData["anima"].cend())
        for (auto iter : areaData["anima"]["LEDs"])
          addLEDsAnima((iter).value()["name"].as_string(), (iter).value()["argv"].dump());
    }

    //添加单个LED到区域内（线性）
    inline void addLED(RGB_info *singleLED_ptr)
    {
      LEDs.emplace_back(singleLED_ptr);
    }
    //添加一群LED
    void addLEDs(const std::vector<RGB_info *> LEDs_vector)
    {
      for (auto iter : LEDs_vector)
        addLED(iter);
    }
    void addLEDs(RGB_info *beginLED_ptr, uint16_t num)
    {
      LEDs.reserve(LEDs.size() + num);
      for (int i = 0; i < num; ++i)
        LEDs.emplace_back(beginLED_ptr + i);
    }

    //添加一个颜色动画函数
    bool addColorAnima(std::string name, std::string setArgv)
    {
      auto anima_ptr = getColorAnima(name);
      if (anima_ptr != NULL)
      {
        anima_ptr->bindArgv(setArgv);

        colorAnima.emplace_back(anima_ptr);
        return true;
      }
      return false;
    }
    //添加一个颜色动画函数
    bool addLEDsAnima(std::string name, std::string setArgv)
    {
      auto anima_ptr = getLEDsAnima(name);
      if (anima_ptr != NULL)
      {
        anima_ptr->initLEDs(&LEDs); //先初始化
        anima_ptr->bindArgv(setArgv);

        LEDsAnima.emplace_back(anima_ptr);
        return true;
      }
      return false;
    }

    //更新区域内的LED颜色
    void update()
    {
      //更新所有颜色动画函数
      RGB_info nowColor = setColor;
      for (auto iter : colorAnima)
      {
        (*iter).update(nowColor);
        nowColor = (*iter).calRGB;
      }
      for (auto iter : LEDs)
        *iter = nowColor;

      //更新所有灯组动画函数
      for (auto iter : LEDsAnima)
        (*iter).update();
    }
  };
}
#endif
