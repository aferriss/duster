#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    img.load("2007-6.png");

    
    w = img.getWidth();
    h = img.getHeight();
    
    fbo.allocate(w, h, GL_RGBA, 8);
    fbo.begin();
    ofClear(0,255);
    fbo.end();
    
    ofSetWindowShape(w, h);
    ofSetFrameRate(60);
    
    w /=4;
    h /=4;
    
    particles.init(w, h, OF_PRIMITIVE_LINE_STRIP_ADJACENCY  );
    particles.loadShaders("shaders120/update", "shaders120/draw");
    
    
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
    save = false;
    
    disp = 200;
    go = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    particles.update();
    
    particles.getDrawShaderRef().begin();
    particles.getDrawShaderRef().setUniform1f("time", ofGetFrameNum());
    particles.getDrawShaderRef().setUniform1f("disp", disp );//+ sin(ofGetFrameNum()*0.01)*100);
    particles.getDrawShaderRef().setUniform2f("res", w, h);
    particles.getDrawShaderRef().setUniformTexture("tex0", img.getTexture(), 2);
//    img.getTexture().bind();
    particles.getDrawShaderRef().end();
    
    if(save){
        if(ofGetFrameNum()%10 == 0){
            ofPixels savePix;
            fbo.readToPixels(savePix);
            ofSaveImage(savePix, "saved/"+ofGetTimestampString()+".png");
        }
    }
    
}
//--------------------------------------------------------------
void ofApp::onParticlesUpdate(ofShader& shader){
    ofVec3f mouse(ofGetMouseX() - .5f * ofGetWidth(), .5f * ofGetHeight() - ofGetMouseY() , 0.f);
    shader.setUniform3fv("mouse", mouse.getPtr());
    shader.setUniform1f("elapsed", ofGetLastFrameTime());
    
    if(ofGetKeyPressed('g')){
        go = 1;
    }
    shader.setUniform1f("go", go);
    shader.setUniform1f("radiusSquared", 200.f * 200.f);
}
//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
//    if(ofGetKeyPressed(' ')){
        ofClear(0,255);
//    }
    cam.begin();
//    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    ofPushMatrix();
//    ofRotate(ofGetFrameNum()*0.8, 0, 1, 0);
    particles.draw();
    ofPopMatrix();
//    particles.getDrawShaderRef().begin();
//    particles.getDrawShaderRef().setUniform1f("disp", 200);
//    particles.getDrawShaderRef().end();
//    ofTranslate(0,0,-120);
//    particles.draw();
//    particles.getDrawShaderRef().begin();
//    particles.getDrawShaderRef().setUniform1f("disp", 10);
//    particles.getDrawShaderRef().end();
//    ofTranslate(0,0,-120);
//    particles.draw();
//    ofDisableBlendMode();
    cam.end();
    fbo.end();
    
    fbo.draw(0,0);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '-'){
        disp -=5;
    }
    if(key == '='){
        disp +=5;
    }
    
    if(key == 's'){
        save = !save;
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
