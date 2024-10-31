#include "Logger.h"
#include <filesystem>

namespace Sean
{
    // Static instance
    Logger Logger::instance;

    // Constructor: Initializes the logger with a custom stream buffer
    Logger::Logger()
        : mLogFile(),                              // Initialize the log file
          mLoggerBuf(std::cout.rdbuf(), mLogFile), // Initialize the custom stream buffer with console and file buffers
          mOriginalCoutBuf(std::cout.rdbuf())      // Save the original cout buffer
    {
        createLogFile(); // Open the log file
        std::ostream::rdbuf(&mLoggerBuf); // Set the custom buffer for this stream
    }

    // Destructor: Closes the log file
    Logger::~Logger()
    {
        if (mLogFile.is_open())
            mLogFile.close();
    }

    // Get the current date and time as a string
    std::string Logger::getCurrentDateTime()
    {
        auto now = std::time(nullptr);
        std::tm tm;
        localtime_r(&now, &tm);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
        return oss.str();
    }

    // Create and open a log file with the current date and time in its name
    void Logger::createLogFile()
    {
        std::string folderPath = "../../../log";
        
        // Ensure the folder exists
        std::filesystem::create_directories(folderPath);

        std::string fileName = folderPath + "/GameLog_" + getCurrentDateTime() + ".log";
        instance.mLogFile.open(fileName, std::ios_base::out | std::ios_base::app);

        if (!instance.mLogFile.is_open()) {
            throw std::runtime_error("Failed to open log file: " + fileName);
        }
    }

    // Constructor: Initializes the custom stream buffer with console and file buffers
    Logger::LoggerBuf::LoggerBuf(std::streambuf *aConsoleBuf, std::ofstream &aFileStream)
        : mConsoleBuf(aConsoleBuf), mFileStream(aFileStream) {}

    // Write a character to both the console and the log file
    int Logger::LoggerBuf::overflow(int c)
    {
        if (c == EOF)
        {
            return !EOF;
        }
        else
        {
            int const r1 = mConsoleBuf->sputc(c);     // Write to console
            int const r2 = mFileStream.rdbuf()->sputc(c); // Write to file buffer
            return r1 == EOF || r2 == EOF ? EOF : c;
        }
    }

    // Synchronize the console and file buffers
    int Logger::LoggerBuf::sync()
    {
        int const r1 = mConsoleBuf->pubsync(); // Sync console buffer
        int const r2 = mFileStream.rdbuf()->pubsync();  // Sync file buffer
        return r1 == 0 && r2 == 0 ? 0 : -1;
    }

    // Static method to replace std::cout buffer
    void Logger::replaceCout()
    {
        std::cout.rdbuf(instance.rdbuf());
    }

    // Static method to get the original std::cout buffer
    std::streambuf* Logger::getOriginalCoutBuf()
    {
        return instance.mOriginalCoutBuf;
    }

} // namespace Sean