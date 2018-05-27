// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.

// This sample illustrates how to interface with multiple Myo armbands and distinguish between them.

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstdlib>
#include <myo/myo.hpp>
#include <AVFoundation/AVFoundation.h>
#include "OurAudioWrapper.h"
#include <string>
#include "multiple-myos.h"
#import <Cocoa/Cocoa.h>

using namespace myo;

class PrintMyoEvents : public DeviceListener {
    
public:
    std::string gestureRight = "";
    std::string gestureLeft = "";
    std::vector<oaw::OurAudioWrapper*> audioWrappers;
    int *frames;
    
    Quaternion<float> quart[2];
    int roll_w=0, pitch_w=0, yaw_w=0;
    
    int discreteVolume = 0;
    int discreteRate = 0;
    PrintMyoEvents(std::vector<oaw::OurAudioWrapper*> _audioWrappers, int* _frames) {
        audioWrappers = _audioWrappers;
        frames = _frames;
    };
    
    // Every time Myo Connect successfully pairs with a Myo armband, this function will be called.
    //
    // You can rely on the following rules:
    //  - onPair() will only be called once for each Myo device
    //  - no other events will occur involving a given Myo device before onPair() is called with it
    //
    // If you need to do some kind of per-Myo preparation before handling events, you can safely do it in onPair().
    void onPair(Myo* myo, uint64_t timestamp, FirmwareVersion firmwareVersion)
    {
        // Print out the MAC address of the armband we paired with.

        // The pointer address we get for a Myo is unique - in other words, it's safe to compare two Myo pointers to
        // see if they're referring to the same Myo.

        // Add the Myo pointer to our list of known Myo devices. This list is used to implement identifyMyo() below so
        // that we can give each Myo a nice short identifier.
        knownMyos.push_back(myo);

        // Now that we've added it to our list, get our short ID for it and print it out.
        std::cout << "Paired with " << identifyMyo(myo) << "." << std::endl;
    }

    void onPose(Myo* myo, uint64_t timestamp, Pose pose)
    {
        //std::cout << "Myo " << identifyMyo(myo) << " switched to pose " << pose.toString() << "." << std::endl; //pose.toString()
        if(pose.toString().compare("unknown")==0){
            std::cout << "Unknown " << std::endl;
        }
        if(pose.toString().compare("rest")!=0 && pose.toString().compare("unknown")!=0){
            if(identifyMyo(myo)==1){
                gestureLeft = pose.toString();
            }
            if(identifyMyo(myo)==2){
                gestureRight = pose.toString();
            }
        }
        
        
    }

    void onConnect(Myo* myo, uint64_t timestamp, FirmwareVersion firmwareVersion)
    {
        std::cout << "Myo " << identifyMyo(myo) << " has connected." << std::endl;
    }

    void onDisconnect(Myo* myo, uint64_t timestamp)
    {
        std::cout << "Myo " << identifyMyo(myo) << " has disconnected." << std::endl;
    }
    
    void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
    {
        using std::atan2;
        using std::asin;
        using std::sqrt;
        using std::max;
        using std::min;
        // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
        float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
                           1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
        float pitch = asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));
        float yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
                          1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
        // Convert the floating point angles in radians to a scale from 0 to 18.
        roll_w = static_cast<int>((roll + (float)M_PI)/(M_PI * 2.0f) * 18);
        pitch_w = static_cast<int>((pitch + (float)M_PI/2.0f)/M_PI * 18);
        yaw_w = static_cast<int>((yaw + (float)M_PI)/(M_PI * 2.0f) * 18);
        
        if (identifyMyo(myo)==1) {
            discreteVolume = pitch_w;
            float volume = pitch_w/18.0;
            for(int i=0; i<audioWrappers.size(); i++) {
                audioWrappers[i]->setvolume(volume);
            }
            frames[8] = discreteVolume;
        } else {
            discreteRate = pitch_w;
            float norm_pitch = pitch_w/18.0;
            float rate = 0.7 + norm_pitch;
            for(int i=0; i<audioWrappers.size(); i++) {
                audioWrappers[i]->setrate(rate);
            }
            frames[9] = discreteRate;
        }
    }
    

    // This is a utility function implemented for this sample that maps a myo::Myo* to a unique ID starting at 1.
    // It does so by looking for the Myo pointer in knownMyos, which onPair() adds each Myo into as it is paired.
    size_t identifyMyo(Myo* myo) {
        // Walk through the list of Myo devices that we've seen pairing events for.
        for (size_t i = 0; i < knownMyos.size(); ++i) {
            // If two Myo pointers compare equal, they refer to the same Myo device.
            if (knownMyos[i] == myo) {
                return i + 1;
            }
        }

        return 0;
    }
    
    

    // We store each Myo pointer that we pair with in this list, so that we can keep track of the order we've seen
    // each Myo and give it a unique short identifier (see onPair() and identifyMyo() above).
    std::vector<Myo*> knownMyos;
};

int ranzig(int frames[])
{
    const std::string one ="/Users/roberthacker/Documents/GitHub/pointco/sounds/2/1_AuroraBeat_2.wav";
    
    const std::string two ="/Users/roberthacker/Documents/GitHub/pointco/sounds/2/2_ClippingBeatTopper.wav";
    
    const std::string three ="/Users/roberthacker/Documents/GitHub/pointco/sounds/2/3_ContinuumBeat01.wav";
    const std::string four ="/Users/roberthacker/Documents/GitHub/pointco/sounds/2/4_LeftCoastPiano.wav";
    const std::string five ="/Users/roberthacker/Documents/GitHub/pointco/sounds/2/5_LongingStrings01.wav";
    const std::string six ="/Users/roberthacker/Documents/GitHub/pointco/sounds/2/6_BotChordLayers02.wav";
    const std::string seven ="/Users/roberthacker/Documents/GitHub/pointco/sounds/2/7_GospelImprov01.wav";
    const std::string eight ="/Users/roberthacker/Documents/GitHub/pointco/sounds/2/8_DistantMemoriesPiano.wav";
    const std::string nine ="/Users/roberthacker/Documents/GitHub/pointco/sounds/2/9_hackaburg8s.wav";
    
    try {
        Hub hub("com.example.multiple-myos-withGUI");
        oaw::OurAudioWrapper fistAudio(one);
        oaw::OurAudioWrapper spreadAudio(three);
        oaw::OurAudioWrapper doubleTapAudio(five);
        oaw::OurAudioWrapper waveInAudio(seven);
        
        oaw::OurAudioWrapper second_fistAudio(two);
        oaw::OurAudioWrapper second_spreadAudio(four);
        oaw::OurAudioWrapper second_doubleTapAudio(nine);
        oaw::OurAudioWrapper second_waveInAudio(eight);
        
        // Set Locking Policy so it does not lock anything.
        hub.setLockingPolicy(Hub::LockingPolicy::lockingPolicyNone);

        // Instantiate the PrintMyoEvents class we defined above, and attach it as a listener to our Hub.
        std::vector<oaw::OurAudioWrapper*> wrapperVector(8);
        wrapperVector[0] = &fistAudio;
        wrapperVector[1] = &spreadAudio;
        wrapperVector[2] = &doubleTapAudio;
        wrapperVector[3] = &waveInAudio;
        
        wrapperVector[4] = &second_fistAudio;
        wrapperVector[5] = &second_spreadAudio;
        wrapperVector[6] = &second_doubleTapAudio;
        wrapperVector[7] = &second_waveInAudio;
        
        PrintMyoEvents printer(wrapperVector, frames);
        hub.addListener(&printer);
        
        while (1) {
            // Process events for x milliseconds at a time.
            int x = 500;
            hub.run(x);
            
            
            // Left Arm Comands
            if(printer.gestureLeft.compare("fist")==0) {
                fistAudio.makesomenoice();
                std::cout << "Left:  fist started" << std::endl;
                (frames)[0]=1;
            }
            else if(printer.gestureLeft.compare("fingersSpread")==0) {
                spreadAudio.makesomenoice();
                std::cout << "Left:  spread started" << std::endl;
                (frames)[1]=1;
            }
            else if(printer.gestureLeft.compare("doubleTap")==0) {
                doubleTapAudio.makesomenoice();
                std::cout << "Left:  doubleTap started" << std::endl;
                (frames)[2]=1;
            }
            else if(printer.gestureLeft.compare("waveIn")==0) {
                waveInAudio.makesomenoice();
                std::cout << "Left:  waveIn started" << std::endl;
                (frames)[3]=1;
                
            }
            else if(printer.gestureLeft.compare("waveOut")==0) {
                spreadAudio.stopnoice();
                fistAudio.stopnoice();
                doubleTapAudio.stopnoice();
                waveInAudio.stopnoice();
                std::cout << "Left: stopped" << std::endl;
                (frames)[0]=0;
                (frames)[1]=0;
                (frames)[2]=0;
                (frames)[3]=0;
                
            }
            
            //right Arm Comands
            
            if(printer.gestureRight.compare("fist")==0) {
                second_fistAudio.makesomenoice();
                std::cout << "Right: fist started" << std::endl;
                (frames)[4]=1;
            }
            else if(printer.gestureRight.compare("fingersSpread")==0) {
                second_spreadAudio.makesomenoice();
                std::cout << "Right: spread started" << std::endl;
                (frames)[5]=1;
            }
            else if(printer.gestureRight.compare("doubleTap")==0) {
                second_doubleTapAudio.makesomenoice();
                std::cout << "Right: doubleTap started" << std::endl;
                (frames)[6]=1;
            }
            else if(printer.gestureRight.compare("waveIn")==0) {
                second_waveInAudio.makesomenoice();
                std::cout << "Right: waveIn started" << std::endl;
                (frames)[7]=1;
            }
            else if(printer.gestureRight.compare("waveOut")==0) {
                second_spreadAudio.stopnoice();
                second_fistAudio.stopnoice();
                second_doubleTapAudio.stopnoice();
                second_waveInAudio.stopnoice();
                std::cout << "Right: stopped" << std::endl;
                (frames)[4] = 0;
                (frames)[5]=0;
                (frames)[6]=0;
                (frames)[7]=0;
            }
            
            // reset Gestures for next Second action
            printer.gestureLeft = "";
            printer.gestureRight = "";
            
            //frames[8] = printer.discreteVolume;
            //frames[9] = printer.discreteRate;
            
            /*std::cout << "Myo 1 rotation"
            <<" w:" << static_cast<int>(printer.quart[0].w()*100)
            <<" x:"<< static_cast<int>(printer.quart[0].x()*100)
            <<" y:"<<static_cast<int>(printer.quart[0].y()*100)
            <<" z:"<< static_cast<int>(printer.quart[0].z()*100)
            << std::endl;*/
            
            //std::cout << "Myo 1 rotation"
            //<<" roll:" << printer.roll_w
            //<<" pitch:"<< printer.pitch_w
            //<<" yaw:"<< printer.yaw_w
            //<< std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        return 1;
    }
}
