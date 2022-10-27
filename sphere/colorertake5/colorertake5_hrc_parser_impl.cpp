#include "framework.h"
#include "aqua/xml.h"


namespace colorertake5
{


   HRCParserImpl::HRCParserImpl(::particle * pparticle) :
      object(pparticle),
      fileTypeHash(pparticle),
      schemeHash(pparticle),
      regionNamesHash(pparticle)
   {
      regionNamesVector.allocate(0, 203);
      fileTypeVector.allocate(0, 203);
      parseType = nullptr;
      errorHandler = nullptr;
      updateStarted = false;
   }

   HRCParserImpl::~HRCParserImpl()
   {
   }

   void HRCParserImpl::setErrorHandler(ErrorHandler *eh)
   {
      errorHandler = eh;
   }

   void HRCParserImpl::loadSource(const ::string & pszSourceLocation, const ::string & pszSource)
   {
      string strPreviousSourceLocation = m_strCurrentSourceLocation;
      string strPreviousSource = m_strCurrentSource;
      m_strCurrentSourceLocation = pszSourceLocation;
      m_strCurrentSource = pszSource;
      try
      {
         parseHRC(pszSource);
      }
      catch (const ::exception & exception)
      {

         __rethrow(pexception);

      }
      m_strCurrentSourceLocation = strPreviousSourceLocation;
      m_strCurrentSource = strPreviousSource;
   }

   void HRCParserImpl::loadFileType(file_type *filetype)
   {
      if (filetype == nullptr) return;

      file_type_impl *thisType = (file_type_impl*)filetype;

      if (thisType->typeLoaded || thisType->inputSourceLoading || thisType->loadBroken)
      {
         return;
      }
      thisType->inputSourceLoading = true;

      thisType->m_strSource = pcontext->m_papexcontext->file().as_string(thisType->m_strSourceLocation);

      try
      {
         loadSource(thisType->m_strSourceLocation, thisType->m_strSource);
      }
      catch(::file::exception &e)
      {
         if (errorHandler != nullptr)
         {
            errorHandler->fatalError("Can't open source stream: " +e.get_message());
         }
         thisType->loadBroken = true;
      }
      catch(HRCParserException &e)
      {
         if (errorHandler != nullptr)
         {
            errorHandler->fatalError(string(e.get_message())+" ["+thisType->m_strSourceLocation+"]");
         }
         thisType->loadBroken = true;
      }
      catch(exception &e)
      {
         if (errorHandler != nullptr)
         {
            errorHandler->fatalError(e.get_message()+" ["+thisType->m_strSourceLocation+"]");
         }
         thisType->loadBroken = true;
      }
      catch(...)
      {
         if (errorHandler != nullptr)
         {
            errorHandler->fatalError(string("Unknown exception while loading ")+thisType->m_strSourceLocation);
         }
         thisType->loadBroken = true;
      }
   }

   file_type *HRCParserImpl::chooseFileType(const ::string &fileName, const ::string &firstLine, i32 typeNo)
   {
      file_type_impl *best = nullptr;
      double max_prior = 0;
      const double DELTA = 1e-6;
      for(strsize idx = 0; idx < fileTypeVector.get_size(); idx++)
      {
         file_type_impl *ret = fileTypeVector.element_at(idx);
         double prior = 0.0;
         //      const char * psz = ret->m_strSourceLocation;
         try
         {
            prior = ret->getPriority(fileName, firstLine);
         }
         catch(...)
         {
            continue;
         }

         if (typeNo > 0 && (prior-max_prior < DELTA))
         {
            best = ret;
            typeNo--;
         }
         if (prior-max_prior > DELTA || best == nullptr)
         {
            best = ret;
            max_prior = prior;
         }
      }
      if (typeNo > 0) return nullptr;
      return best;
   }





   file_type *HRCParserImpl::getFileType(const ::string &name)
   {
      if (name == nullptr) return nullptr;
      return fileTypeHash[name];
   }

   file_type *HRCParserImpl::enumerateFileTypes(i32 index)
   {
      if (index < fileTypeVector.get_size()) return fileTypeVector.element_at(index);
      return nullptr;
   }

   ::count HRCParserImpl::getRegionCount()
   {
      return regionNamesVector.get_size();
   }

   class region *HRCParserImpl::getRegion(i32 atom)
   {
      if (atom < 0 || atom >= regionNamesVector.get_size())
      {
         return nullptr;
      }
      return regionNamesVector.element_at(atom);
   }

   class region* HRCParserImpl::getRegion(const ::string &name)
   {
      if (name == nullptr) return nullptr;
      return getNCRegion(name, false); // regionNamesHash.get(name);
   }

   string HRCParserImpl::getVersion()
   {
      return versionName;
   }


   // protected methods


   void HRCParserImpl::parseHRC(const ::string & psz)
   {
      xml::document doc(this);
      doc.m_pparseinfo->m_chEscapeValue = '\0';
      doc.load(psz);
      if(doc.get_root() == nullptr)
      {
         throw ::exception(HRCParserException(string("main '<hrc>' block not found")));
      }
      xml::node & types = *doc.get_root();

      if(types.get_name() != "hrc")
      {
         throw ::exception(HRCParserException(string("main '<hrc>' block not found")));
      }

      if(versionName.is_empty())
         versionName = types.attr("version");

      bool globalUpdateStarted = false;
      if (!updateStarted)
      {
         globalUpdateStarted = true;
         updateStarted = true;
      };
      for (strsize i = 0; i < types.get_children_count(); i++)
      {
         ::pointer<::xml::node>lem = types.child_at(i);
         if (elem->get_name() == "prototype")
         {
            addPrototype(elem);
            continue;
         };
         if (elem->get_name() == "package")
         {
            addPrototype(elem);
            continue;
         };
         if (elem->get_name() == "type")
         {
            addType(elem);
            continue;
         };
      };
      structureChanged = true;
      if (globalUpdateStarted)
      {
         updateLinks();
         updateStarted = false;
      };
   }


   void HRCParserImpl::addPrototype(::pointer<::xml::node>lem)
   {

      string typeName         = elem->attr("name");
      string typeGroup        = elem->attr("group");
      string typeDescription  = elem->attr("description");

      if (typeName.is_empty())
      {

         if (errorHandler != nullptr)
            errorHandler->error(string("unnamed prototype "));

         return;
      }

      if (typeDescription.is_empty())
      {
         typeDescription = typeName;
      }

      if (fileTypeHash[typeName] != nullptr)
      {

         if (errorHandler != nullptr)
         {

            errorHandler->error(string("Duplicate prototype '")+typeName+"'");

         }

         return;
      }

      file_type_impl *type = memory_new file_type_impl(this);

      type->name           = typeName;

      type->description    = typeDescription;

      type->group          = typeGroup;

      if (elem->get_name() == "package")
      {

         type->isPackage = true;
      }

      for(strsize i = 0; i < elem->get_children_count(); i++)
      {
         ::pointer<::xml::node>ontent = elem->child_at(i);
         if (content->get_name() == "location")
         {
            string locationLink = (content)->attr("link");
            if (locationLink.is_empty())
            {
               if (errorHandler != nullptr)
               {
                  errorHandler->error(string("Bad 'location' link attribute in prototype '")+typeName+"'");
               }
               continue;
            };
            type->m_strSourceLocation = m_strCurrentSourceLocation.sibling(locationLink);
            /*type->m_strSource =
            pcontext->m_papexcontext->file().as_string(
            type->m_strSourceLocation);*/

         };
         if (content->get_name() == "filename" || content->get_name() == "firstline")
         {
            if (content->get_children_count() > 0)
            {
               if (errorHandler != nullptr)
                  errorHandler->warning(string("Bad '")+content->get_name()+"' matter in prototype '"+typeName+"'");
               continue;
            }
            string match = content->get_value();
            cregexp *matchRE = memory_new cregexp(match);
            matchRE->setPositionMoves(true);
            if (!matchRE->isOk())
            {
               if (errorHandler != nullptr)
               {
                  errorHandler->warning(string("Fault compiling chooser RE '")+match+"' in prototype '"+typeName+"'");
               }
               delete matchRE;
               continue;
            };
            i32 ctype = content->get_name() == "filename" ? 0 : 1;
            double prior = content->get_name() == "filename" ? 2 : 1;
            if(content->find_attr("weight") != nullptr)
            {
               prior = atof((content)->attr("weight"));
            }
            FileTypeChooser *ftc = memory_new FileTypeChooser(ctype, prior, matchRE);
            type->chooserVector.add(ftc);
         }
         if (content->get_name() == "parameters")
         {
            for(strsize i = 0; i < content->get_children_count(); i++)
            {
               ::pointer<::xml::node>aram = content->child_at(i);
               if (param->get_name() == "param")
               {
                  string name    = (param)->attr("name");
                  string value   = (param)->attr("value");
                  string descr   = (param)->attr("description");
                  if(name.is_empty() || value.is_empty())
                  {
                     if (errorHandler != nullptr)
                     {
                        errorHandler->warning(string("Bad parameter in prototype '")+typeName+"'");
                     }
                     continue;
                  }
                  type->paramVector.add((name));
                  if(descr.has_char())
                  {
                     type->paramDescriptionHash.set_at(name, descr);
                  }
                  type->paramDefaultHash.set_at(name, value);
               }
            }
         }
      }

      type->protoLoaded = true;
      fileTypeHash.set_at(typeName, type);
      if (!type->isPackage)
      {
         fileTypeVector.add(type);
      }
   }

   void HRCParserImpl::addType(::pointer<::xml::node>lem)
   {
      string typeName = elem->attr("name");

      if (typeName.is_empty())
      {
         if (errorHandler != nullptr)
         {
            errorHandler->error(string("Unnamed type found"));
         }
         return;
      };
      file_type_impl *type_ref = fileTypeHash[typeName];
      if (type_ref == nullptr)
      {
         if (errorHandler != nullptr)
         {
            errorHandler->error(string("type '")+typeName+"' without prototype");
         }
         return;
      };
      file_type_impl *type = type_ref;
      if (type->typeLoaded)
      {
         if (errorHandler != nullptr) errorHandler->warning(string("type '")+typeName+"' is already loaded");
         return;
      };
      type->typeLoaded = true;

      file_type_impl *o_parseType = parseType;
      parseType = type;

      for(strsize i = 0; i < elem->get_children_count(); i++)
      {
         ::pointer<::xml::node>mlpar = elem->child_at(i);
         if(xmlpar->get_name() == "region")
         {

            string regionName    = (xmlpar)->attr("name");
            string regionParent  = (xmlpar)->attr("parent");
            string regionDescr   = (xmlpar)->attr("description");
            if (regionName.is_empty())
            {
               if (errorHandler != nullptr)
               {
                  errorHandler->error(string("No 'name' attribute in <region> matter"));
               }
               continue;
            };

            string qname1        = qualifyOwnName(regionName);

            if(qname1.is_empty())
               continue;

            string qname2 = qualifyForeignName(regionParent, QNT_DEFINE, true);

            if (regionNamesHash[qname1] != nullptr)
            {
               if (errorHandler != nullptr)
               {
                  errorHandler->warning(string("Duplicate region '") + qname1 + "' definition in type '"+parseType->getName()+"'");
               }
               continue;
            };

            class region *region = memory_new class region(qname1, regionDescr, getRegion(qname2), regionNamesVector.get_size());
            regionNamesVector.add(region);
            regionNamesHash.set_at(qname1, region);

         };
         if (xmlpar->get_name() == "entity")
         {
            string entityName  = (xmlpar)->attr("name");
            string entityValue = (xmlpar)->attr("value");
            if (entityName.is_empty() || entityValue.is_empty())
            {
               if (errorHandler != nullptr)
               {
                  errorHandler->error(string("Bad entity attributes"));
               }
               continue;
            };
            string qname1 = qualifyOwnName(entityName);
            string qname2 = useEntities(entityValue);
            if (qname1.has_char() && qname2.has_char())
            {
               schemeEntitiesHash.set_at(qname1, qname2);
               //delete qname1;
            };
         };
         if (xmlpar->get_name() == "import")
         {
            string typeParam = (xmlpar)->attr("type");
            if (typeParam.is_empty() || fileTypeHash[typeParam] == nullptr)
            {
               if (errorHandler != nullptr)
               {
                  errorHandler->error(string("Import with bad '")+typeParam+"' attribute in type '"+typeName+"'");
               }
               continue;
            };
            type->importVector.add((typeParam));
         };
         if (xmlpar->get_name() == "scheme")
         {
            addScheme(xmlpar);
            continue;
         };
      };
      string baseSchemeName = qualifyOwnName(type->name);
      if(baseSchemeName.has_char() && schemeHash.plookup(baseSchemeName) != nullptr)
      {
         type->baseScheme = schemeHash[baseSchemeName];
      }
      if (type->baseScheme == nullptr && !type->isPackage)
      {
         if (errorHandler != nullptr)
         {
            errorHandler->warning(string("type '")+typeName+"' has no default scheme");
         }
      }
      type->loadDone = true;
      parseType = o_parseType;
   }

   void HRCParserImpl::addScheme(::pointer<::xml::node>lem)
   {
      string schemeName = elem->attr("name");
      string qSchemeName = qualifyOwnName(schemeName);
      if (qSchemeName.is_empty())
      {
         if (errorHandler != nullptr) errorHandler->error(string("bad scheme name in type '")+parseType->getName()+"'");
         return;
      }
      if (schemeHash.plookup(qSchemeName) != nullptr ||
            disabledSchemes[qSchemeName] != 0)
      {
         if (errorHandler != nullptr) errorHandler->error(string("duplicate scheme name '")+qSchemeName+"'");
         return;
      }

      scheme_impl *scheme = memory_new scheme_impl(qSchemeName);
      scheme->fileType = parseType;

      schemeHash.set_at(scheme->schemeName, scheme);

      string condIf = elem->attr("if");
      string condUnless = elem->attr("unless");
      if ((condIf.has_char() && parseType->getParamValue(condIf) != "true") ||
            (condUnless.has_char() && parseType->getParamValue(condUnless) != "true"))
      {
         //disabledSchemes.set_at(scheme->schemeName, 1);
         return;
      }

      addSchemeNodes(scheme, elem->child_at(0));
   }

   void HRCParserImpl::addSchemeNodes(scheme_impl *scheme, ::pointer<::xml::node>lem)
   {
      ::pointer<SchemeNode>next;
      for(::pointer<::xml::node>mpel = elem; tmpel; tmpel = tmpel->get_next_sibling())
      {
         if (tmpel->get_name().is_empty()) continue;

         if (next == nullptr)
         {
            next = memory_new SchemeNode();
         }

         if (tmpel->get_name() == "inherit")
         {
            string nqSchemeName = tmpel->attr("scheme");
            if (nqSchemeName.is_empty() || nqSchemeName.get_length() == 0)
            {
               if (errorHandler != nullptr)
               {
                  errorHandler->error(string("is_empty scheme name in inheritance operator in scheme '")+scheme->schemeName+"'");
               }
               continue;
            };
            next->type = SNT_INHERIT;
            next->schemeName = (nqSchemeName);
            string schemeName = qualifyForeignName(nqSchemeName, QNT_SCHEME, false);
            if (schemeName.is_empty())
            {
               //        if (errorHandler != nullptr) errorHandler->warning(string("forward inheritance of '")+nqSchemeName+"'. possible inherit loop with '"+scheme->schemeName+"'");
               delete next.detach();
               continue;
            }
            else
            {
               string_map<scheme_impl *>::pair * ppair = schemeHash.plookup(schemeName);
               if(ppair == nullptr)
               {
                  next->scheme = nullptr;
               }
               else
               {
                  next->scheme = ppair->element2();
               }
            }
            if (schemeName.has_char())
            {
               next->schemeName = schemeName;
            };

            if (tmpel->first_child() != nullptr)
            {
               for(::pointer<::xml::node>el = tmpel->first_child(); vel; vel = vel->get_next_sibling())
               {
                  if (vel->get_name() != "virtual")
                  {
                     continue;
                  }
                  string schemeName = (vel)->attr("scheme");
                  string substName = (vel)->attr("subst-scheme");
                  if (schemeName.is_empty() || substName.is_empty())
                  {
                     if (errorHandler != nullptr)
                     {
                        errorHandler->error(string("bad virtualize attributes in scheme '")+scheme->schemeName+"'");
                     }
                     continue;
                  };
                  next->virtualEntryVector.add(memory_new VirtualEntry(schemeName, substName));
               };
            };
            scheme->nodes.add(next.detach());
            continue;
         };

         if (tmpel->get_name() == "regexp")
         {
            string matchParam = tmpel->attr("match");
            if (matchParam.is_empty() && tmpel->first_child() && tmpel->first_child()->get_type() == xml::node_text)
            {
               matchParam = tmpel->first_child()->get_value();
            }
            if (matchParam.is_empty())
            {
               if (errorHandler != nullptr)
               {
                  errorHandler->error(string("no 'match' in regexp in scheme ")+scheme->schemeName);
               }
               delete next.detach();
               continue;
            };
            string entMatchParam = useEntities(matchParam);
            next->lowPriority = tmpel->attr("priority") == "low";
            next->type = SNT_RE;
            next->start = memory_new cregexp(entMatchParam);
            next->start->setPositionMoves(false);
            if (!next->start || !next->start->isOk())
               if (errorHandler != nullptr) errorHandler->error(string("fault compiling regexp '")+entMatchParam+"' in scheme '"+scheme->schemeName+"'");
            next->end = 0;

            loadRegions(next, tmpel, true);
            if(next->region)
            {
               next->regions[0] = next->region;
            }

            scheme->nodes.add(next.detach());
            next = nullptr;
            continue;
         };


         if (tmpel->get_name() == "block")
         {

            string sParam = tmpel->attr("start");
            string eParam = tmpel->attr("end");

            ::pointer<::xml::node>eStart, eEnd;

            for(::pointer<::xml::node>lkn = tmpel->first_child(); blkn && !(eParam.has_char() && sParam.has_char()); blkn = blkn->get_next_sibling())
            {
               ::pointer<::xml::node>lkel;
               if(blkn->get_type() == xml::node_element) blkel = blkn;
               else continue;

               string p = (blkel->first_child() && blkel->first_child()->get_type() == xml::node_text)
                          ? (blkel->first_child())->get_value()
                          : blkel->attr("match").get_string();

               if(blkel->get_name() == "start")
               {
                  sParam = p;
                  eStart = blkel;
               }
               if(blkel->get_name() == "end")
               {
                  eParam = p;
                  eEnd = blkel;
               }
            }

            string startParam;
            string endParam;
            if ((startParam = useEntities(sParam)).is_empty())
            {
               if (errorHandler != nullptr)
               {
                  errorHandler->error(string("'start' block attribute not found in scheme '")+scheme->schemeName+"'");
               }
               continue;
            };
            if ((endParam = useEntities(eParam)).is_empty())
            {
               if (errorHandler != nullptr)
               {
                  errorHandler->error(string("'end' block attribute not found in scheme '")+scheme->schemeName+"'");
               }
               continue;
            };
            string schemeName = tmpel->attr("scheme");
            if (schemeName.is_empty())
            {
               if (errorHandler != nullptr)
               {
                  errorHandler->error(string("block with bad scheme attribute in scheme '")+scheme->getName()+"'");
               }
               continue;
            };
            next->schemeName = (schemeName);
            next->lowPriority = tmpel->attr("priority") == "low";
            next->lowContentPriority = tmpel->attr("content-priority") == "low";
            next->innerRegion = tmpel->attr("inner-region") == "yes";
            next->type = SNT_SCHEME;
            next->start = memory_new cregexp(startParam);
            next->start->setPositionMoves(false);
            if (!next->start->isOk())
            {
               if (errorHandler != nullptr)
               {
                  errorHandler->error(string("fault compiling regexp '")+startParam+"' in scheme '"+scheme->schemeName+"'");
               }
            }
            next->end = memory_new cregexp();
            next->end->setPositionMoves(true);
            next->end->setBackRE(next->start);
            next->end->setRE(endParam);
            if (!next->end->isOk())
            {
               if (errorHandler != nullptr)
               {
                  errorHandler->error(string("fault compiling regexp '")+endParam+"' in scheme '"+scheme->schemeName+"'");
               }
            }

            // !! EE
            loadBlockRegions(next, tmpel);
            loadRegions(next, eStart, true);
            loadRegions(next, eEnd, false);
            scheme->nodes.add(next.detach());
            continue;
         };

         if (tmpel->get_name() == "keywords")
         {
            bool isCase = tmpel->attr("ignorecase") ? false : true;
            next->lowPriority = tmpel->attr("priority") != "normal";
            class region *brgn = getNCRegion(tmpel, "region");
            if (brgn == nullptr)
            {
               continue;
            }
            string worddiv = tmpel->attr("worddiv");

            next->worddiv = nullptr;
            if(worddiv.has_char())
            {
               string entWordDiv = useEntities(worddiv);
               next->worddiv = ::str().ch_class::createCharClass(entWordDiv, 0, nullptr);
               if(next->worddiv == nullptr)
               {
                  if (errorHandler != nullptr) errorHandler->warning(string("fault compiling worddiv regexp '")+entWordDiv+"' in scheme '"+scheme->schemeName+"'");
               }
               //delete entWordDiv;
            };

            next->kwList = memory_new KeywordList;
            for(::pointer<::xml::node>eywrd_count = tmpel->first_child(); keywrd_count; keywrd_count = keywrd_count->get_next_sibling())
            {
               if (keywrd_count->get_name() == "u16" ||
                     keywrd_count->get_name() == "symb")
               {
                  next->kwList->num++;
               }
            }

            next->kwList->kwList = memory_new KeywordInfo[next->kwList->num];
            next->kwList->num = 0;
            KeywordInfo *pIDs = next->kwList->kwList;
            next->kwList->matchCase = isCase;
            next->kwList->kwList = pIDs;
            next->type = SNT_KEYWORDS;

            for(::pointer<::xml::node>eywrd = tmpel->first_child(); keywrd; keywrd = keywrd->get_next_sibling())
            {
               strsize type = 0;
               if (keywrd->get_name() == "u16") type = 1;
               if (keywrd->get_name() == "symb") type = 2;
               if (!type)
               {
                  continue;
               }
               string param;
               if ((param = (keywrd)->attr("name")).is_empty())
               {
                  continue;
               }

               class region *rgn = brgn;
               if ((keywrd)->attr("region"))
                  rgn = getNCRegion(keywrd, string("region"));

               strsize pos = next->kwList->num;
               pIDs[pos].keyword = (param);
               pIDs[pos].region = rgn;
               pIDs[pos].isSymbol = (type == 2);
               pIDs[pos].ssShorter = -1;
               next->kwList->firstChar->add_char(::str().get_utf8_char(param));
               if (!isCase)
               {
                  next->kwList->firstChar->add_char(::str::ch().to_lower_case(param));
                  next->kwList->firstChar->add_char(::str::ch().to_upper_case(param));
                  next->kwList->firstChar->add_char(::str::ch().to_title_case(param));
               };
               next->kwList->num++;
               if (next->kwList->minKeywordLength > pIDs[pos].keyword.get_length())
                  next->kwList->minKeywordLength = pIDs[pos].keyword.get_length();
            };
            next->kwList->sortList();
            next->kwList->substrIndex();
            scheme->nodes.add(next.detach());
            continue;
         };
      };
      // drop last unused node
      if (next != nullptr)
         delete next.detach();
   };


   void HRCParserImpl::loadRegions(SchemeNode *node, ::pointer<::xml::node>l, bool st)
   {
      static char rg_tmpl[0x10] = "region\0\0";

      if(el)
      {
         if (node->region == nullptr)
         {
            node->region = getNCRegion(el, string("region"));
         }

         for(strsize i = 0; i < REGIONS_NUM; i++)
         {
            rg_tmpl[6] = (char) ((i < 0xA ? i : i+7+32) + '0');

            if(st)
            {
               node->regions[i] = getNCRegion(el, string(rg_tmpl));
            }
            else
            {
               node->regione[i] = getNCRegion(el, string(rg_tmpl));
            }
         }
      }
      /*
      for (strsize i = 0; i < NAMED_REGIONS_NUM; i++)
      {
      if(st) node->regionsn[i] = getNCRegion(node->start->getBracketName(i), false);
      else   node->regionen[i] = getNCRegion(node->end->getBracketName(i), false);
      }*/
   }


   void HRCParserImpl::loadBlockRegions(SchemeNode *node, ::pointer<::xml::node>l)
   {
      strsize i;
      static char rg_tmpl[0x10] = "region";

      node->region = getNCRegion(el, string("region"));
      for (i = 0; i < REGIONS_NUM; i++)
      {
         rg_tmpl[6] = '0';
         rg_tmpl[7] = (char) ((i<0xA?i:i+7)+'0');
         rg_tmpl[8] = 0;
         node->regions[i] = getNCRegion(el, string(rg_tmpl));
         rg_tmpl[6] = '1';
         node->regione[i] = getNCRegion(el, string(rg_tmpl));
      }
   }


   void HRCParserImpl::updateLinks()
   {
      while(structureChanged)
      {
         structureChanged = false;
         for(string_map<scheme_impl *>::pair * scheme = schemeHash.get_start(); scheme != nullptr; scheme = schemeHash.get_next(scheme))
         {

            if (!scheme->element2()->fileType->loadDone) continue;
            file_type_impl *old_parseType = parseType;
            parseType = scheme->element2()->fileType;
            for (strsize sni = 0; sni < scheme->element2()->nodes.get_size(); sni++)
            {
               SchemeNode *snode = scheme->element2()->nodes.element_at(sni);
               if (snode->schemeName.has_char() && (snode->type == SNT_SCHEME || snode->type == SNT_INHERIT) && snode->scheme == nullptr)
               {
                  string schemeName = qualifyForeignName(snode->schemeName, QNT_SCHEME, true);
                  if (schemeName.has_char())
                  {
                     string_map<scheme_impl *>::pair * ppair = schemeHash.plookup(schemeName);
                     if(ppair == nullptr)
                     {
                        snode->scheme = nullptr;
                     }
                     else
                     {
                        snode->scheme = ppair->element2();
                     }
                  }
                  else
                  {
                     if (errorHandler != nullptr)
                     {
                        errorHandler->error(string("cannot resolve scheme name '")+snode->schemeName+"' in scheme '"+scheme->element2()->schemeName+"'");
                     }
                  }
                  //               delete schemeName;
                  //             delete snode->schemeName;
                  snode->schemeName.Empty();
               };
               if (snode->type == SNT_INHERIT)
               {
                  for(strsize vti = 0; vti < snode->virtualEntryVector.get_size(); vti++)
                  {
                     VirtualEntry *vt = snode->virtualEntryVector.element_at(vti);
                     if (vt->virtScheme == nullptr && vt->virtSchemeName.has_char())
                     {
                        string vsn = qualifyForeignName(vt->virtSchemeName, QNT_SCHEME, true);
                        if (vsn.has_char())
                        {
                           string_map<scheme_impl *>::pair * ppair = schemeHash.plookup(vsn);
                           if(ppair == nullptr)
                           {
                              vt->virtScheme = nullptr;
                           }
                           else
                           {
                              vt->virtScheme = ppair->element2();
                           }
                        }

                        if (vsn.is_empty())
                        {
                           if (errorHandler != nullptr)
                           {
                              errorHandler->error(string("cannot virtualize scheme '")+vt->virtSchemeName+"' in scheme '"+scheme->element2()->schemeName+"'");
                           }
                        }
                        vt->virtSchemeName.Empty();
                     };
                     if (vt->substScheme == nullptr && vt->substSchemeName.has_char())
                     {
                        string vsn = qualifyForeignName(vt->substSchemeName, QNT_SCHEME, true);
                        if (vsn.has_char())
                        {
                           string_map<scheme_impl *>::pair * ppair = schemeHash.plookup(vsn);
                           if(ppair == nullptr)
                           {
                              vt->substScheme = nullptr;
                           }
                           else
                           {
                              vt->substScheme = ppair->element2();
                           }
                        }
                        else if (errorHandler != nullptr) errorHandler->error(string("cannot virtualize using subst-scheme scheme '")+vt->substSchemeName+"' in scheme '"+scheme->element2()->schemeName+"'");
                        vt->substSchemeName.Empty();
                     };
                  };
               };
            };
            parseType = old_parseType;
            if (structureChanged) break;
         };
      };
   };



   string HRCParserImpl::qualifyOwnName(const ::string & name)
   {
      if (name == nullptr) return "";
      strsize colon = string(name).find(':');
      if (colon != -1)
      {
         if (parseType && string(name, colon) != parseType->name)
         {
            if (errorHandler != nullptr) errorHandler->error(string("type name qualifer in '")+name+"' doesn't match type '"+parseType->name+"'");
            return "";
         }
         else return (name);
      }
      else
      {
         if (parseType == nullptr) return "";
         string sbuf = (parseType->name);
         sbuf += ":" + string(name);
         return sbuf;
      }

   }


   bool HRCParserImpl::checkNameExist(const ::string & name, file_type_impl *parseType, QualifyNameType qntype, bool logErrors)
   {
      if (qntype == QNT_DEFINE && regionNamesHash[name] == nullptr)
      {
         if (logErrors)
         {
            if (errorHandler != nullptr)
            {
               errorHandler->error(string("region '")+name+"', referenced in type '"+parseType->name+"', is not defined");
            }
         }
         return false;

      }
      else if (qntype == QNT_ENTITY && schemeEntitiesHash[name].is_empty())
      {
         if (logErrors)
         {
            if (errorHandler != nullptr)
            {
               errorHandler->error(string("entity '")+name+"', referenced in type '"+parseType->name+"', is not defined");
            }
         }
         return false;
      }
      else if (qntype == QNT_SCHEME && schemeHash.plookup(name) == nullptr)
      {
         if (logErrors)
         {
            if (errorHandler != nullptr)
            {
               errorHandler->error(string("scheme '")+name+"', referenced in type '"+parseType->name+"', is not defined");
            }
         }
         return false;
      }

      return true;

   }


   string HRCParserImpl::qualifyForeignName(const ::string & name, QualifyNameType qntype, bool logErrors)
   {
      if (name == nullptr) return "";
      strsize colon = string(name).find(':');
      if (colon != -1)  // qualified name
      {
         string prefix(name, colon);
         file_type_impl *prefType = fileTypeHash[prefix];

         if (prefType == nullptr)
         {
            if (logErrors && errorHandler != nullptr) errorHandler->error(string("type name qualifer in '")+name+"' doesn't match any type");
            return "";
         }
         else if (!prefType->typeLoaded) loadFileType(prefType);
         if (prefType == parseType || prefType->typeLoaded)
            return checkNameExist(name, prefType, qntype, logErrors)?((name)): nullptr;
      }
      else   // unqualified name
      {
         for(strsize idx = -1; parseType != nullptr && idx < parseType->importVector.get_size(); idx++)
         {
            string tname = parseType->name;
            if (idx > -1) tname = parseType->importVector.element_at(idx);
            file_type_impl *importer = fileTypeHash[tname];
            if (!importer->typeLoaded) loadFileType(importer);

            string qname = (tname);
            qname += ":" + string(name);
            if (checkNameExist(qname, importer, qntype, false)) return qname;
         };
         if (logErrors && errorHandler != nullptr)
         {
            errorHandler->error(string("unqualified name '")+name+"' doesn't belong to any imported type ["+m_strCurrentSourceLocation+"]");
         }
      };
      return "";
   };


   string HRCParserImpl::useEntities(const ::string & name)
   {
      strsize copypos = 0;
      strsize epos = 0;

      if (!name) return "";
      string newname;

      while(true)
      {
         epos = string(name).find('%', epos);
         if (epos == -1)
         {
            epos = string(name).get_length();
            break;
         };
         if (epos && name[epos-1] == '\\')
         {
            epos++;
            continue;
         };
         strsize elpos = string(name).find(';', epos);
         if (elpos == -1)
         {
            epos = string(name).get_length();
            break;
         };
         string enname(&name[epos+1], elpos-epos-1);

         string qEnName = qualifyForeignName(enname, QNT_ENTITY, true);
         string enval;
         if (qEnName.has_char())
         {
            enval = schemeEntitiesHash[qEnName];
            //delete qEnName;
         };
         if (enval.is_empty())
         {
            epos++;
            continue;
         };
         newname += string(&name[copypos], epos-copypos);
         newname += enval;
         epos = elpos+1;
         copypos = epos;
      };
      if (epos > copypos) newname += string(&name[copypos], epos-copypos);
      return newname;
   };

   class region* HRCParserImpl::getNCRegion(const ::string & name, bool logErrors)
   {
      if (name == nullptr) return nullptr;
      class region *reg = nullptr;
      string qname = qualifyForeignName(name, QNT_DEFINE, logErrors);
      if (qname.is_empty()) return nullptr;
      reg = regionNamesHash[qname];
      /** Check for 'default' region request.
      Regions with this name are always transparent
      */
      if (reg != nullptr)
      {
         string name = reg->getName();
         strsize idx = string(name).find(":default");
         if (idx != -1  && idx+8 == string(name).get_length()) return nullptr;
      };
      return reg;
   };

   class region* HRCParserImpl::getNCRegion(::pointer<::xml::node>l, const ::string & tag)
   {
      string par = el->attr(tag);
      if (par.is_empty()) return nullptr;
      return getNCRegion(par, true);
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
*  Eugene Efremov <4mirror@mail.ru>
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
