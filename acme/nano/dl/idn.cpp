// Created by camilo on 2024-06-02 16:56 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "idn.h"


namespace nano
{

   namespace idn
   {


      idn::idn()
      {

      }


      idn::~idn()
      {


      }


      ::string idn::idn_to_punycode(const ::string & str)
      {

         return ::transfer(str);

      }


      ::string idn::idn_from_punycode(const ::string & str)
      {

         return ::transfer(str);

      }



   } // idn
} // nano