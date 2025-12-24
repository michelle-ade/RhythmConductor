#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(44, 58, 79);

    beatSound.load("beat.mp3");
    beatSound.setMultiPlay(true);

    nocturne.load("nocturne.mp3");
    nocturne.setMultiPlay(false);
    
    ofDrawBitmapString("Press SPACE to play Nocturne", 200, 100);
}

//--------------------------------------------------------------
void ofApp::update(){
    //Get Playhead Pos for timing
    nocturne.getPositionMS();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("Press SPACE to play Nocturne. Press F to hit the drum.", 50, 50);

    string fpsStr = "FPS: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(fpsStr, 900, 50);

    string musicPos = "Track Time: " + ofToString(nocturne.getPositionMS(), 2);
    ofDrawBitmapString(musicPos, 50, 75);

    if (fDown) {
        ofDrawBitmapString("BEAT", 300, 300);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        //Play Music
        nocturne.play();
    }
    
    if (key == 'f') {
        //Play Beat Sound
        beatSound.play();
        fDown = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 'f') {
        fDown = false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
