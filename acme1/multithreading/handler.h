#pragma once


// <3ThomasBS_ [THE MAN], [THE ONLY], [THE GOD], [THE ONLY GOD], Mummi the Goddess, and bilbo the ca2 brother :)
class CLASS_DECL_ACME handler_manager :
   virtual public ::generic
{
public:


   bool                             m_bSingleThread;
   bool                             m_bUseDedicatedThread;
   __pointer(::generic)             m_pgenericThread;
   object_ptra                      m_objecta;
   __pointer(manual_reset_event)    m_pev;
   int                              m_iAliveCount;
   int                              m_iAlive;
   string                           m_strThreadName;


   handler_manager(const string & strThreadName, bool bSingleThread, int iAliveCount = -1);
   virtual ~handler_manager();


   void sync(::generic * pobject);
   void async(::generic * pobject);


   ::estatus handle(::generic * pboject, bool bSync);


   bool wait();

   
   void loop();


};



