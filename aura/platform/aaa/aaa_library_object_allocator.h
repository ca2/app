#pragma once


class library_object_allocator_base :
   virtual public ::object
{
public:


   string m_strName;


   library_object_allocator_base(string strName)
   {

      m_strName = strName;

   }

   virtual ::matter * new_object(::object * pobject) = 0;


};


template < class TYPE >
class library_object_allocator :
   virtual public library_object_allocator_base
{
public:


   library_object_allocator(string strName) :
      library_object_allocator_base(strName)
   {

   }


   virtual ::matter * new_object(::object * pobject) override
   {

      return new TYPE(pobject);

   }


};




