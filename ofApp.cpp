#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("Rocket Race");
	ofSetWindowShape(500, 500);
	ofSetFrameRate(60);

	//loads text
	titleFont.load(ofToDataPath("genos.ttf"), titleSize);
	menuFont.load(ofToDataPath("genos.ttf"), menuSize);
	rulesFont.load(ofToDataPath("genos.ttf"), menuSize);
	rulesTextFont.load(ofToDataPath("genos.ttf"), fontSize);
	text.load(ofToDataPath("genos.ttf"), fontSize);
	score.load(ofToDataPath("genos.ttf"), fontSize);

	//loads music and sounds
	baseBeat.load("baseBeat.mp3");
	baseBeat.setVolume(0.4f);
	goalBeep.load("goalBeep.mp3");
	goalBeep.setVolume(0.4f);
	hitBeep.load("hitBeep.mp3");
	hitBeep.setVolume(0.4f);
	//baseBeat.play();


	firstLeft = ofGetWidth() / 4;
	firstRight = firstLeft + 20;

	secondLeft = ofGetWidth() - ofGetWidth() / 4;
	secondRight = secondLeft + 20;

	//randomizes meteor position
	for (int i = 0; i < 25; i++) {
		yPosLeft[i] = ofRandom(cometRadius, ofGetHeight() - 100);
		xPosLeft[i] = ofRandom(-ofGetWidth(), -cometRadius);
		yPosRight[i] = ofRandom(cometRadius, ofGetHeight() - 100);
		xPosRight[i] = ofRandom(ofGetWidth(), ofGetWidth() * 2);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	if (baseBeat.isPlaying() == false) {
		baseBeat.play();
	}

	if (game) {
		for (int j = 0; j < 25; j++) {
			xPosLeft[j] += 1;
			xPosRight[j] -= 1;
			if (xPosLeft[j] > ofGetWidth()) {
				xPosLeft[j] = ofRandom(-ofGetWidth(), -cometRadius);
			}
			if (xPosRight[j] < 0) {
				xPosRight[j] = ofRandom(ofGetWidth(), ofGetWidth() * 2);
			}
		}

		if (wPressed) {
			rockets[0] -= 1.5;
		}
		if (sPressed) {
			rockets[0] += 2;
		}
		if (upPressed) {
			rockets[1] -= 1.5;
		}
		if (downPressed) {
			rockets[1] += 2;
		}

		ofFill();

		counter++;
		if (counter == 60) {
			timer++;
			counter = 0;
		}
	}
	else {
		timer = 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	if (menu) {
		ofFill();
		//ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

		ofSetColor(255);
		ofDrawRectangle(ofGetWidth() / 2 - w / 2, ofGetHeight() - (h + 175), w, h);
		ofDrawRectangle(ofGetWidth() / 2 - w / 2, ofGetHeight() - (h + 100), w, h);

		std::string rocketText;
		std::string raceText;
		rocketText = "ROCKET";
		raceText = "RACE";
		textBoundingBox = titleFont.getStringBoundingBox(rocketText, ofGetWidth() / 2 - w / 2, ofGetHeight());
		int rocketTextOffsetX = textBoundingBox.width / 2;
		int rocketTextOffsetY = textBoundingBox.height / 2;
		titleFont.drawString(rocketText, ofGetWidth() / 2 - rocketTextOffsetX,
		                     ofGetHeight() - (rocketTextOffsetY + 400));
		textBoundingBox = titleFont.getStringBoundingBox(raceText, ofGetWidth() / 2 - w / 2, ofGetHeight());
		int raceTextOffsetX = textBoundingBox.width / 2;
		int raceTextOffsetY = textBoundingBox.height / 2;
		titleFont.drawString(raceText, ofGetWidth() / 2 - raceTextOffsetX,
		                     ofGetHeight() - (raceTextOffsetY + 350));

		ofSetColor(100);
		std::string menuText;
		menuText = "PLAY";
		textBoundingBox = menuFont.getStringBoundingBox(menuText, ofGetWidth() / 2 - w / 2, ofGetHeight() - h * 4.5);
		int menuTextOffsetX = textBoundingBox.width / 2;
		int menuTextOffsetY = textBoundingBox.height / 2;
		menuFont.drawString(menuText, ofGetWidth() / 2 - menuTextOffsetX,
		                    ofGetHeight() - menuTextOffsetY - (h + 130));
		std::string rulesText;
		rulesText = "RULES";
		textBoundingBox = rulesFont.getStringBoundingBox(rulesText, ofGetWidth() / 2 - w / 2, ofGetHeight() - h * 3);
		int rulesTextOffsetX = textBoundingBox.width / 2;
		int rulesTextOffsetY = textBoundingBox.height / 2;
		rulesFont.drawString(rulesText, ofGetWidth() / 2 - rulesTextOffsetX,
		                     ofGetHeight() - rulesTextOffsetY - (h + 55));
	}

	if (rules) {
		ofSetColor(0);
		ofFill();
		ofSetColor(255);
		std::string rulesTitleText;
		rulesTitleText = "RULES";
		textBoundingBox = titleFont.getStringBoundingBox(rulesTitleText, ofGetWidth() / 2 - w / 2,
		                                                 ofGetHeight() - h * 4.5);
		int rulesTitleTextOffsetX = textBoundingBox.width / 2;
		int rulesTitleTextOffsetY = textBoundingBox.height / 2;
		titleFont.drawString(rulesTitleText, ofGetWidth() / 2 - rulesTitleTextOffsetX,
		                     ofGetHeight() - rulesTitleTextOffsetY - 400);
		std::string rulesText;
		rulesText =
			"In rocket race you race the other\nplayer to the end of the screen,\nevery lap you get a point. At the\nend of 2 minutes the player with\nthe most points wins. Player 1\ncan W to go forward and S to go\nbackwards. Player 2 can use\nthe Up Arrow to go forward and\nthe Down Arrow to go backwards.\nPress R to go back to the menu.";
		textBoundingBox = rulesTextFont.getStringBoundingBox(rulesText, ofGetWidth() / 2 - w / 2,
		                                                     ofGetHeight() - h * 4.5);
		int rulesTextOffsetX = textBoundingBox.width / 2;
		int rulesTextOffsetY = textBoundingBox.height / 2;
		rulesTextFont.drawString(rulesText, ofGetWidth() / 2 - rulesTextOffsetX + 5,
		                         ofGetHeight() - rulesTextOffsetY - 200);
	}

	if (game) {
		ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() - 100, 4, 150);

		ofSetColor(255);
		for (int i = 0; i < 25; i++) {
			yPosLeft[i];
			ofDrawCircle(xPosLeft[i], yPosLeft[i], cometRadius);
			if (xPosLeft[i] >= firstLeft && xPosLeft[i] <= firstRight) {
				if (yPosLeft[i] >= rockets[0] && yPosLeft[i] <= rockets[0] + 30) {
					rockets[0] = 425;
					hitBeep.play();
				}
			}
			if (xPosLeft[i] >= secondLeft && xPosLeft[i] <= secondRight) {
				if (yPosLeft[i] >= rockets[1] && yPosLeft[i] <= rockets[1] + 30) {
					rockets[1] = 425;
					hitBeep.play();
				}
			}
		}

		for (int j = 0; j < 25; j++) {
			yPosRight[j];
			ofDrawCircle(xPosRight[j], yPosRight[j], cometRadius);
			if (xPosRight[j] >= firstLeft && xPosRight[j] <= firstRight) {
				if (yPosRight[j] >= rockets[0] && yPosRight[j] <= rockets[0] + 30) {
					rockets[0] = 425;
					hitBeep.play();
				}
			}
			if (xPosRight[j] >= secondLeft && xPosRight[j] <= secondRight) {
				if (yPosRight[j] >= rockets[1] && yPosRight[j] <= rockets[1] + 30) {
					rockets[1] = 425;
					hitBeep.play();
				}
			}
		}

		ofDrawRectangle(firstLeft, rockets[0], 20, 30);
		ofDrawRectangle(secondLeft, rockets[1], 20, 30);

		if (rockets[0] == 0) {
			firstCounter++;
			rockets[0] = 425;
			goalBeep.play();
		}
		if (rockets[1] == 0) {
			secondCounter++;
			rockets[1] = 425;
			goalBeep.play();
		}

		if (timer >= 20) {
			ofClear(0);
			std::string end;
			int textOffsetX = 0;
			int textOffsetY = 0;
			if (firstCounter > secondCounter) {
				end = "Player 1 wins!";
				textBoundingBox = text.getStringBoundingBox(end, ofGetWidth() / 2, ofGetHeight() / 2);
				textOffsetX = textBoundingBox.width / 2;
				textOffsetY = textBoundingBox.height / 2;
				text.drawString(end, ofGetWidth() / 2 - textOffsetX, ofGetHeight() / 2 - textOffsetY - 15);
			}
			else if (firstCounter < secondCounter) {
				end = "Player 2 wins!";
				textBoundingBox = text.getStringBoundingBox(end, ofGetWidth() / 2, ofGetHeight() / 2);
				textOffsetX = textBoundingBox.width / 2;
				textOffsetY = textBoundingBox.height / 2;
				text.drawString(end, ofGetWidth() / 2 - textOffsetX, ofGetHeight() / 2 - textOffsetY - 15);
			}
			else if (firstCounter == secondCounter) {
				end = "Tie!";
				textBoundingBox = text.getStringBoundingBox(end, ofGetWidth() / 2, ofGetHeight() / 2);
				textOffsetX = textBoundingBox.width / 2;
				textOffsetY = textBoundingBox.height / 2;
				text.drawString(end, ofGetWidth() / 2 - textOffsetX, ofGetHeight() / 2 - textOffsetY - 15);
			}
			std::string scoreText = getPlayerScoreText(firstCounter, secondCounter);
			textBoundingBox = score.getStringBoundingBox(scoreText, ofGetWidth() / 2, ofGetHeight() / 2);
			textOffsetX = textBoundingBox.width / 2;
			textOffsetY = textBoundingBox.height / 2;
			score.drawString(scoreText, ofGetWidth() / 2 - textOffsetX, ofGetHeight() / 2 - textOffsetY + 30);
		}
	}
	if (rPressed) {
		menu = true;
		rules = false;
		timer = 0;
		game = false;
	}
}

std::string ofApp::getPlayerScoreText(int firstScore, int secondScore) {
	return "Player 1 Score: " + ofToString(firstScore) + "\nPlayer 2 Score: " + ofToString(secondScore);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'w') {
		wPressed = true;
	}
	if (key == 's') {
		sPressed = true;
	}
	if (key == OF_KEY_UP) {
		upPressed = true;
	}
	if (key == OF_KEY_DOWN) {
		downPressed = true;
	}
	if (key == 'r') {
		rPressed = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == 'w') {
		wPressed = false;
	}
	if (key == 's') {
		sPressed = false;
	}
	if (key == OF_KEY_UP) {
		upPressed = false;
	}
	if (key == OF_KEY_DOWN) {
		downPressed = false;
	}
	if (key == 'r') {
		rPressed = false;
	}
}

void ofApp::mousePressed(int x, int y, int button) {
	if (menu) {
		int posX = ofGetMouseX();
		int posY = ofGetMouseY();

		if (button == 0) {
			if (posX > ofGetWidth() / 2 - w / 2 && posX < ofGetWidth() / 2 + w / 2) {
				if (posY > ofGetHeight() - h * 4.5 && posY < ofGetHeight() - h * 3.5) {
					menu = false;
					game = true;
				}
				if (posY > ofGetHeight() - h * 3 && posY < ofGetHeight() - h * 2) {
					menu = false;
					rules = true;
				}
			}
		}
	}
}
