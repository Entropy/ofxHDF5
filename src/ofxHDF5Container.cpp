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
#include "H5Cpp.h"

#include "ofLog.h"

using namespace std;

namespace ofxHDF5
{
    //--------------------------------------------------------------
    Container::Container()
    : _bNeedsChildInfo(true)
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

        _groupNames.clear();
        _dataSetNames.clear();
        _bNeedsChildInfo = true;
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

    //--------------------------------------------------------------
    void Container::_getChildInfo()
    {
        if (_bNeedsChildInfo) {
            int num = getH5CommonPtr()->getNumObjs();
            for (int i = 0; i < num; ++i) {
                string name = getH5CommonPtr()->getObjnameByIdx(i);
                H5G_obj_t type = getH5CommonPtr()->getObjTypeByIdx(i);
                if (type == H5G_GROUP) {
                    _groupNames.push_back(name);
                }
                else if (type == H5G_DATASET) {
                    _dataSetNames.push_back(name);
                }
            }

            _bNeedsChildInfo = false;
        }
    }

    //--------------------------------------------------------------
    int Container::getNumGroups()
    {
        _getChildInfo();
        return _groupNames.size();
    }

    //--------------------------------------------------------------
    int Container::getNumDataSets()
    {
        _getChildInfo();
        return _dataSetNames.size();
    }

    //--------------------------------------------------------------
    const string& Container::getGroupName(int i)
    {
        _getChildInfo();
        return _groupNames[i];
    }

    //--------------------------------------------------------------
    const string& Container::getDataSetName(int i)
    {
        _getChildInfo();
        return _dataSetNames[i];
    }
}
