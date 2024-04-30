#pragma once


namespace colorertake5
{


   /**
   * Base Editor functionality.
   * This class implements basic functionality,
   * which could be useful in application's editing system.
   * This includes automatic top-level caching of hilighting
   * state, outline structure creation, pair constructions search.
   * This class has event-oriented structure. Each editor event
   * is passed into this object and gets internal processing.
   * @ingroup colorer_editor
   */
   class CLASS_DECL_SPHERE base_editor :
      public RegionHandler,
      virtual public ::object
   {
   public:
      /**
      * Initial constructor.
      * Creates uninitialized aura editor functionality support.
      * @param pf ParserFactory, used as source of all created
      *        parsers (HRC, HRD, Text parser). Can't be nullptr.
      * @param lineSource Object, that provides parser with
      *        text data in line-separated form. Can't be nullptr.
      */

      base_editor(::particle * pparticle);
      ~base_editor();

      void initialize(line_source * plinesource);

      /**
      * This method informs handler about internal form of
      * requeried LineRegion lists, which is returned after the parsing
      * process. Compact regions are guaranteed not to overlap
      * with each other (this is achieved with more internal processing
      * and more extensive cpu usage); non-compact regions are placed directly
      * as they created by the text_parser and can be overlapped.
      * @note By default, if method is not called, regions are not compacted.
      * @param compact Creates LineRegionsSupport (false) or LineRegionsCompactSupport (true)
      *        object to store lists of RegionDefine's
      */
      void setRegionCompact(bool compact);

      /**
      * Installs specified RegionMapper, which
      * maps HRC Regions into color data.
      * @param rm RegionMapper object to map region values into colors.
      */
      void setRegionMapper(RegionMapper *rm);

      /**
      * Installs specified RegionMapper, which
      * is created with ParserFactory methods and maintained internally by this handler.
      * If no one of two overloads of setRegionMapper is called,
      * all work is started without mapping of extended region information.
      * @param hrdClass Class of RegionMapper instance
      * @param hrdName  Name of RegionMapper instance
      */
      void setRegionMapper(string hrdClass, string hrdName);

      /**
      * Specifies number of lines, for which parser
      * would be able to run continual processing without
      * highlight invalidation.
      * @param backParse Number of lines. If <= 0, dropped into default
      * value.
      */
      void setBackParse(i32 backParse);

      /**
      * Initial HRC type, used for parse processing.
      * If changed during processing, all text information
      * is invalidated.
      */
      void setFileType(file_type *ftype);
      /**
      * Initial HRC type, used for parse processing.
      * If changed during processing, all text information is invalidated.
      */
      file_type *setFileType(const string &fileType);
      /**
      * Tries to choose appropriate file type from HRC database
      * using passed fileName and first line of text (if available through lineSource)
      */
      file_type *chooseFileType(string fileName);

      /**
      * Returns currently used HRC file type
      */
      file_type *getFileType();

      /**
      * Adds specified RegionHandler object
      * into parse process.
      */
      void addRegionHandler(RegionHandler *rh);

      /**
      * Removes previously added RegionHandler object.
      */
      void eraseRegionHandler(RegionHandler *rh);

      /**
      * Adds specified EditorListener object into parse process.
      */
      void addEditorListener(EditorListener *el);

      /**
      * Removes previously added EditorListener object.
      */
      void eraseEditorListener(EditorListener *el);

      /**
      * Searches and creates pair match object in currently visible text.
      * @param lineNo Line number, where to search paired region.
      * @param pos position in line, where paired region to be searched.
      *        Paired region is found, if it includes specified position
      *        or ends directly at one char before line position.
      */
      PairMatch *searchLocalPair(i32 lineNo, i32 pos);

      /**
      * Searches pair match in all available text, possibly,
      * making additional processing.
      * @param pos position in line, where paired region to be searched.
      *        Paired region is found, if it includes specified position
      *        or ends directly at one char before line position.
      */
      PairMatch *searchGlobalPair(i32 lineNo, i32 pos);

      /**
      * Searches and creates pair match object of first enwrapping block.
      * Returned object could be used as with getPairMatch method.
      * Enwrapped block is the first meeted start of block, if moving
      * from specified position to the left and top.
      * Not Implemented yet.
      *
      * @param lineNo Line number, where to search paired region.
      * @param pos position in line, where paired region to be searched.
      */
      PairMatch *getEnwrappedPairMatch(i32 lineNo, i32 pos);

      /**
      * Frees previously allocated PairMatch object.
      * @param pm PairMatch object to free.
      */
      void releasePairMatch(PairMatch *pm);


      /**
      * Return parsed and colored LineRegions of requested line.
      * This method validates current cache state
      * and, if needed, calls Colorer parser to validate modified block of text.
      * size_i32 of reparsed text is choosed according to information
      * about visible text range and modification events.
      * @todo If number of lines, to be reparsed is more, than backParse parameter,
      * then method will return nullptr, until validate() method is called.
      */
      LineRegion *getLineRegions(index lno);

      /**
      * Validates current state of the editor and runs parser, if needed.
      * This method can be called periodically in background thread
      * to make possible background parsing process.
      * @param lno Line number, for which validation is requested.
      *   If this number is in the current visible window range,
      *   the part of text is validated, which is required
      *   for draw2d repaint.
      *   If this number is equals to -1, all the text is validated.
      *   If this number is not in visible range, optimal partial validation
      *   is used.
      * @param rebuildRegions If true, regions will be recalculated and
      *   repositioned for the specified line number usage. If false,
      *   parser will just start internal cache rebuilding procedure.
      */
      void validate(index lno, bool rebuildRegions);

      /**
      * Tries to do some parsing job while ::account::user is doing nothing.
      * @param time integer between 0 and 100, shows an abount of time,
      *             available for this job.
      */
      void idleJob(i32 time);

      /**
      * Informs base_editor object about text modification event.
      * All the text becomes invalid after the specified line.
      * @param topLine Topmost modified line of text.
      */
      void modifyEvent(index topLine);

      /**
      * Informs about single line modification event.
      * Generally, this type of event can be processed much faster
      * because of pre-checking line's changed structure and
      * cancelling further parsing in case of unmodified text structure.
      * @param line Modified line of text.
      * @todo Not used yet! This must include special 'try' parse method.
      */
      void modifyLineEvent(index line);

      /**
      * Informs about changes in visible range of text lines.
      * This information is used to make assumptions about
      * text structure and to make faster parsing.
      * @param wStart Topmost visible line of text.
      * @param wSize  Number of currently visible text lines.
      *               This number must includes all partially visible lines.
      */
      void visibleTextEvent(index wStart, ::raw::count wSize);

      /**
      * Informs about total lines ::raw::count change.
      * This must include initial lines number setting.
      */
      void lineCountEvent(::raw::count newLineCount);

      /** Basic HRC region - default text (background color) */
      class region *def_Text;
      /** Basic HRC region - syntax checkable region */
      class region *def_Syntax;
      /** Basic HRC region - special region */
      class region *def_Special;
      /** Basic HRC region - Paired region start */
      class region *def_PairStart;
      /** Basic HRC region - Paired region end */
      class region *def_PairEnd;

      /** Basic HRC region mapping */
      RegionDefine *rd_def_Text, *rd_def_HorzCross, *rd_def_VertCross;

      void startParsing(index lno);
      void endParsing(index lno);
      void clearLine(index lno, const ::string &line);
      void addRegion(index lno, const ::string &line, strsize sx, strsize ex, class region *region);
      void enterScheme(index lno, const ::string &line, strsize sx, strsize ex, class region *region, class scheme *scheme);
      void leaveScheme(index lno, const ::string &line, strsize sx, strsize ex, class region *region, class scheme *scheme);

   private:
      HRCParser *hrcParser;
      text_parser *textParser;
      ParserFactory *parserFactory;
      line_source *lineSource;
      RegionMapper *regionMapper;
      LineRegionsSupport *lrSupport;

      file_type *currentFileType;
      address_array < RegionHandler * > regionHandlers;
      address_array < EditorListener * > editorListeners;

      i32 backParse;
      // window area
      ::raw::index wStart;
      ::raw::count wSize;
      // line count
      ::raw::count lineCount;
      // this->get_size of line regions
      ::raw::count lrSize;
      // position of last validLine
      ::raw::index invalidLine;
      // no lines structure changes, just single line change
      ::raw::index changedLine;

      bool internalRM;
      bool regionCompact;
      bool breakParse;
      bool validationProcess;

      inline ::raw::index getLastVisibleLine();
      void remapLRS(bool recreate);
      /**
      * Searches for the paired token and creates PairMatch
      * object with valid initial properties filled.
      */
      PairMatch *getPairMatch(index lineNo, index pos);
   protected:
      ErrorHandler *feh;


   };


} // namespace colorertake5


/* ***** BEGIN LICENSE BLOCK *****
* Version: MPL 1.1/GPL 2.0/LGPL 2.1
*
* The contents of this file are topic to the Mozilla Public License Version
* 1.1 (the "License"); you may not use this file except in compliance with
* the License. You may obtain a copy of the License at
* http://www.mozilla.org/MPL/
*
* Software distributed under the License is distributed on an "AS IS" basis,
* WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
* for the specific language governing rights and limitations under the
* License.
*
* The Original Code is the Colorer Library.
*
* The Initial Developer of the Original Code is
* Cail Lomecb <cail@nm.ru>.
* Portions created by the Initial Developer are Copyright (C) 1999-2005
* the Initial Developer.
*
* Contributor(s):
*
* Alternatively, the contents of this file may be used under the terms of
* either the GNU General Public License Version 2 or later (the "GPL"), or
* the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
* in which case the provisions of the GPL or the LGPL are applicable instead
* of those above. If you wish to allow use of your version of this file only
* under the terms of either the GPL or the LGPL, and not to allow others to
* use your version of this file under the terms of the MPL, indicate your
* decision by deleting the provisions above and replace them with the notice
* and other provisions required by the GPL or the LGPL. If you do not delete
* the provisions above, a recipient may use your version of this file under
* the terms of any one of the MPL, the GPL or the LGPL.
*
* ***** END LICENSE BLOCK ***** */
