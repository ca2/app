#include "framework.h" // previously aura/user/user.h


namespace colorertake5
{


#define IDLE_PARSE(time) (100+time*4)

   ErrorHandler *eh;



   base_editor::base_editor(::object * pobject) :
      object(pobject)
   {
      textParser = nullptr;
      lrSupport = nullptr;
      regionMapper = nullptr;
      validationProcess = false;
      internalRM = false;
   }

   base_editor::~base_editor()
   {
      if(textParser != nullptr)
      {
         textParser->breakParse();
      }
      breakParse = true;
      while(validationProcess); /// @todo wait until validation is finished
      if(internalRM)
      {
         if(regionMapper != nullptr)
         {
            delete regionMapper;
         }
      }
      if(lrSupport != nullptr)
      {
         delete lrSupport;
      }
      if(textParser != nullptr)
      {
         delete textParser;
      }
   }


   void base_editor::initialize(line_source *lineSource)
   {

      ParserFactory *parserFactory = &papplication->parser_factory();

      if (parserFactory == nullptr || lineSource == nullptr)
      {

         __throw(exception(string("Bad base_editor constructor parameters")));

      }

      this->parserFactory = parserFactory;

      this->lineSource = lineSource;

      hrcParser = parserFactory->getHRCParser();
      textParser = parserFactory->createTextParser();

      textParser->setRegionHandler(this);
      textParser->setLineSource(lineSource);

      lrSupport = nullptr;

      invalidLine = 0;
      changedLine = 0;
      backParse = -1;
      lineCount = 0;
      wStart = 0;
      wSize = 20;
      lrSize = wSize*3;
      internalRM = false;
      regionMapper = nullptr;
      regionCompact = false;
      currentFileType = nullptr;

      breakParse = false;
      validationProcess = false;

      setRegionCompact(regionCompact);

      def_Text = hrcParser->getRegion(("def:Text"));
      def_Syntax = hrcParser->getRegion(("def:Syntax"));
      def_Special = hrcParser->getRegion(("def:Special"));
      def_PairStart = hrcParser->getRegion(("def:PairStart"));
      def_PairEnd = hrcParser->getRegion(("def:PairEnd"));

      rd_def_Text = rd_def_HorzCross = rd_def_VertCross = nullptr;
      eh = parserFactory->getErrorHandler();
   }


   void base_editor::setRegionCompact(bool compact)
   {
      if (!lrSupport || regionCompact != compact)
      {
         regionCompact = compact;
         remapLRS(true);
      }
   }

   void base_editor::setRegionMapper(RegionMapper *rs)
   {
      if (internalRM) delete regionMapper;
      regionMapper = rs;
      internalRM = false;
      remapLRS(false);
   }

   void base_editor::setRegionMapper(string hrdClass, string hrdName)
   {
      if (internalRM) delete regionMapper;
      regionMapper = parserFactory->createStyledMapper(hrdClass, hrdName);
      internalRM = true;
      remapLRS(false);
   }

   void base_editor::remapLRS(bool recreate)
   {
      if (recreate || lrSupport == nullptr)
      {
         delete lrSupport;
         if (regionCompact)
         {
            lrSupport = new LineRegionsCompactSupport();
         }
         else
         {
            lrSupport = new LineRegionsSupport();
         }
         lrSupport->resize(lrSize);
         lrSupport->clear();
      };
      lrSupport->setRegionMapper(regionMapper);
      lrSupport->setSpecialRegion(def_Special);
      invalidLine = 0;
      rd_def_Text = rd_def_HorzCross = rd_def_VertCross = nullptr;
      if (regionMapper != nullptr)
      {
         rd_def_Text = regionMapper->getRegionDefine(string("def:Text"));
         rd_def_HorzCross = regionMapper->getRegionDefine(string("def:HorzCross"));
         rd_def_VertCross = regionMapper->getRegionDefine(string("def:VertCross"));
      };
   }

   void base_editor::setFileType(file_type *ftype)
   {
      CLR_INFO("axis_editor", "setFileType:%s", ftype->getName().c_str());
      currentFileType = ftype;
      textParser->setFileType(currentFileType);
      invalidLine = 0;
   }

   file_type *base_editor::setFileType(const string &fileType)
   {
      currentFileType = hrcParser->getFileType(fileType);
      setFileType(currentFileType);
      return currentFileType;
   }

   file_type *base_editor::chooseFileType(string fileName)
   {
      if (lineSource == nullptr)
      {
         currentFileType = hrcParser->chooseFileType(fileName, nullptr);
      }
      else
      {
         string textStart;
         strsize totalLength = 0;
         for(i32 i = 0; i < 4; i++)
         {
            string iLine = lineSource->getLine(i);
            if(iLine.is_empty())
               break;
            textStart += iLine;
            textStart + "\n";
            totalLength += iLine.get_length();
            if (totalLength > 500) break;
         }
         currentFileType = hrcParser->chooseFileType(fileName, textStart);
      }
      setFileType(currentFileType);
      return currentFileType;
   }

   file_type *base_editor::getFileType()
   {
      return currentFileType;
   }

   void base_editor::setBackParse(i32 backParse)
   {
      this->backParse = backParse;
   }

   void base_editor::addRegionHandler(RegionHandler *rh)
   {
      regionHandlers.add(rh);
   }

   void base_editor::eraseRegionHandler(RegionHandler *rh)
   {
      regionHandlers.erase(rh);
   }

   void base_editor::addEditorListener(EditorListener *el)
   {
      editorListeners.add(el);
   }

   void base_editor::eraseEditorListener(EditorListener *el)
   {
      editorListeners.erase(el);
   }


   PairMatch *base_editor::getPairMatch(index lineNo, index linePos)
   {

      LineRegion * lrStart = getLineRegions(lineNo);

      if (lrStart == nullptr)
         return nullptr;

      LineRegion *pair = nullptr;
      for(LineRegion *l1 = lrStart; l1; l1 = l1->next)
      {
         if ((l1->region->hasParent(def_PairStart) ||
               l1->region->hasParent(def_PairEnd)) &&
               linePos >= l1->start && linePos <= l1->end)
            pair = l1;
      }

      if (pair != nullptr)
      {
         PairMatch *pm = new PairMatch(pair, lineNo, pair->region->hasParent(def_PairStart));
         pm->setStart(pair);
         return pm;
      }

      return nullptr;

   }

   PairMatch * base_editor::getEnwrappedPairMatch(i32 lineNo, i32 pos)
   {
      __UNREFERENCED_PARAMETER(lineNo);
      __UNREFERENCED_PARAMETER(pos);
      return nullptr;
   }

   void base_editor::releasePairMatch(PairMatch *pm)
   {
      delete pm;
   }

   PairMatch *base_editor::searchLocalPair(i32 lineNo, i32 pos)
   {
      index lno;
      index end_line = getLastVisibleLine();
      PairMatch *pm = getPairMatch(lineNo, pos);
      if (pm == nullptr)
      {
         return nullptr;
      }

      lno = pm->sline;

      LineRegion *pair = pm->getStartRef();
      LineRegion *slr = getLineRegions(lno);
      while(true)
      {
         if (pm->pairBalance > 0)
         {
            pair = pair->next;
            while(pair == nullptr)
            {
               lno++;
               if (lno > end_line) break;
               pair = getLineRegions(lno);
            }
            if (lno > end_line) break;
         }
         else
         {
            if(pair->prev == slr->prev)  // first region
            {
               lno--;
               if (lno < wStart) break;
               slr = getLineRegions(lno);
               pair = slr;
            }
            if (lno < wStart) break;
            pair = pair->prev;
         }
         if (pair->region->hasParent(def_PairStart))
         {
            pm->pairBalance++;
         }
         if (pair->region->hasParent(def_PairEnd))
         {
            pm->pairBalance--;
         }
         if (pm->pairBalance == 0)
         {
            break;
         }
      }
      if (pm->pairBalance == 0)
      {
         pm->eline = lno;
         pm->setEnd(pair);
      }
      return pm;
   }

   PairMatch *base_editor::searchGlobalPair(i32 lineNo, i32 pos)
   {
      index lno;
      index end_line = lineCount;
      PairMatch *pm = getPairMatch(lineNo, pos);
      if (pm == nullptr)
      {
         return nullptr;
      }

      lno = pm->sline;

      LineRegion *pair = pm->getStartRef();
      LineRegion *slr = getLineRegions(lno);
      while(true)
      {
         if (pm->pairBalance > 0)
         {
            pair = pair->next;
            while(pair == nullptr)
            {
               lno++;
               if (lno > end_line) break;
               pair = getLineRegions(lno);
            }
            if (lno > end_line) break;
         }
         else
         {
            if(pair->prev == slr->prev)  // first region
            {
               lno--;
               if (lno < 0) break;
               slr = getLineRegions(lno);
               pair = slr;
            }
            if (lno < 0) break;
            pair = pair->prev;
         }
         if (pair->region->hasParent(def_PairStart))
         {
            pm->pairBalance++;
         }
         if (pair->region->hasParent(def_PairEnd))
         {
            pm->pairBalance--;
         }
         if (pm->pairBalance == 0)
         {
            break;
         }
      }
      if (pm->pairBalance == 0)
      {
         pm->eline = lno;
         pm->setEnd(pair);
      }
      return pm;
   }


   LineRegion *base_editor::getLineRegions(index lno)
   {
      /*
      * Backparse value check
      */
      if (backParse > 0 && lno - invalidLine > backParse)
         return nullptr;

      validate(lno, true);

      return lrSupport->getLineRegions(lno);

   }

   void base_editor::modifyEvent(index topLine)
   {

      CLR_FORMATTED_TRACE("axis_editor", "modifyEvent:%d", topLine);

      if (invalidLine > topLine)
      {
         invalidLine = topLine;

         for(index idx = editorListeners.get_size()-1; idx >= 0; idx--)
            editorListeners.element_at(idx)->modifyEvent(topLine);

      }

   }

   void base_editor::modifyLineEvent(index line)
   {

      if (invalidLine > line)
         invalidLine = line;

      // changedLine = topLine;!!!

   }

   void base_editor::visibleTextEvent(index wStart, ::count wSize)
   {

      CLR_FORMATTED_TRACE("axis_editor", "visibleTextEvent:%d-%d", wStart, wSize);

      this->wStart = wStart;
      this->wSize = wSize;

   }

   void base_editor::lineCountEvent(::count newLineCount)
   {

      CLR_FORMATTED_TRACE("axis_editor", "lineCountEvent:%d", newLineCount);
      lineCount = newLineCount;

   }


   inline index base_editor::getLastVisibleLine()
   {

      index r1 = (wStart+wSize);
      ::count r2 = lineCount;
      return ((r1 > r2)?r2:r1)-1;
   }

   void base_editor::validate(index lno, bool rebuildRegions)
   {

      index parseFrom, parseTo;
      bool layoutChanged = false;
      TextParseMode tpmode = TPM_CACHE_READ;

      if (lno == -1 || lno > lineCount)
      {
         lno = lineCount-1;
      }

      index firstLine = lrSupport->getFirstLine();

      parseFrom = parseTo = (wStart+wSize);

      /*
      * Calculate changes, required by new screen position, if any
      */
      if (lrSize != wSize*2)
      {
         lrSize = wSize*2;
         lrSupport->resize(lrSize);
         lrSupport->clear();
         // Regions were dropped
         layoutChanged = true;
         CLR_TRACE("axis_editor", "lrSize != wSize*2");
      }

      /* Fixes window position according to line number */
      if (lno < wStart || lno > wStart+wSize)
      {
         wStart = lno;
         //if enable, introduces heavy delays on pair searching
         //layoutChanged = true;
      }

      if (layoutChanged || wStart < firstLine || wStart+wSize > firstLine+lrSize)
      {
         /*
         * visible area is shifted and line regions
         * should be rearranged according to
         */
         index newFirstLine = (wStart/wSize)*wSize;
         parseFrom = newFirstLine;
         parseTo   = newFirstLine+lrSize;
         /*
         * Change LineRegions parameters only in case
         * of validate-for-usage request.
         */
         if (rebuildRegions)
         {
            lrSupport->setFirstLine(newFirstLine);
         }
         /* Save time - already has the info in line cache */
         if (!layoutChanged && firstLine - newFirstLine == wSize)
         {
            parseTo -= wSize-1;
         }
         firstLine = newFirstLine;
         layoutChanged = true;
         CLR_FORMATTED_TRACE("axis_editor", "newFirstLine=%d, parseFrom=%d, parseTo=%d", firstLine, parseFrom, parseTo);
      }

      if (!layoutChanged)
      {
         /* Text modification only event */
         if (invalidLine < parseTo)
         {
            parseFrom = invalidLine;
            tpmode = TPM_CACHE_UPDATE;
         }
      }

      /* Text modification general ajustment */
      if (invalidLine < parseFrom)
      {

         parseFrom = invalidLine;
         tpmode = TPM_CACHE_UPDATE;

      }

      if (parseTo > lineCount)
         parseTo = lineCount;

      /* Runs parser */
      if (parseTo-parseFrom > 0)
      {

         CLR_FORMATTED_TRACE("axis_editor", "validate:parse:%d-%d, %s", parseFrom, parseTo, tpmode == TPM_CACHE_READ?"READ":"UPDATE");

         index stopLine = textParser->parse(parseFrom, parseTo-parseFrom, tpmode);

         if (tpmode == TPM_CACHE_UPDATE)
         {
            invalidLine = stopLine+1;
         }
         CLR_FORMATTED_TRACE("axis_editor", "validate:parsed: invalidLine=%d", invalidLine);
      }
   }

   void base_editor::idleJob(i32 time)
   {
      if(time < 0)
         time = 0;

      if(time > 100)
         time = 100;

      if(invalidLine < lineCount)
      {
         validate(invalidLine+IDLE_PARSE(time), false);
      }

   }



   void base_editor::startParsing(index lno)
   {
      lrSupport->startParsing(lno);
      for(index idx = 0; idx < regionHandlers.get_size(); idx++)
         regionHandlers.element_at(idx)->startParsing(lno);
   }

   void base_editor::endParsing(index lno)
   {
      lrSupport->endParsing(lno);
      for(i32 idx = 0; idx < regionHandlers.get_size(); idx++)
         regionHandlers.element_at(idx)->endParsing(lno);
   }

   void base_editor::clearLine(index lno, const ::string &line)
   {
      lrSupport->clearLine(lno, line);
      for(index idx = 0; idx < regionHandlers.get_size(); idx++)
         regionHandlers.element_at(idx)->clearLine(lno, line);
   }

   void base_editor::addRegion(index lno, const ::string &line, strsize sx, strsize ex, class region *region)
   {
      lrSupport->addRegion(lno, line, sx, ex, region);
      for(index idx = 0; idx < regionHandlers.get_size(); idx++)
         regionHandlers.element_at(idx)->addRegion(lno, line, sx, ex, region);
   }

   void base_editor::enterScheme(index lno, const ::string &line, strsize sx, strsize ex, class region *region, class scheme *scheme)
   {
      lrSupport->enterScheme(lno, line, sx, ex, region, scheme);
      for(i32 idx = 0; idx < regionHandlers.get_size(); idx++)
         regionHandlers.element_at(idx)->enterScheme(lno, line, sx, ex, region, scheme);
   }

   void base_editor::leaveScheme(index lno, const ::string &line, strsize sx, strsize ex, class region *region, class scheme *scheme)
   {
      lrSupport->leaveScheme(lno, line, sx, ex, region, scheme);
      for(i32 idx = 0; idx < regionHandlers.get_size(); idx++)
         regionHandlers.element_at(idx)->leaveScheme(lno, line, sx, ex, region, scheme);
   }


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
* decision by deleting thd provisions above and replace them with the notice
* and other provisions required by the GPL or the LGPL. If you do not delete
* the provisions above, a recipient may use your version of this file under
* the terms of any one of the MPL, the GPL or the LGPL.
*
* ***** END LICENSE BLOCK ***** */
