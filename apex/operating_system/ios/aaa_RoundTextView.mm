/*
     File: RoundTextView.m
 Abstract:
 A view that draws text, reasons about layout, and manages a selection over its text range.
 
 IMPORTANT: Its use of CoreText is naive and inefficient, it deals only with left-to-right text layout, and it is by no means a good template for any text editor. It is a toy implementation included only to illustrate how to bind the system keyboard to some pre-existing text editor.
 
  Version: 2.0
 
 Disclaimer: IMPORTANT:  This Apple software is supplied to you by Apple
 Inc. ("Apple") in consideration of your agreement to the following
 terms, and your use, installation, modification or redistribution of
 this Apple software constitutes acceptance of these terms.  If you do
 not agree with these terms, please do not use, install, modify or
 redistribute this Apple software.
 
 In consideration of your agreement to abide by the following terms, and
 subject to these terms, Apple grants you a personal, non-exclusive
 license, under Apple's copyrights in this original Apple software (the
 "Apple Software"), to use, reproduce, modify and redistribute the Apple
 Software, with or without modifications, in source and/or binary forms;
 provided that if you redistribute the Apple Software in its entirety and
 without modifications, you must retain this notice and the following
 text and disclaimers in all such redistributions of the Apple Software.
 Neither the name, trademarks, service marks or logos of Apple Inc. may
 be used to endorse or promote products derived from the Apple Software
 without specific prior written permission from Apple.  Except as
 expressly stated in this notice, no other rights or licenses, express or
 implied, are granted by Apple herein, including but not limited to any
 patent rights that may be infringed by your derivative works or by other
 works in which the Apple Software may be incorporated.
 
 The Apple Software is provided by Apple on an "AS IS" basis.  APPLE
 MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION
 THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS
 FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND
 OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.
 
 IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL
 OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION,
 MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED
 AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE),
 STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 
 Copyright (C) 2013 Apple Inc. All Rights Reserved.
 
 */

#import "_mm.h"
#import "RoundTextView.h"
#import "RoundTextRange.h"
#import <QuartzCore/CALayer.h>

//#import "RoundCaretView.h"


@interface RoundTextView ()

@property (nonatomic) NSDictionary *attributes;
//@property (nonatomic) RoundCaretView *caretView; // Subview that draws the insertion caret.

@end


// Helper function to obtain the intersection of two ranges.
NSRange RangeIntersection(NSRange first, NSRange second);


@implementation RoundTextView


- (id)initWithFrame:(CGRect)frame
{
   
   self = [super initWithFrame:frame];
    
   if (self)
    {
       
       _contentText = @"";
//       _caretView = [[RoundCaretView alloc] initWithFrame:CGRectZero];
       self.layer.geometryFlipped = YES;  // For ease of interaction with the CoreText coordinate system.
       self.font = [UIFont systemFontOfSize:18];
       self.backgroundColor = [UIColor clearColor];
       self.contentMode = UIViewContentModeRedraw;
       self.markedTextRange = NSMakeRange(NSNotFound, NSNotFound);
       self.selectedTextRange = NSMakeRange(NSNotFound, NSNotFound);
       
    }
   
    return self;
   
}


- (void) on_text_composed;
{
   
   NSString * str = self.contentText;
   
   const char * psz=[str UTF8String];
   
   NSRange range = self.selectedTextRange;

   m_pwindow->m_pwindow->round_window_on_text(psz,
                                              range.location, range.location + range.length);
   
}


// Helper method to update our text storage when the text content has changed.
- (void)textChanged
{
    [self setNeedsDisplay];
    [self clearPreviousLayoutInformation];

   // Build the attributed string from our text data and string attribute data,
    NSAttributedString *attributedString = [[NSAttributedString alloc] initWithString:self.contentText attributes:self.attributes];

//   // Create the Core Text framesetter using the attributed string.
//    if (_framesetter != NULL) {
//        CFRelease(_framesetter);
//    }
//    _framesetter = CTFramesetterCreateWithAttributedString((__bridge CFAttributedStringRef)attributedString);

}



-(void)setFrame:(CGRect)frame
{
   
   [super setFrame:frame];
   
}


-(void)setBounds:(CGRect)bounds
{

   [super setBounds:bounds];

}

//
//// Helper method for drawing the current selection range (as a simple filled rect).
//- (void)drawRangeAsSelection:(NSRange)selectionRange
//{
//   // If not in editing mode, do not draw selection rectangles.
//    if (!self.editing) {
//        return;
//    }
//
//    // If the selection range is empty, do not draw.
//    if (selectionRange.length == 0 || selectionRange.location == NSNotFound) {
//        return;
//    }
//
//   // Set the fill color to the selection color.
//    [[RoundTextView selectionColor] setFill];
//
//   /*
//     Iterate over the lines in our CTFrame, looking for lines that intersect with the given selection range, and draw a selection rect for each intersection.
//     */
//    CFArrayRef lines = CTFrameGetLines(_ctFrame);
//    CFIndex linesCount = CFArrayGetCount(lines);
//
//    for (CFIndex linesIndex = 0; linesIndex < linesCount; linesIndex++) {
//
//        CTLineRef line = (CTLineRef) CFArrayGetValueAtIndex(lines, linesIndex);
//        CFRange lineRange = CTLineGetStringRange(line);
//        NSRange range = NSMakeRange(lineRange.location, lineRange.length);
//        NSRange intersection = RangeIntersection(range, selectionRange);
//        if (intersection.location != NSNotFound && intersection.length > 0) {
//         // The text range for this line intersects our selection range.
//            CGFloat xStart = CTLineGetOffsetForStringIndex(line, intersection.location, NULL);
//            CGFloat xEnd = CTLineGetOffsetForStringIndex(line, intersection.location + intersection.length, NULL);
//            CGPoint origin;
//         // Get coordinate and bounds information for the intersection text range.
//            CTFrameGetLineOrigins(_ctFrame, CFRangeMake(linesIndex, 0), &origin);
//            CGFloat ascent, descent;
//            CTLineGetTypographicBounds(line, &ascent, &descent, NULL);
//         // Create a rect for the intersection and draw it with selection color.
//            CGRect selectionRect = CGRectMake(xStart, origin.y - descent, xEnd - xStart, ascent + descent);
//            UIRectFill(selectionRect);
//        }
//    }
//}

// Standard UIView drawRect override that uses Core Text to draw our text contents.
- (void)drawRect:(CGRect)rect
{
/*    // First draw selection / marked text, then draw text.
    [self drawRangeAsSelection:_selectedTextRange];
    [self drawRangeAsSelection:_markedTextRange];

    CTFrameDraw(_ctFrame, UIGraphicsGetCurrentContext());*/
}


// Public method to find the text range index for a given CGPoint.
- (NSInteger)closestIndexToPoint:(CGPoint)point
{
   /*
     Use Core Text to find the text index for a given CGPoint by iterating over the y-origin points for each line, finding the closest line, and finding the closest index within that line.
     */
//    CFArrayRef lines = CTFrameGetLines(_ctFrame);
//    CFIndex linesCount = CFArrayGetCount(lines);
//    CGPoint origins[linesCount];
//
//    CTFrameGetLineOrigins(_ctFrame, CFRangeMake(0, linesCount), origins);
//
//    for (CFIndex linesIndex = 0; linesIndex < linesCount; linesIndex++) {
//        if (point.y > origins[linesIndex].y) {
//         // This line origin is closest to the y-coordinate of our point; now look for the closest string index in this line.
//            CTLineRef line = (CTLineRef)CFArrayGetValueAtIndex(lines, linesIndex);
//            return CTLineGetStringIndexForPosition(line, point);
//        }
//    }

   return m_pwindow->m_pwindow->round_window_edit_hit_test(point.x, point.y);
   
    //return  self.contentText.length;
}


/*
 Public method to determine the CGRect for the insertion point or selection, used when creating or updating the simple caret view instance.
 */
- (CGRect)caretRectForIndex:(int)index
{
   
   CGRect r;
   
   if(m_pwindow->m_pwindow->round_window_edit_caret_rect(&r,index))
   {
      
      return r;
      
   }
   
   return CGRectNull;
   
}

/*
 Public method to create a rect for a given range in the text contents.
 Called by our EditableTextRange to implement the required UITextInput:firstRectForRange method.
 */
- (CGRect)firstRectForRange:(NSRange)range;
{
   
   long beg = range.location;
   
   long end = range.location + range.length;
   
   CGRect rBeg;
   
   if(!m_pwindow->m_pwindow->round_window_edit_caret_rect(&rBeg, beg))
   {
      
      return CGRectNull;
      
   }

   CGRect rEnd;
   
   if(!m_pwindow->m_pwindow->round_window_edit_caret_rect(&rEnd, end))
   {
      
      return CGRectNull;
      
   }


   return CGRectNull;
   
}


// Helper method to update caretView when insertion point/selection changes.
- (void)selectionChanged
{
   // If not in editing mode, we don't show the caret.
    if (!self.editing) {
//        [self.caretView removeFromSuperview];
        return;
    }

   /*
     If there is no selection range (always true for this sample), find the insert point rect and create a caretView to draw the caret at this position.
     */
    if (self.selectedTextRange.length == 0) {
//        self.caretView.frame = [self caretRectForIndex:(int)self.selectedTextRange.location];
//        if (self.caretView.superview == nil) {
//            [self addSubview:self.caretView];
//            [self setNeedsDisplay];
//        }
//        // Set up a timer to "blink" the caret.
//        [self.caretView delayBlink];
    }
    else {
      // If there is an actual selection, don't draw the insertion caret.
//        [self.caretView removeFromSuperview];
//        [self setNeedsDisplay];
    }

    if (self.markedTextRange.location != NSNotFound) {
//        [self setNeedsDisplay];
    }
}


// Helper method to release our cached Core Text framesetter and frame.
- (void)clearPreviousLayoutInformation
{
//    if (_framesetter != NULL) {
//        CFRelease(_framesetter);
//        _framesetter = NULL;
//    }
//
//    if (_ctFrame != NULL) {
//        CFRelease(_ctFrame);
//        _ctFrame = NULL;
//    }
}


#pragma mark - Property accessor overrides

/*
 When setting the font, we need to additionally create and set the Core Text font object that corresponds to the UIFont being set.
 */
- (void)setFont:(UIFont *)newFont
{
    if (newFont != _font) {
        _font = newFont;

        // Find matching CTFont via name and size.
        CTFontRef ctFont = CTFontCreateWithName((__bridge CFStringRef) _font.fontName, _font.pointSize, NULL);

        // Set CTFont instance in our attributes dictionary, to be set on our attributed string.
        self.attributes = @{ (NSString *)kCTFontAttributeName : (__bridge id)ctFont };

        CFRelease(ctFont);

        [self textChanged];
    }
}


/*
 We need to call textChanged after setting the new property text to update layout.
 */
- (void)setContentText:(NSString *)text
{
    _contentText = [text copy];
    [self textChanged];
}


/*
 Set accessors should call selectionChanged to update view if necessary.
 */

- (void)setMarkedTextRange:(NSRange)range
{
    _markedTextRange = range;
    [self selectionChanged];
}


- (void)setSelectedTextRange:(NSRange)range
{
    _selectedTextRange = range;
    [self selectionChanged];
}


- (void)setEditing:(BOOL)editing
{
    _editing = editing;
    [self selectionChanged];
}


#pragma mark - Selection and caret colors

// Class method that returns current selection color (in this sample the color cannot be changed).
+ (UIColor *)selectionColor
{
    static UIColor *selectionColor = nil;
    if (selectionColor == nil) {
        selectionColor = [[UIColor alloc] initWithRed:0.25 green:0.50 blue:1.0 alpha:0.50];
    }
    return selectionColor;
}


// Class method that returns current caret color (in this sample the color cannot be changed).
+ (UIColor *)caretColor
{
    static UIColor *caretColor = nil;
    if (caretColor == nil) {
        caretColor = [[UIColor alloc] initWithRed:0.25 green:0.50 blue:1.0 alpha:1.0];
    }
    return caretColor;
}




@end


#pragma mark - Range intersection function
/*
 Helper function to obtain the intersection of two ranges (for handling selection range across multiple line ranges in drawRangeAsSelection).
 */
NSRange RangeIntersection(NSRange first, NSRange second)
{
    NSRange result = NSMakeRange(NSNotFound, 0);

   // Ensure first range does not start after second range.
    if (first.location > second.location) {
        NSRange tmp = first;
        first = second;
        second = tmp;
    }

   // Find the overlap intersection range between first and second.
    if (second.location < first.location + first.length) {
        result.location = second.location;
        NSUInteger end = min(first.location + first.length, second.location + second.length);
        result.length = end - result.location;
    }

    return result;
}

