#include <iostream>
#include <filesystem>

#include "sqlite3.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    // Get the directory of the current file
    std::filesystem::path currentPath = std::filesystem::path(__FILE__).parent_path();
    // Construct the absolute path to the database file
    std::filesystem::path dbPath = currentPath / "../../sql/kerkersendraken.db";
    std::string dbPathStr = dbPath.lexically_normal().string();
    std::cout << "Database path: " << dbPathStr << std::endl;


    sqlite3 *db;
    if(sqlite3_open(dbPathStr.c_str(), &db) == SQLITE_OK) {
        std::cout << "Database opened successfully!" << std::endl;
    } else {
        std::cerr << "Error opening database!" << std::endl;
    }

    sqlite3_close(db);

    return 0;
}