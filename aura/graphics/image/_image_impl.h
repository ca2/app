#pragma once


//#pragma once
//
//
//
////inline ::image::image_pointer object::create_image()
////{
////
////   return __create < ::image::image >();
////
////}
////
////
////inline ::image::image_pointer object::create_image(const ::size_i32 & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
////{
////
////   ::image::image_pointer pimage;
////
////   auto estatus = __construct(pimage);
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
////inline void object::__construct(::pointer<::image::image>& pimage)
////{
////
////   return __construct < ::image::image >(pimage);
////
////}
////
////
////inline void object::__construct(::pointer<::image::image>& pimage, ::image::image *pimageSource)
////{
////
////   if (pimageSource)
////   {
////
////      __construct < ::image::image >(pimage, pimageSource);
////
////   }
////
////   return m_estatus;
////
////}
//
//
////inline void object::__construct(::pointer<::image::image>& pimage, const ::size_i32 & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
////{
////
////   __construct(pimage);
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
////inline void object::__internal_preserve_ownership(::pointer<::image::image>& pimage, const ::size_i32 & size, ::eobject eobjectCreate, int iGoodStride)
////{
////
////   return __construct(pimage, size, uidCreate, iGoodStride, true);
////
////}
//
//
////inline void object::__construct(::image::image_pointer & pimage)
////{
////
////   m_estatus = ::success;
////
////   if (!pimage)
////   {
////
////      pimage = __create < ::image::image >();
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
////inline void object::__construct(::image::image_pointer & pimage, IMAGE_SOURCE pimageSource)
////{
////
////   m_estatus = __construct(pimage);
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
////inline void object::__construct(::image::image_pointer & pimage, const ::size_i32 & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
////{
////
////   // DIFFERENT __construct behaviour (for image)
////   // DEFERRED.....
////   if (!pimage)
////   {
////
////      __construct(pimage);
////
////   }
////
////   if (pimage && pimage->size() != size_i32)
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
////inline void object::__preserve(::image::image_pointer & pimage, const ::size_i32 & size, ::eobject eobjectCreate, int iGoodStride)
////{
////
////   return __construct(pimage, size, eobjectCreate, iGoodStride, true);
////
////}
//
//
//
//
////inline ::image::image_pointer create_image(const ::size_i32 & size, ::eobject eobjectFlag = IMAGE_OBJECT_OK)
////{
////
////   auto ptype = __create < ::image::image >();
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
//// inline void __construct(COMPOSER && pcomposer, ::pointer<::image::image>& pimage)
//// {
//
////    //if (((uptr)&pimage) < (uptr)pcomposer || ((uptr)&pimage) >= ((uptr)pcomposer) + sizeof(COMPOSER))
////    //{
//
////    //   return error_composite_not_composer_member;
//
////    //}
//
////    return pcomposer->__construct(pimage);
//
//// }
//
//
//// template < typename COMPOSER >
//// inline void __construct(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, ::image::image *pimageSource)
//// {
//
////    return pcomposer->__construct(pimage, pimageSource);
//
//// }
//
//
//
//// template < typename COMPOSER >
//// inline void __construct(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, const ::size_i32 & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
//// {
//
////    auto estatus = __construct(pcomposer, pimage);
//
////    if (!estatus)
////    {
//
////       return estatus;
//
////    }
//
////    if (pimage && pimage->size() != size_i32)
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
//// inline void __preserve(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, const ::size_i32 & size, ::eobject eobjectCreate, int iGoodStride)
//// {
//
////    //if (((uptr)&pimage) < (uptr)pcomposer || ((uptr)&pimage) >= ((uptr)pcomposer) + sizeof(COMPOSER))
////    //{
//
////    //   return error_composite_not_composer_member;
//
////    //}
//
////    return pcomposer->__construct(pimage, size, uidCreate, iGoodStride, true);
//
//// }
//
//
////inline void __construct(::image::image_pointer & pimage)
////{
////
////   if (!pimage)
////   {
////
////      return __construct < ::image::image >(pimage);
////
////   }
////
////   return ::success;
////
////}
//
////
////inline void __construct(::image::image_pointer & pimage, ::image::image *pimageSource)
////{
////
////   auto estatus = __construct(pimage);
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
////inline ::image::image_pointer & __construct(::image::image_pointer & pimage, ::object * pobjectSource)
////{
////
////   __construct(pimage);
////
////   pimage->initialize(pobjectSource);
////
////   return pimage;
////
////}
//
////
////inline void __construct(::image::image_pointer & pimage, const ::size_i32 & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
////{
////
////   auto estatus = __construct(pimage);
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
////inline void __preserve_construct(::image::image_pointer & pimage, const ::size_i32 & size, ::eobject eobjectCreate, int iGoodStride)
////{
////
////   return __construct(pimage, size, eobjectCreate, iGoodStride, true);
////
////}
//



