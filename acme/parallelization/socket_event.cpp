#include "framework.h"


#if 0 


#if defined(ANDROID)
#undef USE_MISC

#endif


///  \brief		constructor with passed socket handle and read state
///  \lparam		socket socket handle (default: -1)
///  \lparam		read true if socket should be ready to read (default: true)
socket_event::socket_event(::matter * pobject, u32 socket, bool read) :
   ::matter(pobject),
	event(papp, false, true),
	m_bRead(read),
	m_bActive(false),
	m_iSocket(socket),
	m_bUsedBySocketWaiterThread(false)
{

}


socket_event::~socket_event()
{
	if ( !m_bUsedBySocketWaiterThread )
		exit_wait();
}


void socket_event::set_active(bool active)
{
   m_bActive = active;
}


///  \brief		socket handle setter
///  \lparam		socket socket handle
void socket_event::SetSocketHandle(u32 socket)
{
   m_iSocket = socket;
}
//void SetSocketHandle(const SocketBase& socket) { m_iSocket = socket.get_handle_(); }   // MBO: alternative solution
//void ChangeSocketHandle(socket_id socket);

///  \brief		destructor
void socket_event::SetUsedBySocketWaiterThread()
{
   m_bUsedBySocketWaiterThread = true;
}






void socket_event::init_wait ()
{
/*xxx	if ( internal::g_globals ) {
		set_active();
		internal::g_globals->socketWaiterThread_.AddEvent(this);
	}*/
	//std_cout << "init wait " << static_cast<i32>(m_iSocket) << std::endl;
};

void socket_event::exit_wait ()
{
/*xxx	if ( internal::g_globals && m_bActive )
		internal::g_globals->socketWaiterThread_.RemoveEvent(this); */
	//std_cout << "exit wait " << static_cast<i32>(m_iSocket) << std::endl;
};

//void socket_event::ChangeSocketHandle (socket_id socket)
//{
//	internal::g_globals.socketWaiterThread_.RemoveEvent(this);
//	m_iSocket = socket;
//	internal::g_globals.socketWaiterThread_.AddEvent(this);
//}


//virtual
socket_event::operator bool ()
{
#ifdef BSD_STYLE_SOCKETS
	fd_set fileDescs;
	FD_ZERO(&fileDescs);

#pragma warning(push)
#pragma warning(disable:4127)
	FD_SET(m_iSocket, &fileDescs);
#pragma warning(pop)

	timeval timeout = {0};
	return select(0, m_bRead ? &fileDescs : 0, m_bRead ? 0 : &fileDescs, 0, &timeout) == 1;
#else

   return true;

#endif

}



#endif
