//2021-6-13 sethome

#include "LEDsAnimaList.h"

using namespace Reflection;

namespace LED_anima
{
  namespace LEDsAnimaList
  {
    Reflection::classFactory animaFactory;

    REGISTER(flow,animaFactory);
    REGISTER(randomFlash,animaFactory);
    REGISTER(colorFlow,animaFactory);
  }
}