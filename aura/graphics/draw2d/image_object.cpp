#include "framework.h"


//::image_result con::get_image(const ::payload & varFile, bool bCache, bool bSync)
//{
//
//   return pcontext->m_papexcontext->load_image(varFile, bCache, bSync);
//
//}
//
//
//::image_result object::matter_image(const ::string & strMatter, bool bCache, bool bSync)
//{
//
//   return psystem->matter_image(this, strMatter, bCache, bSync);
//
//}
//
//
//::image_result object::load_image(const ::payload & varFile, bool bSync, bool bFromCache, bool bCreateHelperMaps)
//{
//
//   {
//
//      auto pimage = varFile.image();
//
//      if (pimage)
//      {
//
//         return pimage;
//
//      }
//
//   }
//
//   ::image_pointer pimage;
//   
//   auto estatus = __construct(pimage);
//
//   if (!pimage)
//   {
//
//      return estatus;
//
//   }
//
//   estatus = pcontext->m_papexcontext->_load_image(pimage, varFile, bSync, bCreateHelperMaps);
//
//   if (!estatus && estatus != error_not_ready)
//   {
//
//      return estatus;
//
//   }
//
//   return pimage;
//
//}
//
//
//::image_result object::load_matter_image(const ::string & pszMatter, bool bSync, bool bCache, bool bCreateHelperMaps)
//{
//
//   ::image_pointer pimage;
//   
//   auto estatus = __construct(pimage);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   estatus = pcontext->m_papexcontext->_load_matter_image(pimage, pszMatter, bSync, bCreateHelperMaps);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return pimage;
//
//}
//
//
//image_result object::load_matter_icon(string_array & straMatter, string strIcon)
//{
//
//   ::image_result pimage = create_image();
//
//   if (!pimage)
//   {
//
//      return pimage;
//
//   }
//
//   auto estatus = pcontext->m_papexcontext->_load_matter_icon(pimage, straMatter, strIcon);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return pimage;
//
//}
//
//
//::image_result object::load_thumbnail(const ::payload & varFile, int w, int h)
//{
//
//   auto pimage = create_image();
//
//   if (!pimage)
//   {
//
//      return pimage;
//
//   }
//
//   auto estatus = pcontext->m_papexcontext->_load_thumbnail(pimage, varFile, w, h);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return pimage;
//
//}
//
//
//::image_result object::load_thumbnail(const ::string & pszPath)
//{
//
//   auto pimage = create_image();
//
//   if (pimage)
//   {
//
//      return pimage;
//
//   }
//
//   auto estatus = pcontext->m_papexcontext->_load_thumbnail(pimage, pszPath);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return pimage;
//
//}
//
//
//::image_result object::load_dib(const ::file::path & pathDib)
//{
//
//   auto pimage = create_image();
//
//   if (pimage)
//   {
//
//      return pimage;
//
//   }
//
//   auto estatus = pcontext->m_papexcontext->_load_dib(pimage, pathDib);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return pimage;
//
//}
//

