//
//  ofxHDF5File.h
//  ofxHDF5
//
//  Created by Elias Zananiri on 2016-02-01.
//
//

#pragma once

#include "ofMain.h"

#include "ofxHDF5Container.h"
#include "ofxHDF5DataSet.h"
#include "ofxHDF5Group.h"

namespace ofxHDF5
{
    class File : public Container
    {
    public:
        File();
        File(const string& filename, bool bReadOnly = false);
        ~File();

        bool open(const string& filename, bool bReadOnly = false);
        virtual void close();

        virtual GroupPtr loadGroup(const string& name);
        virtual DataSetPtr loadDataSet(const string& name);

        virtual H5::CommonFG *getH5CommonPtr();
        H5::H5File& getH5File();

    protected:
        H5::H5File h5_file;
    };
}
