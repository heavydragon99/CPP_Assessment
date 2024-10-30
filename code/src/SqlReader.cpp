#include "SqlReader.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>

/**
 * @brief Custom deleter for sqlite3 database.
 *
 * @param db Pointer to the sqlite3 database.
 */
void sqlite3Deleter(sqlite3 *db)
{
    if (db)
    {
        sqlite3_close(db);
    }
}

// Constructors

/**
 * @brief Constructs an SQLReader object and opens the database.
 */
SQLReader::SQLReader() : db(nullptr, sqlite3Deleter)
{
    openDatabase();
}

// Methods

/**
 * @brief Prepares and binds a SQLite statement.
 * 
 * @param query The SQL query string.
 * @param stmt Pointer to the SQLite statement.
 * @param bindText The text to bind to the statement.
 * @return bool True if the statement was successfully prepared and bound, false otherwise.
 */
bool SQLReader::prepareAndBindStatement(const std::string &query, sqlite3_stmt **stmt, const char *bindText) const
{
    if (sqlite3_prepare_v2(db.get(), query.c_str(), -1, stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.get()) << std::endl;
        return false;
    }

    if (bindText && sqlite3_bind_text(*stmt, 1, bindText, -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db.get()) << std::endl;
        sqlite3_finalize(*stmt);
        return false;
    }

    return true;
}

/**
 * @brief Retrieves location information from the database.
 * 
 * @param aName The name of the location.
 * @param aDescription The description of the location.
 * @return bool True if the location information was successfully retrieved, false otherwise.
 */
bool SQLReader::getLocationInfo(Sean::String &aName, Sean::String &aDescription) const
{
    std::string query = "SELECT naam, beschrijving FROM Locaties WHERE naam = ?";
    sqlite3_stmt *stmt;
    if (!prepareAndBindStatement(query, &stmt, aName.c_str()))
    {
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

/**
 * @brief Retrieves a random location from the database.
 * 
 * @param aName The name of the location.
 * @param aDescription The description of the location.
 * @return bool True if a random location was successfully retrieved, false otherwise.
 */
bool SQLReader::getRandomLocation(Sean::String &aName, Sean::String &aDescription) const
{
    std::string query = "SELECT naam, beschrijving FROM Locaties ORDER BY RANDOM() LIMIT 1";
    sqlite3_stmt *stmt;
    if (!prepareAndBindStatement(query, &stmt, nullptr))
    {
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

/**
 * @brief Retrieves enemy information from the database.
 * 
 * @param aName The name of the enemy.
 * @param aDescription The description of the enemy.
 * @param aHealth The health of the enemy.
 * @param aAttackPercent The attack percentage of the enemy.
 * @param aMinDamage The minimum damage of the enemy.
 * @param aMaxDamage The maximum damage of the enemy.
 * @return bool True if the enemy information was successfully retrieved, false otherwise.
 */
bool SQLReader::getEnemyInfo(Sean::String &aName, Sean::String &aDescription, int &aHealth, int &aAttackPercent, int &aMinDamage, int &aMaxDamage) const
{
    std::string query = "SELECT naam, omschrijving, levenspunten, aanvalskans, minimumschade, maximumschade FROM Vijanden WHERE naam = ?";
    sqlite3_stmt *stmt;
    if (!prepareAndBindStatement(query, &stmt, aName.c_str()))
    {
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

/**
 * @brief Retrieves a random enemy from the database.
 * 
 * @param aName The name of the enemy.
 * @param aDescription The description of the enemy.
 * @param aHealth The health of the enemy.
 * @param aAttackPercent The attack percentage of the enemy.
 * @param aMinDamage The minimum damage of the enemy.
 * @param aMaxDamage The maximum damage of the enemy.
 * @return bool True if a random enemy was successfully retrieved, false otherwise.
 */
bool SQLReader::getRandomEnemy(Sean::String &aName, Sean::String &aDescription, int &aHealth, int &aAttackPercent, int &aMinDamage, int &aMaxDamage) const
{
    std::string query = "SELECT naam, omschrijving, levenspunten, aanvalskans, minimumschade, maximumschade FROM Vijanden ORDER BY RANDOM() LIMIT 1";
    sqlite3_stmt *stmt;
    if (!prepareAndBindStatement(query, &stmt, nullptr))
    {
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

/**
 * @brief Retrieves object information from the database.
 * 
 * @param aName The name of the object.
 * @param aDescription The description of the object.
 * @param aType The type of the object.
 * @param aMinValue The minimum value of the object.
 * @param aMaxValue The maximum value of the object.
 * @param aProtection The protection value of the object.
 * @return bool True if the object information was successfully retrieved, false otherwise.
 */
bool SQLReader::getObjectInfo(Sean::String &aName, Sean::String &aDescription, Sean::String &aType, int &aMinValue, int &aMaxValue, int &aProtection) const
{
    std::string query = "SELECT naam, omschrijving, type, minimumwaarde, maximumwaarde, bescherming FROM Objecten WHERE naam = ?";
    sqlite3_stmt *stmt;
    if (!prepareAndBindStatement(query, &stmt, aName.c_str()))
    {
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

/**
 * @brief Retrieves the amount of objects associated with an enemy from the database.
 * 
 * @param aName The name of the enemy.
 * @param aMinimum The minimum amount of objects.
 * @param aMaximum The maximum amount of objects.
 * @return bool True if the object amount was successfully retrieved, false otherwise.
 */
bool SQLReader::getObjectAmount(Sean::String aName, int &aMinimum, int &aMaximum) const
{
    std::string query = "SELECT minimumobjecten, maximumobjecten FROM Vijanden WHERE naam = ?";
    sqlite3_stmt *stmt;
    if (!prepareAndBindStatement(query, &stmt, aName.c_str()))
    {
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

/**
 * @brief Retrieves a random object from the database.
 * 
 * @param aName The name of the object.
 * @param aDescription The description of the object.
 * @param aType The type of the object.
 * @param aMinValue The minimum value of the object.
 * @param aMaxValue The maximum value of the object.
 * @param aProtection The protection value of the object.
 * @return bool True if a random object was successfully retrieved, false otherwise.
 */
bool SQLReader::getRandomObject(Sean::String &aName, Sean::String &aDescription, Sean::String &aType, int &aMinValue, int &aMaxValue, int &aProtection) const
{
    std::string query = "SELECT naam, omschrijving, type, minimumwaarde, maximumwaarde, bescherming FROM Objecten ORDER BY RANDOM() LIMIT 1";
    sqlite3_stmt *stmt;
    if (!prepareAndBindStatement(query, &stmt, nullptr))
    {
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

/**
 * @brief Inserts a high score into the leaderboard.
 * 
 * @param aName The name of the player.
 * @param aScore The score of the player.
 */
void SQLReader::putHighscore(const Sean::String aName, int aScore) const
{
    std::string query = "INSERT INTO Leaderboard (naam, goudstukken) VALUES (?, ?)";
    sqlite3_stmt *stmt;
    if (!prepareAndBindStatement(query, &stmt, aName.c_str()))
    {
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

/**
 * @brief Retrieves a high score from the leaderboard.
 * 
 * @param aName The name of the player.
 * @param aScore The score of the player.
 * @param aRank The rank of the high score to retrieve.
 * @return bool True if the high score was successfully retrieved, false otherwise.
 */
bool SQLReader::getHighscore(Sean::String &aName, int &aScore, int aRank) const
{
    std::string query = "SELECT naam, goudstukken FROM Leaderboard ORDER BY goudstukken DESC LIMIT 1 OFFSET ?";
    sqlite3_stmt *stmt;
    if (!prepareAndBindStatement(query, &stmt, nullptr))
    {
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

// Private Methods

/**
 * @brief Opens the database.
 */
void SQLReader::openDatabase()
{
    // Get the directory of the current file
    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path();
    // Construct the absolute path to the database file
    std::filesystem::path dbPath = currentPath / "../../sql/kerkersendraken.db";
    std::string dbPathStr = dbPath.lexically_normal().string();

    sqlite3 *tempDb = nullptr;
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

/**
 * @brief Closes the database.
 */
void SQLReader::closeDatabase()
{
    db.reset(); // Reset the Sean::Object, which will call the custom deleter
}

/**
 * @brief Gets the singleton instance of SQLReader.
 * 
 * @return SQLReader& Reference to the singleton instance of SQLReader.
 */
SQLReader &SQLReader::getInstance()
{
    static SQLReader instance;
    return instance;
}