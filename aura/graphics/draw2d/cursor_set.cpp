#include "framework.h"


//namespace draw2d
//{
//
//
//   cursor_set::cursor_set()
//   {
//
//   }
//
//
//   cursor_set::~cursor_set()
//   {
//
//
//   }
//
//
//   void cursor_set::finalize()
//   {
//
//      for (auto& pcursor : m_cursormap.values())
//      {
//
//         pcursor->finalize();
//
//      }
//
//      m_cursormap.remove_all();
//
//      ::matter::finalize();
//
//   }
//
//
//   string cursor_set::cursor_name(enum_cursor ecursor)
//   {
//
//      switch (ecursor)
//      {
//      case e_cursor_arrow:
//         return "arrow";
//      case e_cursor_hand:
//         return "hand";
//      case e_cursor_text_select:
//         return "text_select";
//      case e_cursor_size_top_left:
//         return "size_top_left";
//      case e_cursor_size_top:
//         return "size_top";
//      case e_cursor_size_top_right:
//         return "size_top_right";
//      case e_cursor_size_right:
//         return "size_top_right";
//      case e_cursor_size_bottom_right:
//         return "size_bottom_right";
//      case e_cursor_size_bottom:
//         return "size_bottom";
//      case e_cursor_size_bottom_left:
//         return "size_bottom_left";
//      case e_cursor_size_left:
//         return "size_left";
//      case e_cursor_size_vertical:
//         return "size_vertical";
//      case e_cursor_size_horizontal:
//         return "size_horizontal";
//      case e_cursor_move:
//         return "size_top_right";
//      default:
//         return "(unknown)";
//      }
//
//   }
//
//   enum_cursor cursor_set::cursor_enum(string strCursor)
//   {
//
//      strCursor.make_lower();
//      strCursor.trim();
//
//      if (strCursor == "arrow") { return e_cursor_arrow; }
//      else if (strCursor == "hand") { return e_cursor_hand; }
//      else if (strCursor == "text_select") { return e_cursor_text_select; }
//      else if (::str::begins_eat_ci(strCursor, "size_"))
//      {
//         if (::str::begins_eat_ci(strCursor, "top"))
//         {
//            if (strCursor.is_empty()) { return e_cursor_size_top; }
//            else if (strCursor == "_left") { return e_cursor_size_top_left; }
//            else if (strCursor == "_right") { return e_cursor_size_top_right; }
//         }
//         else if (::str::begins_eat_ci(strCursor, "bottom"))
//         {
//            if (strCursor.is_empty()) { return e_cursor_size_bottom; }
//            else if (strCursor == "_left") { return e_cursor_size_bottom_left; }
//            else if (strCursor == "_right") { return e_cursor_size_bottom_right; }
//         }
//         else if (strCursor == "left") { return e_cursor_size_left; }
//         else if (strCursor == "right") { return e_cursor_size_right; }
//         else if (strCursor == "vertical") { return e_cursor_size_vertical; }
//         else if (strCursor == "horizontal") { return e_cursor_size_horizontal; }
//      }
//      else if (strCursor == "move") { return e_cursor_move; }
//
//
//      return e_cursor_none;
//
//   }
//
//
//   __pointer(cursor) cursor_set::get_cursor(enum_cursor ecursor)
//   {
//
//      synchronization_lock synchronizationlock(mutex());
//
//      auto & pcursor = m_cursormap[ecursor];
//
//      if (pcursor)
//      {
//
//         return pcursor;
//
//      }
//
//      __construct_new(pcursor);
//
//      pcursor->m_ecursor = ecursor;
//
//      m_cursormap.set_at(ecursor, pcursor);
//
//      return pcursor;
//
//   }
//
//
//   __pointer(cursor) cursor_set::set_cursor_file(enum_cursor ecursor, const ::file::path& pathParam, bool bFromCache)
//   {
//
//      cursor* pcursor = nullptr;
//
//      //{
//
//      //   synchronization_lock synchronizationlock(mutex());
//
//      //   pcursor = get_cursor(ecursor);
//
//      //}
//
//      //auto path = pathParam;
//
//      //if (psystem->m_bImaging)
//      //{
//
//      ////fork([this, pcursor, path, bFromCache]()
//      //{
//
//      //   pcursor->initialize_system_default();
//
//      //   if (psession->user()->windowing()->load_cursor(pcursor, path, true, bFromCache))
//      //   {
//
//      //      //return pcursor;
//
//      //   }
//      //   else
//      //   {
//
//
//      //      {
//
//      //         //return pcursor;
//
//      //      }
//
//      //      //return nullptr;
//
//      //   }
//
//      //}//);
//
//      //}
//
//      return pcursor;
//
//   }
//
//   void cursor_set::load_hotspot(const ::file::path& pathDir)
//   {
//
//      parse_hotspot_text(pcontext->file().as_string(pathDir / "hotspot.txt"));
//
//   }
//
//   void cursor_set::parse_hotspot_text(string strText)
//   {
//
//      string_array straLines;
//
//      straLines.add_lines(strText, false);
//
//      for (auto& strLine : straLines)
//      {
//
//         string_array straColon;
//
//         straColon.explode(":", strLine);
//
//         if (straColon.get_count() == 2)
//         {
//
//            string_array straComma;
//
//            straComma.explode(",", straColon[1]);
//
//            if (straComma.get_count() == 2)
//            {
//
//               string strName = straColon[0];
//
//               strName.trim();
//
//               auto pcursor = m_cursormap[cursor_enum(strName)];
//
//               if (pcursor.is_set())
//               {
//
//                  pcursor->m_szHotspotOffset.cx = atoi(straComma[0].trimmed());
//
//                  pcursor->m_szHotspotOffset.cy = atoi(straComma[1].trimmed());
//
//               }
//
//            }
//
//         }
//
//      }
//
//   }
//   ::count cursor_set::set_cursor_set_from_matter(const ::file::path & pathMatter)
//   {
//
//      // "arrow.png" is a troll/bait for getting the right path of the cursor file, then the directory where found
//
//      ::file::path pathArrow = pcontext->dir().matter(pathMatter / "arrow.png");
//
//      ::file::path pathFolder = pathArrow.folder();
//
//      return set_cursor_set_from_dir(pathFolder);
//
//   }
//
//
//   ::count cursor_set::set_cursor_set_from_dir(const ::file::path & pathDir, bool bFromCache)
//   {
//
//      ::count count = 0;
//
//      if (set_cursor_file(e_cursor_arrow, pathDir / "arrow.png", bFromCache))
//      {
//         count++;
//      }
//      else
//      {
//         return 0;
//      }
//      if (set_cursor_file(e_cursor_hand, pathDir / "hand.png", bFromCache))
//      {
//         count++;
//      }
//      else
//      {
//         set_cursor_file(e_cursor_hand, pathDir / "arrow.png", bFromCache);
//      }
//      if (set_cursor_file(e_cursor_text_select, pathDir / "text_select.png", bFromCache))
//      {
//         count++;
//      }
//      else
//      {
//         set_cursor_file(e_cursor_text_select, pathDir / "arrow.png", bFromCache);
//      }
//      if (set_cursor_file(e_cursor_size_top_left, pathDir / "size_top_left.png", bFromCache))
//      {
//         count++;
//      }
//      else
//      {
//         set_cursor_file(e_cursor_size_top_left, pathDir / "arrow.png", bFromCache);
//      }
//      if (set_cursor_file(e_cursor_size_top, pathDir / "size_top.png", bFromCache))
//      {
//         count++;
//      }
//      else
//      {
//         set_cursor_file(e_cursor_size_top, pathDir / "arrow.png", bFromCache);
//      }
//      if (set_cursor_file(e_cursor_size_top_right, pathDir / "size_top_right.png", bFromCache))
//      {
//         count++;
//      }
//      else
//      {
//         set_cursor_file(e_cursor_size_top_right, pathDir / "arrow.png", bFromCache);
//      }
//      if (set_cursor_file(e_cursor_size_right, pathDir / "size_right.png", bFromCache))
//      {
//         count++;
//      }
//      else
//      {
//         set_cursor_file(e_cursor_size_right, pathDir / "arrow.png", bFromCache);
//      }
//      if (set_cursor_file(e_cursor_size_bottom_right, pathDir / "size_bottom_right.png", bFromCache))
//      {
//         count++;
//      }
//      else
//      {
//         set_cursor_file(e_cursor_size_bottom_right, pathDir / "arrow.png", bFromCache);
//      }
//      if (set_cursor_file(e_cursor_size_bottom, pathDir / "size_bottom.png", bFromCache))
//      {
//         count++;
//      }
//      else
//      {
//         set_cursor_file(e_cursor_size_bottom, pathDir / "arrow.png", bFromCache);
//      }
//      if (set_cursor_file(e_cursor_size_bottom_left, pathDir / "size_bottom_left.png", bFromCache))
//      {
//         count++;
//      }
//      else
//      {
//         set_cursor_file(e_cursor_size_bottom_left, pathDir / "arrow.png", bFromCache);
//      }
//      if (set_cursor_file(e_cursor_size_left, pathDir / "size_left.png", bFromCache))
//      {
//         count++;
//      }
//      else
//      {
//         set_cursor_file(e_cursor_size_left, pathDir / "arrow.png", bFromCache);
//      }
//      if (set_cursor_file(e_cursor_size_vertical, pathDir / "size_vertical.png", bFromCache))
//      {
//         count++;
//      }
//      else
//      {
//         set_cursor_file(e_cursor_size_vertical, pathDir / "arrow.png", bFromCache);
//      }
//      if (set_cursor_file(e_cursor_size_horizontal, pathDir / "size_horizontal.png", bFromCache))
//      {
//         count++;
//      }
//      else
//      {
//         set_cursor_file(e_cursor_size_horizontal, pathDir / "arrow.png", bFromCache);
//      }
//      if (set_cursor_file(e_cursor_move, pathDir / "move.png", false))
//      {
//         count++;
//      }
//      else
//      {
//         set_cursor_file(e_cursor_move, pathDir / "arrow.png", bFromCache);
//      }
//
//      load_hotspot(pathDir);
//
//      return count;
//
//   }
//
//
//   ::count cursor_set::set_cursor_set_system_default()
//   {
//
//      ::count count = 0;
//
//      if (set_system_default_cursor(e_cursor_arrow))
//      {
//         count++;
//      }
//
//      if (set_system_default_cursor(e_cursor_hand))
//      {
//         count++;
//      }
//
//      if (set_system_default_cursor(e_cursor_text_select))
//      {
//         count++;
//      }
//
//      if (set_system_default_cursor(e_cursor_size_top_left))
//      {
//         count++;
//      }
//
//      if (set_system_default_cursor(e_cursor_size_top))
//      {
//         count++;
//      }
//
//      if (set_system_default_cursor(e_cursor_size_top_right))
//      {
//         count++;
//      }
//
//      if (set_system_default_cursor(e_cursor_size_right))
//      {
//         count++;
//      }
//
//      if (set_system_default_cursor(e_cursor_size_bottom_right))
//      {
//         count++;
//      }
//
//      if (set_system_default_cursor(e_cursor_size_bottom))
//      {
//         count++;
//      }
//
//      if (set_system_default_cursor(e_cursor_size_bottom_left))
//      {
//         count++;
//      }
//
//      if (set_system_default_cursor(e_cursor_size_left))
//      {
//         count++;
//      }
//
//      if (set_system_default_cursor(e_cursor_size_vertical))
//      {
//         count++;
//      }
//
//      if (set_system_default_cursor(e_cursor_size_horizontal))
//      {
//         count++;
//      }
//
//      return count;
//
//   }
//
//   __pointer(cursor) cursor_set::set_system_default_cursor(enum_cursor ecursor)
//   {
//
//      synchronization_lock synchronizationlock(mutex());
//
//      cursor* pcursor = get_cursor(ecursor);
//
//      if (pcursor->initialize_system_default())
//      {
//
//         return pcursor;
//
//      }
//
//      return nullptr;
//
//   }
//
//
//
//} // namespace draw2d
//
//
//
