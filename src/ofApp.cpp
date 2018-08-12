#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0,0,0);

    // try to grab at this size
    camWidth = 640;
    camHeight = 480;

    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth,camHeight);

    font.load("Courier New Bold.ttf", 9);

    // this set of characters comes from the Ascii Video Processing example by Ben Fry,
    // changed order slightly to work better for mapping
    asciiCharacters =  string("  ..,,,'''``--_:;^^**""=+<>iv%&xclrs)/){}I?!][1taeo7zjLunT#@JCwfy325Fp6mqSghVd4EgXPGZbYkOA8U$KHDBWNMR0Q");

    ofEnableAlphaBlending();

    for (int i = 0; i < 10; ++i) {
        ofPoint loc{ofRandomWidth(), ofRandomHeight()};
        Ball b = Ball(loc, 1 + 0.25 * i);
        b.color = ofColor(255 * b.mass, 0, 255 * 0.5 * b.mass);
        balls.push_back(b);
    }

    // wind
    forces.push_back(ofPoint{0.01, 0});

    liquids.push_back(Liquid{0, double(ofGetHeight()/2), double(ofGetWidth()), double(ofGetHeight()/2), 0.1});
}


//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    for (Ball &b : balls) {
        for (auto f : forces) {
            b.applyForce(f);
        }

        // Gravity
        b.applyForce(gravity * b.mass);

        // Friction
        double c = 0.01;
        double normal = 1;
        double frictionMag = c*normal;
        ofPoint friction = b.velocity;
        friction *= -1;
        friction.normalize();
        friction *= frictionMag;
        b.applyForce(friction);


        for (Liquid l : liquids) {
            if (b.isInside(l)) {
                b.drag(l);
            }
        }


        b.update();
        b.checkEdges();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    // change background video alpha value based on the cursor's x-position
    float videoAlphaValue = ofMap(mouseX, 0, ofGetWidth(), 0, 255);

    // set a white fill color with the alpha generated above
    ofSetColor(255,255,255,videoAlphaValue);

    // draw the raw video frame with the alpha value generated above
    vidGrabber.draw(0,0);

    ofPixelsRef pixelsRef = vidGrabber.getPixels();

    ofSetHexColor(0xffffff);

    for (int i = 0; i < camWidth; i+= 7){
        for (int j = 0; j < camHeight; j+= 9){
            // get the pixel and its lightness (lightness is the average of its RGB values)
            float lightness = pixelsRef.getColor(i,j).getLightness();

            // calculate the index of the character from our asciiCharacters array
            int character = powf( ofMap(lightness, 0, 255, 0, 1), 2.5) * asciiCharacters.size();

            // draw the character at the correct location
            if (character < asciiCharacters.size() * 0.25) {
                ofSetColor(0,0,0,0);
            } else {
                ofSetColor(ofColor::blue);
            }
            ofDrawRectangle(i, j, 10, 10);

            ofSetColor(ofColor::white);
            // font.drawString(ofToString(asciiCharacters[character]), i, j);
            //            ofDrawLine(i,j, i+character/2, j+character/2);

        }
    }

    for (Ball b : balls) {
        b.draw();
    }

    for (Liquid l : liquids) {
        l.draw();
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){

    // in fullscreen mode, on a pc at least, the
    // first time video settings the come up
    // they come up *under* the fullscreen window
    // use alt-tab to navigate to the settings
    // window. we are working on a fix for this...

    if (key == 's' || key == 'S'){
        vidGrabber.videoSettings();
    }


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
