//
//  ofApp.cpp
//  NoiseTerrain
//
//  Created by Andres Mueller
//  Reformated and commented by William Karges.
//
//This project was entirely coded by Andres Mueller
//I, William Karges, have gone through and reformated and commented his code as part of a class homework assignemnt
//I take no credit for any of this project's code
//
//
//This project uses the ofMesh variable type to draw a flat plane and create bumps in the plane by implementing noise and mapping functions on the points within the plane.


#include "ofApp.h"

void ofApp::setup() {
    fontSmall.loadFont("Fonts/DIN.otf", 8 );
    
    camera.setAutoDistance( false );
    camera.setPosition( ofVec3f(0,1,4) ); //Set Camera Position
    camera.setNearClip( 0.001 ); //Set Camera front clipping plane
}

void ofApp::draw() {
    ofBackgroundGradient( ofColor(55), ofColor(0), OF_GRADIENT_CIRCULAR ); //set background
    
    float t = ofGetElapsedTimef();
    
    mx = ofNormalize( ofGetMouseX(), 0, ofGetWidth() ); //remap the value of mouse x between 0 & 1
    my = ofNormalize( ofGetMouseY(), 0, ofGetHeight() ); //remap the value of mouse y between 0 & 1
    
    float frequency = ofMap( mx, 0, 1, 0.1, 1.0 ); //remap valuse of mouseX from 0-1 to .1-1.0
    
    int res = 100;
    ofVec3f size(5, 1, 5);
    
    ofMesh mesh;
    mesh.setMode( OF_PRIMITIVE_TRIANGLES ); //set mesh mode to triangles
    
    for( int y = 0; y < res; y++ )
    {
        for( int x = 0; x < res; x++ )
        {
            ofVec3f p = getTerrain( ofMap( x, 0, res, size.x * -0.5f, size.x * 0.5f ),
                                   ofMap( y, 0, res, size.z * -0.5f, size.z * 0.5f ),
                                   frequency, size.y ); //within the getTerrain function remap the values of x & y to a range between size.x/size.y & -.5f/.5f, set the value p to the returned value p
            
            pRight = getTerrain( ofMap( x + 1, 0, res, size.x * -0.5f, size.x * 0.5f ),
                                        ofMap( y, 0, res, size.z * -0.5f, size.z * 0.5f ),
                                        frequency, size.y ); //within the getTerrain function remap the values of x+1 & y to a range between size.x/size.y & -.5f/.5f, set the value pRight to the returned value p
            
            pBot = getTerrain(  ofMap( x, 0, res, size.x * -0.5f, size.x * 0.5f ),
                                      ofMap( y + 1, 0, res, size.z * -0.5f, size.z * 0.5f ),
                                      frequency, size.y ); //within the getTerrain function remap the values of x & y+1 to a range between size.x/size.y & -.5f/.5f, set the value pBot to the returned value p
            
            //ofVec3f normal = (pRight-p).getCrossed( (pBot-p) ).getNormalized();
            normal = (pBot-p).getCrossed( (pRight-p) ).getNormalized(); //ofvec3f normal gets the normalized vector perpendicular to the vectors pBot-p * pRight-p
            
            mesh.addVertex( p );
            mesh.addNormal( normal );
            
            //mesh.addVertex( p );
            //mesh.addVertex( p + (normal * 1));
            
        }
    }
    
    
    for( int y = 0; y < res-1; y++ )
    {
        for( int x = 0; x < res-1; x++ )
        {
            int tmp = (y * res) + x;
            
            //mesh.addIndex( tmp ); mesh.addIndex( tmp + 1 );
            //mesh.addIndex( tmp ); mesh.addIndex( tmp + res );
            
            mesh.addTriangle( tmp, tmp + 1, tmp + 1 + res ); //draw the mesh plane
            mesh.addTriangle( tmp, tmp + 1 + res, tmp + res ); //draw the mesh plane
        }
    }
    
    ofEnableDepthTest();
    
    camera.begin();
    
    // Grid
    ofSetColor( ofColor(60) ); //set color
    ofPushMatrix();
    ofRotate(90, 0, 0, -1);
    ofDrawGridPlane( size.x, (int)size.x, false ); //set the size and position of the grid pplane
    ofPopMatrix();
    
    ofLight light;
    light.setPosition( ofVec3f(1,4,0) ); //set light position
    light.enable();
    
    ofEnableLighting();
    ofSetColor( ofColor::white ); //set color
    mesh.draw(); //draw the mesh
    ofDisableLighting();
    
    ofSphere( light.getPosition(), 0.1 );
    
    camera.end();
    
    ofDisableDepthTest();
}

ofVec3f ofApp::getTerrain( float _x, float _y, float _frequency, float _magnitude ) {
    ofVec3f p( _x, 0, _y );
    p.y = ofNoise( p.x * _frequency, p.z * _frequency ) * _magnitude; //set the y value of p to a value between .1 and 1
    //p.y = MathUtils::fbm( ofVec2f(p.x * _frequency, p.z * _frequency), 4, 2.0, 0.5 ) * _magnitude;
    return p;
}

void ofApp::keyPressed( int _key ) {
    if( _key == ' ' ) {
    }
}