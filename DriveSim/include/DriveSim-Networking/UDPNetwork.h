

#ifndef UDPNETWORK_H
#define UDPNETWORK_H

#if !defined(DRIVESIM_NETWORKING_LIBRARY)
    #include <DriveSim-Networking/Export.h>
    #include <DriveSim-Networking/Network.h>
#else
    #include <Library-Networking/Export.h>
    #include <Library-Networking/Network.h>
#endif

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>


namespace DriveSim {
    namespace Library {
        namespace Networking {

            class DRIVESIM_LIBNETWORKING_EXPORT UDPNetwork : public Network
            {
            public:
                explicit UDPNetwork(const std::string& host, const std::string& destination="", bool broadcast=true, bool nonBlocking = false);
                virtual ~UDPNetwork();

                virtual void send(const Buffer&);
                virtual void receive(Buffer&, bool resetBuffer = true);

            protected:
                boost::asio::io_service			_senderIOService;
                boost::asio::ip::udp::socket*	_senderSocket;
                boost::asio::ip::udp::endpoint	_senderBroadcastEndpoint;

                boost::asio::io_service			_recieverIOService;
                boost::asio::ip::udp::socket*	_recieverSocket;

                std::string						_host;
                std::string                     _destination;
                bool							_senderSocketInitiated;
                bool							_recieverSocketInitiated;
                bool                            _broadcast;
				bool							_nonBlocking;
            };
        } // namespace
    } // namespace
} // namespace

#endif // UDPNETWORK_H
