//
//  AuraWindowFrameView.h
//  AuraWindow
//
//  Created by Matt Gallagher on 12/12/08.
//  Copyright 2008 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file without charge in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//


#define NS_ROUND_WINDOW_FRAME_PADDING 0

@class AuraWindow;

@interface AuraWindowFrameView : UIView
{
@public
   
   AuraWindow *     m_roundwindow;
   bool              m_bShift;
   bool              m_bControl;
   bool              m_bAlt;
   CGPoint           m_pointLastTouchBegan;
   
}


-(void)on_text : (NSString *) text;
-(void)on_sel : (UITextRange *) sel;


//@property (nonatomic, copy) NSString *contentText; // The text content (without attributes).
//@property (nonatomic, strong) UIFont *font; // Font used for text content.
//@property (nonatomic, getter=isEditing) BOOL editing; // Is impact in "editing" mode or not (affects drawn results).
//@property (nonatomic) NSRange nsMarkedTextRange; // Marked text range (for input method marked text).
//@property (nonatomic) NSRange nselectedTextRange; // Selected text range.
// @property (nonatomic) RoundPlainTextView *textView;
// @property (nonatomic) NSMutableString *text;

//- (CGRect)caretRectForIndex:(int)index;
//- (CGRect)firstRectForRange:(NSRange)range;
//- (NSInteger)closestIndexToPoint:(CGPoint)point_i32;
 
//+ (UIColor *)caretColor;
//Working with Marked and Selected Text
//selectedTextRange
//The range of selected text in a document.
//Required.
//@property(readwrite, copy) UITextRange *selectedTextRange;

//markedTextRange
//The range of text that is currently marked in a document.
//Required.
//@property(nonatomic, readonly) UITextRange *markedTextRange;

//markedTextStyle
//A dictionary of attributes that describes how marked text should be drawn.
//Required.
//@property(nonatomic, copy) NSDictionary<NSAttributedStringKey, atom> *markedTextStyle;



//beginningOfDocument
//The text position for the beginning of a document.
//Required.
//@property(nonatomic, readonly) UITextPosition *beginningOfDocument;
//endOfDocument
//The text position for the end of a document.
//Required.
//@property(nonatomic, readonly) UITextPosition *endOfDocument;



//Text Input Delegate and Text Input Tokenizer
//inputDelegate
//An input delegate that is notified when text changes or when the selection changes.
//Required.
//@property(nonatomic, weak) atom<UITextInputDelegate> inputDelegate;
//tokenizer
//An input tokenizer that provides information about the granularity of text units.
//Required.
//@property(nonatomic, readonly) atom<UITextInputTokenizer> tokenizer;

@end
