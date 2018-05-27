//
//  OurAudio.m
//  multiple-myos
//
//  Created by Robert Häcker on 26.05.18.
//  Copyright © 2018 Thalmic Labs. All rights reserved.
//

#import "OurAudio.h"

@implementation OurAudio



-(void) makesomenoice
{
    if([_audioPlayer isPlaying]) {
        // Do not start playing again if currently playing
        return;
    }
    
    [_audioPlayer play];
}

-(void) stopnoice
{
    [_audioPlayer stop];
}

-(void) setvolume:(float)vol
{
    _audioPlayer.volume = vol;
}

-(void) setrate:(float)rate
{
    _audioPlayer.enableRate=true;
    _audioPlayer.rate=rate;
}

-(id) initWithString:(NSString *)musicfile
{
    self = [super init];
    if (self) {
        NSURL *soundUrl = [NSURL fileURLWithPath:musicfile];
        
        // Create audio player object and initialize with URL to sound
        NSError *error;
        _audioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:soundUrl error:&error];
        if(error) {
            NSLog(@"Error %@", error);
        }
        
        _audioPlayer.numberOfLoops = 1000;
        
    }
    return self;
}




@end
