//
//  ofxHDF5DataSet.hpp
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
    typedef enum DataType
    {
        DATA_TYPE_INTEGER = H5T_INTEGER,
        DATA_TYPE_FLOAT = H5T_FLOAT
    } DataType;

    class DataSet
    {
    public:
        DataSet();
        ~DataSet();

        bool open(const string& name, H5::CommonFG *fg);
        void close();

        DataType getDataType();

        int getNumDimensions();
        int getDimensionSize(int d);

        void setHyperslab(int offset, int count, int stride = 1, int block = 1);
        void setHyperslab(hsize_t *offset, hsize_t *count, hsize_t *stride = nullptr, hsize_t *block = nullptr);
        void resetHyperslab();

        void read(void *buffer);

        H5::DataSet& getH5();

    protected:
        H5::DataSet h5_dataSet;
        H5::DataSpace h5_dataSpace;

        DataType _dataType;

        int _numDimensions;
        hsize_t *_dimensions;

        hsize_t *_offset;
        hsize_t *_count;
        hsize_t *_stride;
        hsize_t *_block;
    };
}
