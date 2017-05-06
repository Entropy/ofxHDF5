//
//  ofxHDF5Container.h
//  ofxHDF5
//
//  Created by Elias Zananiri on 2016-02-01.
//
//

#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>

namespace H5
{
	class CommonFG;
}

namespace ofxHDF5
{
    class Group;
    class DataSet;

    typedef std::shared_ptr<Group> GroupPtr;
    typedef std::shared_ptr<DataSet> DataSetPtr;

    class Container
    {
    public:
        Container();
        virtual ~Container();

        virtual void close();

        virtual GroupPtr loadGroup(const std::string& name) = 0;
        virtual DataSetPtr loadDataSet(const std::string& name) = 0;

        GroupPtr group(const std::string& name);
        DataSetPtr dataSet(const std::string& name);

        int getNumGroups();
        int getNumDataSets();

        const std::string& getGroupName(int i);
        const std::string& getDataSetName(int i);

        virtual H5::CommonFG *getH5CommonPtr() = 0;

    protected:
		std::map<std::string, GroupPtr> _groups;
		std::map<std::string, DataSetPtr> _dataSets;

        void _getChildInfo();
        bool _bNeedsChildInfo;
		std::vector<std::string> _groupNames;
		std::vector<std::string> _dataSetNames;
    };
}
