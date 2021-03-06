/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information.
 *
 *    Copyright 2018 (c) HOOTAN MANOOCHEHRI, TOI s.r.l
 */

// some handy file to look at
// ~/.zerynth2/dist/r2.1.2/stdlib/csrc/tls/mbedtls/library/net_sockets.c
// ~/.zerynth2/dist/r2.1.2/stdlib/csrc/zsockets/zerynth_sockets.h
// ~/.zerynth2/dist/r2.1.2/libs/official/espressif/esp32net/csrc/wifi_ifc.c
// ~/.zerynth2/dist/r2.1.2/libs/official/espressif/esp32net/esp32eth.py
// ~/.zerynth2/dist/r2.1.2/libs/official/espressif/esp32net/esp32wifi.py


// here we use VOSAL API

#ifdef UA_ARCHITECTURE_ZERYNTH
#include <stddef.h>
#include "zerynth_sockets.h"

#ifndef PLUGINS_ARCH_ZERYNTH_UA_ARCHITECTURE_H_
#define PLUGINS_ARCH_ZERYNTH_UA_ARCHITECTURE_H_

// BEGIN OF I DON'T KNOW WHAT TO DO 

/* Enable POSIX features 
#if !defined(_XOPEN_SOURCE)
# define _XOPEN_SOURCE 600
#endif
#ifndef _DEFAULT_SOURCE
# define _DEFAULT_SOURCE
#endif
 On older systems we need to define _BSD_SOURCE.
 * _DEFAULT_SOURCE is an alias for that. */
// #ifndef _BSD_SOURCE
// # define _BSD_SOURCE
// #endif
// #include <errno.h>
// #include <arpa/inet.h>
// #include <netinet/in.h>
// #include <netdb.h>
// #include <sys/ioctl.h>
// #include <sys/select.h>
// #include <sys/types.h>
// #include <net/if.h>

#ifndef UA_sleep_ms
# define UA_sleep_ms(X) vosThSleep(TIME_U(X, MILLIS))
#else /* UA_sleep_ms */
/* With this one can define its own UA_sleep_ms using a preprocessor define.
E.g. see unit tests. */
void UA_sleep_ms(size_t ms);
#endif

#define OPTVAL_TYPE int

// #include <fcntl.h>
// #include <unistd.h> // read, write, close

// #ifdef __QNX__
// # include <sys/socket.h>
// #endif
// #if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
// # include <sys/param.h>
// # if defined(BSD)
// #  include<sys/socket.h>
// # endif
// #endif
// #if !defined(__CYGWIN__)
// # include <netinet/tcp.h>
// #endif

/* unsigned int for windows and workaround to a glibc bug */
/* Additionally if GNU_LIBRARY is not defined, it may be using
 * musl libc (e.g. Docker Alpine) */
// #if  defined(__OpenBSD__) || \
//     (defined(__GNU_LIBRARY__) && (__GNU_LIBRARY__ <= 6) && \
//      (__GLIBC__ <= 2) && (__GLIBC_MINOR__ < 16) || \
//     !defined(__GNU_LIBRARY__))
// # define UA_fd_set(fd, fds) FD_SET((unsigned int)fd, fds)
// # define UA_fd_isset(fd, fds) FD_ISSET((unsigned int)fd, fds)
// #else
# define UA_fd_set(fd, fds) FD_SET(fd, fds)
# define UA_fd_isset(fd, fds) FD_ISSET(fd, fds)
// #endif

// END OF I DON'T KNOW
#include "zerynth_sockets.h"


#define UA_access access

#define UA_IPV6 0
#define UA_SOCKET int
#define UA_INVALID_SOCKET -1
#define UA_ERRNO errno
#define UA_INTERRUPTED EINTR
#define UA_AGAIN EAGAIN
#define UA_EAGAIN EAGAIN
#define UA_WOULDBLOCK EWOULDBLOCK
#define UA_ERR_CONNECTION_PROGRESS EINPROGRESS

#define UA_ENABLE_LOG_COLORS

#define UA_getnameinfo getnameinfo // non c'è in z
#define UA_send zsock_send
#define UA_recv zsock_recv
#define UA_sendto zsock_sendto
#define UA_recvfrom zsock_recvfrom
#define UA_htonl htonl // non c'è in z
#define UA_ntohl ntohl // non c'è in z
#define UA_close zsock_close
#define UA_select zsock_select
#define UA_shutdown zsock_shutdown
#define UA_socket zsock_socket
#define UA_bind zsock_bind
#define UA_listen zsock_listen
#define UA_accept zsock_accept
#define UA_connect zsock_connect
#define UA_getaddrinfo zsock_getaddrinfo
#define UA_getsockopt getsockopt
#define UA_setsockopt zsock_setsockopt
#define UA_freeaddrinfo zsock_freeaddrinfo
#define UA_gethostname gethostname // non c'è in z
#define UA_inet_pton inet_pton // non c'è in z , è in lwpi

#if UA_IPV6
# define UA_if_nametoindex if_nametoindex // non c'è
#endif

// #include <stdlib.h>
#include "zerynth.h"
#define UA_free gc_free
#define UA_malloc gc_malloc
#define UA_calloc gc_calloc // should be implemented
#define UA_realloc gc_realloc //  should be implemented

// #include <stdio.h>
// #define UA_snprintf snprintf

#include "mini_snprintf.h"
#define UA_snprintf mini_snprintf

#define UA_LOG_SOCKET_ERRNO_WRAP(LOG) { 
    char *errno_str = strerror(errno); 
    LOG; 
}
#define UA_LOG_SOCKET_ERRNO_GAI_WRAP(LOG) { 
    const char *errno_str = gai_strerror(errno); 
    LOG; 
}

#include "../ua_architecture_functions.h"

#undef SLIST_EMPTY
#undef SLIST_FOREACH
#undef SLIST_INIT
#undef SLIST_REMOVE

#undef LIST_EMPTY
#undef LIST_FOREACH
#undef LIST_INIT
#undef LIST_REMOVE

#undef TAILQ_EMPTY
#undef TAILQ_FOREACH
#undef TAILQ_INIT
#undef TAILQ_REMOVE
#undef TAILQ_FOREACH_REVERSE

#undef CIRCLEQ_EMPTY
#undef CIRCLEQ_FOREACH
#undef CIRCLEQ_INIT
#undef CIRCLEQ_FOREACH_REVERSE
#undef CIRCLEQ_REMOVE
#undef CIRCLEQ_INSERT_TAIL
#undef CIRCLEQ_INSERT_HEAD
#undef CIRCLEQ_INSERT_AFTER
#undef CIRCLEQ_INSERT_BEFORE

#undef _SYS_QUEUE_H_

#endif /* PLUGINS_ARCH_POSIX_UA_ARCHITECTURE_H_ */

#endif /* UA_ARCHITECTURE_POSIX */
