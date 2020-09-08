

#include "aqua/primitive/primitive/generic_object.h"


@interface mmos : NSObject
{
   
   @public  char ** m_ppszWallpaper;
   @public   long long m_llWallpaper;
   @public  int m_iIcon;
   @public  unsigned int * m_picon;
   @public   int m_cxIcon;
   @public   int m_cyIcon;
   @public   int m_iScanIcon;
   @public  const char * m_pszIcon;
   @public NSRecursiveLock *theLock;
   
}

+ (id)get;

- (void)get_user_wallpaper:(void **)charpp forScreen:(NSScreen *) s;

- (void)get_user_wallpaper:(void *)charppp getCount:(void *) pll;

- (void)desktopImageChanged:(NSNotification *)notification;

- (void)applicationActivity:(NSNotification *)notification;

- (void)monitorWallpaper;

- (void)deferWallpaper:(NSTimer *)timer;

- (void)monitorIconForFile;

- (void)deferIconForFile:(NSTimer *)timer;

-(void)runRunnableOnMainThread:(::generic_object *)pobjectTask;

-(void)runRunnable:(::generic_object *)pobjectTask;

-(NSURL *)browse_folder : (NSURL *) directoryURL canCreateDirectories: (bool) bCanCreateDirectories;
-(NSArray < NSURL * > *)browse_file_open : (NSURL **) startDir multi: (bool) b;
@end

