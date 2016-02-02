#include "ofApp.h"
#include "H5Cpp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(ofColor::black);
    ofSetLogLevel(OF_LOG_VERBOSE);

    string filename = "snap_000.0.hdf5";
    string groupName = "PartType1";
    string dataSetName = "Coordinates";

    hdf5File.open(filename, true);
    ofxHDF5GroupPtr group = hdf5File.loadGroup(groupName);
    ofxHDF5DataSetPtr dataSet = group->loadDataSet(dataSetName);

    int offset = 0;
    int count = 1024 * 128;
    int stride = 1;
    dataSet->setHyperslab(offset, count, stride);

    mesh.getVertices().resize(count);
    dataSet->read(mesh.getVerticesPointer());

//    for (int i = 0; i < mesh.getNumVertices(); ++i) {
//        cout << i << "[" << (offset + i * stride) << "] => " << mesh.getVertex(i) << endl;
//    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(ofColor::white);

    cam.begin();
    {
        mesh.draw(OF_MESH_POINTS);

        ofDrawAxis(20);
    }
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
