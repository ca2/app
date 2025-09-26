#pragma once


template < typename TYPE >
class class_set_base :
   public ::list_base  TYPE > 
{
public:

   using ARG_TYPE = ::argument_of< TYPE >;

   void add(ARG_TYPE t)
   {

      auto p = find(t);

      this->insert_at(p, t);

   }

   iterator find(ARG_TYPE t) const
   {

      auto p = this->begin();

      while (this->is_ok(p))
      {

         if (t < p)
         {

            return p;

         }

         p++;

      }

      return this->end();

   }


   bool has(ARG_TYPE t) const
   {

      return this->find(t) != nullptr;

   }

};



