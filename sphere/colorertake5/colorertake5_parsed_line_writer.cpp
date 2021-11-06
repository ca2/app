#include "framework.h" // previously aura/user/user.h
#include <stdio.h>


namespace colorertake5
{
   /**
   Static service methods of LineRegion output.
   @ingroup colorer_viewer
   */

   /** Writes given line of text using list of passed line regions.
   Formats output with class of each token, enclosed in
   \<span class='regionName'>...\</span>
   @param markupWriter writer, used for markup output
   @param textWriter writer, used for text output
   @param line Line of text
   @param lineRegions Linked list of LineRegion structures.
   Only region references are used there.
   */
   void ParsedLineWriter::tokenWrite(stream & markupWriter, stream & textWriter, string_to_string * docLinkHash, const char  *line, LineRegion *lineRegions)
   {
      __UNREFERENCED_PARAMETER(docLinkHash);
      index pos = 0;
      for(LineRegion *l1 = lineRegions; l1; l1 = l1->next)
      {
         if (l1->special || l1->region == nullptr) continue;
         if (l1->start == l1->end) continue;
         index end = l1->end;
         if (end == -1) end = strlen(line);
         if (l1->start > pos)
         {
            textWriter.write(&line[pos], l1->start - pos);
            pos = l1->start;
         }
         markupWriter << "<span class='";

         class region *region = l1->region;
         while(region != nullptr)
         {
            string token0 = ::str::replace(":", "-", region->getName());
            string token = ::str::replace(".", "-", token0);
            markupWriter << token;
            region = region->getParent();
            if (region != nullptr)
            {
               markupWriter << " ";
            }
         }

         markupWriter << "'>";
         textWriter.write(&line[pos], end - l1->start);
         markupWriter << "</span>";
         pos += end - l1->start;
      }
      if ((u32) pos < strlen(line))
      {
         textWriter.write(&line[pos], strlen(line) - pos);
      }
   }


   /** write specified line of text using list of LineRegion's.
   This method uses text fields of LineRegion class to enwrap each line
   region.
   It uses two Writers - @ca markupWriter and @ca textWriter.
   @ca markupWriter is used to write markup elements of LineRegion,
   and @ca textWriter is used to write line content.
   @param markupWriter writer, used for markup output
   @param textWriter writer, used for text output
   @param line Line of text
   @param lineRegions Linked list of LineRegion structures
   */
   void ParsedLineWriter::markupWrite(stream & markupWriter, stream & textWriter, string_to_string *docLinkHash, const ::string &line, LineRegion *lineRegions)
   {
      __UNREFERENCED_PARAMETER(docLinkHash);

      index pos = 0;

      for(LineRegion *l1 = lineRegions; l1; l1 = l1->next)
      {

         if(l1->special || l1->rdef == nullptr)
            continue;

         if(l1->start == l1->end)
            continue;

         index end = l1->end;

         if (end == -1)
            end = strlen(line);

         if (l1->start > pos)
         {
            textWriter.write(&line[pos], l1->start - pos);
            pos = l1->start;
         }

         if (l1->texted()->sback.has_char())
            markupWriter << l1->texted()->sback;

         if (l1->texted()->stext.has_char())
            markupWriter << l1->texted()->stext;

         textWriter.write(&line[pos], end - l1->start);

         if (l1->texted()->etext.has_char())
            markupWriter << l1->texted()->etext;

         if (l1->texted()->eback.has_char())
            markupWriter << l1->texted()->eback;

         pos += end - l1->start;

      }

      if((u32) pos < strlen(line))
      {
         textWriter.write(&line[pos], strlen(line) - pos);
      }
   }


   /** write specified line of text using list of LineRegion's.
   This method uses integer fields of LineRegion class
   to enwrap each line region with generated HTML markup.
   Each region is
   @param markupWriter writer, used for markup output
   @param textWriter writer, used for text output
   @param line Line of text
   @param lineRegions Linked list of LineRegion structures
   */
   void ParsedLineWriter::htmlRGBWrite(stream & markupWriter, stream & textWriter, string_to_string *docLinkHash, const ::string &line, LineRegion *lineRegions)
   {

      index pos = 0;

      for(LineRegion *l1 = lineRegions; l1; l1 = l1->next)
      {

         if (l1->special || l1->rdef == nullptr)
            continue;

         if (l1->start == l1->end)
            continue;

         index end = l1->end;

         if (end == -1)
            end = i32(strlen(line));

         if (l1->start > pos)
         {
            textWriter.write(&line[pos], l1->start - pos);
            pos = l1->start;
         }

         if (docLinkHash->get_size() > 0)
            writeHref(markupWriter, docLinkHash, l1->scheme, string(&line[pos], (i32)(end - l1->start)), true);
         writeStart(markupWriter, l1->styled());
         textWriter.write(&line[pos], end - l1->start);
         writeEnd(markupWriter, l1->styled());
         if (docLinkHash->get_size() > 0)
            writeHref(markupWriter, docLinkHash, l1->scheme, string(&line[pos], (i32)(end - l1->start)), false);
         pos += end - l1->start;
      }
      if((u32) pos < strlen(line))
      {
         textWriter.write(&line[pos], strlen(line) - pos);
      }
   }

   /** Puts into stream style attributes from RegionDefine object.
   */
   void ParsedLineWriter::writeStyle(stream & writer, const StyledRegion *lr)
   {
      static char span[256];
      i32 cp = 0;
      if (lr->bfore) cp += sprintf(span, "color:#%.6x; ", lr->fore);
      if (lr->bback) cp += sprintf(span+cp, "background:#%.6x; ", lr->back);
      if (lr->style&StyledRegion::RD_BOLD) cp += sprintf(span+cp, "font-weight:bold; ");
      if (lr->style&StyledRegion::RD_ITALIC) cp += sprintf(span+cp, "font-style:italic; ");
      if (lr->style&StyledRegion::RD_UNDERLINE) cp += sprintf(span+cp, "text-decoration:underline; ");
      if (lr->style&StyledRegion::RD_STRIKEOUT) cp += sprintf(span+cp, "text-decoration:strikeout; ");
      if (cp > 0) writer << span;
   }

   /** Puts into stream starting HTML \<span> tag with requested style specification
   */
   void ParsedLineWriter::writeStart(stream & writer, const StyledRegion *lr)
   {
      if (!lr->bfore && !lr->bback) return;
      writer << "<span style='";
      writeStyle(writer, lr);
      writer << "'>";
   }

   /** Puts into stream ending HTML \</span> tag
   */
   void ParsedLineWriter::writeEnd(stream & writer, const StyledRegion *lr)
   {
      if (!lr->bfore && !lr->bback) return;
      writer << "</span>";
   }

   void ParsedLineWriter::writeHref(stream & writer, string_to_string *docLinkHash, const class scheme *scheme, const string &token, bool start)
   {
      string url;
      if (scheme != nullptr)
      {
         url = docLinkHash->operator [](token + "--" + scheme->getName());
      }
      if (url.is_empty())
      {
         url = docLinkHash->operator[](token);
      }
      if (url.has_char())
      {
         if (start) writer << "<a href='" +url + "'>";
         else writer << "</a>";
      }
   }


} // namespace colorertake5

/* ***** BEGIN LICENSE BLOCK *****
* Version: MPL 1.1/GPL 2.0/LGPL 2.1
*
* The contents of this file are subject to the Mozilla Public License Version
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
