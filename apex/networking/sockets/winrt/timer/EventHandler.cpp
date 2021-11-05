#include "framework.h"


namespace sockets
{


   EventHandler::EventHandler(::axis::application * papp, logger *p) :
      ::object(pobject),
      socket_handler(papp, p), m_quit(false), m_socket(nullptr)
   {
   }


   EventHandler::EventHandler(::axis::application * papp, ::mutex & m,logger *p) :
      ::object(pobject),
      socket_handler(papp, m, p),
      m_quit(false), m_socket(nullptr)
   {
   }


   EventHandler::~EventHandler()
   {
      POSITION pos = m_events.get_head_position();
      while(pos != nullptr)
      {
         Event * pe = m_events.get_next(pos);
         pe -> GetFrom() -> SetHandlerInvalid();
         delete pe;
      }
      m_events.erase_all();
   }


   bool EventHandler::GetTimeUntilNextEvent(struct timeval *tv)
   {
      if (!m_events.get_size())
         return false;
      POSITION pos = m_events.get_head_position();
      if(pos != nullptr)
      {
         Event * pe = m_events.get_next(pos);
         EventTime now;
         mytime_t diff = pe->get_time() - now;
         if (diff < 1)
         {
            diff = 1;
         }
//         tv -> tv_sec = static_cast<long>(diff / 1000000);
  //       tv -> tv_usec = static_cast<int>(diff % 1000000);
         return true;
      }
      return false;
   }


   void EventHandler::CheckEvents()
   {
      EventTime now;
      POSITION pos = m_events.get_head_position();
      while(pos != nullptr)
      {
         Event * pe = m_events.get_next(pos);
         if(!(pe->get_time() < now))
            break;
         socket * s = dynamic_cast<socket *>(pe->GetFrom());
         /*
         s == nullptr    This is another object implementing 'IEventOwner' and not a socket.
         s != nullptr    This is a socket implementing IEventOwner, and we can check that the
                 object instance still is valid using socket_handler::Valid.
         */
         if (!s || (s && Valid(s)))
         {
            pe ->GetFrom()->OnEvent(pe->GetID());
         }
         for (pos = m_events.get_head_position(); pos != nullptr; )
         {
            Event * pe2 = m_events.get_next(pos);
            if(pe2 == pe)
               break;
         }
         delete pe;
         if(pos != nullptr)
            m_events.erase_at(pos);
         pos = m_events.get_head_position();
      }
   }


   long EventHandler::AddEvent(IEventOwner *from,long sec,long usec)
   {
      Event * peNew = new Event(from, sec, usec);
      POSITION pos = m_events.get_head_position();
      while(pos != nullptr)
      {
         Event * pe = m_events.get_next(pos);
         if(!(*pe < *peNew))
            break;
      }
      m_events.insert_before(pos, peNew);
      if (m_socket)
      {
         m_socket->write("\n");
      }
      return peNew->GetID();
   }


   void EventHandler::ClearEvents(IEventOwner *from)
   {
      bool repeat;
      do
      {
         repeat = false;
         POSITION pos = m_events.get_head_position();
         for(; pos != nullptr;)
         {
            Event * pe = m_events.get_next(pos);
            if(pe->GetFrom() == from)
            {
               delete pe;
               repeat = true;
               break;
            }
         }
         m_events.erase_all();
      } while (repeat);
   }


   void EventHandler::EventLoop()
   {
      __throw(todo);
      /*
      while (!m_quit)
      {
         struct timeval tv;
         if (GetTimeUntilNextEvent(&tv))
         {
            Select(&tv);
            CheckEvents();
         }
         else
         {
            Select();
         }
      }*/
   }


   void EventHandler::SetQuit(bool x)
   {
      m_quit = x;
   }


   void EventHandler::RemoveEvent(IEventOwner *from, long eid)
   {
      POSITION pos = m_events.get_head_position();
      for(; pos != nullptr; )
      {
         Event * pe = m_events.get_next(pos);
         if(from == pe->GetFrom() && eid == pe->GetID())
         {
            delete pe;
            m_events.erase_at(pos);
            break;
         }
      }
   }


   void EventHandler::add(socket *p)
   {
      if (!m_socket)
      {
         listen_socket<tcp_socket> *l = new listen_socket<tcp_socket>(*this);
         l -> SetDeleteByHandler();
         l -> Bind("127.0.0.1", 0);
         m_port = l -> GetPort();
         socket_handler::add(l);
         m_socket = new tcp_socket( *this );
         m_socket -> SetDeleteByHandler();
         m_socket -> SetConnectTimeout(5);
         m_socket -> SetConnectionRetry(-1);
   #ifdef ENABLE_RECONNECT
         m_socket -> SetReconnect(true);
   #endif
         m_socket -> open("127.0.0.1", m_port);
         socket_handler::add(m_socket);
      }
      socket_handler::add( p );
   }

}



