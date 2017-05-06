//
//  ofxHDF5DataSet.hpp
//  ofxHDF5
//
//  Created by Elias Zananiri on 2016-02-01.
//
//

#pragma once

#include <string>
#include <memory>


#define H5_DATATYPE_CHAR   H5::PredType::NATIVE_CHAR
#define H5_DATATYPE_UCHAR  H5::PredType::NATIVE_UCHAR
#define H5_DATATYPE_INT32  H5::PredType::NATIVE_INT32
#define H5_DATATYPE_INT64  H5::PredType::NATIVE_INT64
#define H5_DATATYPE_UINT32 H5::PredType::NATIVE_UINT32
#define H5_DATATYPE_UINT64 H5::PredType::NATIVE_UINT64
#define H5_DATATYPE_FLOAT  H5::PredType::NATIVE_FLOAT
#define H5_DATATYPE_DOUBLE H5::PredType::NATIVE_DOUBLE

namespace H5
{
	class CompType;
	class FloatType;
	class IntType;
	class CommonFG;
	class DataSet;
	class DataSpace;
	class DataType;

}

namespace ofxHDF5
{
    class DataSet
    {
    public:
        DataSet();
        ~DataSet();

        bool open(const std::string& name, H5::CommonFG *fg);
        void close();

        H5::DataType getDataType();
        size_t getDataSize();

        int getNumDimensions();
        int getDimensionSize(int d);

        void setHyperslab(int offset, int count, int stride = 1, int block = 1);
        void setHyperslab(uint64_t *offset, uint64_t *count, uint64_t *stride = nullptr, uint64_t *block = nullptr);
        void resetHyperslab();

        void read(void *buffer);
        void read(void *buffer, H5::DataType dataType);

        H5::DataSet& getH5();

    protected:
		std::string getTypeString(const H5::IntType& intType);
		std::string getTypeString(const H5::FloatType& floatType);
		std::string getTypeString(const H5::CompType& compType);

        std::unique_ptr<H5::DataSet> h5_dataSet;
        std::unique_ptr<H5::DataSpace> h5_dataSpace;
        std::unique_ptr<H5::DataType> h5_dataType;

        int _numDimensions;
		uint64_t *_dimensions;

		uint64_t *_offset;
		uint64_t *_count;
		uint64_t *_stride;
		uint64_t *_block;
    };
}
