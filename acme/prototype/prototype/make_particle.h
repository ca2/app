// Created by camilo on 2024-08-27 <3ThomasBorregaardSorensen!!
#pragma once




template < typename TYPE >
class make_particle1 :
   virtual public ::particle,
   public TYPE
{
public:


   using TYPE::TYPE;
   using TYPE::operator = ;


};



template < typename TYPE >
class array_particle :
   virtual public ::particle,
   public TYPE
{
public:


   using TYPE::TYPE;
   using TYPE::operator = ;
   using TYPE::operator += ;
   using BASE_ARRAY = TYPE;
   using RAW_BASE_ARRAY = typename BASE_ARRAY::RAW_BASE_ARRAY;


   array_particle(const RAW_BASE_ARRAY& a) : BASE_ARRAY(a) {}


   void destroy() override
   {

      TYPE::destroy();

   }


};


template < typename TYPE >
class comparable_eq_array_particle :
   virtual public ::particle,
   public TYPE
{
public:


   using TYPE::TYPE;
   using TYPE::operator = ;
   using TYPE::operator += ;
   using TYPE::operator -= ;
   using BASE_ARRAY = TYPE;
   using RAW_BASE_ARRAY = typename BASE_ARRAY::RAW_BASE_ARRAY;


   comparable_eq_array_particle(const RAW_BASE_ARRAY& a) : BASE_ARRAY(a) {}


   void destroy() override
   {

      TYPE::destroy();

   }


};


template < typename TYPE >
class comparable_array_particle :
   virtual public ::particle,
   public TYPE
{
public:


   using TYPE::TYPE;
   using TYPE::operator = ;
   using TYPE::operator += ;
   using TYPE::operator -= ;
   using BASE_ARRAY = TYPE;
   using RAW_BASE_ARRAY = typename BASE_ARRAY::RAW_BASE_ARRAY;


   comparable_array_particle(const RAW_BASE_ARRAY& a) : BASE_ARRAY(a) { }


   void destroy() override
   {

      TYPE::destroy();

   }


};



