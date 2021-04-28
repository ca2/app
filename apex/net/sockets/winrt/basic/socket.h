#pragma once


namespace sockets
{

   class base_socket_handler;

   class socket;


   /** \defgroup basic Basic sockets */
   /** socket base class.
   \ingroup basic */
   class CLASS_DECL_APEX socket :
      virtual public base_socket
   {
   public:


      friend class base_socket_handler;

      __pointer(base_socket_handler)   m_phandler; ///< Reference of base_socket_handler in control of this socket

      static SOCKET           s_socketNextIdSeed;
      static socket_map       s_mapSocket;
      bool                    m_bOnConnect;


      /** "Default" constructor */
      socket();

      virtual ~socket();


      /** Assign this base_socket a file descriptor created
      by a call to base_socket() or otherwise. */
      //void attach(os_data & osdata);

      virtual ::e_status     run() override;

      void close();


      void create_socket();


   };






} // namespace sockets




