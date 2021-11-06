#pragma once


// <3ThomasBS_ [THE MAN], [THE ONLY], [THE GOD], [THE ONLY GOD], Mummi the Goddess, and bilbo my pet mate :)
class CLASS_DECL_APEX handler_manager :
   virtual public ::object
{
public:


   //bool                             m_bSingleThread;
   bool                             m_bUseDedicatedThread;
   ::task_pointer                   m_pthread;
   ::routine_array                  m_routinea;
   __pointer(manual_reset_event)    m_pevTaskOnQueue;
   int                              m_iAliveCount;
   int                              m_iAlive;
   string                           m_strThreadName;


   handler_manager();
   ~handler_manager() override;


   virtual ::e_status initialize_handler_manager(::object * pobjectContext, const ::string & strThreadName, int iAliveCount = -1);
   

   virtual void on_start_loop();


   //virtual ::e_status set_finish_composites(::property_object * pcontextobjectFinish) override;
   ::e_status destroy_composites() override;


   virtual bool is_branch_current() const;


   ::e_status handler_sync(const ::routine & routine);
   ::e_status handler_branch(const ::routine & routine);
   

   ::e_status handle(const ::routine & routine, bool bSync);


   ::routine pick_new_task();

   
   void loop();


};



