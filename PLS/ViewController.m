//
//  ViewController.m
//  PLS
//
//  Created by Robert Häcker on 26.05.18.
//  Copyright © 2018 Robert Häcker. All rights reserved.
//

#import "ViewController.h"
#include "multiple-myos.h"

int frames[10];
@implementation ViewController
//+ (int []) frames{return frames;}
- (IBAction)leftCell:(NSImageCell *)sender {
    printf("teste");
}
- (IBAction)lblRight:(NSTextFieldCell *)sender {
}
- (IBAction)lblLeft:(NSTextField *)sender {
}
- (IBAction)but03:(NSButtonCell *)sender {
    printf("push02 ");
    NSImage *fist;
    fist = [NSImage imageNamed:@"NSColor"];
    _imgRightCell.image = fist;
    _imgLeftCell.image = fist;
    
    //changes lvl of the "volume" bar
    _barVol.intValue=2;
    //changes lvl of the "speed" bar
    _barSpeed.intValue=3;
    //changes color of the border around a number. ther is frame01 up to frame08
    _frame01.borderColor=[NSColor blackColor];
}
- (IBAction)butAction:(NSButton *)sender {
    printf("push ");
    
    NSImage *fist;
    fist = [NSImage imageNamed:@"NSColor"];
    _imgLeft.objectValue = fist;
    _imgRight.objectValue = fist;
    
    
    
    //changes lvl of the "volume" bar
    _barVol.intValue=18;
    //changes lvl of the "speed" bar
    _barSpeed.intValue=15;
    //changes color of the border around a number. ther is frame01 up to frame08
    _frame01.borderColor=[NSColor orangeColor];
    //_imgLeft.objectValue = fist;
    //_but01.image = fist;
    printf("release ");
}



- (void)viewDidLoad {
    [super viewDidLoad];
    
    
    [self performSelectorInBackground:@selector(doShit) withObject:nil];
    
    frames[0] = 42;
    
    NSImage *fist;
    NSImage *spread;
    NSImage *wleft;
    NSImage *wright;
    NSImage *tap;
    fist = [NSImage imageNamed:@"/Users/roberthacker/Documents/GitHub/pls/PLS/img/01.png"];
    spread = [NSImage imageNamed:@"/Users/roberthacker/Documents/GitHub/pls/PLS/img/02.svg"];
    wleft = [NSImage imageNamed:@"/Users/roberthacker/Documents/GitHub/pls/PLS/img/03.svg"];
    wright = [NSImage imageNamed:@"/Users/roberthacker/Documents/GitHub/pls/PLS/img/04.svg"];
    tap = [NSImage imageNamed:@"/Users/roberthacker/Documents/GitHub/pls/PLS/img/05.svg"];
    printf("test12");
    _imgLeft.objectValue = fist;
    printf("111111");
    //_imgLeft.imageScaling;
    //leftCell->fist;
    //_imgLeft.image = fist;
    //[_imgLeft setImage:fist];
    //_imgLeft.updateLayer;
    
    //[self performSelectorInBackground:@selector(updategui) withObject:nil];
    
    // Do any additional setup after loading the view.
    
    
    // Create timer to handle UI updates
    [NSTimer scheduledTimerWithTimeInterval: 0.05 target:self selector:@selector(targetMethod) userInfo:nil repeats:YES];
}

- (void) targetMethod {
   // NSLog(@"Timer fired");
    
    if(frames[0] == 1) {
        _frame01.borderColor=[NSColor orangeColor];
    } else {
        _frame01.borderColor=[NSColor grayColor];
    }
    
    if(frames[1] == 1) {
        _frame02.borderColor=[NSColor orangeColor];
    } else {
        _frame02.borderColor=[NSColor grayColor];
    }
    
    if(frames[2] == 1) {
        _frame03.borderColor=[NSColor orangeColor];
    } else {
        _frame03.borderColor=[NSColor grayColor];
    }
    
    if(frames[3] == 1) {
        _frame04.borderColor=[NSColor orangeColor];
    } else {
        _frame04.borderColor=[NSColor grayColor];
    }
    
    if(frames[4] == 1) {
        _frame05.borderColor=[NSColor orangeColor];
    } else {
        _frame05.borderColor=[NSColor grayColor];
    }
    
    if(frames[5] == 1) {
        _frame06.borderColor=[NSColor orangeColor];
    } else {
        _frame06.borderColor=[NSColor grayColor];
    }
    
    if(frames[6] == 1) {
        _frame07.borderColor=[NSColor orangeColor];
    } else {
        _frame07.borderColor=[NSColor grayColor];
    }
    
    if(frames[7] == 1) {
        _frame08.borderColor=[NSColor orangeColor];
    } else {
        _frame08.borderColor=[NSColor grayColor];
    }
    
    //changes lvl of the "volume" bar
    _barVol.intValue=frames[8];
    //changes lvl of the "speed" bar
    _barSpeed.intValue=frames[9];
    
    //TODO: Speed * Volume
}

- (NSDictionary *) userInfo{
    return @{@"Start Date": [NSDate date]};
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];
    
    // Update the view, if already loaded.
}
- (void) updategui{
    //check the values from the "side channel thread" from the ranzig() function for updates... every 1s should be enought
    while(1){
        [NSThread sleepForTimeInterval:2.0f];
        // printf("%s", &" "[*frames[0]]);
        printf("test");
    }
    
    
    
}

- (void) doShit
{
    ranzig(frames);
}

@end
