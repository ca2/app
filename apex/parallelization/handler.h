#pragma once


// <3ThomasBS_ [THE MAN], [THE ONLY], [THE GOD], [THE ONLY GOD], Mummi the Goddess, and bilbo my pet mate :)
class CLASS_DECL_APEX handler_manager :
   virtual public ::object
{
public:


   bool                             m_bSingleThread;
   bool                             m_bUseDedicatedThread;
   __pointer(::thread)              m_pthread;
   ::promise::routine_array                  m_routinea;
   __pointer(manual_reset_event)    m_pevTaskOnQueue;
   int                              m_iAliveCount;
   int                              m_iAlive;
   string                           m_strThreadName;


   handler_manager(const string & strThreadName, bool bSingleThread, int iAliveCount = -1);
   virtual ~handler_manager();


   virtual ::e_status set_finish_composites(::context_object * pcontextobjectFinish) override;


   ::e_status async(const ::promise::routine & routine);
   ::e_status sync(const ::promise::routine & routine);


   ::e_status handle(const ::promise::routine & routine, bool bSync);


   ::promise::routine pick_new_task();

   
   void loop();


};



