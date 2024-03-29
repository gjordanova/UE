#ifndef DRIVESIM_LIBNETWORKING_EXPORT_H
#define DRIVESIM_LIBNETWORKING_EXPORT_H

// disable VisualStudio warnings
#if defined(_MSC_VER)
#pragma warning( disable : 4244 )
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#pragma warning( disable : 4512 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4702 )
#pragma warning( disable : 4511 )
#pragma warning( disable : 4067 )
#endif

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
#  if defined( DRIVESIM_LIBNETWORKING_LIBRARY_STATIC )
#    define DRIVESIM_LIBNETWORKING_EXPORT
#  elif defined( DRIVESIM_LIBNETWORKING_LIBRARY )
#    define DRIVESIM_LIBNETWORKING_EXPORT   __declspec(dllexport)
#  else
#    define DRIVESIM_LIBNETWORKING_EXPORT   __declspec(dllimport)
#  endif
#else
#  define DRIVESIM_LIBNETWORKING_EXPORT
#endif

// set up define for whether member templates are supported by VisualStudio compilers.
#ifdef _MSC_VER
# if (_MSC_VER >= 1300)
#  define __STL_MEMBER_TEMPLATES
# endif
#endif

/* Define NULL pointer value */

#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#endif //
