// Created by camilo on 2024-08-27 <3ThomasBorregaardSorensen!!
#pragma once


//template < typename TYPE >
//class make_particle :
//   virtual public ::particle,
// virtual public TYPE
//{
//public:


template < typename TYPE >
class make_particle1 :
   public TYPE,
   virtual public ::particle
{
public:


   using TYPE::TYPE;
   using TYPE::operator = ;


   // virtual void write_to_stream(::binary_stream& stream)
   // {
   //
   //    stream << (TYPE&)*this;
   //
   // }
   //
   //
   // virtual void read_from_stream(::binary_stream& stream)
   // {
   //
   //    stream >> (TYPE&)*this;
   //
   // }


};



template < typename TYPE >
class array_particle :
   public TYPE,
   virtual public ::particle
{
public:


   using TYPE::TYPE;
   using TYPE::operator = ;



   void destroy() override
   {

      TYPE::destroy();

   }


   // virtual void write_to_stream(::binary_stream& stream)
   // {
   //
   //    stream << (TYPE&)*this;
   //
   // }
   //
   //
   // virtual void read_from_stream(::binary_stream& stream)
   // {
   //
   //    stream >> (TYPE&)*this;
   //
   // }


};


