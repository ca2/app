#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "span.h"
#include "acme/prototype/geometry2d/rectangle.h"


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE box :
         virtual public object
      {
      public:


         ::pointer<span>      m_pspan;

         ::f64_rectangle        m_rectangleBox;
         ::f64_rectangle        m_rectangleDevice;
         ::f64_rectangle        m_rectangleHitTest;

         ::f64_size             m_sizeBox;
         character_count              m_iPosBeg;
         character_count              m_iPosEnd;

         ::f64               m_dLeft;


         box(span* pspan);
         ~box() override;


         string get_text() const;

         // relative to box
         ::f64 get_dev_pos_left(::collection::index iPos) const;
         ::f64 get_dev_pos_right(::collection::index iPos) const;
         ::f64 get_dev_pos(::collection::index iPos) const;
         ::f64 get_pos_left(::collection::index iPos) const;
         ::f64 get_pos_right(::collection::index iPos) const;
         ::f64 get_pos(::collection::index iPos) const;
         ::f64 get_pos_count() const { return (::f64) (m_iPosEnd - m_iPosBeg + 1); }
         ::f64 get_last_pos() const { return get_pos(m_iPosEnd); }

         // box relative to span
         inline character_count get_beg() const { return m_iPosBeg - m_pspan->m_iPosBeg; }
         inline character_count get_end() const { return m_iPosEnd - m_pspan->m_iPosBeg; }

         inline bool is_line_end() const { return m_iPosEnd == m_pspan->m_iPosEnd - 1; }

      };


   } // namespace rich_text


} // namespace user



