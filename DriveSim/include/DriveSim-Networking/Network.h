#ifndef NETWORK_H
#define NETWORK_H

#if !defined(DRIVESIM_NETWORKING_LIBRARY)
    #include <DriveSim-Networking/Export.h>
    #include <DriveSim-Networking/Packet.h>
    #include <DriveSim-Networking/Buffer.h>
    #include <DriveSim-Networking/Parser.h>
    #include <DriveSim-Networking/Network.h>
    #include <DriveSim-Networking/Error.h>
#else
    #include <Library-Networking/Export.h>
    #include <Library-Networking/Packet.h>
    #include <Library-Networking/Buffer.h>
    #include <Library-Networking/Parser.h>
    #include <Library-Networking/Network.h>
    #include <Library-Networking/Error.h>
#endif

#include <boost/shared_ptr.hpp>

#include <map>
#include <sstream>

//
//Standard MTU 1500
//Standard Header size 64
//1500-64=1436 datagram size left over to use
#define DRIVESIM_BUFFER_SIZE 1436
//

namespace DriveSim {
    namespace Library {
        namespace Networking {

            class DRIVESIM_LIBNETWORKING_EXPORT Network
            {
            public:
                typedef std::map< Packet::Opcode, boost::shared_ptr<Packet::Callback> >		PacketCallbacks;

                Network();
                virtual ~Network();

                virtual void send(const Buffer&) = 0;
                virtual void receive(Buffer&, bool resetBuffer = true) = 0;

                void addCallback(Packet::Opcode, Packet::Callback*);
                void removeCallback(Packet::Opcode);

                void process(Packet&);
                void process();

                void setPort(unsigned int);
                void setParser(Parser*);

                Network& operator<<(const Packet&);

            protected:
                PacketCallbacks					_callbacks;
                unsigned int					_port;
                boost::shared_ptr<Parser>		_parser;

            public:
                static  boost::shared_ptr<ErrorHandler> log;
            };
        } // namespace
    } // namespace
} // namespace

#endif // NETWORK_H
