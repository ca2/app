#include "framework.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "aura/windowing/cursor_manager.h"
#include "aura/windowing/cursor.h"
#include "aura/platform/system.h"


namespace windowing
{

   struct cursor_pair
   {
      enum_cursor m_ecursor;
      const_char_pointer m_pszName;

   };

   cursor_pair g_pcursorpaira[] =
   {
      { e_cursor_arrow              ,  "arrow"},
      { e_cursor_hand               ,  "hand"},
      { e_cursor_text_select        ,  "text_select"},
      { e_cursor_size_top_left      ,  "size_top_left"},
      { e_cursor_size_top           ,  "size_top"},
      { e_cursor_size_top_right     ,  "size_top_right"},
      { e_cursor_size_right         ,  "size_top_right"},
      { e_cursor_size_bottom_right  ,  "size_bottom_right"},
      { e_cursor_size_bottom        ,  "size_bottom"},
      { e_cursor_size_bottom_left   ,  "size_bottom_left"},
      { e_cursor_size_left          ,  "size_left"},
      { e_cursor_size_vertical      ,  "size_vertical"},
      { e_cursor_size_horizontal    ,  "size_horizontal"},
      { e_cursor_move               ,  "size_top_right"},
      { e_cursor_none               ,  nullptr},

   };


   cursor_manager::cursor_manager()
   {

   }


   cursor_manager::~cursor_manager()
   {


   }


   long long cursor_manager::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   long long cursor_manager::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }



   void cursor_manager::destroy()
   {

      for (auto & pcursor : m_cursormap.payloads())
      {

         pcursor.defer_destroy();

      }

      m_cursormap.clear();

      m_pwindowing.release();

      //auto estatus = 
      
      ::matter::destroy();

      //return estatus;

   }


   string cursor_manager::cursor_name(enum_cursor ecursor)
   {

      auto pcursorpair = g_pcursorpaira;

      while (pcursorpair->m_ecursor != e_cursor_none)
      {

         if (pcursorpair->m_ecursor == ecursor)
         {

            return pcursorpair->m_pszName;

         }

         pcursorpair++;

      }

      return "";

   }


   enum_cursor cursor_manager::cursor_enum(const ::scoped_string & scopedstrCursor)
   {

      ::string strCursor(scopedstrCursor);

      strCursor.make_lower();
      strCursor.trim();

      if (strCursor == "arrow") { return e_cursor_arrow; }
      else if (strCursor == "hand") { return e_cursor_hand; }
      else if (strCursor == "text_select") { return e_cursor_text_select; }
      else if (strCursor.case_insensitive_begins_eat("size_"))
      {
         if (strCursor.case_insensitive_begins_eat("top"))
         {
            if (strCursor.is_empty()) { return e_cursor_size_top; }
            else if (strCursor == "_left") { return e_cursor_size_top_left; }
            else if (strCursor == "_right") { return e_cursor_size_top_right; }
         }
         else if (strCursor.case_insensitive_begins_eat("bottom"))
         {
            if (strCursor.is_empty()) { return e_cursor_size_bottom; }
            else if (strCursor == "_left") { return e_cursor_size_bottom_left; }
            else if (strCursor == "_right") { return e_cursor_size_bottom_right; }
         }
         else if (strCursor == "left") { return e_cursor_size_left; }
         else if (strCursor == "right") { return e_cursor_size_right; }
         else if (strCursor == "vertical") { return e_cursor_size_vertical; }
         else if (strCursor == "horizontal") { return e_cursor_size_horizontal; }
      }
      else if (strCursor == "transfer") { return e_cursor_move; }


      return e_cursor_none;

   }


   ::pointer<cursor>cursor_manager::get_cursor(enum_cursor ecursor)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto & pcursor = m_cursormap[ecursor];

      if (pcursor)
      {

         return pcursor;

      }

      __øconstruct(pcursor);

      pcursor->m_pcursormanager = this;

      pcursor->set_cursor(ecursor);

      //m_cursormap.set_at(ecursor, pcursor);

      return pcursor;

   }


   ::pointer<cursor>cursor_manager::set_cursor_file(enum_cursor ecursor, const ::file::path & pathParam, bool bFromCache)
   {

      cursor * pcursor = nullptr;

      {

         _synchronous_lock synchronouslock(this->synchronization());

         pcursor = get_cursor(ecursor);

      }

      auto path = pathParam;

      if (application()->m_bImaging)
      {

         pcursor->set_file_path(path);

         //

         //auto puser = user();

         //auto pwindowing = system()->windowing();

         //if (!pwindowing->load_cursor(pcursor, path, true, bFromCache))
         //{

            //pcursor->load_system_default_cursor_hint();

         //}

      }

      return pcursor;

   }


   void cursor_manager::load_hotspot(const ::file::path & pathFolder)
   {

      // auto pcontext = get_context();

      parse_hotspot_text(file()->as_string(pathFolder / "hotspot.txt"));

   }


   void cursor_manager::parse_hotspot_text(const ::scoped_string & scopedstrText)
   {

      string_array straLines;

      straLines.add_lines(scopedstrText, false);

      for (auto & strLine : straLines)
      {

         string_array straColon;

         straColon.explode(":", strLine);

         if (straColon.get_count() == 2)
         {

            string_array straComma;

            straComma.explode(",", straColon[1]);

            if (straComma.get_count() == 2)
            {

               string strName = straColon[0];

               strName.trim();

               auto pcursor = m_cursormap[cursor_enum(strName)];

               if (pcursor.is_set())
               {

                  pcursor->m_szHotspotOffset.cx() = atoi(straComma[0].trimmed());

                  pcursor->m_szHotspotOffset.cy() = atoi(straComma[1].trimmed());

               }

            }

         }

      }

   }
   
   
   void cursor_manager::set_cursor_set_from_matter(::object * pobjectContext, const ::file::path & pathMatter)
   {

      // "arrow.png" is a troll/bait for getting the right path of the cursor file, then the directory where found

      auto pcontext = pobjectContext->m_papplication;

      ::file::path pathArrow = pcontext->directory()->matter(pathMatter / "arrow.png");
      
      if(pathArrow.is_empty())
      {
         
         return;
         
      }

      ::file::path pathFolder = pathArrow.folder();

      set_cursor_set_from_dir(pobjectContext, pathFolder);

   }


   void cursor_manager::set_cursor_set_from_dir(::object * pobjectContext, const ::file::path & pathFolder, bool bFromCache)
   {

      ::collection::count countSuccess = 0;

      ::collection::count countFailed = 0;

      auto pcursorpair = g_pcursorpaira;

      while (pcursorpair->m_ecursor != e_cursor_none)
      {

         string strCursorName;

         strCursorName.formatf("%s.png", pcursorpair->m_pszName);

         if (set_cursor_file(pcursorpair->m_ecursor, pathFolder / strCursorName, bFromCache))
         {

            information() << "set_cursor_file : " << (pathFolder / strCursorName);

            countSuccess++;

         }
         else
         {

            countFailed++;

         }

         pcursorpair++;

      }

      //if (set_cursor_file(e_cursor_arrow, pathFolder / "arrow.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_hand, pathFolder / "hand.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_text_select, pathFolder / "text_select.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_top_left, pathFolder / "size_top_left.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_top, pathFolder / "size_top.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_top_right, pathFolder / "size_top_right.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_right, pathFolder / "size_right.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}


      //if (set_cursor_file(e_cursor_size_bottom_right, pathFolder / "size_bottom_right.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_bottom, pathFolder / "size_bottom.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_bottom_left, pathFolder / "size_bottom_left.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_left, pathFolder / "size_left.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_vertical, pathFolder / "size_vertical.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}


      //if (set_cursor_file(e_cursor_size_horizontal, pathFolder / "size_horizontal.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_move, pathFolder / "transfer.png", false))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      load_hotspot(pathFolder);

      //return _003CountStatus(countFailed, countSuccess);

   }


   void cursor_manager::set_cursor_set_system_default()
   {


      ::collection::count countSuccess = 0;

      ::collection::count countFailed = 0;

      auto pcursorpair = g_pcursorpaira;

      while (pcursorpair->m_ecursor != e_cursor_none)
      {

         if (set_system_default_cursor(pcursorpair->m_ecursor))
         {

            countSuccess++;

         }
         else
         {

            countFailed++;

         }

         pcursorpair++;

      }
      //::collection::count count = 0;

      //if (set_system_default_cursor(e_cursor_arrow))
      //{
      //   count++;
      //}

      //if (set_system_default_cursor(e_cursor_hand))
      //{
      //   count++;
      //}

      //if (set_system_default_cursor(e_cursor_text_select))
      //{
      //   count++;
      //}

      //if (set_system_default_cursor(e_cursor_size_top_left))
      //{
      //   count++;
      //}

      //if (set_system_default_cursor(e_cursor_size_top))
      //{
      //   count++;
      //}

      //if (set_system_default_cursor(e_cursor_size_top_right))
      //{
      //   count++;
      //}

      //if (set_system_default_cursor(e_cursor_size_right))
      //{
      //   count++;
      //}

      //if (set_system_default_cursor(e_cursor_size_bottom_right))
      //{
      //   count++;
      //}

      //if (set_system_default_cursor(e_cursor_size_bottom))
      //{
      //   count++;
      //}

      //if (set_system_default_cursor(e_cursor_size_bottom_left))
      //{
      //   count++;
      //}

      //if (set_system_default_cursor(e_cursor_size_left))
      //{
      //   count++;
      //}

      //if (set_system_default_cursor(e_cursor_size_vertical))
      //{
      //   count++;
      //}

      //if (set_system_default_cursor(e_cursor_size_horizontal))
      //{
      //   count++;
      //}

      //return _003CountStatus(countFailed, countSuccess);

   }


   ::pointer<cursor>cursor_manager::set_system_default_cursor(enum_cursor ecursor)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      cursor * pcursor = get_cursor(ecursor);

//      if (pcursor->load_system_default_cursor_hint())
//      {
//
//         return pcursor;
//
//      }

      if(!pcursor)
      {

         return nullptr;

      }

      return pcursor;

   }


   // ::aura::application* cursor_manager::get_app()
   // {
   //
   //    return m_papplication && m_papplication->m_papplication ? m_papplication->m_papplication : nullptr;
   //
   // }
   //
   //
   // ::aura::session* cursor_manager::get_session()
   // {
   //
   //    return m_papplication && m_papplication->m_psession ? m_papplication->m_psession : nullptr;
   //
   // }


   //::aura::system* cursor_manageracmesystem()
   //{

   //   return ::is_set(system()) ? system() : nullptr;

   //}




} // namespace windowing



