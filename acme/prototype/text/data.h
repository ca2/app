//Created by camilo on 2021-03-26 00:35 BRT <3ThomasBS_
#pragma once


#include "acme/prototype/prototype/atom.h"
#include "acme/memory/memory_allocate.h"


namespace acme
{

   class context;

} // namespace acme

namespace text
{


   class CLASS_DECL_ACME data :
      public ::memory_quantum
   {
   protected:


      bool                          m_bPendingUpdate;
      translator *                  m_ptranslator;
      ::atom                        m_atom;
      string                        m_str;


      friend class translator;
      friend class text;
      friend class ::platform::context;
      friend class ::allocator::accessor;


      data(translator * ptranslator);
      ~data();



   };


} // namespace text



