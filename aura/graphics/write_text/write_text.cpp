#include "framework.h"
#include "write_text.h"
#include "font_enumeration_item.h"
#include "fonts.h"
#include "true_type_font_utilities.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/platform/system.h"


namespace write_text
{


   write_text::write_text()
   {


   }


   write_text::~write_text()
   {


   }


   void write_text::on_initialize_particle()
   {

      ::acme::department::on_initialize_particle();

#ifdef ANDROID

      auto pfonts = fonts();

      if (pfonts)
      {

         pfonts->enumerate_fonts();

      }

#endif

   }


   class fonts * write_text::fonts()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pfonts == nullptr)
      {

         //auto estatus = 
         
         __construct(m_pfonts);

         //if (!estatus)
         //{

         //   return nullptr;

         //}

         auto psystem = acmesystem()->m_paurasystem;

         psystem->signal(id_font_enumeration);

      }

      return m_pfonts;

   }


   void write_text::term()
   {

      try
      {

         if (m_pfonts)
         {

            m_pfonts->destroy();

         }

      }
      catch (...)
      {

      }

      //auto estatus = 
      
      ::acme::department::term();

      //return success;

   }


   void write_text::destroy()
   {

      m_pfonts.release();

      //auto estatus = 
      
      ::acme::department::destroy();

      //return estatus;

   }


   void write_text::handle_font_enumeration(::topic * ptopic)
   {

      auto pfonts = this->fonts();

      pfonts->enumerate_fonts();

   }


   font_pointer write_text::point_font(const ::string & pszFontName, double dFontSize, int iFontWeight)
   {

      auto pfont = __create < font >();

      pfont->create_point_font(pszFontName, dFontSize, iFontWeight);

      return ::transfer(pfont);

   }


   font_pointer write_text::create_font()
   {

      return __create < font > ();
      
   }

   
   memory_pointer write_text::get_file_memory(::acme::context * pcontext, const ::file::path & path)
   {

      auto & pmemory = m_mapFileMemory[path];

      if (::is_set(pmemory))
      {

         return pmemory;

      }

      __construct_new(pmemory);

      *pmemory = pcontext->m_papexcontext->file()->as_memory(path);

      return pmemory;

   }


   font_descriptor write_text::calculate_font_descriptor(const char * face, float size)
   {
      
      font_descriptor fontdescriptor;
      
      fontdescriptor.m_strFace = face;

      fontdescriptor.m_fSize = floorf(size * 10.f) / 10.f;
      
      return fontdescriptor;
      
   }


   string write_text::get_font_descriptor_face(const font_descriptor & font_descriptor)
   {
      
      return font_descriptor.m_strFace;
      
   }


   //void write_text::enum_write_text_fonts(::write_text::font_enumeration_item_array& itema)
   //{

   //   critical_section_lock synchronouslock(&m_csFont);

   //   ::pointer<::write_text::font_enumeration_item>pitem;

   //   double dAndroid = 4.4;

   //   string strSystemFonts = file()->as_string("/system/etc/system_fonts.xml");

   //   auto psystem = acmesystem()->m_paurasystem;

   //   auto pxml = psystem->xml();

   //   auto pdoc = pxml->create_document();

   //   ::pointer<true_type_font_utilities>ptruetypefontutilities;

   //   __construct_new(ptruetypefontutilities);

   //   if (pdoc->load(strSystemFonts))
   //   {

   //      ::index iFamilyPos = 0;

   //      while (auto pfamily = pdoc->root()->get_child("family", iFamilyPos))
   //      {

   //         if (iFamilyPos < 0)
   //         {

   //            break;

   //         }

   //         iFamilyPos++;

   //         if (pfamily->get_name() == "family")
   //         {

   //            ::index iNamesetPos = 0;

   //            auto pnameset = pfamily->get_child("nameset", iNamesetPos);

   //            ::index iFilesetPos = 0;

   //            auto pfileset = pfamily->get_child("fileset", iFilesetPos);

   //            if (pnameset && pfileset)
   //            {

   //               if (pnameset->get_children_count() >= 1 && pfileset->get_children_count() >= 1)
   //               {

   //                  ::index iNamePos = 0;

   //                  auto pfirstname = pnameset->get_child("name", iNamePos);

   //                  ::index iFilePos = 0;

   //                  auto pfirstfile = pfileset->get_child("file", iFilePos);

   //                  if (pfirstname && pfirstfile)
   //                  {

   //                     string strName = pfirstname->get_value();

   //                     string strFile = pfirstfile->get_value();

   //                     ::file::path path = "/system/fonts";

   //                     path /= strFile;

   //                     pitem = __new(::write_text::font_enumeration_item);

   //                     if (acmefile()->exists(path))
   //                     {

   //                        pitem->m_mapFileName[400] = path;

   //                     }
   //                     else
   //                     {

   //                        pitem->m_mapFileName[400] = strFile;

   //                     }

   //                     pitem->m_strName = strName;

   //                     itema.add(pitem);

   //                     m_mapFontFaceName.set_at(strName, pitem->m_mapFileName[400]);

   //                  }

   //               }

   //            }

   //         }

   //      }

   //   }

   //   if (dAndroid >= 8.0)
   //   {

   //      ::file::listing listing;

   //      listing.set_file_listing("/system/fonts");

   //      acmedirectory()->enumerate(listing);

   //      for (auto & path : listing)
   //      {

   //         pitem = __new(::write_text::font_enumeration_item);

   //         pitem->m_mapFileName[400] = path;

   //         string strName = ptruetypefontutilities->GetFontNameFromFile(path);

   //         if (strName.is_empty())
   //         {

   //            strName = path.title();

   //         }

   //         pitem->m_strName = strName;

   //         itema.add(pitem);

   //         m_mapFontFaceName.set_at(strName, path);

   //      }

   //   }

   //   if (itema.is_empty())
   //   {
   //      
   //      auto pnode = acmenode();

   //      pitem = __new(::write_text::font_enumeration_item);

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_monospace);

   //      pitem->m_strName = pnode->font_name(e_font_monospace);

   //      itema.add(pitem);


   //      pitem = __new(::write_text::font_enumeration_item);

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_sans);

   //      pitem->m_strName = pnode->font_name(e_font_sans);

   //      itema.add(pitem);


   //      pitem = __new(::write_text::font_enumeration_item);

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_serif);

   //      pitem->m_strName = pnode->font_name(e_font_serif);

   //      itema.add(pitem);


   //      pitem = __new(::write_text::font_enumeration_item);

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_sans_ex);

   //      pitem->m_strName = pnode->font_name(e_font_sans_ex);

   //      itema.add(pitem);


   //      pitem = __new(::write_text::font_enumeration_item);

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_serif_ex);

   //      pitem->m_strName = pnode->font_name(e_font_serif_ex);

   //      itema.add(pitem);


   //      pitem = __new(::write_text::font_enumeration_item);

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_sans_fx);

   //      pitem->m_strName = pnode->font_name(e_font_sans_fx);

   //      itema.add(pitem);


   //      pitem = __new(::write_text::font_enumeration_item);

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_serif_fx);

   //      pitem->m_strName = pnode->font_name(e_font_serif_fx);

   //      itema.add(pitem);


   //      pitem = __new(::write_text::font_enumeration_item);

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_serif_ui);

   //      pitem->m_strName = pnode->font_name(e_font_serif_ui);

   //      itema.add(pitem);


   //   }

   //}


} // namespace write_text



