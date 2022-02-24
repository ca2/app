#pragma once


template < typename APPLICATION >
class app_consumer :
   virtual public ::object
{
public:


   __pointer(APPLICATION) m_papp;


   app_consumer()
   {

      add(procedure(CREATE_ROUTINE, [this]()
         {

            initialize_application_consumer();

         }));

   }


   void initialize_application_consumer()
   {

      m_papp = get_app();

   }


   inline APPLICATION* get_app() { return m_papp.get(); }


};


#define __application_consumer ::app_consumer < application >



