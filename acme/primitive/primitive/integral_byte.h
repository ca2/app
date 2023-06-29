// From unit.h by camilo on 2023-06-29 08:54 <3ThomasBorregaardSorensen!!
#pragma once


class integral_byte
{
public:


   memsize m_memsize;


   constexpr integral_byte(memsize memsize = 1) :
      m_memsize(memsize)
   {


   }

   operator memsize() const { return m_memsize; }


};


constexpr integral_byte operator ""KiB(long double d)
{

   return (memsize)(1024.0 * d);

}


constexpr integral_byte operator ""KiB(unsigned long long i)
{

   return (memsize)(i << 10);

}




constexpr integral_byte operator ""MiB(long double d)
{

   return (memsize)(1024.0 * 1024.0 * d);

}


constexpr integral_byte operator ""MiB(unsigned long long i)
{

   return (memsize)(i << 20);

}



constexpr integral_byte operator ""GiB(long double d)
{

   return (memsize)(1'024.0 * 1'024.0 * 1'024.0 * d);

}


constexpr integral_byte operator ""GiB(unsigned long long i)
{

   return (memsize)(i << 30);

}


CLASS_DECL_ACME ::string & copy(::string & str, const integral_byte & memsize);



