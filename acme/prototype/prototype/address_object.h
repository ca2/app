// Created by camilo on 2025-12-17 18:43 <3ThomasBorregaardSørensen!!
#pragma once


template < typename TYPE >
   class address_object
{
public:

   TYPE *m_p;


   address_object()
   {

      m_p = new TYPE;

   }

   ~address_object()
   {

      delete m_p;

   }

      address_object(const TYPE &object) : m_p( new TYPE(object))
      {  
      }


   address_object(const address_object & addressobject) :
      address_object(*addressobject.m_p)
   {

      
   }


  address_object & operator =(const address_object &addressobject)
  {

     if (this != &addressobject && m_p != addressobject.m_p)
     {
      
        *m_p = *addressobject.m_p;

     }

     return *this;
  }

  operator TYPE * ()
  {

     return m_p;

  }
  operator const TYPE *() const
  {
     
     return m_p; 
  }

};