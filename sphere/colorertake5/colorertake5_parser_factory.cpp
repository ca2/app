#include "framework.h" // previously aura/user/user.h


namespace colorertake5
{

#ifndef __TIMESTAMP__
#define __TIMESTAMP__ "28 May 2006"
#endif


   void ParserFactory::init()
   {
#ifdef _UWP
      // metrowin todo
      return;
#endif
      hrcParser = nullptr;
      fileErrorHandler = nullptr;
      xml::document document(this);
      try
      {
         document.load_location(catalogPath);
      }
      //catch(exception * pe)
      //{
      //   ::exception_pointer esp(pe);
      //   throw ::exception(ParserFactoryException(pe->get_message()));
      //}
      catch(const ::exception & e)
      {

         throw ::exception(ParserFactoryException(e->get_message()));

      }

      ::pointer<::xml::node>catalog = document.get_root();
      if(catalog == nullptr || catalog->get_name() != "catalog")
      {
         throw ::exception(ParserFactoryException(string("bad catalog structure")));
      }

      ::pointer<::xml::node>elem = catalog->first_child();
      while(elem != nullptr)
      {
         // hrc locations
         if (elem->get_type() == xml::node_element && elem->get_name() == "hrc-sets")
         {
            string logLocation = (elem)->attr("log-location");

            if (logLocation.has_char())
            {
               string str = pcontext->m_papexcontext->file()->as_string(logLocation);
               colorer_logger_set_target(str);
            }
            if (fileErrorHandler == nullptr)
            {
               fileErrorHandler = memory_new DefaultErrorHandler();
            }
            ::pointer<::xml::node>oc = elem->first_child();
            while(loc != nullptr)
            {
               if(loc->get_type() == xml::node_element && loc->get_name() == "location")
               {
                  hrcLocations.add((const ::string &) (loc)->attr("link"));
               }
               loc = loc->get_next_sibling();
            }
         }
         // hrd locations
         else if (elem->get_type() == xml::node_element && elem->get_name() == "hrd-sets")
         {
            ::pointer<::xml::node>rd = elem->first_child();
            while(hrd != nullptr)
            {
               if(hrd->get_type() == xml::node_element && hrd->get_name() == "hrd")
               {
                  string hrd_class = (hrd)->attr("class");
                  string hrd_name = (hrd)->attr("name");
                  if(hrd_class.is_empty() || hrd_name.is_empty())
                  {
                     hrd = hrd->get_next_sibling();
                     continue;
                  }
                  string hrd_descr = (hrd)->attr("description");
                  if(hrd_descr.is_empty())
                  {
                     hrd_descr = hrd_name;
                  }
                  hrdDescriptions.set_at(hrd_class + "-" + hrd_name, hrd_descr);
                  string_map<string_array> & hrdClass = hrdLocations[hrd_class];
                  string_array & hrdLocV =  hrdClass[hrd_name];
                  ::pointer<::xml::node>oc = hrd->first_child();
                  while(loc != nullptr)
                  {
                     if(loc->get_type() == xml::node_element && loc->get_name() == "location")
                     {
                        hrdLocV.add((const ::string &) loc->attr("link"));
                     }
                     loc = loc->get_next_sibling();
                  }
               }
               hrd = hrd->get_next_sibling();
            }
         }
         elem = elem->get_next_sibling();
      }
   }

   string ParserFactory::searchPath()
   {

      return pcontext->m_papexcontext->dir()->matter("colorer.zip:catalog.xml");

   }

   ParserFactory::ParserFactory(::particle * pparticle) :
      object(pparticle)
   {

      fileErrorHandler = nullptr;

      compress_zip_is_dir zipisdir(true);

      catalogPath = searchPath();

      init();

   }

   ParserFactory::ParserFactory(::particle * pparticle, string catalogPath) :
      object(pparticle)
   {

      fileErrorHandler = nullptr;

      if(catalogPath.is_empty())
         this->catalogPath = searchPath();
      else
         this->catalogPath = (catalogPath);

      init();

   }

   ParserFactory::~ParserFactory()
   {
   }

   const char *ParserFactory::getVersion()
   {

      return "Colorer-take5 Library be5 " __TIMESTAMP__;

   }



   //string ParserFactory::enumerateHRDClasses(i32 idx){
   //return hrdLocations.key(idx);
   //};
   //string ParserFactory::enumerateHRDInstances(const string &classID, i32 idx){
   //string_map<pointer_object<string_array>> *hash = hrdLocations.pget(classID);
   //if (hash == nullptr) return "";
   //return hash->key(idx);
   //};
   string ParserFactory::getHRDescription(const string &classID, const string &nameID)
   {
      return hrdDescriptions[classID+"-"+nameID];
   };

   HRCParser* ParserFactory::getHRCParser()
   {
      if(hrcParser != nullptr)
         return hrcParser;
      hrcParser = memory_new HRCParserImpl(this);
      hrcParser->setErrorHandler(fileErrorHandler);
      for(i32 idx = 0; idx < hrcLocations.get_size(); idx++)
      {
         string relPath = hrcLocations.element_at(idx);
         string path;
         if(file_path_is_relative(relPath))
         {
            path = catalogPath.sibling(relPath);
            string path2del = path;
            path.begins_eat("file://");
            path.begins_eat("file:/");
            path.begins_eat("file:");
         }
         else
         {
            path = relPath;
         }
         if(pcontext->m_papexcontext->dir()->is(path))
         {
            //if(path == "v:\\ca2os\\basis\\app\\appmatter\\main\\_std\\_std\\colorer\\hrc\\auto")
            {
               // debug_break();
            }
            ::file::listing patha(get_app());
            patha.rls(path);
            file_pointer spfile(e_create);
            for(i32 i = 0; i < patha.get_count(); i++)
            {
               if(!pcontext->m_papexcontext->dir()->is(patha[i]))
               {
                  string str = pcontext->m_papexcontext->file()->as_string(patha[i]);
                  try
                  {
                     hrcParser->loadSource(patha[i], str);
                  }
                  catch(::exception  *pe)
                  {
                     ::exception_pointer esp(pe);
                     string str = pe->get_message();

                     FORMATTED_TRACE("exception %s", str.c_str());
                  }
               }
            }
         }
         else
         {
            string strSource = pcontext->m_papexcontext->file()->as_string(path);
            if(strSource.has_char())
            {
               try
               {
                  hrcParser->loadSource(path, strSource);
               }
               catch(const ::exception & e)
               {

                  string str = e->get_message();

                  FORMATTED_TRACE("exception %s", str.c_str());

               }
            }
         }
      }
      return hrcParser;
   }

   
   text_parser *ParserFactory::createTextParser()
   {

      return memory_new text_parser_impl();

   }


   StyledHRDMapper *ParserFactory::createStyledMapper(string classID, string nameID)
   {

      string_map<string_array> * hrdClass = nullptr;

      if (classID.is_empty())
      {

         hrdClass = hrdLocations.pget(("rgb"));

      }
      else
      {

         hrdClass = hrdLocations.pget(classID);

      }

      if (hrdClass == nullptr)
         throw ::exception(ParserFactoryException(string("can't find hrdClass '")+classID+"'"));

      string_array *hrdLocV = nullptr;
      if (nameID.is_empty())
      {
         char * hrd = nullptr;
#ifndef _UWP
         hrd = getenv("COLORER5HRD");
#endif
         hrdLocV = (hrd) ? hrdClass->pget((hrd)) : hrdClass->pget(("default"));
         if(hrdLocV == nullptr)
         {
            hrdLocV = hrdClass->pget(("default"));
         }
      }
      else
         hrdLocV = hrdClass->pget(nameID);
      if (hrdLocV == nullptr)
         throw ::exception(ParserFactoryException(string("can't find hrdName '")+nameID+"'"));

      StyledHRDMapper *mapper = memory_new StyledHRDMapper(this);

      ::file::path strDir = this->catalogPath.folder();

      for(i32 idx = 0; idx < hrdLocV->get_size(); idx++)
      {
         if (hrdLocV->element_at(idx).has_char())
         {

            try
            {

               string strPath;

               strPath = strDir / hrdLocV->element_at(idx);

               stream spfile(pcontext->m_papexcontext->file()->get_file(strPath, ::file::e_open_read | ::file::e_open_binary), FIRST_VERSION);

               if(spfile.is_reader_set())
               {

                  mapper->loadRegionMappings(spfile);

               }

            }
            catch(::exception & )
            {

            }

         }

      }

      return mapper;

   }

   TextHRDMapper *ParserFactory::createTextMapper(string nameID)
   {
      // fixed class 'text'
      string_map<string_array> *hrdClass = hrdLocations.pget(("text"));
      if (hrdClass == nullptr) throw ::exception(ParserFactoryException(string("can't find hrdClass 'text'")));

      string_array *hrdLocV = nullptr;
      if (nameID.is_empty())
         hrdLocV = hrdClass->pget(("default"));
      else
         hrdLocV = hrdClass->pget(nameID);
      if (hrdLocV == nullptr)
         throw ::exception(ParserFactoryException(string("can't find hrdName '")+nameID+"'"));

      TextHRDMapper *mapper = memory_new TextHRDMapper(this);
      for(i32 idx = 0; idx < hrdLocV->get_size(); idx++)
      {
         if (hrdLocV->element_at(idx).has_char())
         {
            try
            {
               stream stream(pcontext->m_papexcontext->file()->get_file(hrdLocV->element_at(idx), ::file::e_open_read |::file::e_open_binary), FIRST_VERSION);
               if(stream.is_reader_set())
               {
                  mapper->loadRegionMappings(stream);
               }
            }
            catch(::exception &)
            {
            }
         }
      }
      return mapper;
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
* decision by deleting the provisions above and replace them with the notice
* and other provisions required by the GPL or the LGPL. If you do not delete
* the provisions above, a recipient may use your version of this file under
* the terms of any one of the MPL, the GPL or the LGPL.
*
* ***** END LICENSE BLOCK ***** */
