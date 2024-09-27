// Created by camilo on 2024-08-27 <3ThomasBorregaardSorensen!!
#pragma once


template < typename TYPE >
class make_particle :
   virtual public ::particle,
   virtual public TYPE
{
public:

   
   template < typename ...Args >
   make_particle(Args &&... args) :
      TYPE(::std::forward<Args>(args)...)
   {

   }


   TYPE& object() { return *this; }
   const TYPE& object() const { return *this; }


   virtual void write_to_stream(::binary_stream& stream)
   {

      stream << (TYPE&)*this;

   }


   virtual void read_from_stream(::binary_stream& stream)
   {

      stream >> (TYPE&)*this;

   }


};



