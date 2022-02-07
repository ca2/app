/*
     File: RoundEditView.m
 Abstract:
A view that illustrates how to implement and use the UITextInput protocol.

Heavily leverages an existing CoreText-based editor and merely serves as the "glue" between the system keyboard and this editor.
 
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
#import "RoundEditView.h"
#import <CoreText/CoreText.h>

#import "RoundTextPosition.h"
#import "RoundTextRange.h"
#import "RoundTextView.h"


// We use a tap gesture recognizer to allow the user to tap to invoke text edit mode.
@interface RoundEditView () <UIGestureRecognizerDelegate>

@property (nonatomic) NSMutableString *text;

/*
 An input tokenizer is an object that provides information about the granularity of text units by implementing the UITextInputTokenizer protocol.  Standard units of granularity include characters, words, lines, and paragraphs. In most cases, you may lazily create and assign an instance of a subclass of UITextInputStringTokenizer for this purpose, as this sample does. If you require different behavior than this system-provided tokenizer, you can create a custom tokenizer that adopts the UITextInputTokenizer protocol.
 */
@property (nonatomic) UITextInputStringTokenizer *tokenizer;


- (void)tap:(UITapGestureRecognizer *)tap;

@end



@implementation RoundEditView


@synthesize markedTextStyle = _markedTextStyle;
@synthesize inputDelegate = _inputDelegate;




- (id)initWithFrame:(CGRect)frame
{
   
   self = [super initWithFrame:frame];
   
   
    // Add tap gesture recognizer to let the user enter editing mode.
    UITapGestureRecognizer *tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tap:)];
    [self addGestureRecognizer:tapGestureRecognizer];
    tapGestureRecognizer.delegate = self;

    // Create our tokenizer and text storage.
    self.tokenizer = [[UITextInputStringTokenizer alloc] initWithTextInput:self];
    self.text = [[NSMutableString alloc] init];

    self.userInteractionEnabled = YES;
    self.autoresizesSubviews = YES;

    // Create and set up the RoundTextView that will do the drawing.
    RoundTextView *textView = [[RoundTextView alloc] initWithFrame:CGRectInset(self.bounds, 5, 5)];
    textView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    [self addSubview:textView];
    textView.contentText = @"";
    textView.userInteractionEnabled = NO;
    self.textView = textView;
   return self;
}


#pragma mark - Custom user interaction

/**
 UIResponder protocol override.
 Our view can become first responder to receive user text input.
 */
- (BOOL)canBecomeFirstResponder
{
    return YES;
}


/**
 UIResponder protocol override.
 Called when our view is being asked to resign first responder state (in this sample by using the "Done" button).
 */
- (BOOL)resignFirstResponder
{
   // Flag that underlying RoundTextView is no longer in edit mode
    self.textView.editing = NO;
   return [super resignFirstResponder];
}


/**
 UIGestureRecognizerDelegate method.
 Called to determine if we want to handle a given gesture.
 */
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gesture shouldReceiveTouch:(UITouch *)touch
{
   // If gesture touch occurs in our view, we want to handle it
    return (touch.view == self);
}


/**
 Our tap gesture recognizer selector that enters editing mode, or if already in editing mode, updates the text insertion point.
 */
- (void)tap:(UITapGestureRecognizer *)tap
{
    if ([self isFirstResponder]) {
      // Already in editing mode, set insertion point (via selectedTextRange).
        [self.inputDelegate selectionWillChange:self];

        // Find and update insertion point in underlying RoundTextView.
        NSInteger index = [self.textView closestIndexToPoint:[tap locationInView:self.textView]];
        self.textView.markedTextRange = NSMakeRange(NSNotFound, 0);
        self.textView.selectedTextRange = NSMakeRange(index, 0);

        // Let inputDelegate know selection has changed.
        [self.inputDelegate selectionDidChange:self];
    }
    else {
      // Inform controller that we're about to enter editing mode.
      [self.editableCoreTextViewDelegate editableCoreTextViewWillEdit:self];
      // Flag that underlying RoundTextView is now in edit mode.
        self.textView.editing = YES;
      // Become first responder state (which shows software keyboard, if applicable).
        [self becomeFirstResponder];
    }
}


#if 0
// Helper method to use whenever selection state changes
- (void)selectionChanged
{
   /*
     Not implemented in this sample -- a user selection mechanism is beyond the scope of this simple sample, but if a mechanism and UI existed to support user selection of text, this method would update selection information, and inform the underlying RoundTextView.
     */
}

// Helper method to use whenever text storage changes.
- (void)textChanged
{
    self.textView.text = self.text;
}
#endif


#pragma mark - UITextInput methods

#pragma mark UITextInput - Replacing and Returning Text

/**
 UITextInput protocol required method.
 Called by text system to get the string for a given range in the text storage.
 */
- (NSString *)textInRange:(UITextRange *)range
{
    RoundTextRange *r = (RoundTextRange *)range;
    return ([self.text substringWithRange:r.range]);
}


/**
 UITextInput protocol required method.
 Called by text system to replace the given text storage range with new text.
 */
- (void)replaceRange:(UITextRange *)range withText:(NSString *)text
{
    RoundTextRange *indexedRange = (RoundTextRange *)range;
   // Determine if replaced range intersects current selection range
   // and update selection range if so.
    NSRange selectedNSRange = self.textView.selectedTextRange;
    if ((indexedRange.range.location + indexedRange.range.length) <= selectedNSRange.location) {
        // This is the easy case.
        selectedNSRange.location -= (indexedRange.range.length - text.length);
    } else {
        // Need to also deal with overlapping ranges.  Not addressed
      // in this simplified sample.
    }

    // Now replace characters in text storage
    [self.text replaceCharactersInRange:indexedRange.range withString:text];

   // Update underlying RoundTextView
    self.textView.contentText = self.text;
    self.textView.selectedTextRange = selectedNSRange;
}


#pragma mark UITextInput - Working with Marked and Selected Text

/**
 UITextInput selectedTextRange property accessor overrides (access/update underlaying RoundTextView)
 */
- (UITextRange *)selectedTextRange
{
    return [RoundTextRange indexedRangeWithRange:self.textView.selectedTextRange];
}


- (void)setSelectedTextRange:(UITextRange *)range
{
    RoundTextRange *indexedRange = (RoundTextRange *)range;
    self.textView.selectedTextRange = indexedRange.range;
}


/**
 UITextInput markedTextRange property accessor overrides (access/update underlaying RoundTextView).
 */
- (UITextRange *)markedTextRange
{
    /*
     Return nil if there is no marked text.
     */
    NSRange markedTextRange = self.textView.markedTextRange;
    if (markedTextRange.length == 0) {
        return nil;
    }
    
    return [RoundTextRange indexedRangeWithRange:markedTextRange];
}


/**
 UITextInput protocol required method.
 Insert the provided text and marks it to indicate that it is part of an active input session.
 */
- (void)setMarkedText:(NSString *)markedText selectedRange:(NSRange)selectedRange
{
    NSRange selectedNSRange = self.textView.selectedTextRange;
    NSRange markedTextRange = self.textView.markedTextRange;

    if (markedTextRange.location != NSNotFound) {
        if (!markedText)
            markedText = @"";
      // Replace characters in text storage and update markedText range length.
        [self.text replaceCharactersInRange:markedTextRange withString:markedText];
        markedTextRange.length = markedText.length;
    }
    else if (selectedNSRange.length > 0) {
      // There currently isn't a marked text range, but there is a selected range,
      // so replace text storage at selected range and update markedTextRange.
        [self.text replaceCharactersInRange:selectedNSRange withString:markedText];
        markedTextRange.location = selectedNSRange.location;
        markedTextRange.length = markedText.length;
    }
    else {
      // There currently isn't marked or selected text ranges, so just insert
      // given text into storage and update markedTextRange.
        [self.text insertString:markedText atIndex:selectedNSRange.location];
        markedTextRange.location = selectedNSRange.location;
        markedTextRange.length = markedText.length;
    }

   // Updated selected text range and underlying RoundTextView.

    selectedNSRange = NSMakeRange(selectedRange.location + markedTextRange.location, selectedRange.length);

    self.textView.contentText = self.text;
    self.textView.markedTextRange = markedTextRange;
    self.textView.selectedTextRange = selectedNSRange;
}


/**
 UITextInput protocol required method.
 Unmark the currently marked text.
 */
- (void)unmarkText
{
    NSRange markedTextRange = self.textView.markedTextRange;

    if (markedTextRange.location == NSNotFound) {
        return;
    }
   // Unmark the underlying RoundTextView.markedTextRange.
    markedTextRange.location = NSNotFound;
    self.textView.markedTextRange = markedTextRange;
}


#pragma mark UITextInput - Computing Text Ranges and Text Positions

// UITextInput beginningOfDocument property accessor override.
- (UITextPosition *)beginningOfDocument
{
   // For this sample, the document always starts at index 0 and is the full length of the text storage.
    return [RoundTextPosition positionWithIndex:0];
}


// UITextInput endOfDocument property accessor override.
- (UITextPosition *)endOfDocument
{
   // For this sample, the document always starts at index 0 and is the full length of the text storage.
    return [RoundTextPosition positionWithIndex:self.text.length];
}


/*
 UITextInput protocol required method.
 Return the range between two text positions using our implementation of UITextRange.
 */
- (UITextRange *)textRangeFromPosition:(UITextPosition *)fromPosition toPosition:(UITextPosition *)toPosition
{
   // Generate IndexedPosition instances that wrap the to and from ranges.
    RoundTextPosition *fromIndexedPosition = (RoundTextPosition *)fromPosition;
    RoundTextPosition *toIndexedPosition = (RoundTextPosition *)toPosition;
    NSRange range = NSMakeRange(MIN(fromIndexedPosition.index, toIndexedPosition.index), ABS(toIndexedPosition.index - fromIndexedPosition.index));

    return [RoundTextRange indexedRangeWithRange:range];
}


/**
 UITextInput protocol required method.
 Returns the text position at a given offset from another text position using our implementation of UITextPosition.
 */
- (UITextPosition *)positionFromPosition:(UITextPosition *)position offset:(NSInteger)offset
{
   // Generate IndexedPosition instance, and increment index by offset.
    RoundTextPosition *indexedPosition = (RoundTextPosition *)position;
    NSInteger end = indexedPosition.index + offset;
   // Verify position is valid in document.
    if (end > self.text.length || end < 0) {
        return nil;
    }

    return [RoundTextPosition positionWithIndex:end];
}


/**
 UITextInput protocol required method.
 Returns the text position at a given offset in a specified direction from another text position using our implementation of UITextPosition.
 */
- (UITextPosition *)positionFromPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction offset:(NSInteger)offset
{
    // Note that this sample assumes left-to-right text direction.
    RoundTextPosition *indexedPosition = (RoundTextPosition *)position;
    NSInteger newPosition = indexedPosition.index;

    switch ((NSInteger)direction) {
        case UITextLayoutDirectionRight:
            newPosition += offset;
            break;
        case UITextLayoutDirectionLeft:
            newPosition -= offset;
            break;
        UITextLayoutDirectionUp:
        UITextLayoutDirectionDown:
         // This sample does not support vertical text directions.
            break;
    }

    // Verify new position valid in document.

    if (newPosition < 0)
        newPosition = 0;

    if (newPosition > self.text.length)
        newPosition = self.text.length;

    return [RoundTextPosition positionWithIndex:newPosition];
}


#pragma mark UITextInput - Evaluating Text Positions

/**
 UITextInput protocol required method.
 Return how one text position compares to another text position.
 */
- (NSComparisonResult)comparePosition:(UITextPosition *)position toPosition:(UITextPosition *)other
{
    RoundTextPosition *indexedPosition = (RoundTextPosition *)position;
    RoundTextPosition *otherIndexedPosition = (RoundTextPosition *)other;

   // For this sample, simply compare position index values.
    if (indexedPosition.index < otherIndexedPosition.index) {
        return NSOrderedAscending;
    }
    if (indexedPosition.index > otherIndexedPosition.index) {
        return NSOrderedDescending;
    }
    return NSOrderedSame;
}


/**
 UITextInput protocol required method.
 Return the number of visible characters between one text position and another text position.
 */
- (NSInteger)offsetFromPosition:(UITextPosition *)from toPosition:(UITextPosition *)toPosition
{
    RoundTextPosition *fromIndexedPosition = (RoundTextPosition *)from;
    RoundTextPosition *toIndexedPosition = (RoundTextPosition *)toPosition;
    return (toIndexedPosition.index - fromIndexedPosition.index);
}


#pragma mark UITextInput - Text Layout, writing direction and position related methods

/**
 UITextInput protocol method.
 Return the text position that is at the farthest extent in a given layout direction within a range of text.
 */
- (UITextPosition *)positionWithinRange:(UITextRange *)range farthestInDirection:(UITextLayoutDirection)direction
{
    // Note that this sample assumes left-to-right text direction.
    RoundTextRange *indexedRange = (RoundTextRange *)range;
    NSInteger position;

   /*
     For this sample, we just return the extent of the given range if the given direction is "forward" in a left-to-right context (UITextLayoutDirectionRight or UITextLayoutDirectionDown), otherwise we return just the range position.
     */
    switch (direction) {
        case UITextLayoutDirectionUp:
        case UITextLayoutDirectionLeft:
            position = indexedRange.range.location;
            break;
        case UITextLayoutDirectionRight:
        case UITextLayoutDirectionDown:
            position = indexedRange.range.location + indexedRange.range.length;
            break;
    }

   // Return text position using our UITextPosition implementation.
   // Note that position is not currently checked against document range.
    return [RoundTextPosition positionWithIndex:position];
}


/**
 UITextInput protocol required method.
 Return a text range from a given text position to its farthest extent in a certain direction of layout.
 */
- (UITextRange *)characterRangeByExtendingPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction
{
    // Note that this sample assumes left-to-right text direction.
    RoundTextPosition *pos = (RoundTextPosition *)position;
    NSRange result;

    switch (direction) {
        case UITextLayoutDirectionUp:
        case UITextLayoutDirectionLeft:
            result = NSMakeRange(pos.index - 1, 1);
            break;
        case UITextLayoutDirectionRight:
        case UITextLayoutDirectionDown:
            result = NSMakeRange(pos.index, 1);
            break;
    }

    // Return range using our UITextRange implementation.
   // Note that range is not currently checked against document range.
    return [RoundTextRange indexedRangeWithRange:result];
}


/**
 UITextInput protocol required method.
 Return the base writing direction for a position in the text going in a specified text direction.
 */
- (UITextWritingDirection)baseWritingDirectionForPosition:(UITextPosition *)position inDirection:(UITextStorageDirection)direction
{
    // This sample assumes left-to-right text direction and does not support bi-directional or right-to-left text.
    return UITextWritingDirectionLeftToRight;
}


/**
 UITextInput protocol required method.
 Set the base writing direction for a given range of text in a document.
 */
- (void)setBaseWritingDirection:(UITextWritingDirection)writingDirection forRange:(UITextRange *)range
{
    // This sample assumes left-to-right text direction and does not support bi-directional or right-to-left text.
}


#pragma mark UITextInput - Geometry methods

/**
 UITextInput protocol required method.
 Return the first rectangle that encloses a range of text in a document.
 */
- (CGRect)firstRectForRange:(UITextRange *)range
{
    RoundTextRange *r = (RoundTextRange *)range;
   // Use underlying RoundTextView to get rect for range.
    CGRect rect = [self.textView firstRectForRange:r.range];
   // Convert rect to our view coordinates.
    return [self convertRect:rect fromView:self.textView];
}


/*
 UITextInput protocol required method.
 Return a rectangle used to draw the caret at a given insertion point.
 */
- (CGRect)caretRectForPosition:(UITextPosition *)position
{
    RoundTextPosition *pos = (RoundTextPosition *)position;

   // Get caret rect from underlying RoundTextView.
    CGRect rect =  [self.textView caretRectForIndex:
                    (int)pos.index];
   // Convert rect to our view coordinates.
    return [self convertRect:rect fromView:self.textView];
}


#pragma mark UITextInput - Hit testing

/*
 For this sample, hit testing methods are not implemented because there is no implemented mechanism for letting user select text via touches. There is a wide variety of approaches for this (gestures, drag rects, etc) and any approach chosen will depend greatly on the design of the application.
 */

/*
 UITextInput protocol required method.
 Return the position in a document that is closest to a specified point.
 */
- (UITextPosition *)closestPositionToPoint:(CGPoint)point
{
   // Not implemented in this sample. Could utilize underlying RoundTextView:closestIndexToPoint:point.
    return nil;
}

/*
 UITextInput protocol required method.
 Return the position in a document that is closest to a specified point in a given range.
 */
- (UITextPosition *)closestPositionToPoint:(CGPoint)point withinRange:(UITextRange *)range
{
   // Not implemented in this sample. Could utilize underlying RoundTextView:closestIndexToPoint:point.
    return nil;
}

/*
 UITextInput protocol required method.
 Return the character or range of characters that is at a given point in a document.
 */
- (UITextRange *)characterRangeAtPoint:(CGPoint)point
{
   // Not implemented in this sample. Could utilize underlying RoundTextView:closestIndexToPoint:point.
    return nil;
}


/*
 UITextInput protocol required method.
 Return an array of UITextSelectionRects.
 */
- (NSArray *)selectionRectsForRange:(UITextRange *)range
{
    // Not implemented in this sample.
    return nil;
}


#pragma mark UITextInput - Returning Text Styling Information

/*
 UITextInput protocol required method.
 Return a dictionary with properties that specify how text is to be style at a certain location in a document.
 */
- (NSDictionary *)textStylingAtPosition:(UITextPosition *)position inDirection:(UITextStorageDirection)direction
{
    // This sample assumes all text is single-styled, so this is easy.
    return @{ UITextInputTextFontKey : self.textView.font };
}


#pragma mark UIKeyInput methods

/**
 UIKeyInput protocol required method.
 A Boolean value that indicates whether the text-entry objects have any text.
 */
- (BOOL)hasText
{
    return (self.text.length != 0);
}


/**
 UIKeyInput protocol required method.
 Insert a character into the displayed text. Called by the text system when the user has entered simple text.
 */
- (void)insertText:(NSString *)text
{
    NSRange selectedNSRange = self.textView.selectedTextRange;
    NSRange markedTextRange = self.textView.markedTextRange;

   /*
     While this sample does not provide a way for the user to create marked or selected text, the following code still checks for these ranges and acts accordingly.
     */
    if (markedTextRange.location != NSNotFound) {
      // There is marked text -- replace marked text with user-entered text.
        [self.text replaceCharactersInRange:markedTextRange withString:text];
        selectedNSRange.location = markedTextRange.location + text.length;
        selectedNSRange.length = 0;
        markedTextRange = NSMakeRange(NSNotFound, 0);
    } else if (selectedNSRange.length > 0) {
      // Replace selected text with user-entered text.
        [self.text replaceCharactersInRange:selectedNSRange withString:text];
        selectedNSRange.length = 0;
        selectedNSRange.location += text.length;
    } else {
      // Insert user-entered text at current insertion point.
        [self.text insertString:text atIndex:selectedNSRange.location];
        selectedNSRange.location += text.length;
    }

   // Update underlying RoundTextView.
   self.textView.contentText = self.text;
   self.textView.markedTextRange = markedTextRange;
   self.textView.selectedTextRange = selectedNSRange;
   
   [ self.textView on_text_composed ];
   
}


/**
 UIKeyInput protocol required method.
 Delete a character from the displayed text. Called by the text system when the user is invoking a delete (e.g. pressing the delete software keyboard key).
 */
- (void)deleteBackward
{
    
   NSRange selectedNSRange = self.textView.selectedTextRange;
   NSRange markedTextRange = self.textView.markedTextRange;

   /*
     Note: While this sample does not provide a way for the user to create marked or selected text, the following code still checks for these ranges and acts accordingly.
     */
   if (markedTextRange.location != NSNotFound)
   {
   
      // There is marked text, so delete it.
      [self.text deleteCharactersInRange:markedTextRange];
      
      selectedNSRange.location = markedTextRange.location;
      
      selectedNSRange.length = 0;
      
      markedTextRange = NSMakeRange(NSNotFound, 0);
      
    }
    else if (selectedNSRange.length > 0)
    {
    
       // Delete the selected text.
       [self.text deleteCharactersInRange:selectedNSRange];
       
       selectedNSRange.length = 0;
       
    }
    else if (selectedNSRange.location > 0)
    {
    
       // Delete one char of text at the current insertion point.
       
       selectedNSRange.location--;
       
       selectedNSRange.length = 1;
       
       [self.text deleteCharactersInRange:selectedNSRange];
       
       selectedNSRange.length = 0;

   }

   // Update underlying RoundTextView.
   self.textView.contentText = self.text;
   
   self.textView.markedTextRange = markedTextRange;
   
   self.textView.selectedTextRange = selectedNSRange;
   
   [ self.textView on_text_composed ];
   
}


@end


