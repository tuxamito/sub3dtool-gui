#ifndef S3TSUBCONF_H
#define S3TSUBCONF_H

#include <QString>
#include "s3tdata.h"

struct s3tSubConf {
    QString inFile;
    QString outFile;
    s3tData data;
};

#endif // S3TSUBCONF_H
