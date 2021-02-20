#include "framework.h" // previously aura/user/user.h


namespace colorertake5
{

   const i32 StyledRegion::RD_BOLD = 1;
   const i32 StyledRegion::RD_ITALIC = 2;
   const i32 StyledRegion::RD_UNDERLINE = 4;
   const i32 StyledRegion::RD_STRIKEOUT = 8;

   StyledHRDMapper::StyledHRDMapper(::layered * pobjectContext) :
      object(pobject),
      RegionMapperImpl(pobject)
   {
   }


   StyledHRDMapper::~StyledHRDMapper()
   {
//  for(RegionDefine *rd = regionDefines.enumerate(); rd;rd = regionDefines.next())
//  delete rd;
   };

   void StyledHRDMapper::loadRegionMappings(stream & istream)
   {
//  DocumentBuilder docbuilder;

      //Document *hrdbase = docbuilder.parse(is);

      string str;

      istream >> str;

      xml::document hbasedoc(get_context_application());

      if(!hbasedoc.load(str))
      {
         __throw(exception("Error loading HRD file"));
      }

      xml::node & hbase = *hbasedoc.get_root();

      if(hbase.get_name() != "hrd")
      {
         __throw(exception("Error loading HRD file"));
      }

      for(__pointer(::xml::node)curel = hbase.first_child(); curel; curel = curel->get_next_sibling())
      {
         if (curel->get_type() == xml::node_element && curel->get_name() == "assign")
         {
            string name = (curel)->attr("name");
            if(name.is_empty())
               continue;


            bool bfore = ansi_char_is_digit(curel->attr("fore").first()) != false;
            i32 fore = atoi((curel)->attr("fore"));
            bool bback = ansi_char_is_digit((curel)->attr("back").last()) != false;
            i32 back = atoi((curel)->attr("back"));
            i32 style = atoi((curel)->attr("style"));
            RegionDefine *rdef = new StyledRegion(bfore, bback, fore, back, style);
            regionDefines.set_at(name, rdef);
         }
      }
   }

   /** Writes all currently loaded region definitions into
       XML spfile-> Note, that this method writes all loaded
       defines from all loaded HRD files.
   */
   void StyledHRDMapper::saveRegionMappings(stream & writer) const
   {
      UNREFERENCED_PARAMETER(writer);


      /*  writer->write(string("<?xml version=\"1.0\"?>\n\
      <!DOCTYPE hrd SYSTEM \"../hrd.dtd\">\n\n\
      <hrd>\n"));
       */
      /*  for(string *key = regionDefines.enumerateKey(); key; key=regionDefines.nextkey()){
          const StyledRegion *rdef = StyledRegion::cast(regionDefines.get(key));
          char temporary[256];
          writer->write(string("  <define name='")+key+"'");
          if (rdef->bfore){
            sprintf(temporary, " fore=\"#%06x\"", rdef->fore);
            writer->write(string(temporary));
          };
          if (rdef->bback){
            sprintf(temporary, " back=\"#%06x\"", rdef->back);
            writer->write(string(temporary));
          };
          if (rdef->style){
            sprintf(temporary, " style=\"#%06x\"", rdef->style);
            writer->write(string(temporary));
          };
          writer->write(string("/>\n"));
        };
        writer->write(string("\n</hrd>\n"));*/
   };

   /** Adds or replaces region definition */
   void StyledHRDMapper::setRegionDefine(const char * name, RegionDefine *rd)
   {
      RegionDefine *rd_old = regionDefines[name];
      delete rd_old;

      const StyledRegion *new_region = StyledRegion::cast(rd);
      RegionDefine *rd_new = new StyledRegion(*new_region);
      regionDefines.set_at(name, rd_new);

      // Searches and replaces old region references
      for(i32 idx = 0; idx < regionDefinesVector.get_size(); idx++)
      {
         if (regionDefinesVector.element_at(idx) == rd_old)
         {
            regionDefinesVector.set_at(idx, rd_new);
            break;
         };
      };
   };

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
