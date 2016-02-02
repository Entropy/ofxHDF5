//
//  ofxHDF5Container.h
//  ofxHDF5
//
//  Created by Elias Zananiri on 2016-02-01.
//
//

#pragma once

#include "ofMain.h"

namespace ofxHDF5
{
    class Group;
    class DataSet;

    typedef shared_ptr<Group> GroupPtr;
    typedef shared_ptr<DataSet> DataSetPtr;

    class Container
    {
    public:
        Container();
        virtual ~Container();

        virtual void close();

        virtual GroupPtr loadGroup(const string& name) = 0;
        virtual DataSetPtr loadDataSet(const string& name) = 0;

        GroupPtr group(const string& name);
        DataSetPtr dataSet(const string& name);

    protected:
        map<string, GroupPtr> _groups;
        map<string, DataSetPtr> _dataSets;
    };
}
