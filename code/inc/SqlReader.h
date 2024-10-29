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

    bool getLocationInfo(Sean::String& aName, Sean::String& aDescription);
    bool getRandomLocation(Sean::String& aName, Sean::String& aDescription);
    bool getEnemyInfo(Sean::String& aName, Sean::String& aDescription, int& aHealth, int& aAttackPercent, int& aMinDamage, int& aMaxDamage);
    bool getRandomEnemy(Sean::String& aName, Sean::String& aDescription, int& aHealth, int& aAttackPercent, int& aMinDamage, int& aMaxDamage);
    bool getObjectInfo(Sean::String& aName, Sean::String& aDescription, Sean::String& aType, int& aMinValue, int& aMaxValue, int& aProtection);
    bool getObjectAmount(Sean::String aName, int& aMinimum, int& aMaximum);
    bool getRandomObject(Sean::String& aName, Sean::String& aDescription, Sean::String& aType, int& aMinValue, int& aMaxValue, int& aProtection);

private:
    SQLReader();  // Private constructor
    ~SQLReader(); // Private destructor

    void openDatabase();
    void closeDatabase();

    Sean::Object<sqlite3> db;
};

#endif // SQLREADER_H