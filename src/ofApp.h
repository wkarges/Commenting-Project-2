
#pragma once

#include "ofMain.h"
#include "Math/MathUtils.h"

class ofApp : public ofBaseApp
{
public:
	
    // --------------------------------
    void setup() ;
    void draw() ;
    void keyPressed( int _key ) ;
    ofVec3f getTerrain( float _x, float _y, float _frequency, float _magnitude ) ;
	
    // --------------------------------
    ofEasyCam camera;
    ofTrueTypeFont fontSmall;
    float mx ;
    float my ;
    ofVec3f pRight ;
    ofVec3f pBot ;
    ofVec3f normal ;
};
