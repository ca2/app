#pragma once


#if !defined(DEBUG) && !defined(CUBE)


#include "acme/inline/_new_impl.h"


#endif



//namespace primitive
//{
//
//
//   template < typename TYPE >
//   template < typename OBJECT >
//   ::pointer<OBJECT>member < TYPE >::cast() const
//   {
//
//      return ::is_null((TYPE*)m_p) ? nullptr : (TYPE*)m_p;
//
//   }
//
//
//} // namespace primitive


namespace acme
{


   namespace array
   {


      template < class TDST,class TSRC >
      ::count __copy(TDST & dsta,const TSRC & srca)
      {

         dsta.set_size(srca.get_size());

         for(int i = 0; i < dsta.get_size(); i++)
         {

            ::copy(dsta[i], srca[i]);

         }

         return dsta.get_count();

      }


   } // namespace array


} // namespace acme


#include "acme/primitive/geometry2d/_defer.h"



