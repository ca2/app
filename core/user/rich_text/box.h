#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE box :
         virtual public object
      {
      public:


         __pointer(span)   m_pspan;

         rectangle_f64             m_rectangleBox;
         rectangle_f64             m_rectangleDevice;
         rectangle_f64             m_rectangleHitTest;

         size_f64             m_sizeBox;
         strsize           m_iPosBeg;
         strsize           m_iPosEnd;

         double            m_dLeft;


         box(span* pspan);
         virtual ~box();


         string get_text() const;

         // relative to box
         double get_dev_pos_left(index iPos) const;
         double get_dev_pos_right(index iPos) const;
         double get_dev_pos(index iPos) const;
         double get_pos_left(index iPos) const;
         double get_pos_right(index iPos) const;
         double get_pos(index iPos) const;
         double get_pos_count() const { return (double) (m_iPosEnd - m_iPosBeg + 1); }
         double get_last_pos() const { return get_pos(m_iPosEnd); }

         // box relative to span
         inline strsize get_beg() const { return m_iPosBeg - m_pspan->m_iPosBeg; }
         inline strsize get_end() const { return m_iPosEnd - m_pspan->m_iPosBeg; }

         inline bool is_line_end() const { return m_iPosEnd == m_pspan->m_iPosEnd - 1; }

      };


   } // namespace rich_text


} // namespace user



