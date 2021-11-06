#pragma once


namespace colorertake5
{


   /** Informs application about internal HRC parsing problems.
   @ingroup colorer
   */
   class HRCParserException :
      public exception
   {
   public:

      HRCParserException(const ::string & pszMessage = nullptr) :
         exception(pszMessage)
      {

      }


   };


   /** Abstract template of HRCParser class implementation.
   Defines basic operations of loading and accessing
   HRC information.
   @ingroup colorer
   */
   class CLASS_DECL_SPHERE HRCParser :
      virtual public ::object
   {
   public:
      /** Error Handler, used to inform application about different error conditions
      @param eh ErrorHandler instance, or nullptr to drop error handling.
      */
      virtual void setErrorHandler(ErrorHandler *eh) = 0;
      /** Loads HRC from specified input_source stream.
      Referred HRC file can contain prototypes and
      real types definitions. If it contains just prototype definition,
      real type load must be performed before using with #loadType() method
      @param is input_source stream of HRC file
      */
      virtual void loadSource(const ::string & pszSourceLocation, const ::string & pszSource) = 0;

      /** Enumerates sequentially all prototypes
      @param index index of type.
      @return Requested type, or nullptr, if #index is too big
      */
      virtual file_type *enumerateFileTypes(i32 index) = 0;

      /** @param name Requested type name.
      @return File type, or nullptr, there are no type with specified name.
      */
      virtual file_type *getFileType(const ::string & name) = 0;

      /** Searches and returns the best type for specified spfile->
      This method uses fileName and firstLine parameters
      to perform selection of the best HRC type from database.
      @param fileName Name of file
      @param firstLine First line of this file, could be nullptr
      @param typeNo Sequential number of type, if more than one type
      satisfy these input parameters.
      */
      virtual file_type *chooseFileType(const ::string & fileName, const ::string & firstLine, i32 typeNo = 0) = 0;

      /** Total number of declared regions
      */
      virtual ::count getRegionCount() = 0;
      /** Returns region by internal id
      */
      virtual class region *getRegion(i32 id) = 0;
      /** Returns region by name
      @note Also loads referred type, if it is not yet loaded.
      */
      virtual class region *getRegion(const ::string & name) = 0;

      /** HRC aura version.
      Usually this is the 'version' attribute of 'hrc' matter
      of the first loaded HRC spfile->
      */
      virtual string getVersion() = 0;

      virtual ~HRCParser() {};
   protected:
      HRCParser() {};
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
