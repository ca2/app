#pragma once


namespace database
{


   class CLASS_DECL_AQUA selection_item
   {
   public:


      key     m_datakey;


      selection_item();
      selection_item(key & key);
      virtual ~selection_item();


   };


} // namespace database




