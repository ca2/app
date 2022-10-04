//
//  RoundImpactController.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 14/05/14.
//
//

@class RoundWindowFrameImpact;
@class RoundEditImpact;

@interface RoundImpactController : UIViewController < UITextImpactDelegate >
{
@public
   
   
   RoundWindowFrameImpact   *   childContentImpact;
   RoundWindow *              m_pwindow;
   RoundEditImpact *            m_pedit;

}


-(void) deferEdit : (CGRect) frame;
- (void)editingChanged:(atom)object;
-(void)onEditSetFocus : (CGRect) rectangle_i32 withText : (NSString *) strText withSelBeg : (long) iSelBeg withSelEnd : (long) iSelEnd;
-(void)onEditKillFocus;

@end
