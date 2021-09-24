//2021-5-31 sethome
//

#pragma once

#include "ColorAnimaList.h"

//using namespace LED_anima::ColorAnimaList;

//Reflection::classFactory animaFactory;

using namespace Reflection;

namespace LED_anima
{
  namespace ColorAnimaList
  {
    Reflection::classFactory animaFactory;

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
