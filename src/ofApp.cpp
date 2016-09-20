#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    w = 907;
    h = 720;
    
    particles.init(w, h);
    particles.loadShaders("shaders120/update", "shaders120/draw");
    ofSetWindowShape(w, h);
    ofSetFrameRate(60);
    
    img.load("bey3.jpg");
    img.resize(w, h);
    
    float* particlePosns = new float[w * h * 4];
    for (unsigned y = 0; y < h; ++y)
    {
        for (unsigned x = 0; x < w; ++x)
        {
            unsigned idx = y * w + x;
            particlePosns[idx * 4] = w * x / (float)w - w/2; // particle x
            particlePosns[idx * 4 + 1] = h * y / (float)h - h/2; // particle y
            particlePosns[idx * 4 + 2] = 0.f; // particle z
            particlePosns[idx * 4 + 3] = 0.f; // dummy
        }
    }
    
    particles.loadDataTexture(ofxGpuParticles::POSITION, particlePosns);
    delete[] particlePosns;
    
    particles.zeroDataTexture(ofxGpuParticles::VELOCITY);
    
    ofAddListener(particles.updateEvent, this, &ofApp::onParticlesUpdate);
    ofEnableDepthTest();
    glPointSize(1);
}

//--------------------------------------------------------------
void ofApp::update(){
    particles.update();
    
    particles.getDrawShaderRef().begin();
    particles.getDrawShaderRef().setUniform1f("time", ofGetFrameNum());
    particles.getDrawShaderRef().setUniform1f("disp", 60);
    particles.getDrawShaderRef().setUniformTexture("tex0", img.getTexture(), 2);
//    img.getTexture().bind();
    particles.getDrawShaderRef().end();
}
//--------------------------------------------------------------
void ofApp::onParticlesUpdate(ofShader& shader){
    ofVec3f mouse(ofGetMouseX() - .5f * ofGetWidth(), .5f * ofGetHeight() - ofGetMouseY() , 0.f);
    shader.setUniform3fv("mouse", mouse.getPtr());
    shader.setUniform1f("elapsed", ofGetLastFrameTime());
    shader.setUniform1f("radiusSquared", 200.f * 200.f);
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
//    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    particles.draw();
    particles.getDrawShaderRef().begin();
    particles.getDrawShaderRef().setUniform1f("disp", 30);
    particles.getDrawShaderRef().end();
    ofTranslate(0,0,-120);
    particles.draw();
    particles.getDrawShaderRef().begin();
    particles.getDrawShaderRef().setUniform1f("disp", 10);
    particles.getDrawShaderRef().end();
    ofTranslate(0,0,-120);
    particles.draw();
//    ofDisableBlendMode();
    cam.end();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
