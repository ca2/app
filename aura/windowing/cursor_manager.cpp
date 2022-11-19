#include "framework.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "aura/windowing/cursor_manager.h"
#include "aura/windowing/cursor.h"
#include "aura/platform/system.h"


namespace windowing
{

   struct cursor_pair
   {
      enum_cursor m_ecursor;
      const char * m_pszName;

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


   void cursor_manager::destroy()
   {

      for (auto & pcursor : m_cursormap.values())
      {

         pcursor->destroy();

      }

      m_cursormap.erase_all();

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


   enum_cursor cursor_manager::cursor_enum(string strCursor)
   {

      strCursor.make_lower();
      strCursor.trim();

      if (strCursor == "arrow") { return e_cursor_arrow; }
      else if (strCursor == "hand") { return e_cursor_hand; }
      else if (strCursor == "text_select") { return e_cursor_text_select; }
      else if (strCursor.begins_eat_ci("size_"))
      {
         if (strCursor.begins_eat_ci("top"))
         {
            if (strCursor.is_empty()) { return e_cursor_size_top; }
            else if (strCursor == "_left") { return e_cursor_size_top_left; }
            else if (strCursor == "_right") { return e_cursor_size_top_right; }
         }
         else if (strCursor.begins_eat_ci("bottom"))
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
      else if (strCursor == "move") { return e_cursor_move; }


      return e_cursor_none;

   }


   ::pointer<cursor>cursor_manager::get_cursor(enum_cursor ecursor)
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto & pcursor = m_cursormap[ecursor];

      if (pcursor)
      {

         return pcursor;

      }

      __construct(pcursor);

      pcursor->set_cursor(ecursor);

      m_cursormap.set_at(ecursor, pcursor);

      return pcursor;

   }


   ::pointer<cursor>cursor_manager::set_cursor_file(enum_cursor ecursor, const ::file::path & pathParam, bool bFromCache)
   {

      cursor * pcursor = nullptr;

      {

         synchronous_lock synchronouslock(this->synchronization());

         pcursor = get_cursor(ecursor);

      }

      auto path = pathParam;

      auto psystem = acmesystem()->m_paurasystem;

      if (psystem->m_bImaging)
      {

         pcursor->set_file_path(path);

         //auto psession = get_session();

         //auto puser = psession->user();

         //auto pwindowing = puser->windowing();

         //if (!pwindowing->load_cursor(pcursor, path, true, bFromCache))
         //{

            //pcursor->load_system_default_cursor_hint();

         //}

      }

      return pcursor;

   }


   void cursor_manager::load_hotspot(const ::file::path & pathDir)
   {

      auto pcontext = get_context();

      parse_hotspot_text(pcontext->m_papexcontext->file()->as_string(pathDir / "hotspot.txt"));

   }


   void cursor_manager::parse_hotspot_text(string strText)
   {

      string_array straLines;

      straLines.add_lines(strText, false);

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

                  pcursor->m_szHotspotOffset.cx = atoi(straComma[0].trimmed());

                  pcursor->m_szHotspotOffset.cy = atoi(straComma[1].trimmed());

               }

            }

         }

      }

   }
   
   
   void cursor_manager::set_cursor_set_from_matter(::object * pobjectContext, const ::file::path & pathMatter)
   {

      // "arrow.png" is a troll/bait for getting the right path of the cursor file, then the directory where found

      auto pcontext = pobjectContext->m_pcontext;

      ::file::path pathArrow = dir()->matter(pathMatter / "arrow.png");
      
      if(pathArrow.is_empty())
      {
         
         return;
         
      }

      ::file::path pathFolder = pathArrow.folder();

      set_cursor_set_from_dir(pobjectContext, pathFolder);

   }


   void cursor_manager::set_cursor_set_from_dir(::object * pobjectContext, const ::file::path & pathDir, bool bFromCache)
   {

      ::count countSuccess = 0;

      ::count countFailed = 0;

      auto pcursorpair = g_pcursorpaira;

      while (pcursorpair->m_ecursor != e_cursor_none)
      {

         string strCursorName;

         strCursorName.format("%s.png", pcursorpair->m_pszName);

         if (set_cursor_file(pcursorpair->m_ecursor, pathDir / strCursorName, bFromCache))
         {

            countSuccess++;

         }
         else
         {

            countFailed++;

         }

         pcursorpair++;

      }

      //if (set_cursor_file(e_cursor_arrow, pathDir / "arrow.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_hand, pathDir / "hand.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_text_select, pathDir / "text_select.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_top_left, pathDir / "size_top_left.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_top, pathDir / "size_top.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_top_right, pathDir / "size_top_right.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_right, pathDir / "size_right.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}


      //if (set_cursor_file(e_cursor_size_bottom_right, pathDir / "size_bottom_right.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_bottom, pathDir / "size_bottom.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_bottom_left, pathDir / "size_bottom_left.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_left, pathDir / "size_left.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_size_vertical, pathDir / "size_vertical.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}


      //if (set_cursor_file(e_cursor_size_horizontal, pathDir / "size_horizontal.png", bFromCache))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      //if (set_cursor_file(e_cursor_move, pathDir / "move.png", false))
      //{

      //   countSuccess++;

      //}
      //else
      //{

      //   countFailed++;

      //}

      load_hotspot(pathDir);

      //return _003CountStatus(countFailed, countSuccess);

   }


   void cursor_manager::set_cursor_set_system_default()
   {


      ::count countSuccess = 0;

      ::count countFailed = 0;

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
      //::count count = 0;

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

      synchronous_lock synchronouslock(this->synchronization());

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


   ::aura::application* cursor_manager::get_app()
   {

      return m_pcontext && m_pcontext->m_papexapplication ? m_pcontext->m_papexapplication->m_pauraapplication : nullptr;

   }


   ::aura::session* cursor_manager::get_session()
   {

      return m_pcontext && m_pcontext->m_papexsession ? m_pcontext->m_papexsession->m_paurasession : nullptr;

   }


   ::aura::system* cursor_manager::get_system()
   {

      return ::is_set(acmesystem()) ? acmesystem()->m_paurasystem : nullptr;

   }




} // namespace windowing



