//
//  OurAudio.h
//  multiple-myos
//
//  Created by Robert Häcker on 26.05.18.
//  Copyright © 2018 Thalmic Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@interface OurAudio : NSObject
    {
     AVAudioPlayer *_audioPlayer;
    }
- (void) makesomenoice;
- (void) stopnoice;
- (void) setvolume:(float)vol;
- (void) setrate:(float)rate;
- (id) initWithString:(NSString*)musicfile;
    
    
    @end;
