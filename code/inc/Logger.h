#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

namespace Sean {

/**
 * @class Logger
 * @brief A custom logger that redirects std::cout to both the console and a log file.
 */
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
        std::streambuf* mConsoleBuf; ///< The original console buffer.
        std::ofstream& mFileStream;  ///< The log file stream.
    };

    LoggerBuf mLoggerBuf; ///< The custom stream buffer.
    std::ofstream mLogFile; ///< The log file stream.
    std::streambuf* mOriginalCoutBuf; ///< The original std::cout buffer.

    static Logger instance; ///< The static logger instance.
};

} // namespace Sean

#endif // LOGGER_H