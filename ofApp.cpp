#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();
	
	float total_height = 600;
	float total_len = total_height * 5;
	float total_height_noise_value = 0;
	float total_len_noise_value = 0;
	vector<float> height_noise_value_list;
	vector<float> len_noise_value_list;

	for (int i = 0; i < 10; i++) {

		auto noise_value = ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005);
		height_noise_value_list.push_back(noise_value);
		total_height_noise_value += noise_value;

		noise_value = ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005);
		len_noise_value_list.push_back(noise_value);
		total_len_noise_value += noise_value;
	}

	float height_param = total_height / total_height_noise_value;
	float len_param = total_len / total_len_noise_value;

	float y = -300;
	float prev_height = 0;
	for (int i = 0; i < 10; i++) {

		auto len = len_noise_value_list[i] * len_param;
		auto height = height_noise_value_list[i] * height_param;
		y += height * 0.5 + prev_height * 0.5;

		this->setBoxToMesh(this->face, this->frame, glm::vec3(0, y, 0), height - 4, len, len, ofMap(ofNoise(ofRandom(360), ofGetFrameNum() * 0.002), 0, 1, -360, 360));
		prev_height = height;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(239);
	this->face.draw();

	ofSetColor(39);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float height, float width, float depth, float rotate_deg) {

	float rad = rotate_deg * DEG_TO_RAD;
	auto rotation = glm::rotate(glm::mat4(), rad, glm::vec3(0, 1, 0));

	int index = face_target.getVertices().size();

	face_target.addVertex(location + glm::vec4(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99, 0) * rotation);
	face_target.addVertex(location + glm::vec4(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99, 0) * rotation);
	face_target.addVertex(location + glm::vec4(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99, 0) * rotation);
	face_target.addVertex(location + glm::vec4(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99, 0) * rotation);

	face_target.addVertex(location + glm::vec4(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99, 0) * rotation);
	face_target.addVertex(location + glm::vec4(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99, 0) * rotation);
	face_target.addVertex(location + glm::vec4(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99, 0) * rotation);
	face_target.addVertex(location + glm::vec4(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99, 0) * rotation);

	face_target.addIndex(index + 0); face_target.addIndex(index + 1); face_target.addIndex(index + 2);
	face_target.addIndex(index + 0); face_target.addIndex(index + 2); face_target.addIndex(index + 3);

	face_target.addIndex(index + 4); face_target.addIndex(index + 5); face_target.addIndex(index + 6);
	face_target.addIndex(index + 4); face_target.addIndex(index + 6); face_target.addIndex(index + 7);

	face_target.addIndex(index + 0); face_target.addIndex(index + 4); face_target.addIndex(index + 1);
	face_target.addIndex(index + 4); face_target.addIndex(index + 5); face_target.addIndex(index + 1);

	face_target.addIndex(index + 1); face_target.addIndex(index + 5); face_target.addIndex(index + 6);
	face_target.addIndex(index + 6); face_target.addIndex(index + 2); face_target.addIndex(index + 1);

	face_target.addIndex(index + 2); face_target.addIndex(index + 6); face_target.addIndex(index + 7);
	face_target.addIndex(index + 7); face_target.addIndex(index + 3); face_target.addIndex(index + 2);

	face_target.addIndex(index + 3); face_target.addIndex(index + 7); face_target.addIndex(index + 4);
	face_target.addIndex(index + 4); face_target.addIndex(index + 0); face_target.addIndex(index + 3);

	frame_target.addVertex(location + glm::vec4(width * -0.5, height * 0.5, depth * -0.5, 0) * rotation);
	frame_target.addVertex(location + glm::vec4(width * 0.5, height * 0.5, depth * -0.5, 0) * rotation);
	frame_target.addVertex(location + glm::vec4(width * 0.5, height * 0.5, depth * 0.5, 0) * rotation);
	frame_target.addVertex(location + glm::vec4(width * -0.5, height * 0.5, depth * 0.5, 0) * rotation);

	frame_target.addVertex(location + glm::vec4(width * -0.5, height * -0.5, depth * -0.5, 0) * rotation);
	frame_target.addVertex(location + glm::vec4(width * 0.5, height * -0.5, depth * -0.5, 0) * rotation);
	frame_target.addVertex(location + glm::vec4(width * 0.5, height * -0.5, depth * 0.5, 0) * rotation);
	frame_target.addVertex(location + glm::vec4(width * -0.5, height * -0.5, depth * 0.5, 0) * rotation);

	frame_target.addIndex(index + 0); frame_target.addIndex(index + 1);
	frame_target.addIndex(index + 1); frame_target.addIndex(index + 2);
	frame_target.addIndex(index + 2); frame_target.addIndex(index + 3);
	frame_target.addIndex(index + 3); frame_target.addIndex(index + 0);

	frame_target.addIndex(index + 4); frame_target.addIndex(index + 5);
	frame_target.addIndex(index + 5); frame_target.addIndex(index + 6);
	frame_target.addIndex(index + 6); frame_target.addIndex(index + 7);
	frame_target.addIndex(index + 7); frame_target.addIndex(index + 4);

	frame_target.addIndex(index + 0); frame_target.addIndex(index + 4);
	frame_target.addIndex(index + 1); frame_target.addIndex(index + 5);
	frame_target.addIndex(index + 2); frame_target.addIndex(index + 6);
	frame_target.addIndex(index + 3); frame_target.addIndex(index + 7);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}