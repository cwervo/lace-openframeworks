#pragma once
#include "Liquid.h"

class Ball {
    public:
        ofPoint location;
        ofPoint velocity;
        ofPoint acceleration;
        double mass;
        ofColor color = ofColor::fromHex(0x2EAFAC);

        Ball(ofPoint _location = ofPoint(float(ofGetWidth() * 0.5), float(ofGetHeight() * 0.5)), double _mass = 1) {
            location = _location;
            mass = _mass;
            velocity = ofPoint{0, 0};
            acceleration = ofPoint{0, 0};
        }

        // Newton’s second law.
        void applyForce(ofPoint force) {
            // Receive a force, divide by mass, and add to acceleration.
            acceleration += force / mass;
        }

        void update() {
            velocity += acceleration;
            location += velocity;
            acceleration *= 0;
        }

        void draw() {
            ofSetColor(color);
            ofFill();
            ofDrawCircle(location, mass*16);
            // ofDrawSphere(location, mass*16);
        }

        void checkEdges() {
            if (location.x > ofGetWidth()) {
                location.x = ofGetWidth();
                velocity.x *= -1;
            } else if (location.x < 0) {
                velocity.x *= -1;
                location.x = 0;
            }

            if (location.y > ofGetHeight()) {
                velocity.y *= -1;
                location.y = ofGetHeight();
            }
        }

        bool isInside(Liquid l) {
            if (location.x>l.x && location.x<l.x+l.w && location.y>l.y && location.y<l.y+l.h)
            {
                return true;
            } else {
                return false;
            }
        }

        void drag(Liquid l) {
            float speed = velocity.lengthSquared();
            float dragMagnitude = l.c * speed * speed;
            ofPoint drag = velocity;
            drag *= -1;
            drag.normalize();
            drag *= dragMagnitude;
            applyForce(drag);
        }

};
