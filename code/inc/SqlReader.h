#ifndef SQLREADER_H
#define SQLREADER_H

#include "sqlite3.h"
#include "Sean.h"

class SQLReader
{
public:
    // Constructors
    static SQLReader &getInstance();

    // Delete copy constructor and assignment operator to prevent copies
    SQLReader(const SQLReader &) = delete;
    SQLReader &operator=(const SQLReader &) = delete;

    // Destructor
    ~SQLReader() = default;

    // Methods
    bool getLocationInfo(Sean::String &aName, Sean::String &aDescription) const;
    bool getRandomLocation(Sean::String &aName, Sean::String &aDescription) const;
    bool getEnemyInfo(Sean::String &aName, Sean::String &aDescription, int &aHealth, int &aAttackPercent, int &aMinDamage, int &aMaxDamage) const;
    bool getRandomEnemy(Sean::String &aName, Sean::String &aDescription, int &aHealth, int &aAttackPercent, int &aMinDamage, int &aMaxDamage) const;
    bool getObjectInfo(Sean::String &aName, Sean::String &aDescription, Sean::String &aType, int &aMinValue, int &aMaxValue, int &aProtection) const;
    bool getObjectAmount(Sean::String aName, int &aMinimum, int &aMaximum) const;
    bool getRandomObject(Sean::String &aName, Sean::String &aDescription, Sean::String &aType, int &aMinValue, int &aMaxValue, int &aProtection) const;
    void putHighscore(const Sean::String aName, int aScore) const;
    bool getHighscore(Sean::String &aName, int &aScore, int aRank) const;

private:
    // Private Methods
    void openDatabase();
    void closeDatabase();

private:
    // Members
    Sean::Object<sqlite3> db;

private:
    // Constructors
    SQLReader(); // Private constructor
};

#endif // SQLREADER_H