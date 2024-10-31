#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

namespace Sean {

class Logger : public std::ostream {
public:
    Logger();
    ~Logger();

    static std::string getCurrentDateTime();
    static void createLogFile();
    static void replaceCout();
    static std::streambuf* getOriginalCoutBuf(); // Add this method

private:
    class LoggerBuf : public std::streambuf {
    public:
        LoggerBuf(std::streambuf* aConsoleBuf, std::ofstream& aFileStream);
    protected:
        virtual int overflow(int c) override;
        virtual int sync() override;
    private:
        std::streambuf* mConsoleBuf;
        std::ofstream& mFileStream;
    };

    LoggerBuf mLoggerBuf;
    std::ofstream mLogFile;
    std::streambuf* mOriginalCoutBuf; // Add this member

    static Logger instance;
};

} // namespace Sean

#endif // LOGGER_H