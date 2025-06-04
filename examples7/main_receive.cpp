
#include "Connection.h"                  // for reading packets from the socket
#include "EntityStatePduProcessor.h"     // for usage
#include "Utils.h"

#include <dis7/EntityStatePdu.h>
#include <dis7/utils/DataStream.h>

#include <cstring>                       // for strlen
#include <cstddef>                       // for size_t definition

#include <iostream>
int main(int argc, char* argv[])
{
   unsigned int port(62040);
   std::string ip("224.0.0.1");
   if( argc > 2 )
   {
      port = Example::ToType<unsigned int>( argv[1] );
      ip = argv[2];
   }

   Example::Connection multicast;
   multicast.Connect( port , ip , true);
   DIS::Endian endian = DIS::BIG;

   char buffer[Example::MTU_SIZE];
   Example::EntityStatePduProcessor processor;
   while( true )
   {
      size_t bytes_read = multicast.Receive( buffer );
      DIS::DataStream ds(buffer, bytes_read, endian);
      DIS::EntityStatePdu pdu;
      pdu.unmarshal(ds);
      processor.Process(pdu);

      // Add a short sleep delay to avoid locking up machine
      // (SDL UDP Reads are non-blocking)
      Example::sleep(10);
   }

   multicast.Disconnect();
   return 0;
}
