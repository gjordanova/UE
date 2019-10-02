

#ifndef PACKET_H
#define PACKET_H

#if !defined(DRIVESIM_NETWORKING_LIBRARY)
    #include <DriveSim-Networking/Export.h>
    #include <DriveSim-Networking/Buffer.h>
#else
    #include <Library-Networking/Export.h>
    #include <Library-Networking/Buffer.h>
#endif

#define META_Packet(code,name)									\
        virtual Packet* clone() const { return new name (); }	\
        virtual Opcode	opcode() const { return code; }

namespace DriveSim {
    namespace Library {
        namespace Networking {

            class DRIVESIM_LIBNETWORKING_EXPORT Packet
            {
            public:
                Packet() {}
                virtual ~Packet() {}

                typedef unsigned int Opcode;

                virtual Opcode	opcode() const = 0;
                virtual Packet*	clone() const = 0;

                virtual int		write(Buffer &buf) const = 0;
                virtual int		read(Buffer &buf) = 0;


                Buffer& operator<<(Buffer&);

                class DRIVESIM_LIBNETWORKING_EXPORT Callback
                {
                public:
                    virtual void process(Packet&) = 0;
                };

            };
        } // namespace
    } // namespace
} // namespace

#endif // PACKET_H
