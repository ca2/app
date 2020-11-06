#pragma once


// <3ThomasBS_ [THE MAN], [THE ONLY], [THE GOD], [THE ONLY GOD], Mummi the Goddess, and bilbo my pet mate :)
class CLASS_DECL_APEX handler_manager :
   virtual public ::object
{
public:


   bool                             m_bSingleThread;
   bool                             m_bUseDedicatedThread;
   __pointer(::thread)              m_pthread;
   procedure_array                  m_procedurea;
   __pointer(manual_reset_event)    m_pevTaskOnQueue;
   int                              m_iAliveCount;
   int                              m_iAlive;
   string                           m_strThreadName;


   handler_manager(const string & strThreadName, bool bSingleThread, int iAliveCount = -1);
   virtual ~handler_manager();


   virtual ::estatus set_finish_composites(::context_object * pcontextobjectFinish) override;


   ::estatus async(const ::procedure & procedure);
   ::estatus sync(const ::procedure & procedure);


   ::estatus handle(const ::procedure & procedure, bool bSync);


   procedure pick_new_task();

   
   void loop();


};



