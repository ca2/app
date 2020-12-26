#include "framework.h"
#include "aqua/xml.h"
#include "aura/graphics/draw2d/ttf_util.h"
#include "aura/platform/static_start.h"


//int_bool window_set_mouse_cursor(oswindow window, HCURSOR hcursor)
//{
//
//   return FALSE;
//
//}


//HCURSOR CreateAlphaCursor(oswindow window, const ::image * pimage, int xHotSpot, int yHotSpot)
//{
//
//   return FALSE;
//
//}
//
//
//HCURSOR load_default_cursor(e_cursor ecursor)
//{
//
//   return nullptr;
//
//}



namespace draw2d
{


   string default_font_name()
   {

      return "Helvetica";

   }


} // namespace draw2d







int_bool delete_hcursor(HCURSOR hcursor)
{

   return TRUE;

}



namespace draw2d
{


   void draw2d::enum_draw2d_fonts(::draw2d::font_enum_item_array & itema)
   {

      cslock sl(::aura::g_pcsFont);

      __pointer(::draw2d::font_enum_item) pitem;

      double dAndroid = 4.4;

      string strSystemFonts = Context.file().as_string("/system/etc/system_fonts.xml");

      auto pdoc = create_xml_document();

      __pointer(ttf_util) putil;

      ::estatus estatus = __construct_new(putil);

      if (pdoc->load(strSystemFonts))
      {

         ::index iFamilyPos = 0;

         while (auto pfamily = pdoc->root()->get_child("family", iFamilyPos))
         {

            if (iFamilyPos < 0)
            {

               break;

            }

            iFamilyPos++;

            if (pfamily->get_name() == "family")
            {

               ::index iNamesetPos = 0;

               auto pnameset = pfamily->get_child("nameset", iNamesetPos);

               ::index iFilesetPos = 0;

               auto pfileset = pfamily->get_child("fileset", iFilesetPos);

               if (pnameset && pfileset)
               {

                  if (pnameset->get_children_count() >= 1 && pfileset->get_children_count() >= 1)
                  {

                     ::index iNamePos = 0;

                     auto pfirstname = pnameset->get_child("name", iNamePos);

                     ::index iFilePos = 0;

                     auto pfirstfile = pfileset->get_child("file", iFilePos);

                     if (pfirstname && pfirstfile)
                     {

                        string strName = pfirstname->get_value();

                        string strFile = pfirstfile->get_value();

                        ::file::path path = "/system/fonts";

                        path /= strFile;

                        pitem = __new(::draw2d::font_enum_item);

                        if (::file_exists(path))
                        {

                           pitem->m_strFile = path;

                        }
                        else
                        {

                           pitem->m_strFile = strFile;

                        }

                        pitem->m_strName = strName;

                        itema.add(pitem);

                        ::aura::g_pmapFontFaceName->set_at(strName, pitem->m_strFile);

                     }

                  }

               }

            }

         }

      }

      if (dAndroid >= 8.0)
      {

         ::file::patha patha;

         ::dir::ls(patha, "/system/fonts");

         if (estatus)
         {

            for (auto & path : patha)
            {

               pitem = __new(::draw2d::font_enum_item);

               pitem->m_strFile = path;

               string strName = putil->GetFontNameFromFile(path);

               if (strName.is_empty())
               {

                  strName = path.title();

               }

               pitem->m_strName = strName;

               itema.add(pitem);

               ::aura::g_pmapFontFaceName->set_at(strName, path);

            }

         }

      }

      if (itema.isEmpty())
      {


#ifdef FONT_MONO

         pitem = __new(::draw2d::font_enum_item);

         pitem->m_strFile = FONT_MONO;

         pitem->m_strName = FONT_MONO;

         itema.add(pitem);

#endif


#ifdef FONT_SANS

         pitem = __new(::draw2d::font_enum_item);

         pitem->m_strFile = FONT_SANS;

         pitem->m_strName = FONT_SANS;

         itema.add(pitem);

#endif


#ifdef FONT_SERIF

         pitem = __new(::draw2d::font_enum_item);

         pitem->m_strFile = FONT_SERIF;

         pitem->m_strName = FONT_SERIF;

         itema.add(pitem);

#endif


#ifdef FONT_SANS_EX

         pitem = __new(::draw2d::font_enum_item);

         pitem->m_strFile = FONT_SANS_EX;

         pitem->m_strName = FONT_SANS_EX;

         itema.add(pitem);

#endif


#ifdef FONT_SERIF_EX

         pitem = __new(::draw2d::font_enum_item);

         pitem->m_strFile = FONT_SERIF_EX;

         pitem->m_strName = FONT_SERIF_EX;

         itema.add(pitem);

#endif


#ifdef FONT_SANS_FX

         pitem = __new(::draw2d::font_enum_item);

         pitem->m_strFile = FONT_SANS_FX;

         pitem->m_strName = FONT_SANS_FX;

         itema.add(pitem);

#endif


#ifdef FONT_SERIF_FX

         pitem = __new(::draw2d::font_enum_item);

         pitem->m_strFile = FONT_SERIF_FX;

         pitem->m_strName = FONT_SERIF_FX;

         itema.add(pitem);

#endif


#ifdef FONT_SANS_FX2

         pitem = __new(::draw2d::font_enum_item);

         pitem->m_strFile = FONT_SANS_FX2;

         pitem->m_strName = FONT_SANS_FX2;

         itema.add(pitem);

#endif


      }

   }


} // namespace draw2d



