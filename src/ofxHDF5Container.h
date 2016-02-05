//
//  ofxHDF5Container.h
//  ofxHDF5
//
//  Created by Elias Zananiri on 2016-02-01.
//
//

#pragma once

#include "H5Cpp.h"

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

        int getNumGroups();
        int getNumDataSets();

        const string& getGroupName(int i);
        const string& getDataSetName(int i);

        virtual H5::CommonFG *getH5CommonPtr() = 0;

    protected:
        map<string, GroupPtr> _groups;
        map<string, DataSetPtr> _dataSets;

        void _getChildInfo();
        bool _bNeedsChildInfo;
        vector<string> _groupNames;
        vector<string> _dataSetNames;
    };
}
