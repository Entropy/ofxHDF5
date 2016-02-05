#include "ofApp.h"
#include "H5Cpp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(ofColor::black);
    ofSetLogLevel(OF_LOG_VERBOSE);

    string filename = "snap_000.0.hdf5";
    hdf5File.open(filename, true);
    cout << "File '" << filename << "' has " << hdf5File.getNumGroups() << " groups and " << hdf5File.getNumDataSets() << " datasets" << endl;
    for (int i = 0; i < hdf5File.getNumGroups(); ++i) {
        cout << "  Group " << i << ": " << hdf5File.getGroupName(i) << endl;
    }
    for (int i = 0; i < hdf5File.getNumDataSets(); ++i) {
        cout << "  DataSet " << i << ": " << hdf5File.getDataSetName(i) << endl;
    }

    string groupName = hdf5File.getGroupName(1);
    ofxHDF5GroupPtr group = hdf5File.loadGroup(groupName);
    cout << "Group '" << groupName << "' has " << hdf5File.getNumDataSets() << " datasets" << endl;
    for (int i = 0; i < group->getNumDataSets(); ++i) {
        cout << "  DataSet " << i << ": " << group->getDataSetName(i) << endl;
    }

    string dataSetName = group->getDataSetName(0);
    ofxHDF5DataSetPtr dataSet = group->loadDataSet(dataSetName);

    int offset = 0;
    int count = dataSet->getDimensionSize(0);
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
