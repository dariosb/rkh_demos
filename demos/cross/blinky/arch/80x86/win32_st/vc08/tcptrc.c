/**
 *  \file       tcptrc.c
 *  \ingroup    bsp
 *
 *  \brief      Socket TCP/IP support for 80x86 OS Win32
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dar�o Bali�a  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/*
 *  (1) To use the windows socket must be added the "ws2_32.lib"
 *      library in Linker->Input->Additional Dependencies
 *      configuration.
 */

/* ----------------------------- Include files ----------------------------- */
#include "tcptrc.h"
#include "rkh.h"
#include <stdio.h>

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
#if RKH_CFG_TRC_EN == 1

int
tcp_trace_open(unsigned short port, char *srv_ip, SOCKET *ps)
{
    WORD wVersionRequested;
    WSADATA wsaData;
    SOCKADDR_IN target; /* Socket address information */
    SOCKET s;
    int err;

    /* --- INITIALIZATION ----------------------------------- */
    wVersionRequested = MAKEWORD(1, 1);
    err = WSAStartup(wVersionRequested, &wsaData);
    *ps = INVALID_SOCKET;

    if (err != 0)
    {
        printf("WSAStartup error %ld", WSAGetLastError());
        WSACleanup();
        return -1;
    }
    /* ------------------------------------------------------ */

    /* ---- build address structure to bind to socket.-------- */
    target.sin_family = AF_INET; /* address family Internet */
    target.sin_port = htons(port);   /* Port to connect on */
    target.sin_addr.s_addr = inet_addr (srv_ip); /* Server IP */
    /* ------------------------------------------------------ */

    /* ---- create SOCKET-------------------------------------- */
    s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); /* Create socket */
    if (s == INVALID_SOCKET)
    {
        printf("socket error %ld", WSAGetLastError());
        WSACleanup();
        return -1; /* Couldn't create the socket */
    }
    /* ------------------------------------------------------ */

    /* ---- try CONNECT ----------------------------------------- */
    if (connect(s, (SOCKADDR*)&target, sizeof(target)) == SOCKET_ERROR)
    {
        printf("connect error %ld", WSAGetLastError());
        WSACleanup();
        return -1; /* Couldn't connect */
    }
    *ps = s;
    return 0;
}

void
tcp_trace_send(SOCKET s, const char *buf, int len)
{
    send(s, buf, len, 0);
}

void
tcp_trace_close(SOCKET s)
{
    closesocket(s);
    WSACleanup();
}

#endif
/* ------------------------------ End of file ------------------------------ */
