#pragma once

#include "ofMain.h"
#include "ofxSimpleTimer.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();

    
    ofxSimpleTimer timer1 ; // background music
    ofxSimpleTimer timer2 ; // entrance song for flan
    ofxSimpleTimer timer3 ; // sensing conductivity

    
    void timer1CompleteHandler( int &args ) ;
    void timer2CompleteHandler( int &args ) ;
    void timer3CompleteHandler( int &args ) ;
    
    void timer1PauseHandler( int &args ) ;
    void timer2PauseHandler( int &args ) ;
    void timer3PauseHandler( int &args ) ;
    
    void timer1StartedHandler( int &args ) ;
    void timer2StartedHandler( int &args ) ;
    void timer3StartedHandler( int &args ) ;

    
    ofSoundPlayer music1;
    ofSoundPlayer music2;
    
    ofSerial serial;
    int byteIn;
    float mapByteIn;
    
    ofTrueTypeFont		font;
    
    int ledPin = 11;
  
    bool bSendSerialMessage;
    bool lightUp;
    bool noLight;
    
    float increment = 0;
    
    bool readVolume;
    
};
