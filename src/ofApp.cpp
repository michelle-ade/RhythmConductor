#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(44, 58, 79);

    //load sounds
    beatSound.load("beat.mp3");
    beatSound.setMultiPlay(true);

    snareSound.load("snare.mp3");
    beatSound.setMultiPlay(true);

    nocturne.load("nocturne.mp3");
    nocturne.setMultiPlay(false);

    //load images
    testimg.load("testimg.png");
    backgroundImg.load("background.png");
    trebleImg.load("trebleClef.png");
    bassImg.load("bassClef.png");

    perfectImg.load("perfect.png");
    earlyImg.load("early.png");
    lateImg.load("late.png");
    missImg.load("miss.png");

    okPerformance.load("ok.png");
    greatPerformance.load("great.png");
    badPerformance.load("bad.png");
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

    //Check Performance
    if (performanceCounter >= 5) {
        performance -= 2;
        performanceCounter = 0;
    }
    //how do i make sure these only happen on beat/snare respectively?
    //Move to next beat
    if (currentMS >= lateUpperBoundB + 1) {
        //Player Completely missed
        if (!beatHit) {
            //set rating for current beat to miss
            beatScore = 0;
            performanceCounter++;
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
            performanceCounter++;
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

    //check performance
    if (performance > 7) {
        performanceImg = greatPerformance;
    }
    else if (performance > 3) {
        performanceImg = okPerformance;
    }
    else {
        performanceImg = badPerformance;
    }

    //draw background first
    backgroundImg.draw(0, 0);
    performanceImg.draw(0, 0);

    string fpsStr = "FPS: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(fpsStr, 900, 50);

    string musicPos = "Track Time: " + ofToString(currentMS, 2);
    ofDrawBitmapString(musicPos, 50, 25);

    string score = "Total Score: " + ofToString(totalScore, 2);
    ofDrawBitmapString(score, 50, 50);

    string beatRateString = "Beat (F) Rating: " + beatRating + "!";
    ofDrawBitmapString(beatRateString, 200, 25);

    string snareRateString = "Snare (J) Rating: " + snareRating + "!";
    ofDrawBitmapString(snareRateString, 200, 50);

    //draw notes based on currentMS and beat/snareMS[beat/snare index]
    ofSetColor(255, 0, 0);
    ofFill();

    /*
    //draw frame. notes move from right to left.
    ofDrawCircle(25, 500, 5); //top left
    ofDrawCircle(999, 500, 5); //top right
    ofDrawCircle(25, 743, 5); //bottom left
    ofDrawCircle(999, 743, 5); //bottom right
    */

    //X Bounds: 50 - 974 -> translate directly to MS?
    //Y Bounds: 100 - 718
    
    //draw images
    ofSetColor(0, 0, 0);
    //testimg.draw(50, 300);

    //draw stave lines
    ofSetLineWidth(3);
    ofDrawLine(25, 575, 999, 575);
    ofDrawLine(25, 668, 999, 668);

    ofSetColor(255, 255, 255);
    //draw rating
    if (beatHit) {
        beatRatingImg.draw(250, 300);
    }

    if (snareHit) {
        snareRatingImg.draw(250, 350);
    }
    

    if (nocturnePlaying) {
        //Draw Beat Note
        if (beatHit) {
            ofSetColor(0, 0, 0);
            ofSetLineWidth(3);
            ofDrawLine(beatHitTime+50, 575, beatHitTime+50, 668);
        }
        else {
            beatDist = beatMS[beatIndex] - currentMS + beatOffset;
            if (beatDist <= 974 + beatOffset) {
                ofFill();
                ofSetColor(0, 0, 0);
                ofDrawCircle(beatDist, 575, 30);

                ofSetColor(255, 255, 255);
                ofDrawCircle(beatDist, 575, 20);
            }
        }

        nextBeatDist = beatMS[beatIndex + 1] - currentMS + beatOffset;
        if (nextBeatDist <= 974 + beatOffset) {
            ofFill();
            ofSetColor(0, 0, 0);
            ofDrawCircle(nextBeatDist, 575, 30);

            ofSetColor(255, 255, 255);
            ofDrawCircle(nextBeatDist, 575, 20);
        }
        

        if (snareHit) {
            ofSetColor(255, 255, 255);
            ofSetLineWidth(3);
            ofDrawLine(snareHitTime+beatOffset, 575, snareHitTime+beatOffset, 668);
        } else {
            //Draw Snare Note
            snareDist = snareMS[snareIndex] - currentMS + beatOffset;
            if (snareDist <= 974 + beatOffset) {
                ofFill();
                ofSetColor(255, 255, 255);
                ofDrawCircle(snareDist, 668, 30);

                ofSetColor(0, 0, 0);
                ofDrawCircle(snareDist, 668, 20);
            }
        }

        nextSnareDist = snareMS[snareIndex + 1] - currentMS + beatOffset;
        int nextNextSnareDist = snareMS[snareIndex + 2] - currentMS + beatOffset;

        if (nextSnareDist <= 974+beatOffset) {
            ofFill();
            ofSetColor(255, 255, 255);
            ofDrawCircle(nextSnareDist, 668, 30);

            ofSetColor(0, 0, 0);
            ofDrawCircle(nextSnareDist, 668, 20);
        }

        if (nextNextSnareDist <= 974 + beatOffset) {
            ofFill();
            ofSetColor(255, 255, 255);
            ofDrawCircle(nextNextSnareDist, 668, 30);
            
            ofSetColor(0, 0, 0);
            ofDrawCircle(nextNextSnareDist, 668, 20);
        }
    }

    //Draw Stave Symbols
    ofSetColor(255, 255, 255);
    trebleImg.draw(25, 514);
    bassImg.draw(25, 623);
    
    //Draw Hit Visual Feedback
    /*if (beatHit) {
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
    }*/
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
                beatRatingImg = earlyImg;
                beatHitTime = beatMS[beatIndex] - currentMS;
                performance += 1;
                performanceCounter++;
            }
            //Perfect
            else if (currentMS > perfectLowerBoundB && currentMS < perfectUpperBoundB) {
                //testRate = PERFECT;
                beatRating = "perfect";
                beatHit = true;
                beatScore = 50;
                beatRatingImg = perfectImg;
                beatHitTime = beatMS[beatIndex] - currentMS;
                performance += 2;
                performanceCounter++;
            }
            //Late
            else if (currentMS > lateLowerBoundB && currentMS < lateUpperBoundB) {
                //testRate = LATE;
                beatRating = "late";
                beatHit = true;
                beatScore = 25;
                beatRatingImg = lateImg;
                beatHitTime = beatMS[beatIndex] - currentMS;
                performance += 1;
                performanceCounter++;
            }
            //Miss
            else {
                //testRate = MISS;
                beatRating = "miss";
                beatHit = true;
                beatScore = 0;
                beatRatingImg = missImg;
                performanceCounter++;
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
                snareRatingImg = earlyImg;
                snareHitTime = snareMS[snareIndex] - currentMS;
                performance += 1;
                performanceCounter++;
            }
            //Perfect
            else if (currentMS > perfectLowerBoundS && currentMS < perfectUpperBoundS) {
                //testRate = PERFECT;
                snareRating = "perfect";
                snareHit = true;
                snareScore = 50;
                snareRatingImg = perfectImg;
                snareHitTime = snareMS[snareIndex] - currentMS;
                performance += 2;
                performanceCounter++;
            }
            //Late
            else if (currentMS > lateLowerBoundS && currentMS < lateUpperBoundS) {
                //testRate = LATE;
                snareRating = "late";
                snareHit = true;
                snareScore = 25;
                snareRatingImg = lateImg;
                snareHitTime = snareMS[snareIndex] - currentMS;
                performance += 1;
                performanceCounter++;
            }
            //Miss
            else {
                //testRate = MISS;
                snareRating = "miss";
                snareHit = true;
                snareScore = 0;
                snareRatingImg = missImg;
                performanceCounter++;
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
