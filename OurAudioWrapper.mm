//
//  OurAudioWrapper.cpp
//  multiple-myos
//
//  Created by Robert Häcker on 26.05.18.
//  Copyright © 2018 Thalmic Labs. All rights reserved.
//
#include "OurAudioWrapper.h"
#import "OurAudio.h"
//#include <string>

namespace oaw {
    struct OurAudioImpl {
        OurAudio* wrapped;
    };
    
    OurAudioWrapper::OurAudioWrapper(std::string musicpath) : impl(new OurAudioImpl) {
        // Convert c++ string to NSString*
        NSString* musicpath_ns = [NSString stringWithUTF8String:musicpath.c_str()];
        impl->wrapped = [[OurAudio alloc] initWithString:musicpath_ns];
    }
    
    OurAudioWrapper::~OurAudioWrapper() {
        if(impl)
            [impl->wrapped release];
        delete impl;
    }
    
    void OurAudioWrapper::makesomenoice() {
        [impl->wrapped makesomenoice];
    }
    void OurAudioWrapper::stopnoice() {
        [impl->wrapped stopnoice];
    }
    
    void OurAudioWrapper::setvolume(float vol) {
        [impl->wrapped setvolume:vol];
    }
    
    void OurAudioWrapper::setrate(float rate) {
        [impl->wrapped setrate:rate];
    }
}
