//
//  ofxHDF5Group.h
//  ofxHDF5
//
//  Created by Elias Zananiri on 2016-02-01.
//
//

#pragma once

#include <string>

#include "ofxHDF5Container.h"
#include "ofxHDF5DataSet.h"

namespace H5
{
	class CommonFG;
	class Group;
}

namespace ofxHDF5
{
    class Group : public Container
    {
    public:
        Group();
        ~Group();

        bool open(const std::string& name, H5::CommonFG *fg);
        virtual void close();

        virtual GroupPtr loadGroup(const std::string& name);
        virtual DataSetPtr loadDataSet(const std::string& name);

        virtual H5::CommonFG *getH5CommonPtr();
        H5::Group& getH5Group();

    protected:
        std::unique_ptr<H5::Group> h5_group;
    };
}
