#pragma once


class CLASS_DECL_AURA context_image :
   virtual public ::object
{
public:


   //handler_manager                     m_managerImageLoad;


   context_image();
   virtual ~context_image();


   virtual ::estatus initialize(::layered * pobjectContext) override;

   virtual ::image_result get_image(const ::var & varFile, bool bCache = true, bool bSync = true);
   virtual ::image_result matter_image(const string & strMatter, bool bCache = true, bool bSync = true);

   virtual ::image_result load_image(const ::var & varFile, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::image_result load_matter_image(const string & strMatter, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::image_result load_matter_icon(string_array & straMatter, string strIcon);
   virtual ::image_result load_thumbnail(const ::var & varFile, int w, int h);
   virtual ::image_result load_thumbnail(const string & strPath);
   virtual ::image_result load_dib(const ::file::path & pathDib);
   virtual ::icon_result load_icon(const ::var & varFile);


   virtual ::estatus _get_image(image * pimage, const ::var & varFile, bool bSync = true);
   virtual ::estatus _matter_image(image * pimage, const string & strMatter, bool bSync = true);


   virtual ::estatus _load_image(image * pimage, const ::var & varFile, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::estatus _load_matter_image(image * pimage, const string & pszMatter, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::estatus _load_matter_icon(image * pimage, string_array & straMatter, string strIcon);
   virtual ::estatus _load_thumbnail(image * pimage, const ::var & varFile, int w, int h);
   virtual ::estatus _load_thumbnail(image * pimage, const ::var & varFile);
   virtual ::estatus _load_dib(image * pimage, const ::file::path & pathDib);


   virtual ::estatus save_image(const ::var & varFile, const image * pimage, const ::save_image * psaveimage = nullptr);
   virtual ::estatus save_image(memory & memory, const image * pimage, const ::save_image * psaveimage = nullptr);
   virtual ::estatus save_dib(const ::file::path & path, const image * pimage);

   
   virtual HCURSOR CreateAlphaCursor(oswindow oswindow, const image * pimage, int xHotSpot, int yHotSpot);
   virtual HCURSOR load_default_cursor(e_cursor ecursor);
   virtual void set_cursor_image(const image * pimage, int xHotSpot, int yHotSpot);
   virtual WINBOOL window_set_mouse_cursor(oswindow window, HCURSOR hcursor);


   virtual ::image_result _load_image_from_file(const ::var & varFile, const var & varOptions);
   virtual ::estatus _save_to_file(const ::var & varFile, const image * pimage, const var & varOptions);
   
   virtual ::estatus _load_image(::image* pimage, __pointer(image_frame_array)& pframea, ::memory_pointer pmemory);
   
   virtual ::estatus load_cursor(::draw2d::cursor* pcursor, ::file::path path, bool bSync, bool bCache = true);

   virtual bool _load_multi_frame_image(::image* pimage, memory_pointer pmemory);

   virtual ::estatus load_svg(::image* pimage, ::memory_pointer pmemory);

#ifdef _UWP
   virtual bool _desk_to_image(::image* pimage);
   virtual bool _desk_has_image();
   virtual bool _image_to_desk(const ::image* pimage);
#endif

};



