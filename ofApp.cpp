#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1.5);

	this->len = 20;
	for (float x = 0; x < ofGetWidth(); x += this->len) {

		for (float y = 0; y < ofGetHeight(); y += this->len) {

			this->start_location_list.push_back(glm::vec3(x, y, 0));
		}
	}

	for (int i = 0; i < 16; i++) {

		int r = ofRandom(this->start_location_list.size());

		auto log_list = vector<glm::vec2>();
		log_list.push_back(this->start_location_list[r]);
		this->location_list.push_back(log_list);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 1 == 0) {

		for (auto& log_list : this->location_list) {

			int r = ofRandom(4);
			int deg_start = r * 90;
			for (int deg = deg_start; deg < deg_start + 360; deg += 90) {

				auto tmp_location = log_list.back() + glm::vec2(this->len * cos(deg * DEG_TO_RAD), this->len * sin(deg * DEG_TO_RAD));
				if (tmp_location.x < this->len || tmp_location.x > ofGetWidth() - this->len * 2  
					|| tmp_location.y < this->len || tmp_location.y > ofGetHeight() - this->len * 2) {

					continue;
				}

				bool flag = false;
				for (int i = 0; i < log_list.size(); i++) {

					if (tmp_location == log_list[i] && deg_start != deg && deg_start % 360 == deg % 360) {

						flag = true;
						break;
					}
				}
				if (flag) { continue; }

				log_list.push_back(tmp_location);
				break;
			}

			while (log_list.size() > 15) {

				log_list.erase(log_list.begin());
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofColor color;
	for (auto& log_list : this->location_list) {

		for (int i = 0; i < log_list.size(); i++) {

			ofFill();
			color.setHsb(ofMap(i, 0, log_list.size(), 0, 255), 180, 255);
			ofSetColor(color);
			ofDrawRectangle(log_list[i], this->len, this->len);

			ofNoFill();
			ofSetColor(39);
			ofDrawRectangle(log_list[i], this->len, this->len);
		}
	}

	ofSetColor(0, 32);
	ofNoFill();
	for (float x = 0; x < ofGetWidth(); x += this->len) {

		for (float y = 0; y < ofGetHeight(); y += this->len) {

			ofDrawRectangle(glm::vec3(x, y, 0), this->len, this->len);
		}
	}

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}