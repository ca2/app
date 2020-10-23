#pragma once


// <3ThomasBS_ [THE MAN], [THE ONLY], [THE GOD], [THE ONLY GOD], Mummi the Goddess, and bilbo the ca2 brother :)
class CLASS_DECL_APEX handler_manager :
   virtual public ::object
{
public:


   bool                             m_bSingleThread;
   bool                             m_bUseDedicatedThread;
   __pointer(::thread)              m_pthread;
   method_array                     m_methoda;
   __pointer(manual_reset_event)    m_pev;
   int                              m_iAliveCount;
   int                              m_iAlive;
   string                           m_strThreadName;


   handler_manager(const string & strThreadName, bool bSingleThread, int iAliveCount = -1);
   virtual ~handler_manager();


   void sync(const ::method & method);
   void async(const ::method & method);


   ::estatus handle(::object * pboject, bool bSync);


   bool wait();

   
   void loop();


};



