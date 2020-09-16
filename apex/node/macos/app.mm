//
//  app.m
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 16/09/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//
#import "_mm.h"


bool nsapp_activation_policy_is_regular()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyRegular)
   {
      
      return true;
      
   }
   
   return false;
   
}


bool nsapp_activation_policy_is_accessory()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyAccessory)
   {
      
      return true;
      
   }
   
   return false;
   
}


bool nsapp_activation_policy_is_prohibited()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyProhibited)
   {
      
      return true;
      
   }
   
   return false;
   
}


void nsapp_activation_policy_regular()
{
   
   ns_main_async(^{
   
      [NSApp  setActivationPolicy:NSApplicationActivationPolicyRegular];
   
   });
   
}


void nsapp_activation_policy_accessory()
{
   ns_main_async(^{
      
      [NSApp setActivationPolicy:NSApplicationActivationPolicyAccessory];
       
   });
   
}


void nsapp_activation_policy_prohibited()
{
  
   ns_main_async(^{
   
      [NSApp setActivationPolicy:NSApplicationActivationPolicyProhibited];
   
   });
   
}


void nsapp_activate_ignoring_other_apps(int i)
{
   
   ns_main_async(^{
      
      if(i)
      {
      
         [NSApp activateIgnoringOtherApps: YES];
      
      }
      else
      {
      
         [NSApp activateIgnoringOtherApps: NO];
      
      }
                 
   });
   
}
