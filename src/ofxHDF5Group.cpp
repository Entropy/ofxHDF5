//
//  ofxHDF5Group.cpp
//  ofxHDF5
//
//  Created by Elias Zananiri on 2016-02-01.
//
//

#include "ofxHDF5Group.h"

namespace ofxHDF5
{
    //--------------------------------------------------------------
    Group::Group()
    {

    }

    //--------------------------------------------------------------
    Group::~Group()
    {
        close();
    }

    //--------------------------------------------------------------
    void Group::close()
    {
        Container::close();

        h5_group.close();
    }

    //--------------------------------------------------------------
    bool Group::open(const string& name, H5::CommonFG *fg)
    {
        close();

        try {
            h5_group = fg->openGroup(name);
        }
        catch (H5::GroupIException error) {
            if (ofGetLogLevel() == OF_LOG_VERBOSE) {
                error.printError();
            }
            ofLogError("ofxHDF5::Group::open") << "Group " << name << " not found!";
            return false;
        }

        return true;
    }

    //--------------------------------------------------------------
    GroupPtr Group::loadGroup(const string& name)
    {
        GroupPtr group = GroupPtr(new Group());
        if (group->open(name, &h5_group)) {
            _groups[name] = group;
            return group;
        }
        return nullptr;
    }

    //--------------------------------------------------------------
    DataSetPtr Group::loadDataSet(const string& name)
    {
        DataSetPtr dataSet = DataSetPtr(new DataSet());
        if (dataSet->open(name, &h5_group)) {
            _dataSets[name] = dataSet;
            return dataSet;
        }
        return nullptr;
    }

    //--------------------------------------------------------------
    H5::CommonFG * Group::getH5CommonPtr()
    {
        return &h5_group;
    }

    //--------------------------------------------------------------
    H5::Group& Group::getH5Group()
    {
        return h5_group;
    }
}
