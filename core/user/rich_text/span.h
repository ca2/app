#pragma once


//#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/primitive/geometry2d/size.h"


namespace user
{


   namespace rich_text
   {


      class data;


      class CLASS_DECL_CORE span :
         virtual public ::particle
      {
      public:


         class data *            m_pdata;
         ::pointer<class format>        m_pformat;


         ::e_align           m_ealignNewLine;
         string            m_str;

         // Common thing among indexes:
         // A single character is accounted for the same as the UTF8-::u8-count.
         //
         // Sel* -> Selection
         // (selection index:
         //     memory_new line = 1 sel index (only one sel index increment even for "\r\n")
         //     memory_new line due wrap = 0 sel index (no sel increment index, m_bCaretRight hinting for the Caret through mouse selection)
         // Pos* -> Position (Selection Indexing, but not necessary a selection)
         // Char* -> Very String Specific, just "small" string part indexing

         /// cached, derived, ephemeral, temporary values
         strsize           m_iPosBeg;
         strsize           m_iPosEnd;
         size_f64             m_sizeSpan;
         size_f64             m_sizeDevice;
         double_array      m_daPositionLeft;
         double_array      m_daPositionRight;
         double_array      m_daPositionDeviceLeft;
         double_array      m_daPositionDeviceRight;


         span();
         span(class data * pdata);
         span(class data * pdata, ::e_align ealignNewLine);
         span(class data * pdata, const span & span);
         span(const span & span);
         ~span() override;


         void set_new_format();

         bool is_new_line() const { return m_ealignNewLine != e_align_none; }

         ::e_align get_align() const;

         ::pointer<class format> fork_format();

         inline ::pointer<class format> format() { return m_pformat; }

         ::pointer<class span> fork();

         ::pointer<class span> fork(const class format * pformat, const e_attribute & eattribute);

         //void write(::binary_stream & stream) const override;
         //void read(::binary_stream & stream) override;

         span & operator=(const span & span);

         void calculate_position(::draw2d::graphics_pointer & pgraphics);


      };


   } // namespace rich_text


} // namespace user



