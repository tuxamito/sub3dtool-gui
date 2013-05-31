#ifndef S3TDATA_H
#define S3TDATA_H

#include <QString>

enum type3d {N3D, SBS, TB};

class s3tData
{
public:
    s3tData();
    ~s3tData();

    type3d transformation3d;
    QString inFile;
    QString outFile;
    QString resolution;
    QString font;
    int fontSize;
};

#endif // S3TDATA_H
