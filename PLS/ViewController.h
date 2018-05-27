//
//  ViewController.h
//  PLS
//
//  Created by Robert Häcker on 26.05.18.
//  Copyright © 2018 Robert Häcker. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ViewController : NSViewController
//+(int [])frames;
//@property (weak) IBOutlet NSImageView *imgLeft;
//@property (weak) IBOutlet NSImageView *imgRight;
@property (weak) IBOutlet NSButton *but01;
@property (weak) IBOutlet NSTextFieldCell *lblLeft;
@property (weak) IBOutlet NSTextFieldCell *lblRight;
@property (weak) IBOutlet NSBox *frame01;
@property (weak) IBOutlet NSBox *frame02;
@property (weak) IBOutlet NSBox *frame03;
@property (weak) IBOutlet NSBox *frame04;
@property (weak) IBOutlet NSBox *frame05;
@property (weak) IBOutlet NSBox *frame06;
@property (weak) IBOutlet NSBox *frame07;
@property (weak) IBOutlet NSBox *frame08;
@property (weak) IBOutlet NSLevelIndicator *barVol;
@property (weak) IBOutlet NSLevelIndicator *barSpeed;
@property (weak) IBOutlet NSImageView *imgRight;
@property (weak) IBOutlet NSImageCell *imgRightCell;
@property (weak) IBOutlet NSButtonCell *but02;
@property (weak) IBOutlet NSImageView *leftimg;
@property (weak) IBOutlet NSImageCell *leftimgcell;

- (NSDictionary *) userInfo;
- (void) targetMethod;
@end

