#pragma once

#if !defined(DRIVESIM_LIBPROTOCOL_LIBRARY)
    #include <DriveSim-Networking/Buffer.h>
    #include <DriveSim-Networking/Packet.h>
    #include <DriveSim-Protocol/Export.h>
    #include <DriveSim-Protocol/Opcodes.h>
#else
    #include <Library-Networking/Buffer.h>
    #include <Library-Networking/Packet.h>
    #include <Library-Protocol/Export.h>
    #include <Library-Protocol/Opcodes.h>
#endif

#include <string>

namespace DriveSim {
    namespace Library {
        namespace Protocol {

            struct DRIVESIM_LIBPROTOCOL_EXPORT Camera : public DriveSim::Library::Networking::Packet
            {
                Camera();
                virtual ~Camera() {}

                META_Packet(OPCODE_CAMERA, Camera);

                virtual int write(DriveSim::Library::Networking::Buffer &buf) const;
                virtual int read(DriveSim::Library::Networking::Buffer &buf);

                double x;
                double y;
                double z;
                double h;
                double p;
                double r;
            };

        }
    }
}
