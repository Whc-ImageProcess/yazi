#include "Socket.h"
#include "Logger.h"

using namespace yazi::utility;
using namespace yazi::socket;

#include <cerrno>
#include <cstring>
using namespace std;


Socket::Socket() : m_sockfd(0)
{
}

Socket::Socket(const string &ip, int port) : m_ip(ip), m_port(port), m_sockfd(0)
{
}

Socket::~Socket()
{
    close();
}

bool Socket::bind(const string &ip, int port)
{
    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    if (ip != "")
    {
        sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    }
    else
    {
        sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    sockaddr.sin_port = htons(port);

    // ::bind 表示对系统API的调用
    if (::bind(m_sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        error("socket bind error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::listen(int backlog)
{
    if (::listen(m_sockfd, backlog) < 0)
    {
        error("socket listen error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::connect(const string &ip, int port)
{
    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);
    if (::connect(m_sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        error("socket connect error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::close()
{
    if (m_sockfd > 0)
    {
        ::close(m_sockfd);
        m_sockfd = 0;
    }
    return true;
}

int Socket::accept()
{
	int sockfd = ::accept(m_sockfd, NULL, NULL);
	if (sockfd < 0)
	{
        error("accept call error: errno=%d errstr=%s", errno, strerror(errno));
        sockfd = -1;
	}
	return sockfd;
}

int Socket::recv(char * buf, int len)
{
    return ::recv(m_sockfd, buf, len, 0);
}

int Socket::send(const char * buf, int len)
{
    return ::send(m_sockfd, buf, len, 0);
}

bool Socket::set_non_blocking()
{
    int flags = fcntl(m_sockfd, F_GETFL, 0);
    if (flags < 0)
    {
        error("Socket::set_non_blocking(F_GETFL, O_NONBLOCK): errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    // 这里应该保留原来文件的 IO 标志位，为还原 IO 标志
    flags |= O_NONBLOCK;
    if (fcntl(m_sockfd, F_SETFL, flags) < 0)
    {
        error("Socket::set_non_blocking(F_SETFL, O_NONBLOCK): errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_send_buffer(int size)
{
    int buff_size = size;
    // 设置套接字的发送缓冲区大小
    // SOL_SOCKET 是一个常量，用于表示要设置的选项级别。在这里，SOL_SOCKET 表示套接字级别的选项。
    // SO_SNDBUF 是一个套接字选项常量，用于表示发送缓冲区的大小。
    // 通过调整发送缓冲区的大小，可以对发送数据的性能和吞吐量进行优化。较大的发送缓冲区可以容纳更多的数据，
    // 减少频繁的发送操作，从而提高发送效率。
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_SNDBUF, &buff_size, sizeof(buff_size)) < 0)
    {
        error("socket set send buffer error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_recv_buffer(int size)
{
    int buff_size = size;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_RCVBUF, &buff_size, sizeof(buff_size)) < 0)
    {
        error("socket set recv buffer error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_linger(bool active, int seconds)
{
    struct linger l;
    memset(&l, 0, sizeof(l));

    if (active)
        l.l_onoff = 1;
    else
        l.l_onoff = 0;
    l.l_linger = seconds;

    if (setsockopt(m_sockfd, SOL_SOCKET, SO_LINGER, &l, sizeof(l)) < 0)
    {
        error("socket set sock linger error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_keep_alive()
{
    int flag = 1;
    // 当启用 Keep-Alive 选项后，操作系统会定期发送一些探测数据给对方，
    // 并等待对方的响应。如果对方没有及时响应，那么连接可能已经断开。
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof(flag)) < 0)
    {
        error("socket set sock keep alive error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_reuse_addr()
{
    int flag = 1;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) < 0)
    {
        error("socket set sock reuser addr error: errno=%s errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_reuse_port()
{
    int flag = 1;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag)) < 0)
    {
        error("socket set sock reuser port error: errno=%d errstr=%s", errno, strerror(errno));
        return false;
    }
    return true;
}
