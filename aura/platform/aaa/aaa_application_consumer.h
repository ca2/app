#pragma once


template < typename APPLICATION >
class app_consumer :
   virtual public ::object
{
public:


   ::pointer<APPLICATION>m_papplication;


   app_consumer()
   {

      add(procedure(CREATE_ROUTINE, [this]()
         {

            initialize_application_consumer();

         }));

   }


   void initialize_application_consumer()
   {

      m_papplication = get_app();

   }


   inline APPLICATION* get_app() { return m_papplication.get(); }


};


#define __application_consumer ::app_consumer < application >



