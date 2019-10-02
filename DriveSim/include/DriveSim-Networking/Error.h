

#ifndef ERROR_H
#define ERROR_H

#ifdef DRIVESIM_NETWORKING_LIBRARY
    #include <Library-Networking/Export.h>
#else
    #include <DriveSim-Networking/Export.h>
#endif

#include <sstream>
#include <iostream>

namespace DriveSim {
    namespace Library {
        namespace Networking {

            class DRIVESIM_LIBNETWORKING_EXPORT ErrorHandler
            {
            public:

                virtual std::ostream& operator<<(const std::ostringstream&) = 0;

            };

            class DRIVESIM_LIBNETWORKING_EXPORT COUTErrorHandler : public ErrorHandler
            {
            public:
                virtual std::ostream& operator<<(const std::ostringstream& oss)
                {
                    std::cout << oss.str();
                    return std::cout;
                }
            };
        } // namespace
    } // namespace
} // namespace

#endif
