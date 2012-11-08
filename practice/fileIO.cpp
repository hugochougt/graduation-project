/*
 * fileIO.cpp
 *
 *  Created on: 8 Nov, 2012
 *      Author: hugo
 */

#include "opencv2/core/core.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

class MyData {
public:
	MyData() :
			A(0), X(0), id() {
	}

	explicit MyData(int) :
			A(97), X(CV_PI), id("1234567") {
	}

	void write(FileStorage& fs) const {
		fs << "{" << "A" << A << "X" << X << "id" << id << "}";
	}

	void read(const FileNode& node) {
		A = (int) node["A"];
		X = (double) node["X"];
		id = (string) node["id"];
	}
public:
	int A;
	double X;
	string id;
};

void write(FileStorage& fs, const string&, const MyData& x) {
	x.write(fs);
}

void read(const FileNode& node, MyData& x, const MyData& defaultValue =
		MyData()) {
	if (node.empty())
		x = defaultValue;
	else
		x.read(node);
}

ostream& operator <<(ostream& out, const MyData& data) {
	out << "{ id = " << data.id << ", ";
	out << "X = " << data.X << ", ";
	out << "A = " << data.A << "}";
	return out;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Argument error." << endl;
		return 1;
	}

	string filename = argv[1];

	// write
    {
        Mat R = Mat_<uchar>::eye(3, 3);
        Mat T = Mat_<double>::zeros(3, 1);
        MyData data(1);

        FileStorage fs(filename, FileStorage::WRITE);

        fs << "iterationNr" << 100;
        fs << "strings" << "[";
        fs << "image.jpg" << "Awesomeness" << " photo.png";
        fs << "]";

        fs << "Mapping" << "{";
        fs<< "One" << 1 << "Two" << 2;
        fs << "}";

        fs << "R" << R;
        fs << "T" << T;

        fs << "MyData" << data;

        fs.release();
        cout << "Write done." << endl;
    }

    // read
    {
        cout << endl << "Reading" << endl;
        FileStorage fs;
        fs.open(filename, FileStorage::READ);

        if (!fs.isOpened()) {
            cout << "Fail to open " << filename << endl;
            return -1;
        }
        int itNr;
        itNr = (int) fs["iterationNr"];
        cout << itNr;

        FileNode n = fs["strings"];
        if (n.type() != FileNode::SEQ)
        {
            cerr << "strngs is not a sequence! FAIL" << endl;
            return 1;
        }

        FileNodeIterator it = n.begin(), itEnd = n.end();
        for (; it != itEnd; it++)
            cout << (string)*it << endl;

        n = fs["Mapping"];
        cout << "Two    " << (int) (n["Two"]) << "; ";
        cout << "One    " << (int) (n["One"]) << endl << endl;

        MyData data;
        Mat R, T;
        fs["R"] >> R;
        fs["T"] >> T;
        fs["MyData"] >> data;
        
        cout << endl;
        cout << "R = " << R << endl;
        cout << "T = " << T << endl;
        cout << "MyData = " << endl << data << endl << endl;

        // Show default behavior for non existing nodes
        cout << "Attempt to read NonExisting (should initialize the data structure with its default)." << endl;
        fs["NonExisting"] >> data;
        cout << "NonExisting = " << endl << data << endl;
    }

    return 0;
}
