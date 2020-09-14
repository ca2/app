#pragma once

namespace colorertake5
{

   /**
    * Maintains catalog of HRC and HRD references.
    * This class searches and loads <code>catalog.xml</code> file
    * and creates HRCParser, StyledHRDMapper, TextHRDMapper and text_parser instances
    * with information, loaded from specified sources.
    *
    * If no path were passed to it's constructor,
    * it uses the next search order to find 'catalog.xml' file:
    *
    * - win32 systems:
    *   - image_start_dir, image_start_dir/../, image_start_dir/../../
    *   - \%COLORER5CATALOG%
    *   - \%HOME%/.colorer5catalog
    *   - \%HOMEPATH%/.colorer5catalog
    *   - \%SYSTEMROOT%/.colorer5catalog (or \%WINDIR% in w9x)
    *
    * - unix/macos systems:
    *   - \$COLORER5CATALOG
    *   - \$HOME/.colorer5catalog
    *   - \$HOMEPATH/.colorer5catalog
    *   - /usr/share/colorer/catalog.xml
    *   - /usr/local/share/colorer/catalog.xml
    *
    * @note
    *   - \%NAME%, \$NAME - Environment var of the current process.
/*    *   - image_start_dir - Directory, where current image was started.
    *
    * @ingroup colorer
    */
   class CLASS_DECL_SPHERE ParserFactory :
      virtual public ::object
   {
      public:

         /**
          * ParserFactory Constructor.
          * Searches for catalog.xml in the set of predefined locations
          * @__throw( ParserFactoryException If can't find catalog at any of standard locations.
          */
         ParserFactory(::layered * pobjectContext);

         /**
          * ParserFactory Constructor with explicit catalog path.
          * @param catalogPath Path to catalog.xml spfile-> If nullptr,
          *        standard search method is used.
          * @__throw( ParserFactoryException If can't load specified catalog.
          */
         ParserFactory(::object * pobject, string catalogPath);
         virtual ~ParserFactory();

         static const char *getVersion();

         /**
          * Enumerates all declared hrd classes
          */
         //string enumerateHRDClasses(i32 idx);

         /**
          * Enumerates all declared hrd instances of specified class
          */
         //string enumerateHRDInstances(const string &classID, i32 idx);

         /**
          * Returns description of HRD instance, pointed by classID and nameID parameters.
          */
         string getHRDescription(const string &classID, const string &nameID);

         /**
          * Creates and loads HRCParser instance from catalog.xml spfile->
          * This method can detect directory entries, and sequentally load their
          * contents into created HRCParser instance.
          * In other cases it uses input_source#newInstance() method to
          * create input data stream.
          * Only one HRCParser instance is created for each ParserFactory instance.
          */
         HRCParser  *getHRCParser();

         /**
          * Creates text_parser instance
          */
         text_parser *createTextParser();

         /**
          * Creates RegionMapper instance and loads specified hrd files into it.
          * @param classID Class identifier of loaded hrd instance.
          * @param nameID  Name identifier of loaded hrd instances.
          * @__throw( ParserFactoryException If method can't find specified pair of
          *         class and name IDs in catalog.xml file
          */
         StyledHRDMapper *createStyledMapper(string classID, string nameID);
         /**
          * Creates RegionMapper instance and loads specified hrd files into it.
          * It uses 'text' class by default.
          * @param nameID  Name identifier of loaded hrd instances.
          * @__throw( ParserFactoryException If method can't find specified pair of
          *         class and name IDs in catalog.xml file
          */
         TextHRDMapper *createTextMapper(string nameID);

         /**
          * Returns currently used global error handler.
          * If no error handler were installed, returns nullptr.
          */
         ErrorHandler *getErrorHandler()
         {
            return fileErrorHandler;
         };

      private:
         void init();
         string searchPath();

         ::file::path catalogPath;
         stream * catalogFIS;
         ErrorHandler *fileErrorHandler;
         string_array hrcLocations;
         string_map < string_map < string_array >, const string_map < string_array > & > hrdLocations;
         string_to_string hrdDescriptions;
         HRCParser  *hrcParser;
         __pointer(::xml::node)catalog;

         ParserFactory(const ParserFactory&);
         void operator=(const ParserFactory&);
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
