
#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#if !defined(DRIVESIM_NETWORKING_LIBRARY)
    #include <DriveSim-Networking/Export.h>
    #include <DriveSim-Networking/Network.h>
#else
    #include <Library-Networking/Export.h>
    #include <Library-Networking/Network.h>
#endif

#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace DriveSim {
    namespace Library {
        namespace Networking {

            class DRIVESIM_LIBNETWORKING_EXPORT TCPClient : public Network
            {
            public:
                explicit TCPClient(const std::string& host, const std::string& server);
                virtual ~TCPClient();

                virtual void send(const Buffer&);
                virtual void receive(Buffer&, bool resetBuffer = true);

            protected:

                std::string						_server;
                boost::asio::io_service			_io_service;
                boost::asio::ip::tcp::socket*	_socket;
                bool							_setup_socket;
                std::string						_host;

                void createSocket();
                void setupSocket(boost::asio::ip::tcp::socket& socket);
                void handle(const boost::system::error_code& error, size_t bytes_transferred);
            };
        } // namespace
    } // namespace
} // namespace

#endif
