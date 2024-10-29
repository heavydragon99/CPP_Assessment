#include "SqlReader.h"
#include <filesystem>
#include <iostream>

/**
 * @brief Custom deleter for sqlite3 database.
 *
 * @param db Pointer to the sqlite3 database.
 */
void sqlite3Deleter(sqlite3* db)
{
    if (db)
    {
        sqlite3_close(db);
    }
}

SQLReader::SQLReader() : db(nullptr, sqlite3Deleter)
{
    openDatabase();
}

SQLReader::~SQLReader()
{
    // No need to call closeDatabase() explicitly as the custom deleter will handle it
}

void SQLReader::openDatabase()
{
    // Get the directory of the current file
    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path();
    // Construct the absolute path to the database file
    std::filesystem::path dbPath = currentPath / "../../sql/kerkersendraken.db";
    std::string dbPathStr = dbPath.lexically_normal().string();

    sqlite3* tempDb = nullptr;
    if (sqlite3_open(dbPathStr.c_str(), &tempDb) == SQLITE_OK)
    {
        db.reset(tempDb); // Transfer ownership to Sean::Object
    }
    else
    {
        std::cerr << "Error opening database!" << std::endl;
        if (tempDb)
        {
            sqlite3_close(tempDb);
        }
    }
}

void SQLReader::closeDatabase()
{
    db.reset(); // Reset the Sean::Object, which will call the custom deleter
}

SQLReader &SQLReader::getInstance()
{
    static SQLReader instance;
    return instance;
}

bool SQLReader::getLocationInfo(Sean::String &aName, Sean::String &aDescription)
{
    std::string query = "SELECT naam, beschrijving FROM Locaties WHERE naam = ?";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.get(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.get()) << std::endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, aName.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db.get()) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        aName.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        aDescription.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}

bool SQLReader::getRandomLocation(Sean::String &aName, Sean::String &aDescription)
{
    std::string query = "SELECT naam, beschrijving FROM Locaties ORDER BY RANDOM() LIMIT 1";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.get(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.get()) << std::endl;
        return false;
    }

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        aName.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        aDescription.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}

bool SQLReader::getEnemyInfo(Sean::String &aName, Sean::String &aDescription, int &aHealth, int &aAttackPercent, int &aMinDamage, int &aMaxDamage)
{
    std::string query = "SELECT naam, omschrijving, levenspunten, aanvalskans, minimumschade, maximumschade FROM Vijanden WHERE naam = ?";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.get(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.get()) << std::endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, aName.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db.get()) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        aName.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        aDescription.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
        aHealth = sqlite3_column_int(stmt, 2);
        aAttackPercent = sqlite3_column_int(stmt, 3);
        aMinDamage = sqlite3_column_int(stmt, 4);
        aMaxDamage = sqlite3_column_int(stmt, 5);
        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}

bool SQLReader::getRandomEnemy(Sean::String &aName, Sean::String &aDescription, int &aHealth, int &aAttackPercent, int &aMinDamage, int &aMaxDamage)
{
    std::string query = "SELECT naam, omschrijving, levenspunten, aanvalskans, minimumschade, maximumschade FROM Vijanden ORDER BY RANDOM() LIMIT 1";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.get(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.get()) << std::endl;
        return false;
    }

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        aName.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        aDescription.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
        aHealth = sqlite3_column_int(stmt, 2);
        aAttackPercent = sqlite3_column_int(stmt, 3);
        aMinDamage = sqlite3_column_int(stmt, 4);
        aMaxDamage = sqlite3_column_int(stmt, 5);
        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}

bool SQLReader::getObjectInfo(Sean::String &aName, Sean::String &aDescription, Sean::String &aType, int &aMinValue, int &aMaxValue, int &aProtection)
{
    std::string query = "SELECT naam, omschrijving, type, minimumwaarde, maximumwaarde, bescherming FROM Objecten WHERE naam = ?";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.get(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.get()) << std::endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, aName.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db.get()) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        aName.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        aDescription.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
        aType.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        aMinValue = sqlite3_column_int(stmt, 3);
        aMaxValue = sqlite3_column_int(stmt, 4);
        aProtection = sqlite3_column_int(stmt, 5);
        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}

bool SQLReader::getObjectAmount(Sean::String aName, int &aMinimum, int &aMaximum)
{
    std::string query = "SELECT minimumobjecten, maximumobjecten FROM Vijanden WHERE naam = ?";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.get(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.get()) << std::endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, aName.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db.get()) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        aMinimum = sqlite3_column_int(stmt, 0);
        aMaximum = sqlite3_column_int(stmt, 1);
        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}

bool SQLReader::getRandomObject(Sean::String &aName, Sean::String &aDescription, Sean::String &aType, int &aMinValue, int &aMaxValue, int &aProtection)
{
    std::string query = "SELECT naam, omschrijving, type, minimumwaarde, maximumwaarde, bescherming FROM Objecten ORDER BY RANDOM() LIMIT 1";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.get(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.get()) << std::endl;
        return false;
    }

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        aName.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        aDescription.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
        aType.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        aMinValue = sqlite3_column_int(stmt, 3);
        aMaxValue = sqlite3_column_int(stmt, 4);
        aProtection = sqlite3_column_int(stmt, 5);
        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}

void SQLReader::putHighscore(const Sean::String aName, int aScore)
{
    std::string query = "INSERT INTO Leaderboard (naam, goudstukken) VALUES (?, ?)";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.get(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.get()) << std::endl;
        return;
    }

    if (sqlite3_bind_text(stmt, 1, aName.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db.get()) << std::endl;
        sqlite3_finalize(stmt);
        return;
    }

    if (sqlite3_bind_int(stmt, 2, aScore) != SQLITE_OK)
    {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db.get()) << std::endl;
        sqlite3_finalize(stmt);
        return;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db.get()) << std::endl;
    }

    sqlite3_finalize(stmt);
}

bool SQLReader::getHighscore(Sean::String &aName, int &aScore, int aRank)
{
    std::string query = "SELECT naam, goudstukken FROM Leaderboard ORDER BY goudstukken DESC LIMIT 1 OFFSET ?";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.get(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.get()) << std::endl;
        return false;
    }

    if (sqlite3_bind_int(stmt, 1, aRank - 1) != SQLITE_OK)
    {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db.get()) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        aName.set(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        aScore = sqlite3_column_int(stmt, 1);
        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}