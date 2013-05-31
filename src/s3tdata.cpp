#include "s3tdata.h"

s3tData::s3tData()
{
    transformation3d = N3D;

    char *defaultDir = getenv("HOME");
    if(defaultDir != NULL)
    {
        inFile = QString(defaultDir) + "/";
        outFile = QString(defaultDir) + "/";
    }
    else
    {
        inFile = "/";
        outFile = "/";
    }

    resolution = "1920x1080";
    font = "FreeSans";
    fontSize = 64;
}

s3tData::~s3tData()
{
}
