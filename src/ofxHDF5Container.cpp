//
//  ofxHDF5Container.cpp
//  ofxHDF5
//
//  Created by Elias Zananiri on 2016-02-01.
//
//

#include "ofxHDF5Container.h"

#include "ofxHDF5DataSet.h"
#include "ofxHDF5Group.h"

namespace ofxHDF5
{
    //--------------------------------------------------------------
    Container::Container()
    {

    }

    //--------------------------------------------------------------
    Container::~Container()
    {
        
    }

    //--------------------------------------------------------------
    void Container::close()
    {
        for (auto& it : _groups) {
            it.second->close();
        }

        for (auto& it : _dataSets) {
            it.second->close();
        }
    }

    //--------------------------------------------------------------
    GroupPtr Container::group(const string& name)
    {
        if (_groups.find(name) != _groups.end()) {
            return _groups[name];
        }
        else {
            ofLogError("ofxHDF5::Container::group") << "Could not find Group with name " << name;
            return nullptr;
        }
    }

    //--------------------------------------------------------------
    DataSetPtr Container::dataSet(const string &name)
    {
        if (_dataSets.find(name) != _dataSets.end()) {
            return _dataSets[name];
        }
        else {
            ofLogError("ofxHDF5::Container::dataSet") << "Could not find DataSet with name " << name;
            return nullptr;
        }
    }
}
