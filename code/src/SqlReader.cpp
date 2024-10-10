#include "SqlReader.h"
#include <filesystem>
#include <iostream>

SQLReader::SQLReader() : db(nullptr)
{
    openDatabase();
}

SQLReader::~SQLReader()
{
    closeDatabase();
}

void SQLReader::openDatabase()
{
    // Get the directory of the current file
    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path();
    // Construct the absolute path to the database file
    std::filesystem::path dbPath = currentPath / "../../sql/kerkersendraken.db";
    std::string dbPathStr = dbPath.lexically_normal().string();

    if (sqlite3_open(dbPathStr.c_str(), &db) == SQLITE_OK)
    {
        std::cout << "Database opened successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Error opening database!" << std::endl;
    }
}

void SQLReader::closeDatabase()
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

SQLReader &SQLReader::getInstance()
{
    static SQLReader instance;
    return instance;
}

bool SQLReader::getLocationInfo(const char* locationName, Sean::CharArray& name, Sean::CharArray& description)
{
    std::string query = "SELECT naam, beschrijving FROM Locaties WHERE naam = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, locationName, -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        name.set(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        description.set(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}