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

#define H5_DATATYPE_CHAR   H5::PredType::NATIVE_CHAR
#define H5_DATATYPE_UCHAR  H5::PredType::NATIVE_UCHAR
#define H5_DATATYPE_INT32  H5::PredType::NATIVE_INT32
#define H5_DATATYPE_INT64  H5::PredType::NATIVE_INT64
#define H5_DATATYPE_UINT32 H5::PredType::NATIVE_UINT32
#define H5_DATATYPE_UINT64 H5::PredType::NATIVE_UINT64
#define H5_DATATYPE_FLOAT  H5::PredType::NATIVE_FLOAT
#define H5_DATATYPE_DOUBLE H5::PredType::NATIVE_DOUBLE

namespace ofxHDF5
{
    typedef H5::PredType DataType;

    class DataSet
    {
    public:
        DataSet();
        ~DataSet();

        bool open(const string& name, H5::CommonFG *fg);
        void close();

        DataType getDataType();
        size_t getDataSize();

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
        size_t _dataSize;

        int _numDimensions;
        hsize_t *_dimensions;

        hsize_t *_offset;
        hsize_t *_count;
        hsize_t *_stride;
        hsize_t *_block;
    };
}
