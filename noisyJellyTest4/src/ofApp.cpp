#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    
    ofSetVerticalSync(true);
	
	ofBackground(34);
	ofSetLogLevel(OF_LOG_VERBOSE);
    
    timer1.setup(15000) ;
    timer2.setup(5000) ;
    timer3.setup(245000);
//    timer1.setup(5000) ;
//    timer2.setup(5000) ;
//    timer3.setup(10000);
    
    ofAddListener( timer1.TIMER_COMPLETE , this, &ofApp::timer1CompleteHandler ) ;
    ofAddListener( timer2.TIMER_COMPLETE , this, &ofApp::timer2CompleteHandler ) ;
    ofAddListener( timer3.TIMER_COMPLETE , this, &ofApp::timer3CompleteHandler );
    
    ofAddListener( timer1.TIMER_PAUSED , this, &ofApp::timer1PauseHandler ) ;
    ofAddListener( timer2.TIMER_PAUSED , this, &ofApp::timer2PauseHandler ) ;
    ofAddListener( timer3.TIMER_PAUSED , this, &ofApp::timer3PauseHandler ) ;
    
    ofAddListener( timer1.TIMER_STARTED , this, &ofApp::timer1StartedHandler ) ;
    ofAddListener( timer2.TIMER_STARTED , this, &ofApp::timer2StartedHandler ) ;
    ofAddListener( timer3.TIMER_STARTED , this, &ofApp::timer3StartedHandler ) ;
    
    serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    int baud = 9600;
	serial.setup(0, baud);
    serial.setup("/dev/tty.usbmodem1421", baud);
    
    music1.loadSound("music1.mp3");
    music2.loadSound("music2.mp3");
    music1.setVolume(0.3);
    music1.play();
    
    noLight = true;
    timer1.start(false) ;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSoundUpdate();
    
    timer1.update();
    timer2.update();
    timer3.update();

    int byteIn = serial.readByte();
    
    if(readVolume){

        if( byteIn == OF_SERIAL_NO_DATA || byteIn == OF_SERIAL_ERROR){
        
        }else{
            mapByteIn = ofMap(byteIn,0,255,0,1);
            music2.setVolume(MIN(mapByteIn,1));
            cout << "Mapped Byte :" << mapByteIn << endl;
//            if(!music1.getIsPlaying()){
//                music1.play();
//                
//            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofSetColor(0);
    timer1.draw( 15 , 15 ) ;
    timer2.draw( ofGetWidth() *2/3 - 100 , 15 ) ;
    timer3.draw( ofGetWidth() - 100 , 15 ) ;
    
    if(serial.available()){
        
        if (bSendSerialMessage){
            
            if (increment >= 0){
                increment += 10;
                increment = ofClamp(increment, 0,255);
                serial.writeByte(increment);
                cout << "Writing Byte: " << increment << endl;
                ofSetColor(increment,0,0);
                ofEllipse(100,100,100,100);
//                serial.flush();
            }
        }
        
        if (lightUp){
            serial.writeByte(255);
            cout << "lightUp" << endl;
            ofSetColor(255,0,0);
            ofEllipse(100,100,100,100);
//            serial.flush();
        }
        
        if (noLight){
            serial.writeByte(0);
            cout << "noLight" << endl;
            ofSetColor(0,0,0);
            ofEllipse(100,100,100,100);
//            serial.flush();
        }
        
    }

    
}


void ofApp::timer1CompleteHandler( int &args ) //light incrememnt
{

    timer2.start(false);
    music1.stop();
    music2.setVolume(0.5);
    music2.play();

    bSendSerialMessage = true;
    increment = 0;
    lightUp = false;
    noLight = false;
    
    
}

void ofApp::timer2CompleteHandler( int &args ) //full light up
{

    timer3.start(false);
    music1.stop();
    
    readVolume = true;

    bSendSerialMessage = false;
    lightUp = true;
    noLight = false;
    
    music1.stop();

    
}

void ofApp::timer3CompleteHandler( int &args ) //dark
{
    
    timer1.start(false);
    readVolume = false;
    music2.stop();
    music1.setVolume(0.2);
    music1.play();

    bSendSerialMessage = false;
    lightUp = false;
    noLight = true;
    
}


void ofApp::timer1PauseHandler( int &args ) {
    cout<<"TIMER1 PAUSED"<<endl;
    
}
void ofApp::timer2PauseHandler( int &args ) {
    cout<<"TIMER2 PAUSED"<<endl;
    
}
void ofApp::timer3PauseHandler( int &args ) {
    cout<<"TIMER3 PAUSED"<<endl;
    
}

void ofApp::timer1StartedHandler( int &args ) {
    cout<<"TIMER1 STARTED"<<endl;
    timer2.togglePause();
}
void ofApp::timer2StartedHandler( int &args ) {
    cout<<"TIMER2 STARTED"<<endl;
    timer1.togglePause();
}
void ofApp::timer3StartedHandler( int &args ) {
    cout<<"TIMER2 STARTED"<<endl;
    timer1.togglePause();
}