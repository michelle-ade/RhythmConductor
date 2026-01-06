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
    
    ofDrawBitmapString("Press SPACE to play Nocturne", 200, 100);
}

//--------------------------------------------------------------
void ofApp::update(){
    //Get Playhead Pos for timing
    int currentMS = nocturne.getPositionMS();
    //+100ms to all
    //Get Beat Bounds
    int earlyLowerBoundB = beatMS[beatIndex] - 201; //533
    int earlyUpperBoundB = beatMS[beatIndex] - 50; //582

    int perfectLowerBoundB = beatMS[beatIndex] - 51; //583
    int perfectUpperBoundB = beatMS[beatIndex] + 51; //683

    int lateLowerBoundB = beatMS[beatIndex] + 50; //684
    int lateUpperBoundB = beatMS[beatIndex] + 201; //733

    //Get Snare Bounds
    int earlyLowerBoundS = snareMS[snareIndex] - 201;
    int earlyUpperBoundS = snareMS[snareIndex] - 50;

    int perfectLowerBoundS = snareMS[snareIndex] - 51;
    int perfectUpperBoundS = snareMS[snareIndex] + 51;

    int lateLowerBoundS = snareMS[snareIndex] + 50;
    int lateUpperBoundS = snareMS[snareIndex] + 201;

    //how do i make sure these only happen on beat/snare respectively?
    //Move to next beat
    if (currentMS >= lateUpperBoundB + 1) {
        //Player Completely missed
        if (!beatHit) {
            //set rating for current beat to miss
            beatScore = 0;
        }
        else {
            beatHit = false;
        }

        beatIndex++;
        beatRating = " ";
        totalScore += beatScore;
    }

    if (currentMS >= lateUpperBoundS + 1) {
        //Player Completely missed
        if (!snareHit) {
            //set rating for current snare to miss
            snareScore = 0;
        }
        else {
            snareHit = false;
        }

        snareIndex++;
        snareRating = " ";
        totalScore += snareScore;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //Get Playhead Pos for timing
    int currentMS = nocturne.getPositionMS();

    ofSetColor(255, 255, 255);

    string fpsStr = "FPS: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(fpsStr, 900, 50);

    string musicPos = "Track Time: " + ofToString(currentMS, 2);
    ofDrawBitmapString(musicPos, 50, 50);

    string score = "Total Score: " + ofToString(totalScore, 2);
    ofDrawBitmapString(score, 50, 75);

    string beatRateString = "Beat Rating: " + beatRating + "!";
    ofDrawBitmapString(beatRateString, 50, 125);

    string snareRateString = "Snare Rating: " + snareRating + "!";
    ofDrawBitmapString(snareRateString, 50, 150);

    //draw notes based on currentMS and beat/snareMS[beat/snare index]
    ofSetColor(255, 0, 0);
    ofFill();
    //draw frame. notes move from right to left.
    ofDrawCircle(50, 100, 5); //top left
    ofDrawCircle(974, 100, 5); //top right
    ofDrawCircle(50, 718, 5); //bottom left
    ofDrawCircle(974, 718, 5); //bottom right

    //X Bounds: 50 - 974 -> translate directly to MS?
    //Y Bounds: 100 - 718

    if (nocturnePlaying) {
        //Draw Beat Note
            beatDist = beatMS[beatIndex] - currentMS;
            nextBeatDist = beatMS[beatIndex + 1] - currentMS;
            if (beatDist <= 974) {
                ofSetColor(0, 0, 255);
                ofFill();
                ofDrawCircle(beatDist, 500, 10);
            }

            if (nextBeatDist <= 974) {
                ofSetColor(0, 0, 255);
                ofFill();
                ofDrawCircle(nextBeatDist, 500, 10);
            }

            //Draw Snare Note
            snareDist = snareMS[snareIndex] - currentMS;
            nextSnareDist = snareMS[snareIndex + 1] - currentMS;
            if (snareDist <= 974) {
                ofSetColor(0, 255, 255);
                ofFill();
                ofDrawCircle(snareDist, 500, 10);
            }

            if (nextSnareDist <= 974) {
                ofSetColor(0, 255, 255);
                ofFill();
                ofDrawCircle(nextSnareDist, 500, 10);
            }
    }
    

    //Draw Hit Visual Feedback
    if (beatHit) {
        if (beatRating == "early") {
            ofSetColor(255, 128, 0);
        }
        else if (beatRating == "perfect") {
            ofSetColor(0, 255, 0);
        }
        else if (beatRating == "late") {
            ofSetColor(255, 0, 0);
        }
        
        ofFill();
        ofDrawRectangle(50, 500, 50, 50);
    }
    
    if (snareHit) {
        if (snareRating == "early") {
            ofSetColor(225, 128, 0);
        }
        else if (snareRating == "perfect") {
            ofSetColor(0, 255, 0);
        }
        else if (snareRating == "late") {
            ofSetColor(255, 0, 0);
        }

        ofFill();
        ofDrawRectangle(50, 600, 50, 50);
    }

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
    //+100ms to all
    //Get Beat Bounds
    int earlyLowerBoundB = beatMS[beatIndex] - 201; //533
    int earlyUpperBoundB = beatMS[beatIndex] - 100; //582

    int perfectLowerBoundB = beatMS[beatIndex] - 101; //583
    int perfectUpperBoundB = beatMS[beatIndex] + 101; //683

    int lateLowerBoundB = beatMS[beatIndex] + 100; //684
    int lateUpperBoundB = beatMS[beatIndex] + 201; //733

    //Get Snare Bounds
    int earlyLowerBoundS = snareMS[snareIndex] - 201;
    int earlyUpperBoundS = snareMS[snareIndex] - 100;

    int perfectLowerBoundS = snareMS[snareIndex] - 101;
    int perfectUpperBoundS = snareMS[snareIndex] + 101;

    int lateLowerBoundS = snareMS[snareIndex] + 100;
    int lateUpperBoundS = snareMS[snareIndex] + 201;
    
    if (key == ' ') {
        //Play Music
        nocturne.play();

        nocturnePlaying = true;
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
                beatScore = 25;
            }
            //Perfect
            else if (currentMS > perfectLowerBoundB && currentMS < perfectUpperBoundB) {
                //testRate = PERFECT;
                beatRating = "perfect";
                beatHit = true;
                beatScore = 50;
            }
            //Late
            else if (currentMS > lateLowerBoundB && currentMS < lateUpperBoundB) {
                //testRate = LATE;
                beatRating = "late";
                beatHit = true;
                beatScore = 25;
            }
            //Miss
            else {
                //testRate = MISS;
                beatRating = "miss";
                beatHit = true;
                beatScore = 0;
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
                snareScore = 25;
            }
            //Perfect
            else if (currentMS > perfectLowerBoundS && currentMS < perfectUpperBoundS) {
                //testRate = PERFECT;
                snareRating = "perfect";
                snareHit = true;
                snareScore = 50;
            }
            //Late
            else if (currentMS > lateLowerBoundS && currentMS < lateUpperBoundS) {
                //testRate = LATE;
                snareRating = "late";
                snareHit = true;
                snareScore = 25;
            }
            //Miss
            else {
                //testRate = MISS;
                snareRating = "miss";
                snareHit = true;
                snareScore = 0;
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
