//
//  ios_thread_mm.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 4/23/14.
// Feliz Aniversário Mummi!! Feliz 63 anos e 1 dia!! Graças a Deus!!
//




void * get_thread_ptr(const char * pszKey)
{
    
    return (void *)[[[[NSThread currentThread] threadDictionary] valueForKey: [NSString stringWithUTF8String : pszKey]] longValue];
    
}


void set_thread_ptr(const char * pszKey, const void * p)
{
    
    [[[NSThread currentThread] threadDictionary] setValue: [NSNumber numberWithLong : (long) p] forKey: [NSString stringWithUTF8String : pszKey]];
    
}


int get_thread_int(const char * pszKey)
{
    
    return (int)[[[[NSThread currentThread] threadDictionary] valueForKey: [NSString stringWithUTF8String : pszKey]] intValue];
    
}


void set_thread_int(const char * pszKey, int i)
{
    
    [[[NSThread currentThread] threadDictionary] setValue: [NSNumber numberWithInt : i] forKey: [NSString stringWithUTF8String : pszKey]];
    
}


