#pragma once


template < typename APPLICATION >
class application_consumer :
   virtual public ::object
{
public:


   __pointer(APPLICATION) m_papplication;


   application_consumer()
   {

      add(procedure(CREATE_ROUTINE, [this]()
         {

            initialize_application_consumer();

         }));

   }


   void initialize_application_consumer()
   {

      m_papplication = get_application();

   }


   inline APPLICATION* get_app() { return m_papplication.get(); }


};


#define __application_consumer ::application_consumer < application >



