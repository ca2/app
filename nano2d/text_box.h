// From types.h by camilo on 
// 2023-09-12 12:21 <3ThomasBorregaardSorensen!!
#pragma once


namespace nano2d
{


	struct text_row :
		virtual public ::particle
	{
		::string m_str;
		//const char* start;	// Pointer to the input text where the row starts.
		//const char* end;	// Pointer to the input text where the row ends (one past the last character).
		//const char* next;	// Pointer to the beginning of the next row.
		float width;		// Logical width of the row.
		float minx, maxx;	// Actual bounds of the row. Logical with and bounds can differ because of kerning and some parts over extending.
	};
	typedef struct text_row text_row;

	class text_box :
		public ::particle
	{
	public:

		::pointer_array < text_row >     m_rowa;
		::f32                            m_fWidth;

	};


} // namespace nano2d



