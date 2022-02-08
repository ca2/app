#pragma once

namespace colorertake5
{

   /**
    * File Type storage implementation.
    * Contains different attributes of HRC file type.
    * @ingroup colorer_parsers
    */
   class file_type_impl : public file_type
   {
      friend class HRCParserImpl;
      friend class text_parser_impl;
   public:
      const string getName()
      {
         return name;
      }
      const string getGroup()
      {
         return group;
      }
      const string getDescription()
      {
         return description;
      }
      scheme * getBaseScheme()
      {
         if (!typeLoaded) hrcParser->loadFileType(this);
         return baseScheme;
      }


      string enumerateParameters(i32 idx)
      {

         if (idx >= paramVector.get_size() || idx < 0)
         {

            throw ::exception(::exception("integer_exception 127"));

         }

         return paramVector.element_at(idx);

      }


      string getParameterDescription(const ::string &name)
      {
         return paramDescriptionHash[name];
      }

      string getParamValue(const ::string & name)
      {
         string val = paramHash[name];
         if(val.is_empty())
            return getParamDefaultValue(name);
         return val;
      }
      string getParamDefaultValue(const ::string & name)
      {
         return paramDefaultHash[name];
      }

      void setParamValue(const ::string & name, const ::string & value)
      {
         paramHash.set_at(name, value);
      }

      /**
       * Returns total priority, accordingly to all it's
       * choosers (filename and firstline choosers).
       * All <code>fileContent</code> RE's are tested only if priority of previously
       * computed <code>fileName</code> RE's is more, than zero.
       * @param fileName string representation of file name (without path).
       *        If nullptr, method skips filename matching, and starts directly
       *        with fileContent matching.
       * @param fileContent Some part of file's starting content (first line,
       *        for example). If nullptr, skipped.
       * @return Computed total filetype priority.
       */
      double getPriority(const ::string & fileName, const ::string & fileContent) const
      {
         SMatches match;
         double cur_prior = 0;
         for(i32 idx = 0; idx < chooserVector.get_size(); idx++)
         {
            FileTypeChooser *ftc = chooserVector.element_at(idx);
            if (fileName != nullptr && ftc->isFileName() && ftc->getRE()->parse(fileName, &match))
               cur_prior += ftc->getPrior();
            if (fileContent != nullptr && ftc->isFileContent() && ftc->getRE()->parse(fileContent, &match))
               cur_prior += ftc->getPrior();
         }
         return cur_prior;
      }
   protected:
      /// is prototype component loaded
      bool protoLoaded;
      /// is type component loaded
      bool typeLoaded;
      /// is type references fully resolved
      bool loadDone;
      /// is initial type load failed
      bool loadBroken;
      /// is this IS loading was started
      bool inputSourceLoading;

      string name, group, description;
      bool isPackage;
      HRCParserImpl *hrcParser;
      scheme_impl *baseScheme;

      address_array < FileTypeChooser * > chooserVector;
      string_to_string paramDefaultHash;
      string_to_string paramHash;
      string_to_string paramDescriptionHash;
      string_array paramVector;
      string_array importVector;
      string    m_strSourceLocation;
      string    m_strSource;

   public:
      file_type_impl(HRCParserImpl *hrcParser)
      {
         this->hrcParser = hrcParser;
         protoLoaded = typeLoaded = loadDone = loadBroken = inputSourceLoading = false;
         isPackage = false;
         baseScheme = nullptr;
      }

      ~file_type_impl()
      {
      }

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
