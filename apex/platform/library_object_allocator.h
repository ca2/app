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

   virtual ::elemental * new_object(::layered * pobjectContext) = 0;


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


   virtual ::elemental * new_object(::layered * pobjectContext) override
   {

      return new TYPE(pobjectContext);

   }


};




