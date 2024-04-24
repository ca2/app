#pragma once


////#include "acme/primitive/primitive/object.h"
//#include "acme/primitive/collection/procedure_array.h"


// <3ThomasBS_ [THE MAN], [THE ONLY], [THE GOD], [THE ONLY GOD], Mummi the Goddess, and bilbo my pet mate :)
class CLASS_DECL_APEX handler_manager :
   virtual public ::object
{
public:


   //bool                             m_bSingleThread;
   bool                             m_bUseDedicatedThread;
   ::task_pointer                   m_pthread;
   ::procedure_array                  m_procedurea;
   ::pointer<manual_reset_event>   m_pevTaskOnQueue;
   int                              m_iAliveCount;
   int                              m_iAlive;
   string                           m_strThreadName;


   handler_manager();
   ~handler_manager() override;


   virtual void initialize_handler_manager(::particle * pparticleContext, const ::string & strThreadName, int iAliveCount = -1);
   

   virtual void on_start_loop();


   //virtual void set_finish_composites(::property_object * pcontextobjectFinish) override;
   void on_destroy() override;


   bool is_branch_current() const override;


   void handle_synchronously(const ::procedure & procedure);
   void handle_asynchronously(const ::procedure & procedure);
   

   void handle(const ::procedure & procedure, bool bSynchronously);


   ::procedure pick_new_task();

   
   void loop();


};



