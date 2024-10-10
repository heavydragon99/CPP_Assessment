#ifndef SQLREADER_H
#define SQLREADER_H

#include "sqlite3.h"
#include "Sean.h"

class SQLReader
{
public:
    static SQLReader &getInstance();

    // Delete copy constructor and assignment operator to prevent copies
    SQLReader(const SQLReader &) = delete;
    SQLReader &operator=(const SQLReader &) = delete;

    bool getLocationInfo(const char* locationName, Sean::CharArray& name, Sean::CharArray& description);

private:
    SQLReader();  // Private constructor
    ~SQLReader(); // Private destructor

    void openDatabase();
    void closeDatabase();

    sqlite3 *db;
};

#endif // SQLREADER_H