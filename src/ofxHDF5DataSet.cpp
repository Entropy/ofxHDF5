//
//  ofxHDF5DataSet.cpp
//  ofxHDF5
//
//  Created by Elias Zananiri on 2016-02-01.
//
//

#include "ofxHDF5DataSet.h"

namespace ofxHDF5
{
    //--------------------------------------------------------------
    DataSet::DataSet()
    : _numDimensions(0)
    , _dimensions(nullptr)
    , h5_dataType(H5_DATATYPE_INT32)
    {

    }

    //--------------------------------------------------------------
    DataSet::~DataSet()
    {
        close();
    }

    //--------------------------------------------------------------
    void DataSet::close()
    {
        h5_dataSet.close();
        _numDimensions = 0;
        if (_dimensions) {
            delete [] _dimensions;
            _dimensions = nullptr;

            delete [] _count;
            _count = nullptr;
            delete [] _offset;
            _offset = nullptr;
            delete [] _stride;
            _stride = nullptr;
            delete [] _block;
            _block = nullptr;
        }
    }

    //--------------------------------------------------------------
    bool DataSet::open(const string &name, H5::CommonFG *fg)
    {
        close();

        try {
            h5_dataSet = fg->openDataSet(name);

            // Get the data type.
            string typeString = "???";
            H5T_class_t typeClass = h5_dataSet.getTypeClass();
            if (typeClass == H5T_INTEGER) {
                H5::IntType intType = h5_dataSet.getIntType();
                typeString = getTypeString(intType);
                h5_dataType = intType;
            }
            else if (typeClass == H5T_FLOAT) {
                H5::FloatType floatType = h5_dataSet.getFloatType();
                typeString = getTypeString(floatType);
                h5_dataType = floatType;
            }
            else if (typeClass == H5T_COMPOUND) {
                H5::CompType compType = h5_dataSet.getCompType();
                typeString = getTypeString(compType);
                h5_dataType = compType;
            }
            else {
                ofLogError("DataSet::open") << "Unsupported type class " << typeClass;
            }

            // Get the data space.
            h5_dataSpace = h5_dataSet.getSpace();
            _numDimensions = h5_dataSpace.getSimpleExtentNdims();
            _dimensions = new hsize_t[_numDimensions];
            h5_dataSpace.getSimpleExtentDims(_dimensions);

            // Set default hyperslab parameters.
            _count = new hsize_t[_numDimensions];
            _offset = new hsize_t[_numDimensions];
            _stride = new hsize_t[_numDimensions];
            _block = new hsize_t[_numDimensions];
            for (int i = 0; i < _numDimensions; ++i) {
                _count[i] = _dimensions[i];
                _offset[i] = 0;
                _stride[i] = 1;
                _block[i] = 1;
            }

            string dimsString = "";
            for (int i = 0; i < _numDimensions; ++i) {
                dimsString += ofToString(_dimensions[i]);
                if (i < _numDimensions - 1) {
                    dimsString += " x ";
                }
            }

            ofLogNotice("ofxHDF5::DataSet::open") << "DataSet loaded with " << dimsString << " " << typeString << "s";
        }
        catch (H5::DataSetIException error) {
            if (ofGetLogLevel() == OF_LOG_VERBOSE) {
                error.printError();
            }
            ofLogError("ofxHDF5::DataSet::open") << "Data Set " << name << " not found!";
			return false;
        }

        return true;
    }

    //--------------------------------------------------------------
    string DataSet::getTypeString(const H5::IntType& intType)
    {
        string str = "";

        H5T_sign_t sign = intType.getSign();
        if (sign != H5T_SGN_NONE) {
            str += "u";
        }

        size_t size = intType.getSize();
        if (size == 1) {
            str += "char";
        }
        else if (size <= 4) {
            str += "int32";
        }
        else {
            str += "int64";
        }

        return str;
    }

    //--------------------------------------------------------------
    string DataSet::getTypeString(const H5::FloatType& floatType)
    {
        size_t size = floatType.getSize();
        if (size <= 4) {
            return "float";
        }
        return "double";
    }

    //--------------------------------------------------------------
    string DataSet::getTypeString(const H5::CompType& compType)
    {
        string str = "compound (";

        for (int i = 0; i < compType.getNmembers(); ++i) {
            H5T_class_t memberClass = compType.getMemberClass(i);
            if (memberClass == H5T_INTEGER) {
                H5::IntType intType = h5_dataSet.getIntType();
                str += getTypeString(intType);
            }
            else if (memberClass == H5T_FLOAT) {
                H5::FloatType floatType = h5_dataSet.getFloatType();
                str += getTypeString(floatType);
            }
            if (i < compType.getNmembers() - 1) {
                str += " ";
            }
        }

        str += ")";
        return str;
    }

    //--------------------------------------------------------------
    H5::DataType DataSet::getDataType()
    {
        return h5_dataType;
    }

    //--------------------------------------------------------------
    size_t DataSet::getDataSize()
    {
        return h5_dataType.getSize();
    }

    //--------------------------------------------------------------
    int DataSet::getNumDimensions()
    {
        return _numDimensions;
    }

    //--------------------------------------------------------------
    int DataSet::getDimensionSize(int d)
    {
        if (d < _numDimensions) {
            return _dimensions[d];
        }
        return 0;
    }

    //--------------------------------------------------------------
    void DataSet::setHyperslab(int offset, int count, int stride, int block)
    {
        _offset[0] = offset;
        _count[0] = count;
        _stride[0] = stride;
        _block[0] = block;

        h5_dataSpace.selectHyperslab(H5S_SELECT_SET, _count, _offset, _stride, _block);
    }

    //--------------------------------------------------------------
    void DataSet::setHyperslab(hsize_t *offset, hsize_t *count, hsize_t *stride, hsize_t *block)
    {
        // Validate parameters.
        bool bValid = sizeof(offset) == sizeof(_offset);
        bValid &= sizeof(count) == sizeof(_count);
        bValid &= (!stride || sizeof(stride) == sizeof(_stride));
        bValid &= (!block || sizeof(block) == sizeof(_block));

        if (!bValid) {
            ofLogError("ofxHDF5::DataSet::setHyperslab") << "Parameter sizes don't match data space!";
            return;
        }

        for (int i = 0; i < _numDimensions; ++i) {
            _offset[i] = offset[i];
            _count[i] = count[i];
            if (stride) {
                _stride[i] = stride[i];
            }
            if (block) {
                _block[i] = block[i];
            }
        }

        h5_dataSpace.selectHyperslab(H5S_SELECT_SET, _count, _offset, _stride, _block);
    }

    //--------------------------------------------------------------
    void DataSet::resetHyperslab()
    {
        h5_dataSpace.selectAll();
    }

    //--------------------------------------------------------------
    void DataSet::read(void *buffer)
    {
        // Use native data type.
        read(buffer, h5_dataType);
    }

	//--------------------------------------------------------------
	void DataSet::read(void *buffer, H5::DataType dataType)
	{
		hsize_t *readSize = new hsize_t[_numDimensions];
		for (int i = 0; i < _numDimensions; ++i)
		{
			readSize[i] = _count[i] * (_block ? _block[i] : 1);
		}
		H5::DataSpace readSpace(_numDimensions, readSize);

		try
		{
			h5_dataSet.read(buffer, dataType, readSpace, h5_dataSpace);
		}
		catch (H5::DataSetIException error)
		{
			ofLogError(__FUNCTION__) << "Could not read data!";
			if (ofGetLogLevel() == OF_LOG_VERBOSE) {
				error.printError();
			}
		}

		delete[] readSize;
	}

    //--------------------------------------------------------------
    H5::DataSet& DataSet::getH5()
    {
        return h5_dataSet;
    }
}
