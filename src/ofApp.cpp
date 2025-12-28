#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(44, 58, 79);

    beatSound.load("beat.mp3");
    beatSound.setMultiPlay(true);

    snareSound.load("snare.mp3");
    beatSound.setMultiPlay(true);

    nocturne.load("nocturne.mp3");
    nocturne.setMultiPlay(false);

    beatHit = false;
    snareHit = false;
    
    ofDrawBitmapString("Press SPACE to play Nocturne", 200, 100);
}

//--------------------------------------------------------------
void ofApp::update(){
    //Get Playhead Pos for timing
    int currentMS = nocturne.getPositionMS();

    //Get Beat Bounds
    int earlyLowerBoundB = beatMS[beatIndex] - 101;
    int earlyUpperBoundB = beatMS[beatIndex] - 50;

    int perfectLowerBoundB = beatMS[beatIndex] - 51;
    int perfectUpperBoundB = beatMS[beatIndex] + 51;

    int lateLowerBoundB = beatMS[beatIndex] + 50;
    int lateUpperBoundB = beatMS[beatIndex] + 101;

    //Get Snare Bounds
    int earlyLowerBoundS = snareMS[snareIndex] - 101;
    int earlyUpperBoundS = snareMS[snareIndex] - 50;

    int perfectLowerBoundS = snareMS[snareIndex] - 51;
    int perfectUpperBoundS = snareMS[snareIndex] + 51;

    int lateLowerBoundS = snareMS[snareIndex] + 50;
    int lateUpperBoundS = snareMS[snareIndex] + 101;

    //Move to next beat
    if (currentMS >= lateUpperBoundB + 1) {
        //Player Completely missed
        if (!beatHit) {
            //set rating for current beat to miss
        }
        else {
            beatHit = false;
        }

        beatIndex++;
        beatRating = " ";
    }

    if (currentMS >= lateUpperBoundS + 1) {
        //Player Completely missed
        if (!snareHit) {
            //set rating for current snare to miss
        }
        else {
            snareHit = false;
        }

        snareIndex++;
        snareRating = " ";
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("Press SPACE to play Nocturne. Press F to hit the drum.", 50, 50);

    string fpsStr = "FPS: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(fpsStr, 900, 50);

    string musicPos = "Track Time: " + ofToString(nocturne.getPositionMS(), 2);
    ofDrawBitmapString(musicPos, 50, 75);

    string beatRateString = "Beat Rating: " + beatRating + "!";
    ofDrawBitmapString(beatRateString, 50, 200);

    string snareRateString = "Snare Rating: " + snareRating + "!";
    ofDrawBitmapString(snareRateString, 50, 225);

    if (fDown) {
        ofDrawBitmapString("BEAT", 300, 300);
    }
    if (jDown) {
        ofDrawBitmapString("SNARE", 400, 400);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //Get Playhead Pos for timing
    int currentMS = nocturne.getPositionMS();

    //Get Beat Bounds
    int earlyLowerBoundB = beatMS[beatIndex] - 101; //533
    int earlyUpperBoundB = beatMS[beatIndex] - 50; //582

    int perfectLowerBoundB = beatMS[beatIndex] - 51; //583
    int perfectUpperBoundB = beatMS[beatIndex] + 51; //683

    int lateLowerBoundB = beatMS[beatIndex] + 50; //684
    int lateUpperBoundB = beatMS[beatIndex] + 101; //733

    //Get Snare Bounds
    int earlyLowerBoundS = snareMS[snareIndex] - 101;
    int earlyUpperBoundS = snareMS[snareIndex] - 50;

    int perfectLowerBoundS = snareMS[snareIndex] - 51;
    int perfectUpperBoundS = snareMS[snareIndex] + 51;

    int lateLowerBoundS = snareMS[snareIndex] + 50;
    int lateUpperBoundS = snareMS[snareIndex] + 101;
    
    if (key == ' ') {
        //Play Music
        nocturne.play();
    }
    
    if (key == 'f') {
        //Play Beat Sound
        beatSound.play();
        fDown = true;

        //Check Beat Timing
     
        // First Check the currentMS is even close enough to the beat to count
        if (currentMS > earlyLowerBoundB) {

            //Early
            if (currentMS > earlyLowerBoundB && currentMS < earlyUpperBoundB) {
                //testRate = EARLY;
                beatRating = "early";
                beatHit = true;
            }
            //Perfect
            else if (currentMS > perfectLowerBoundB && currentMS < perfectUpperBoundB) {
                //testRate = PERFECT;
                beatRating = "perfect";
                beatHit = true;
            }
            //Late
            else if (currentMS > lateLowerBoundB && currentMS < lateUpperBoundB) {
                //testRate = LATE;
                beatRating = "late";
                beatHit = true;
            }
            //Miss
            else {
                //testRate = MISS;
                beatRating = "miss";
                beatHit = true;
            }
        } 
        else {
            //too soon to consider this note. do nothing
            beatRating = " ";
        }
    }

    if (key == 'j') {
        //Play Snare Sound
        snareSound.play();
        jDown = true;

        //Check Snare Timing

        // First Check the currentMS is even close enough to the snare to count
        if (currentMS > earlyLowerBoundS) {

            //Early
            if (currentMS > earlyLowerBoundS && currentMS < earlyUpperBoundS) {
                //testRate = EARLY;
                snareRating = "early";
                snareHit = true;
            }
            //Perfect
            else if (currentMS > perfectLowerBoundS && currentMS < perfectUpperBoundS) {
                //testRate = PERFECT;
                snareRating = "perfect";
                snareHit = true;
            }
            //Late
            else if (currentMS > lateLowerBoundS && currentMS < lateUpperBoundS) {
                //testRate = LATE;
                snareRating = "late";
                snareHit = true;
            }
            //Miss
            else {
                //testRate = MISS;
                snareRating = "miss";
                snareHit = true;
            }
        }
        else {
            //too soon to consider this note. do nothing
            snareRating = " ";
        }

    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 'f') {
        fDown = false;
    }

    if (key == 'j') {
        jDown = false;
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
