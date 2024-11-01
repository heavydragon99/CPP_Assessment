#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

namespace Sean
{

    /**
     * @class Logger
     * @brief A custom logger that redirects std::cout to both the console and a log file.
     */
    class Logger : public std::ostream
    {
    public:
        Logger();
        ~Logger();

        static std::string getCurrentDateTime();
        static void createLogFile();
        static void replaceCoutCin();
        static std::streambuf *getOriginalCoutBuf();
        static std::streambuf *getOriginalCinBuf();

    private:
        class LoggerBufCout : public std::streambuf
        {
        public:
            LoggerBufCout(std::streambuf *aConsoleBufCout, std::ofstream &aFileStream);

        protected:
            virtual int overflow(int c) override;
            virtual int sync() override;

        private:
            std::streambuf *mConsoleBufCout; ///< The original console buffer for Cout.
            std::ofstream &mFileStream;      ///< The log file stream.
        };

        class LoggerBufCin : public std::streambuf
        {
        public:
            LoggerBufCin(std::streambuf *aCinBuf, std::ofstream &aFileStream);

        protected:
            int uflow() override;
            int underflow() override;

        private:
            std::streambuf *mCinBuf;
            std::ofstream &mFileStream;
        };

        LoggerBufCout mLoggerBufCout;     ///< The custom stream buffer for cout.
        LoggerBufCin mLoggerBufCin;       ///< The custom stream buffer for cin.
        std::ofstream mLogFile;           ///< The log file stream.
        std::streambuf *mOriginalCoutBuf; ///< The original std::cout buffer.
        std::streambuf *mOriginalCinBuf;  ///< The original std::cin buffer.

        static Logger instance; ///< The static logger instance.
    };

} // namespace Sean

#endif // LOGGER_H