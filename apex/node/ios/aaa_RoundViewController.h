//
//  RoundViewController.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 14/05/14.
//
//

@class RoundWindowFrameView;
@class RoundEditView;

@interface RoundViewController : UIViewController < UITextViewDelegate >
{
@public
   
   
   RoundWindowFrameView   *   childContentView;
   RoundWindow *              m_pwindow;
   RoundEditView *            m_pedit;

}


-(void) deferEdit : (CGRect) frame;
- (void)editingChanged:(id)object;
-(void)onEditSetFocus : (CGRect) rectangle withText : (NSString *) strText withSelBeg : (long) iSelBeg withSelEnd : (long) iSelEnd;
-(void)onEditKillFocus;

@end
