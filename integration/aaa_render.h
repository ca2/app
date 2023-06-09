#pragma once


//
//
//#define __PROPERTIES2(xxx)\
//class xxx ## _properties: \
//   public property_set \
//{ \
//public: \
//
//
//#define __PROPERTY2(type, name, ID) type & name = payload_reference(topic(ID))
//
//
//
//#define __END_PROPERTIES2(xxx) }; \
//xxx ## _properties & properties() {return *m_pobjectproperties;} \
//inline void create_object_properties() { m_pobjectproperties = m_ppropertyset = __new(xxx ## _properties(this));} \
//__pointer(xxx ## _properties) m_pobjectproperties
//
//
//
//


#include "acme/primitive/collection/string_map.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include "apex/platform/app_consumer.h"


namespace app_integration
{


   class CLASS_DECL_APP_INTEGRATION render :
      virtual public app_consumer < application >
   {
   public:


      rectangle_i32                       m_rectangle;
      ::user::impact *                    m_pimpact;
      string                              m_strFont1;
      string                              m_strHoverFont;
      int                                 m_iDrawing;
      string_map < ::image_pointer >      m_pimagemap;
      ::image_pointer                     m_pimage1;
      ::image_pointer                     m_pimage2;
      ::color::hls                        m_hlsText;

      render();
      virtual ~render();

#ifdef _DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif

      string get_font();

      ::e_status set_font(const string& strFont);

      ::e_status set_hover_font(const string& strHoverFont);

      virtual void initialize_simple_drawing(int iDrawing);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDraw1Through3(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDrawArcs(::draw2d::graphics_pointer & pgraphics, bool bPath);

      virtual void _001OnDrawBoxGradient(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDrawCirclePath(::draw2d::graphics_pointer & pgraphics);

      virtual void draw_arc(::draw2d::graphics_pointer & pgraphics, rectangle_i32 & r, angle angleStart, angle angleAngle, bool bPath);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);


   virtual void draw_text(::draw2d::graphics_pointer & pgraphics);

      

   };


} // namespace simple_drawing


