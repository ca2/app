#include "framework.h" // previously aura/user/user.h


namespace colorertake5
{


   RegionHandler::RegionHandler()
   {
   }

   RegionHandler::~RegionHandler()
   {
   }

   /** Start of text parsing.
   Called only once, when text_parser starts
   parsing of the specified block of text.
   All other event messages comes between this call and
   endParsing call.
   @param lno Start line number
   */
   void RegionHandler::startParsing(index lno)
   {
      UNREFERENCED_PARAMETER(lno);
   }

   /** End of text parsing.
   Called only once, when text_parser stops
   parsing of the specified block of text.
   @param lno End line number
   */
   void RegionHandler::endParsing(index lno)
   {
      UNREFERENCED_PARAMETER(lno);
   }

   /** clear line event.
   Called once for each parsed text line, when text_parser starts to parse
   specified line of text. This method is called before any of the region
   information passed, and used often to clear internal handler
   structure of this line before adding memory_new one.
   @param lno Line number
   */
   void RegionHandler::clearLine(index lno, const ::string &line)
   {
      UNREFERENCED_PARAMETER(lno);
      UNREFERENCED_PARAMETER(line);
   }

   /** Informs handler about lexical region in line.
   This is a basic method, wich transfer information from
   parser to application. Positions of different passed regions
   can be overlapped.
   @param lno Current line number
   @param sx Start X position of region in line
   @param ex End X position of region in line
   @param region region information
   */
   //virtual void RegionHandler::addRegion(i32 lno, const ::string &line, i32 sx, i32 ex, class region *region) = 0;

   /** Informs handler about entering into specified scheme.
   Parameter <code>region</code> is used to specify
   scheme background region information.
   If text is parsed not from the first line, this method is called
   with fake parameters to compensate required scheme structure.
   @param lno Current line number
   @param sx Start X position of region in line
   @param ex End X position of region in line
   @param region scheme region information (background)
   @param scheme Additional scheme information
   */
   //virtual void RegionHandler::enterScheme(i32 lno, const ::string &line, i32 sx, i32 ex, class region *region, class scheme *scheme) = 0;

   /** Informs handler about leaveing specified scheme.
   Parameter <code>region</code> is used to specify
   scheme background region information.
   If text parse process ends, but current schemes stack is not balanced
   (this can happends because of bad balanced structure of source text,
   or partial text parse) this method is <b>not</b> called for unbalanced
   levels.
   @param lno Current line number
   @param sx Start X position of region in line
   @param ex End X position of region in line
   @param region scheme region information (background)
   @param scheme Additional scheme information
   */
   //void RegionHandler::leaveScheme(i32 lno, const char  *line, i32 sx, i32 ex, class region *region, class scheme *scheme) = 0


} // namespace colorertake5

