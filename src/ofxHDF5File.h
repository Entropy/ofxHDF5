//
//  ofxHDF5File.h
//  ofxHDF5
//
//  Created by Elias Zananiri on 2016-02-01.
//
//

#pragma once

#include <string>

#include "ofxHDF5Container.h"
#include "ofxHDF5DataSet.h"
#include "ofxHDF5Group.h"

namespace H5
{
	class H5File;
}

namespace ofxHDF5
{
    class File : public Container
    {
    public:
        File();
        File(const std::string& filename, bool bReadOnly = false);
        ~File();

        bool open(const std::string& filename, bool bReadOnly = false);
        virtual void close();

        virtual GroupPtr loadGroup(const std::string& name);
        virtual DataSetPtr loadDataSet(const std::string& name);

        virtual H5::CommonFG *getH5CommonPtr();
        H5::H5File& getH5File();

    protected:
        std::unique_ptr<H5::H5File> h5_file;
    };
}
