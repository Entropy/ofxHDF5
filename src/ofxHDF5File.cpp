//
//  ofxHDF5File.cpp
//  ofxHDF5
//
//  Created by Elias Zananiri on 2016-02-01.
//
//

#include "ofxHDF5File.h"

namespace ofxHDF5
{
    //--------------------------------------------------------------
    File::File()
    {

    }

    //--------------------------------------------------------------
    File::File(const string& filename, bool bReadOnly)
    : File()
    {
        open(filename, bReadOnly);
    }

    //--------------------------------------------------------------
    File::~File()
    {
        close();
    }

    //--------------------------------------------------------------
    void File::close()
    {
        Container::close();

        h5_file.close();
    }

    //--------------------------------------------------------------
    bool File::open(const string& filename, bool bReadOnly)
    {
        close();

        string filePath = ofToDataPath(filename);
        try {
            h5_file.openFile(filePath, bReadOnly? H5F_ACC_RDONLY:H5F_ACC_RDWR);
        }
        catch (H5::FileIException error) {
            if (ofGetLogLevel() == OF_LOG_VERBOSE) {
                error.printError();
            }
            ofLogError("ofxHDF5::load") << "File " << filename << " not found or not HDF5!";
            return false;
        }
    }

    //--------------------------------------------------------------
    GroupPtr File::loadGroup(const string& name)
    {
        GroupPtr group = GroupPtr(new Group());
        if (group->open(name, &h5_file)) {
            _groups[name] = group;
            return group;
        }
        return nullptr;
    }

    //--------------------------------------------------------------
    DataSetPtr File::loadDataSet(const string& name)
    {
        DataSetPtr dataSet = DataSetPtr(new DataSet());
        if (dataSet->open(name, &h5_file)) {
            _dataSets[name] = dataSet;
            return dataSet;
        }
        return nullptr;
    }

    //--------------------------------------------------------------
    H5::CommonFG * File::getH5CommonPtr()
    {
        return &h5_file;
    }

    //--------------------------------------------------------------
    H5::H5File& File::getH5File()
    {
        return h5_file;
    }
}
