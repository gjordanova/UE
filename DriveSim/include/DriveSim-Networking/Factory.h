
#ifndef FACTORY_H
#define FACTORY_H

#ifdef DRIVESIM_NETWORKING_LIBRARY
    #include <Library-Networking/Export.h>
    #include <Library-Networking/Packet.h>
#else
    #include <DriveSim-Networking/Export.h>
    #include <DriveSim-Networking/Packet.h>
#endif

#include <boost/shared_ptr.hpp>

#include <map>

namespace DriveSim {
    namespace Library {
        namespace Networking {

            class DRIVESIM_LIBNETWORKING_EXPORT Factory
            {
            public:
                static Factory* instance();

                Packet* packet(Packet::Opcode opcode);
                void	addTemplate(Packet* packet);

            protected:
                Factory() {}
                ~Factory() {}

                typedef boost::shared_ptr<Packet>				PacketPointer;
                typedef std::map<Packet::Opcode, PacketPointer>	Packets;

                Packets	_packets;
            };
        }
    }
}

#endif
