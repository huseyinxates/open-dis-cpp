#include "EntityStatePduProcessor.h"

#include <iostream>

using namespace Example;

void EntityStatePduProcessor::Process(const DIS::EntityStatePdu& espdu)
{
   if( espdu.getTimestamp() % 10 )
   {
      const DIS::Vector3Double& position = espdu.getEntityLocation();
      std::cout << "x:" << position.getX()
                << "\ty:" << position.getY()
                << "\tz:" << position.getZ()
                << std::endl;
   }
}
