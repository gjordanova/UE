
#ifndef BUFFER_H
#define BUFFER_H

#ifdef DRIVESIM_NETWORKING_LIBRARY
    #include <Library-Networking/Export.h>
#else
    #include <DriveSim-Networking/Export.h>
#endif


namespace DriveSim {
    namespace Library {
        namespace Networking {

            class DRIVESIM_LIBNETWORKING_EXPORT Buffer
            {
            public:
                Buffer(int size = 0, bool swapBytes = false, bool defaultToNetworkByteOrder = true);
                Buffer(const Buffer &);
                virtual ~Buffer();

                int write(const void *, int);
                int read(void *, int);

                void reset();
                void rewrite();

                void setData(const char *, int);
                void setSwapBytes(bool);
                void setSize(int);
                bool needToSwapBytesForNetworkByteOrder();

                const char*          getData() const;
                int                  getWritten() const;
                int                  getRest() const;
                int                  getSize() const;
                const unsigned char* fetch() const;

                virtual void print() const;

                Buffer &operator=(const Buffer &);

                Buffer &operator<<(float);
                Buffer &operator<<(double);
                Buffer &operator<<(unsigned int);
                Buffer &operator<<(int);
                Buffer &operator<<(long long);
                Buffer &operator<<(unsigned short int);
                Buffer &operator<<(unsigned char);
                Buffer &operator<<(const Buffer &);

                Buffer &operator>>(float &);
                Buffer &operator>>(double &);
                Buffer &operator>>(unsigned int &);
                Buffer &operator>>(int &);
                Buffer &operator>>(long long &);
                Buffer &operator>>(unsigned short int &);
                Buffer &operator>>(unsigned char &);
                Buffer &operator>>(Buffer &);

            protected:
                bool isShort(int) const;
                void resize(int);

                unsigned char*	_data;
                int				_len;
                int				_pos;
                int				_written;
                bool			_swapBytes;
            };
        } // namespace
    } // namespace
} // namespace


#endif // BUFFER_H
