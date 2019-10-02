

#ifndef PARSER_H
#define PARSER_H

#if !defined(DRIVESIM_NETWORKING_LIBRARY)
    #include <DriveSim-Networking/Export.h>
    #include <DriveSim-Networking/Buffer.h>
    #include <DriveSim-Networking/Packet.h>
#else
    #include <Library-Networking/Export.h>
    #include <Library-Networking/Buffer.h>
    #include <Library-Networking/Packet.h>
#endif

namespace DriveSim {
    namespace Library {
        namespace Networking {

            class DRIVESIM_LIBNETWORKING_EXPORT Parser
            {
            public:
                virtual Packet* parse(Buffer&) = 0;
            };
        } // namespace
    } // namespace
} // namespace

#endif // PARSER_H
