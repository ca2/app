//
//  RoundViewController.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 14/05/14.
//
//

@class AuraWindowFrameView;
@class RoundEditView;

@interface RoundViewController : UIViewController < UITextViewDelegate >
{
@public
   
   
   AuraWindowFrameView   *   childContentView;
   AuraWindow *              m_pwindow;
   RoundEditView *            m_pedit;

}


-(void) deferEdit : (CGRect) frame;
- (void)editingChanged:(id)object;
-(void)onEditSetFocus : (CGRect) rectangle_i32 withText : (NSString *) strText withSelBeg : (long) iSelBeg withSelEnd : (long) iSelEnd;
-(void)onEditKillFocus;

@end
