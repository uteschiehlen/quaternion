**This readme is copied over form the Devpost submission. For details please see: https://devpost.com/software/quaternion/**

## Inspiration
Music is a shared human experience that everybody can enjoy. However, getting good at it takes tons of time and many people are simply to busy to master an instrument. What if you could compose the perfect soundtrack for your life with just your hands?
## What it does
Employing two myo wristbands we recognize gestures of both hands and link them to music samples. You can compose your own tunes step-by-step by selecting the samples that you feel belong there.
In order to make things even more interesting, you can also dynamically control the volume and the speed of your creation by simply moving your arm up and down.
But I am with friends?! Even better, friends that jam together stay together. Just give one of the controllers to your friend and you're all set for a unique collaborative experience.
You are always in control of what's going on: It's all just one glance onto the dashboard away.
## How we built it
All the low-level stuff with gestures and processing tracking data etc. is done in C++. This interacts with the Cocoa app via an Objective-C wrapper.
## Challenges we ran into
Getting the audio output to work

Turns out it is not as easy to mix Objective-C and C++ as _Objective C++ input file_ suggests - (ever heard of PIMPL?)

MacOS sandboxing only applies to GUI applications and not to console ones

A quaternion ain't your usual (X,Y,Z) coordiantes
## Accomplishments that we're proud of
Our intuitive user experience

How well our samples go with each other making it easy to get an amazing tune
## What we learned
We figured out how to built our first MacOS X app ever

Objective-C sure loves brackets :]

Your neighbors don't appreciate you debugging an application that makes sounds all the time that much

## What's next for Quaternion
We'd love to let even more people be part of your experience. All we need are more controllers (How about a hundred?).
