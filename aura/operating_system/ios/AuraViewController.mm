//
//  RoundViewController.m
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 14/05/14.
//
//

#import "_mm.h"
#import "RoundEditView.h"
#import "RoundTextView.h"
#import "RoundTextPosition.h"

@interface RoundViewController ()

@end

@implementation RoundViewController


- (BOOL)shouldAutorotate
{
   return YES;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
   
   [super viewDidLoad];
   
   self->m_pedit = nullptr;
   
   // Do any additional setup after loading the view.

   childContentView.frame = self.view.frame;
   
   //childContentView.delegate = self;
   
   //childContentView.text = @"Lorem Ipsum";
   
}




//- (void)didRotate:(NSNotification *)notification {
//   UIDeviceOrientation orientation = [[notification object] orientation];
//
//   CGAffineTransform t;
//   if (orientation == UIDeviceOrientationLandscapeLeft) {
//      t = CGAffineTransformMakeRotation(M_PI / 2.0);
//   } else if (orientation == UIDeviceOrientationLandscapeRight) {
//      t = CGAffineTransformMakeRotation(M_PI / -2.0);
//   } else if (orientation == UIDeviceOrientationPortraitUpsideDown) {
//      t = CGAffineTransformMakeRotation(M_PI);
//   } else if (orientation == UIDeviceOrientationPortrait) {
//      t = CGAffineTransformMakeRotation(0.0);
//   }
//
//   CGPoint screenCenter = CGPointMake([UIScreen mainScreen].bounds.size.width/2,[UIScreen mainScreen].bounds.size.height/2);
//   self.view.center = CGPointApplyAffineTransform(screenCenter, t);
//   self.view.bounds = CGRectApplyAffineTransform([UIScreen mainScreen].bounds, t);
//   [self.view setTransform:t];
//
//}

-(BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
   
   return YES;
   
}

- (void)textViewDidChange:(UITextView *)textView
{
   
   NSString * text = [textView text];
   
   [childContentView on_text : text ];
   
}


- (void)textViewDidChangeSelection:(UITextView *)textView
{
   
   //UITextRange * sel = [textView selectedTextRange];
   
   //[childContentView on_sel : sel ];
   
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/


-(void) viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id )coordinator
{
   
   [super viewWillTransitionToSize:size withTransitionCoordinator:coordinator];
   
   try
   {
      
      CGRect rect;
      
      rect.origin.x = 0;
      rect.origin.y = 0;
      rect.size = size;
      
      childContentView.frame = rect;

      
      m_pwindow->m_pwindow->round_window_resized(rect.size.width, rect.size.height);
      
   }
   catch (...)
   {
      
      
      
   }
   
   //      NSRect rect = [self frame];
   //
   //      rect.origin.y        = [[NSScreen mainScreen] frame ].size.height - (rect.origin.y + rect.size.height);
   //
   //      m_pwindow->round_window_resized(rect);
   
}

- (BOOL)canBecomeFirstResponder
{
   
//   aura_window * p = m_pwindow->m_pwindow;
//   
//   return p->m_bCanBecomeFirstResponder;
   
   return YES;
}


- (BOOL)becomeFirstResponder
{
   
   //aura_window * p = m_pwindow->m_pwindow;
   
   //if(p->m_bCanBecomeFirstResponder)
   {
      
      return [super becomeFirstResponder];
      
   }
   
   //return FALSE;
   
}


- (BOOL)textViewShouldBeginEditing:(UITextView * ) pview
{
   
   aura_window * p = m_pwindow->m_pwindow;
   
   if(p->m_bCanBecomeFirstResponder)
   {
      
       return YES;
      
   }
   
   return NO;
   
}


-(void)deferEdit : (CGRect) frame
{
   
   if(!self->m_pedit)
   {

      self->m_pedit = [[RoundEditView alloc] initWithFrame:frame];
   
      [ self->childContentView addSubview: self->m_pedit];

      self->m_pedit.textView->m_pwindow = m_pwindow;

   }
   else
   {
      
      [ self->m_pedit setFrame : frame ];
      
      [ self->m_pedit setHidden : FALSE ];
      
   }
   
}


- (void)editingChanged:(id)object {
    // Do your code here
}

-(void)onEditSetFocus : (CGRect) rect withText: (NSString *) strText withSelBeg:(long)iSelBeg withSelEnd:(long)iSelEnd
{
   
   //ns_main_async(^()
   {
   
      [ self deferEdit : rect ];
      
      UITextPosition * beg = self->m_pedit.beginningOfDocument;
      
      UITextPosition * end = self->m_pedit.endOfDocument;
      
      UITextRange * prange = [ self->m_pedit textRangeFromPosition: beg toPosition: end ];

      [ self->m_pedit replaceRange : prange withText : strText ];

      beg = [ RoundTextPosition positionWithIndex : iSelBeg ];
      
      end = [ RoundTextPosition positionWithIndex : iSelEnd ];

      prange = [ self->m_pedit textRangeFromPosition: beg toPosition: end ];

      [ self->m_pedit setSelectedTextRange: prange ];

      [ self->m_pedit becomeFirstResponder];
      
   }
   //);
   
}


-(void)onEditKillFocus
{
   
   if(self->m_pedit && [ self->m_pedit isFirstResponder ])
   {
   
      [ self->m_pedit resignFirstResponder];
      
      [ self->m_pedit setHidden: TRUE ];
      
   }
   
}


@end



