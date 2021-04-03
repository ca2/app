#pragma once




template <  typename APPLICATION, typename BASE1 = optional_base1, typename BASE2 = optional_base2, typename BASE3 = optional_base3, typename BASE4 = optional_base4 >
class application_consumer :
   virtual public ::object,
   virtual public BASE1, 
   virtual public BASE2,
   virtual public BASE3,
   virtual public BASE4
{
public:


   __pointer(APPLICATION) m_papplication;


   application_consumer()
   {

      //add_routine(CREATE_ROUTINE, __routine([this]()
        // {

           // initialize_application_consumer();

         //}));

   }


   virtual ::e_status on_initialize_object() override
   {

      m_papplication = m_pcontext ? m_pcontext->m_papexapplication : nullptr;

      auto estatus1 = BASE1::on_initialize_object();

      auto estatus2 = BASE2::on_initialize_object();

      auto estatus3 = BASE3::on_initialize_object();

      auto estatus4 = BASE4::on_initialize_object();

      return ::is_set(m_papplication) && estatus1 && estatus2 && estatus3 && estatus4;

   }


   inline APPLICATION* get_application() { return m_papplication.get(); }
   inline APPLICATION* get_application() const { return (APPLICATION *) m_papplication.get(); }


};


#define __application_consumer ::application_consumer < application >



