#pragma once


#include "acme/primitive/primitive/object.h"


namespace xml
{


   class input_tree;


   class CLASS_DECL_AQUA importable :
      virtual public ::object
   {
   public:


      importable();


      virtual void xml_import(input_tree & xmlif) = 0;


   };


} // namespace xml





