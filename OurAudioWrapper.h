//
//  OurAudioWrapper.h
//  multiple-myos
//
//  Created by Robert Häcker on 26.05.18.
//  Copyright © 2018 Thalmic Labs. All rights reserved.
//

#ifndef OurAudioWrapper_h
#define OurAudioWrapper_h
#import "OurAudio.h"
#include <string>
namespace oaw {
    struct OurAudioImpl;
    class OurAudioWrapper {
        OurAudioImpl* impl;
        public:
        OurAudioWrapper(std::string musicpath);
            ~OurAudioWrapper();
            void makesomenoice();
            void stopnoice();
            void setvolume(float vol);
            void setrate(float rate);
    };
}

#endif /* OurAudioWrapper_h */
