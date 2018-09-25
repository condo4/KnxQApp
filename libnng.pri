
HEADERS += \
    $$PWD/libnng/src/nng.h \
    $$PWD/libnng/src/core/defs.h \
    $$PWD/libnng/src/core/aio.h \
    $$PWD/libnng/src/core/clock.h \
    $$PWD/libnng/src/core/device.h \
    $$PWD/libnng/src/core/dialer.h \
    $$PWD/libnng/src/core/file.h \
    $$PWD/libnng/src/core/idhash.h \
    $$PWD/libnng/src/core/init.h \
    $$PWD/libnng/src/core/list.h \
    $$PWD/libnng/src/core/listener.h \
    $$PWD/libnng/src/core/message.h \
    $$PWD/libnng/src/core/msgqueue.h \
    $$PWD/libnng/src/core/nng_impl.h \
    $$PWD/libnng/src/core/options.h \
    $$PWD/libnng/src/core/pollable.h \
    $$PWD/libnng/src/core/panic.h \
    $$PWD/libnng/src/core/pipe.h \
    $$PWD/libnng/src/core/platform.h \
    $$PWD/libnng/src/core/protocol.h \
    $$PWD/libnng/src/core/random.h \
    $$PWD/libnng/src/core/reap.h \
    $$PWD/libnng/src/core/socket.h \
    $$PWD/libnng/src/core/strs.h \
    $$PWD/libnng/src/core/taskq.h \
    $$PWD/libnng/src/core/thread.h \
    $$PWD/libnng/src/core/timer.h \
    $$PWD/libnng/src/core/transport.h \
    $$PWD/libnng/src/core/url.h \
    $$PWD/libnng/src/platform/posix/posix_impl.h \
    $$PWD/libnng/src/platform/posix/posix_config.h \
    $$PWD/libnng/src/platform/posix/posix_pollq.h \
    $$PWD/libnng/src/compat/nanomsg/nn.h \
    $$PWD/libnng/src/compat/nanomsg/bus.h \
    $$PWD/libnng/src/compat/nanomsg/inproc.h \
    $$PWD/libnng/src/compat/nanomsg/ipc.h \
    $$PWD/libnng/src/compat/nanomsg/pair.h \
    $$PWD/libnng/src/compat/nanomsg/pipeline.h \
    $$PWD/libnng/src/compat/nanomsg/pubsub.h \
    $$PWD/libnng/src/compat/nanomsg/reqrep.h \
    $$PWD/libnng/src/compat/nanomsg/survey.h \
    $$PWD/libnng/src/compat/nanomsg/tcp.h \
    $$PWD/libnng/src/compat/nanomsg/ws.h \
    $$PWD/libnng/src/transport/tcp/tcp.h \
    $$PWD/libnng/src/protocol/reqrep0/req.h \
    $$PWD/libnng/src/protocol/reqrep0/rep.h \
    $$PWD/libnng/src/protocol/pubsub0/pub.h \
    $$PWD/libnng/src/protocol/pubsub0/sub.h \

SOURCES += \
    $$PWD/libnng/src/nng.c \
    $$PWD/libnng/src/core/aio.c \
    $$PWD/libnng/src/core/clock.c \
    $$PWD/libnng/src/core/device.c \
    $$PWD/libnng/src/core/dialer.c \
    $$PWD/libnng/src/core/file.c \
    $$PWD/libnng/src/core/idhash.c \
    $$PWD/libnng/src/core/init.c \
    $$PWD/libnng/src/core/list.c \
    $$PWD/libnng/src/core/listener.c \
    $$PWD/libnng/src/core/message.c \
    $$PWD/libnng/src/core/msgqueue.c \
    $$PWD/libnng/src/core/options.c \
    $$PWD/libnng/src/core/pollable.c \
    $$PWD/libnng/src/core/panic.c \
    $$PWD/libnng/src/core/pipe.c \
    $$PWD/libnng/src/core/protocol.c \
    $$PWD/libnng/src/core/random.c \
    $$PWD/libnng/src/core/reap.c \
    $$PWD/libnng/src/core/socket.c \
    $$PWD/libnng/src/core/strs.c \
    $$PWD/libnng/src/core/taskq.c \
    $$PWD/libnng/src/core/thread.c \
    $$PWD/libnng/src/core/timer.c \
    $$PWD/libnng/src/core/transport.c \
    $$PWD/libnng/src/core/url.c \
    $$PWD/libnng/src/platform/posix/posix_alloc.c \
    $$PWD/libnng/src/platform/posix/posix_atomic.c \
    $$PWD/libnng/src/platform/posix/posix_clock.c \
    $$PWD/libnng/src/platform/posix/posix_debug.c \
    $$PWD/libnng/src/platform/posix/posix_epdesc.c \
    $$PWD/libnng/src/platform/posix/posix_file.c \
    $$PWD/libnng/src/platform/posix/posix_ipc.c \
    $$PWD/libnng/src/platform/posix/posix_pipe.c \
    $$PWD/libnng/src/platform/posix/posix_pipedesc.c \
    $$PWD/libnng/src/platform/posix/posix_rand.c \
    $$PWD/libnng/src/platform/posix/posix_resolv_gai.c \
    $$PWD/libnng/src/platform/posix/posix_sockaddr.c \
    $$PWD/libnng/src/platform/posix/posix_tcp.c \
    $$PWD/libnng/src/platform/posix/posix_thread.c \
    $$PWD/libnng/src/platform/posix/posix_udp.c \
    $$PWD/libnng/src/platform/posix/posix_pollq_epoll.c \
    $$PWD/libnng/src/compat/nanomsg/nn.c \
    $$PWD/libnng/src/transport/tcp/tcp.c \
    $$PWD/libnng/src/protocol/reqrep0/req.c \
    $$PWD/libnng/src/protocol/reqrep0/xreq.c \
    $$PWD/libnng/src/protocol/reqrep0/rep.c \
    $$PWD/libnng/src/protocol/reqrep0/xrep.c \
    $$PWD/libnng/src/protocol/pubsub0/pub.c \
    $$PWD/libnng/src/protocol/pubsub0/sub.c


HEADERS += \
    $$PWD/qnngsubscriber.h

SOURCES += \
    $$PWD/qnngsubscriber.cpp


INCLUDEPATH += "$$PWD/libnng/src/"

#DEFINES += DEBUG_LOCAL_SERVER

DEFINES += NNG_STATIC_LIB NNG_PLATFORM_POSIX NNG_PLATFORM_LINUX NNG_USE_EVENTFD  NNG_HAVE_EPOLL=1 NNG_HAVE_EVENTFD NNG_PRIVATE
DEFINES += NNG_HAVE_UNIX_SOCKETS=1 NNG_HAVE_STRNCASECMP=1 NNG_HIDDEN_VISIBILITY NNG_HAVE_EPOLL_CREATE1=1 NNG_HAVE_ALLOCA=1
DEFINES += NNG_HAVE_STDATOMIC=1 NNG_HAVE_STRCASECMP=1 NNG_HAVE_STRNLEN=1 NNG_HAVE_CLOCK_GETTIME=1 NNG_HAVE_MSG_CONTROL=1 NNG_HAVE_SEMAPHORE_PTHREAD=1
DEFINES += NNG_TRANSPORT_TCP NNG_HAVE_SUB0 NNG_HAVE_PUB0 NNG_HAVE_REP0 NNG_HAVE_REQ0
DEFINES += _GNU_SOURCE _REENTRANT _THREAD_SAFE _POSIX_PTHREAD_SEMANTICS

android{
    DEFINES += NNG_PLATFORM_ANDROID
    DEFINES += NNG_BIG_ENDIAN
}
else{
    DEFINES += NNG_HAVE_BACKTRACE=1  NNG_HAVE_FLOCK=1 NNG_HAVE_LIBNSL=1 NNG_HAVE_LOCKF=1 NNG_HAVE_SOPEERCRED=1
    DEFINES += NNG_LITTLE_ENDIAN
    # DEFINES += NNG_HAVE_BUS0 NNG_HAVE_SURVEYOR0 NNG_SUPP_HTTP NNG_TRANSPORT_INPROC NNG_TRANSPORT_IPC NNG_TRANSPORT_WS NNG_HAVE_PAIR0 NNG_HAVE_PAIR1  NNG_HAVE_PULL0 NNG_HAVE_PUSH0 NNG_HAVE_RESPONDENT0
}

QMAKE_CFLAGS += -std=c99
