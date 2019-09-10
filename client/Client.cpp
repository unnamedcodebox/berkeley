///** @file
// * @brief     Client declaration
// *
// * @ingroup   Berkeley
// *
// * @copyright (C) 2019
// */



//namespace berkeley
//{



////int attachSocketToPort(
////    int socketFileDescriptor, sockaddr* address, socklen_t length)
////{
////    auto attached = bind(socketFileDescriptor, address, length);

////    if (attached < 0)
////    {
////        std::cerr << BIND_ERROR;
////    }
////    return attached;
////}

////sockaddr_in createSocketAddress(int port)
////{
////    auto address = sockaddr_in();
////    address.sin_family = AF_INET;
////    address.sin_addr.s_addr = INADDR_ANY;
////    address.sin_port = htons(port);

////    return address;
////}

////void listenSocket(int descriptor, int backlog)
////{
////    auto ptr = getenv("LISTENQ");
////    if (ptr != nullptr)
////    {
////        backlog = std::atoi(ptr);
////    }

////    if (listen(descriptor, backlog))
////    {
////        std::cerr << LISTEN_ERROR;
////    }
////}

////ssize_t
////readline(int fd, void *vptr, ssize_t maxlen)
////{
////    ssize_t	n, rc;
////    char	c, *ptr;

////    ptr = static_cast<char*>(vptr);
////    for (n = 1; n < maxlen; n++) {
////        if ( (rc = read(fd, &c, 1)) == 1) {
////            *ptr++ = c;
////            if (c == '\n')
////                break;
////        } else if (rc == 0) {
////            if (n == 1)
////                return(0);	/* EOF, no data read */
////            else
////                break;		/* EOF, some data was read */
////        } else
////            return(-1);	/* error */
////    }

////    *ptr = 0;
////    return(n);
////}
///* end readline */

////size_t
////readMessageFromSocket(int fd, void *ptr, ssize_t maxlen)
////{
////    auto n = readline(fd, ptr, maxlen);

////    if ( n == -1)
////    {
////        std::cerr << READLINE_ERROR;
////    }

////    return n;
////}

////ssize_t						/* Write "n" bytes to a descriptor. */
////writen(int fd, const void *vptr, size_t n)
////{

////    size_t		nleft;
////    ssize_t		nwritten;
////    const char	*ptr;

////    ptr = static_cast<const char*>(vptr);
////    nleft = n;
////    while (nleft > 0) {
////        if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
////            if (nwritten < 0 && errno == EINTR)
////                nwritten = 0;		/* and call write() again */
////            else
////                return(-1);			/* error */
////        }

////        nleft -= nwritten;
////        ptr   += nwritten;
//////    auto message = std::string();
//////    std::getline(std::cin, message);
//////    nwritten = write(fd, message.c_str(), sizeof (message.c_str()));
//////    if(nwritten <= 0)
//////    {
//////        nwritten = 0;
//////        if(nwritten == -1)
//////        std::cerr << WRITE_ERROR;
//////    }
////}
////    return n;
////}
///* end writen */

////void
////Writen(int fd, void *ptr, size_t nbytes)
////{
////    if (writen(fd, ptr, nbytes)
////        != static_cast<decltype(writen(fd, ptr, nbytes))>(nbytes))
////    {
////        std::cerr << BIND_ERROR;
////    }
////}






//Client::Client(unsigned int port): m_port(port)
//{

//}

//int Client::init()
//{

//}

//void Client::process(FILE *fp, int descriptor)
//{

//}

//// anonymous

//} // berkeley
