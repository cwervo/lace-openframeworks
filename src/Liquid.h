#pragma once

class Liquid {
    public:
        double x,y,w,h;
        double c;

        Liquid(double _x = 0, double _y = 0, double _w = 0, double _h = 0, double _c = 0.5) {
            x = _x;
            y = _y;
            w = _w;
            h = _h;
            c = _c;
        }

        void draw() {
            ofSetColor(255, 255, 255, 255 * 0.25);
            ofFill();
            ofDrawRectangle(x,y,w,h);
        }
};
