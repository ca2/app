#pragma once


class library_object_allocator_base :
   virtual public ::generic
{
public:


   string m_strName;


   library_object_allocator_base(string strName)
   {

      m_strName = strName;

   }

   virtual ::generic * new_object(::generic * pobjectContext) = 0;


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


   virtual ::generic * new_object(::generic * pobjectContext) override
   {

      return new TYPE(pobjectContext);

   }


};




