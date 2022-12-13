//
//  apple.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 21/07/17.
//
//

#include "framework.h"
#include "main.h"
//#include "aura/os/_.h"
#include "aura/os/_os.h"
#include "aura/update.h"
//char * ns_realpath(const ::string & pszPath);
char * mm_ca2_command_line();


// ThomasBS-LiveEdu.TV(LiveCoding.TV)

void * CreateDispatchQueue()
{

   return dispatch_queue_create (nullptr, nullptr);

}


void CancelDispatchSource(void * p)
{

   dispatch_source_cancel((dispatch_source_t) p);

}


void * CreateDispatchTimer(u64 interval, u64 leeway, void * queue, void (*pfnTimer)(void * p), void * p)
{

   dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, (dispatch_queue_t) queue);

   if (timer)
   {

      dispatch_source_set_timer(timer, dispatch_walltime(DISPATCH_TIME_NOW, interval * NSEC_PER_MSEC), DISPATCH_TIME_FOREVER, leeway * NSEC_PER_MSEC);

      dispatch_source_set_event_handler(timer, ^() { pfnTimer(p); });

      dispatch_resume(timer);

   }

   return timer;

}


void * ResetDispatchTimer(void * timerParam, u64 interval, u64 leeway)
{

   dispatch_source_t timer = (dispatch_source_t) timerParam;

   if (timer)
   {

      dispatch_source_set_timer(timer, dispatch_walltime(DISPATCH_TIME_NOW, interval * NSEC_PER_MSEC), DISPATCH_TIME_FOREVER, leeway * NSEC_PER_MSEC);

      //dispatch_resume(timer);

   }

   return timer;

}


void ReleaseDispatch(void * p)
{

   dispatch_release((dispatch_object_t) p);

}


static bool g_bRunSystem = false;


i32 defer_run_system()
{

   if(g_bRunSystem)
   {

      return 0;

   }

   g_bRunSystem = true;

   //return __start_system_with_file(nullptr);
   
   return 0;

}


i32 defer_run_system(const ::string & pszFileName)
{

   return __start_system_with_file(pszFileName);

}


i32 defer_run_system(char ** pszaFileName, int iFileCount)
{

   return __start_system_with_file((const ::string &*) pszaFileName, iFileCount);

}





//void apple_on_app_activate()
//{
//
//   psystem->call_subject(id_app_activated);
//
//}


void apple_on_new_file()
{

   psystem->on_open_file(::e_type_empty, "");

}

// iMillisDelay default 500ms good
void apple_accumulate_on_open_file(const ::string &* psza, int iCount, const ::string & pszExtra)
{

   string_array stra;

   stra.c_add((char **) psza, iCount, false);

   for(index i = 0; i < stra.get_count(); i++)
   {

      if(::str().case_insensitive_begins_eat(stra[i], "file://"))
      {

         if(!string_begins(stra[i], "/"))
         {

            stra[i] = "/" + stra[i];

         }

         stra[i] = purl->url_decode(stra[i]);

      }

   }

   psystem->defer_accumulate_on_open_file(stra, pszExtra);

}



void apple_on_open_file(const ::string &* psza, int iCount, const ::string & pszExtra)
{

   if(iCount <= 0)
   {

      apple_on_new_file();

   }
   else if(iCount == 1)
   {

      psystem->on_open_file(psza[0], pszExtra);

      ::free((void *) psza[0]);

      ::free(psza);

   }
   else
   {

      string_array stra;

      stra.c_add((char **) psza, iCount, false);

      psystem->on_open_file(stra, pszExtra);

   }

}




string ca2_command_line()
{

   return ::string_from_strdup(mm_ca2_command_line());

}


void screen_coordinates_aware_copy(CGRect * prectTarget, const ::rectangle * prectSource)
{

   CGRect rectangleWorkspace = mm_get_workspace_rect();

   prectTarget->origin.x       = prectSource->left;
   prectTarget->origin.y       = rectangleWorkspace.size.height - prectSource->bottom;
   prectTarget->size.width     = prectSource->right - prectSource->left;
   prectTarget->size.height    = prectSource->bottom - prectSource->top;

}


void screen_coordinates_aware_copy(RECT32 * prectTarget, const CGRect * prectSource)
{

   CGRect rectangleWorkspace = mm_get_workspace_rect();

   prectTarget->left        = prectSource->origin.x;
   prectTarget->bottom      = rectangleWorkspace.size.height - prectSource->origin.y;
   prectTarget->right       = prectTarget->left + prectSource->size.width;
   prectTarget->top         = prectTarget->bottom - prectSource->size.height;

}

void copy(CGPoint * ppointTarget, const POINT32 * ppointSource)
{

   ppointTarget->x      = ppointSource->x;
   ppointTarget->y      = ppointSource->y;

}


void copy(POINT32 * ppointTarget, const CGPoint * ppointSource)
{

   ppointTarget->x      = ppointSource->x;
   ppointTarget->y      = ppointSource->y;

}

void copy(CGPoint * ppointTarget, const POINT_F64 * ppointSource)
{

   ppointTarget->x      = ppointSource->x;
   ppointTarget->y      = ppointSource->y;

}


void copy(POINT_F64 * ppointTarget, const CGPoint * ppointSource)
{

   ppointTarget->x      = ppointSource->x;
   ppointTarget->y      = ppointSource->y;

}

void copy(CGRect * prectTarget, const RECT32 * prectSource)
{

   prectTarget->origin.x      = prectSource->left;
   prectTarget->origin.y      = prectSource->top;
   prectTarget->size.width    = width(prectSource);
   prectTarget->size.height   = height(prectSource);

}


void copy(RECT32 * prectTarget, const CGRect * prectSource)
{
   
   prectTarget->left          = prectSource->origin.x;
   prectTarget->top           = prectSource->origin.y;
   prectTarget->right         = prectSource->origin.x + prectSource->size.width;
   prectTarget->bottom        = prectSource->origin.y + prectSource->size.height;
   
}


void copy(CGRect * prectTarget, const RECTANGLE_F64 * prectSource)
{
   
   prectTarget->origin.x      = prectSource->left;
   prectTarget->origin.y      = prectSource->top;
   prectTarget->size.width    = width(prectSource);
   prectTarget->size.height   = height(prectSource);
   
}


void copy(RECTANGLE_F64 * prectTarget, const CGRect * prectSource)
{
   
   prectTarget->left          = prectSource->origin.x;
   prectTarget->top           = prectSource->origin.y;
   prectTarget->right         = prectSource->origin.x + prectSource->size.width;
   prectTarget->bottom        = prectSource->origin.y + prectSource->size.height;
   
}



bool __node_further_file_is_equal(file::path const & path1, file::path const & path2)
{

   return __xxxnode_full_file_path(path1).case_insensitive_order(__xxxnode_full_file_path(path2)) == 0;

}


::file::path __xxxnode_full_file_path(file::path path)
{

   if(path.is_empty())
   {

      return path;

   }

   //return ::string_from_strdup(ns_realpath(path));

   char sz[4096];

   zero(sz);

   return realpath(path, sz);

}



i64 oswindow_id(oswindow w)
{

   return (i64) (w);

}


int is_window(oswindow window)
{
   return (window == nullptr) ? false : (window->get_user_interaction() != nullptr);
}




int show_window(oswindow oswindow, int iShow)
{
   
   if(::is_null(oswindow))
   {
    
      return false;
      
   }
 
   if(::is_null(oswindow->m_pimpl))
   {
      
      return false;
      
   }
   
   return oswindow->m_pimpl->ShowWindow(iShow);
   
}
