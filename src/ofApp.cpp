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
    int currentMS = nocturne.getPositionMS();

    //Get Bounds
    int earlyLowerBound = beatMS[beatIndex] - 101;
    int earlyUpperBound = beatMS[beatIndex] - 50;

    int perfectLowerBound = beatMS[beatIndex] - 51;
    int perfectUpperBound = beatMS[beatIndex] + 51;

    int lateLowerBound = beatMS[beatIndex] + 50;
    int lateUpperBound = beatMS[beatIndex] + 101;

    //Check Beat

    //Early
    if (currentMS > earlyLowerBound && currentMS < earlyUpperBound) {
        testRate = EARLY;
    } 
    //Perfect
    else if (currentMS > perfectLowerBound && currentMS < perfectUpperBound) {
        testRate = PERFECT;
    } 
    //Late
    else if (currentMS > lateLowerBound && currentMS < lateUpperBound) {
        testRate = LATE;
    }
    //Miss
    else {
        testRate = MISS;
    }

    if (currentMS >= lateUpperBound + 1) {
        beatIndex++;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("Press SPACE to play Nocturne. Press F to hit the drum.", 50, 50);

    string fpsStr = "FPS: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(fpsStr, 900, 50);

    string musicPos = "Track Time: " + ofToString(nocturne.getPositionMS(), 2);
    ofDrawBitmapString(musicPos, 50, 75);

    string enumString;
    //Convert Enum to String
    if (testRate = EARLY) {
        enumString = "Early...";
    }
    else if (testRate = PERFECT) {
        enumString = "Perfecto!";
    }
    else if (testRate = LATE) {
        enumString = "Late...";
    }
    else {
        enumString = "Missed!!!";
    }

    string testRateString = "Beat Rating: " + enumString + "!";
    ofDrawBitmapString(testRateString, 50, 200);

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
