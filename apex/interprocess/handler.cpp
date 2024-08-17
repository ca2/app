// From interprocess*.h/*.cpp by camilo on 2022-10-11 00:18 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "handler.h"


namespace interprocess
{


   /*bool handler::on_interprocess_handle(::interprocess::target * ptarget, const ::string & strUri)
   {

      return true;

   }*/

   bool handler::_handle_interprocess(::interprocess::target* ptarget, ::payload& payload, const ::string& strObject, const ::string& strMember, ::property_set& propertyset)
   {

      if (m_pinterprocesshandlerNext)
      {

         if (m_pinterprocesshandlerNext->_handle_interprocess(
            ptarget,
            payload,
            strObject,
            strMember,
            propertyset
         ))
         {

            return true;

         }


      }
         return _on_interprocess_handle(
            ptarget,
            payload,
            strObject,
            strMember,
            propertyset

         );

      }

   bool handler::_on_interprocess_handle(::interprocess::target* ptarget, ::payload& payload, const ::string& strObject, const ::string& strMember, ::property_set& propertyset)
   {

      return false;

   }


} // namespace interprocess



