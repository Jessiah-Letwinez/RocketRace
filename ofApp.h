#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup() override;
	void update() override;
	void draw() override;

	void keyPressed(int key) override;
	void keyReleased(int key) override;
	void mousePressed(int x, int y, int button) override;

	std::string getPlayerScoreText(int firstScore, int secondScore);

	bool menu = true;
	bool rules = false;
	bool game = false;

	int cometRadius = 5;
	int yPosLeft[25] = {};
	int yPosRight[25] = {};
	int xPosLeft[25] = {};
	int xPosRight[25] = {};

	bool wPressed{false};
	bool sPressed{false};
	bool upPressed{false};
	bool downPressed{false};
	bool rPressed{false};

	int rockets[2] = {425, 425};

	int firstCounter = 0;
	int secondCounter = 0;

	int firstLeft = 0;
	int firstRight = 0;

	int secondLeft = 0;
	int secondRight = 0;

	int counter = 0;
	int timer = 0;

	ofTrueTypeFont titleFont;
	ofTrueTypeFont rulesTextFont;
	ofTrueTypeFont menuFont;
	ofTrueTypeFont rulesFont;
	ofTrueTypeFont text;
	ofTrueTypeFont score;
	int fontSize = 18;
	int menuSize = 30;
	int titleSize = 64;
	ofRectangle textBoundingBox;

	ofSoundPlayer baseBeat;
	ofSoundPlayer goalBeep;
	ofSoundPlayer hitBeep;

	int w = 150;
	int h = 50;


	//---------------------------------------------------


};
