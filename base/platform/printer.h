#pragma once


namespace aura
{


   class CLASS_DECL_AURA printer :
      virtual public ::object
   {
   public:

      

      printer();
      virtual ~printer();

      virtual bool open(const char * pszDeviceName);
      virtual ::draw2d::graphics_pointer create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };


} // namespace aura























