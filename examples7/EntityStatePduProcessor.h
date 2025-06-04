#pragma once

#include <dis7/EntityStatePdu.h>

namespace Example
{
   class EntityStatePduProcessor
   {
   public:
      typedef DIS::EntityStatePdu PduType;
      void Process(const DIS::EntityStatePdu& packet);
   };
}

