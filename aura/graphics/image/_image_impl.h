#pragma once


//#pragma once
//
//
//
////inline ::image::image_pointer object::create_image()
////{
////
////   return øcreate < ::image::image >();
////
////}
////
////
////inline ::image::image_pointer object::create_image(const ::int_size & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
////{
////
////   ::image::image_pointer pimage;
////
////   auto estatus = øconstruct(pimage);
////
////   if (!estatus)
////   {
////
////      return nullptr;
////
////   }
////
////   estatus = pimage->create(size, eobjectCreate, iGoodStride, bPreserve);
////
////   if (!estatus)
////   {
////
////      return nullptr;
////
////   }
////
////   return pimage;
////
////}
////
////
////inline void object::øconstruct(::pointer<::image::image>& pimage)
////{
////
////   return øconstruct < ::image::image >(pimage);
////
////}
////
////
////inline void object::øconstruct(::pointer<::image::image>& pimage, ::image::image *pimageSource)
////{
////
////   if (pimageSource)
////   {
////
////      øconstruct < ::image::image >(pimage, pimageSource);
////
////   }
////
////   return m_estatus;
////
////}
//
//
////inline void object::øconstruct(::pointer<::image::image>& pimage, const ::int_size & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
////{
////
////   øconstruct(pimage);
////
////   if (pimage)
////   {
////
////      pimage->create(size, uidCreate, iGoodStride, bPreserve);
////
////   }
////
////   return m_estatus;
////
////}
//
//
////inline void object::__internal_preserve_ownership(::pointer<::image::image>& pimage, const ::int_size & size, ::eobject eobjectCreate, int iGoodStride)
////{
////
////   return øconstruct(pimage, size, uidCreate, iGoodStride, true);
////
////}
//
//
////inline void object::øconstruct(::image::image_pointer & pimage)
////{
////
////   m_estatus = ::success;
////
////   if (!pimage)
////   {
////
////      pimage = øcreate < ::image::image >();
////
////      if (!pimage)
////      {
////
////         m_estatus = ::error_no_memory;
////
////      }
////      else
////      {
////
////         m_estatus = pimage->initialize(this);
////
////      }
////
////   }
////
////   return m_estatus;
////
////}
////
//
////template < typename IMAGE_SOURCE >
////inline void object::øconstruct(::image::image_pointer & pimage, IMAGE_SOURCE pimageSource)
////{
////
////   m_estatus = øconstruct(pimage);
////
////   if (m_estatus)
////   {
////
////      if (!pimage->copy_from(pimageSource))
////      {
////
////         m_estatus = error_failed;
////
////      }
////
////   }
////
////   return m_estatus;
////
////}
//
//
////inline void object::øconstruct(::image::image_pointer & pimage, const ::int_size & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
////{
////
////   // DIFFERENT øconstruct behaviour (for image)
////   // DEFERRED.....
////   if (!pimage)
////   {
////
////      øconstruct(pimage);
////
////   }
////
////   if (pimage && pimage->size() != int_size)
////   {
////
////      m_estatus = pimage->create(size, eobjectCreate, iGoodStride, bPreserve);
////
////   }
////
////
////   return m_estatus;
////
////}
//
//
////inline void object::__preserve(::image::image_pointer & pimage, const ::int_size & size, ::eobject eobjectCreate, int iGoodStride)
////{
////
////   return øconstruct(pimage, size, eobjectCreate, iGoodStride, true);
////
////}
//
//
//
//
////inline ::image::image_pointer create_image(const ::int_size & size, ::eobject eobjectFlag = IMAGE_OBJECT_OK)
////{
////
////   auto ptype = øcreate < ::image::image >();
////
////   if (!ptype)
////   {
////
////      return nullptr;
////
////   }
////
////   auto estatus = ptype->create(size, eobjectFlag);
////
////   if (!estatus)
////   {
////
////      return nullptr;
////
////   }
////
////   return ptype;
////
////}
//
//
//// inline ::image::image_pointer __create_image(::particle * pparticle)
//// {
//
////    auto ptype = __create_new_image();
//
////    if (!ptype)
////    {
//
////       return ptype;
//
////    }
//
////    auto estatus = ptype->initialize(pparticle);
//
////    if (!estatus)
////    {
//
////       return estatus;
//
////    }
//
////    return ptype;
//
//// }
//
//
//
//// template < typename COMPOSER >
//// inline void øconstruct(COMPOSER && pcomposer, ::pointer<::image::image>& pimage)
//// {
//
////    //if (((uptr)&pimage) < (uptr)pcomposer || ((uptr)&pimage) >= ((uptr)pcomposer) + sizeof(COMPOSER))
////    //{
//
////    //   return error_composite_not_composer_member;
//
////    //}
//
////    return pcomposer->øconstruct(pimage);
//
//// }
//
//
//// template < typename COMPOSER >
//// inline void øconstruct(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, ::image::image *pimageSource)
//// {
//
////    return pcomposer->øconstruct(pimage, pimageSource);
//
//// }
//
//
//
//// template < typename COMPOSER >
//// inline void øconstruct(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, const ::int_size & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
//// {
//
////    auto estatus = øconstruct(pcomposer, pimage);
//
////    if (!estatus)
////    {
//
////       return estatus;
//
////    }
//
////    if (pimage && pimage->size() != int_size)
////    {
//
////       estatus = pimage->create(size, uidCreate, iGoodStride, bPreserve);
//
////    }
//
////    return estatus;
//
//// }
//
//
//// template < typename COMPOSER >
//// inline void __preserve(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, const ::int_size & size, ::eobject eobjectCreate, int iGoodStride)
//// {
//
////    //if (((uptr)&pimage) < (uptr)pcomposer || ((uptr)&pimage) >= ((uptr)pcomposer) + sizeof(COMPOSER))
////    //{
//
////    //   return error_composite_not_composer_member;
//
////    //}
//
////    return pcomposer->øconstruct(pimage, size, uidCreate, iGoodStride, true);
//
//// }
//
//
////inline void øconstruct(::image::image_pointer & pimage)
////{
////
////   if (!pimage)
////   {
////
////      return øconstruct < ::image::image >(pimage);
////
////   }
////
////   return ::success;
////
////}
//
////
////inline void øconstruct(::image::image_pointer & pimage, ::image::image *pimageSource)
////{
////
////   auto estatus = øconstruct(pimage);
////
////   if(estatus.succeeded())
////   {
////
////      if (!pimage->copy_from(pimageSource))
////      {
////
////         return ::error_failed;
////
////      }
////
////   }
////
////   return estatus;
////
////}
////
////
////inline ::image::image_pointer & øconstruct(::image::image_pointer & pimage, ::object * pobjectSource)
////{
////
////   øconstruct(pimage);
////
////   pimage->initialize(pobjectSource);
////
////   return pimage;
////
////}
//
////
////inline void øconstruct(::image::image_pointer & pimage, const ::int_size & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
////{
////
////   auto estatus = øconstruct(pimage);
////
////   if (!estatus)
////   {
////
////      return estatus;
////
////   }
////
////   if (pimage && pimage->get_size() != size)
////   {
////
////      estatus = pimage->create(size, eobjectCreate, iGoodStride, bPreserve);
////
////   }
////
////   return estatus;
////
////}
////
////
////inline void __preserve_construct(::image::image_pointer & pimage, const ::int_size & size, ::eobject eobjectCreate, int iGoodStride)
////{
////
////   return øconstruct(pimage, size, eobjectCreate, iGoodStride, true);
////
////}
//



