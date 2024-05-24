//Created by camilo on 2021-03-26 00:35 BRT <3ThomasBS_
#pragma once


#include "acid/primitive/primitive/atom.h"


namespace acid
{

   class context;

} // namespace acid

namespace text
{


   class CLASS_DECL_ACID data
   {
   protected:


      bool                       m_bPendingUpdate;
      translator *               m_ptranslator;
      ::atom                       m_atom;
      string                     m_str;


      friend class translator;
      friend class text;
      friend class ::acid::context;
      friend class ::allocator::accessor;


      data(translator * ptranslator);
      ~data();


   };


} // namespace text



