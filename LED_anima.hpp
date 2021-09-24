//Data:2020/09/01
//Author:sethome or say sethome2

//Function:Control strip LED color and anima library
//功能：控制条状LED带的色彩以及动画

//PS:It doesn't include code for MCU to directly control LED.
//   You need to call a function to read the color data of the current RGB frame
//   and send to the LED strip

//PS:不包含MCU直接控制LED的代码
//   您需要调用函数去读出RGB当前帧的颜色数据
//   发送给LED灯带

//C++ library
#include "vector"
#include "map"

//LED_anima Core library
#include "area.hpp"

//Third party library
//#include "bezier.h"
#include "3dr_part./jsonxx/json.hpp"

#ifndef __LED_anima__
#define __LED_anima__

namespace LED_anima
{
  template <uint16_t LED_NUM>
  class areaManage
  {
  private:
    std::map<std::string, area *> areaList;

  public:
    RGB_info LEDs[LED_NUM];

  public:
    areaManage() {} //do not things
    ~areaManage()
    {
    }

    void bindArgv(std::string argv_json)
    {
      jsonxx::json areaListData = jsonxx::json::parse(argv_json);

      for(auto iter : areaListData)
        addArea(iter.key(),iter.value().as_string());
    }

    void addArea(std::string name, std::string argv)
    {
      areaList.insert(std::make_pair(name, new area(&LEDs[0], argv)));
    }

    void update()
    {
      for (auto iter : areaList)
        iter.second->update();
    }
  };
}

#endif
//end of file
