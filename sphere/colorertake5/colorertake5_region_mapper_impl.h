#pragma once

namespace colorertake5
{
   /** Abstract RegionMapper.
       Stores all region mappings in hashtable and sequental vector.
       @ingroup colorer_handlers
   */
   class RegionMapperImpl : public RegionMapper,
      virtual public ::object
   {
   public:
      RegionMapperImpl(::layered * pobjectContext) : object(pobject) {};
      ~RegionMapperImpl() {};

      /** Loads region defines from @ca is input_source
      */
      virtual void  loadRegionMappings(stream & reader) = 0;
      /** Saves all loaded region defines into @ca writer.
          Note, that result document would not be equal
          to input one, because there could be multiple input
          documents.
      */
      virtual void  saveRegionMappings(stream & writer) const = 0;
      /** Changes specified region definition to @ca rdnew
          @param region region full qualified name.
          @param rdnew  New region definition to replace old one
      */
      virtual void  setRegionDefine(const char * region, RegionDefine *rdnew) = 0;


      RegionDefine *getRegionDefine(class region *region);
      RegionDefine *getRegionDefine(const char * name);

      string_map< RegionDefine *> regionDefines;
      address_array < RegionDefine * > regionDefinesVector;

      RegionMapperImpl(const RegionMapperImpl&);
      void operator=(const RegionMapperImpl&);
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

