#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//global variables set up
		//set up sound
		ofSoundPlayer beatSound;
		ofSoundPlayer snareSound;
		ofSoundPlayer nocturne;

		//set up images
		ofImage testimg;
		ofImage backgroundImg;
		ofImage trebleImg;
		ofImage bassImg;

		ofImage perfectImg;
		ofImage earlyImg;
		ofImage lateImg;
		ofImage missImg;
		ofImage beatRatingImg;
		ofImage snareRatingImg;

		ofImage okPerformance;
		ofImage greatPerformance;
		ofImage badPerformance;
		ofImage performanceImg;

		bool fDown;
		bool jDown;
		bool nocturnePlaying = false;

		//arrays of correct milliseconds for beat and snare
		int beatMS[21] = { 633, 1533, 4700, 6733, 8766, 
						10100, 10400, 10900, 12400, 13900,
						15733, 17233, 18833, 20366, 22366, 
						22966, 23600, 24366, 25000, 25666,
						26466};

		int snareMS[12] = { 4133, 5166, 8033, 9800, 10300,
							10500, 11833, 15200, 18266, 24733,
							25200, 26066};

		int beatIndex = 0;
		int snareIndex = 0;
		//33 hits total for nocturne

		enum hitRating {
			EARLY, //-100ms to -50ms
			PERFECT, //within 50ms
			LATE, //+50ms to +100ms
			MISS, //anything else
			DEBUG
		};

		int beatScore;
		int snareScore;
		int totalScore = 0;
		int performanceCounter = 0;
		int performance = 0; //5-note performance
		hitRating testRate = DEBUG;
		string beatRating = "No Rating Yet";
		string snareRating = "No Rating Yet";
		bool beatHit = false;
		bool snareHit = false;
		int beatHitTime;
		int snareHitTime;
		int beatDist;
		int nextBeatDist;
		int snareDist;
		int nextSnareDist;
		int beatOffset = 50;
};
