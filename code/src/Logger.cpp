#include "Logger.h"
#include <filesystem>

namespace Sean
{
    // Static instance
    Logger Logger::instance;

    /**
     * @brief Constructor: Initializes the logger with a custom stream buffer.
     */
    Logger::Logger()
        : mLogFile(),                              // Initialize the log file
          mLoggerBuf(std::cout.rdbuf(), mLogFile), // Initialize the custom stream buffer with console and file buffers
          mOriginalCoutBuf(std::cout.rdbuf())      // Save the original cout buffer
    {
        createLogFile(); // Open the log file
        std::ostream::rdbuf(&mLoggerBuf); // Set the custom buffer for this stream
    }

    /**
     * @brief Destructor: Closes the log file.
     */
    Logger::~Logger()
    {
        if (mLogFile.is_open())
            mLogFile.close();
    }

    /**
     * @brief Get the current date and time as a string.
     * @return A string representing the current date and time.
     */
    std::string Logger::getCurrentDateTime()
    {
        auto now = std::time(nullptr);
        std::tm tm;
        localtime_r(&now, &tm);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
        return oss.str();
    }

    /**
     * @brief Create and open a log file with the current date and time in its name.
     */
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

    /**
     * @brief Constructor: Initializes the custom stream buffer with console and file buffers.
     * @param aConsoleBuf The original console buffer.
     * @param aFileStream The log file stream.
     */
    Logger::LoggerBuf::LoggerBuf(std::streambuf *aConsoleBuf, std::ofstream &aFileStream)
        : mConsoleBuf(aConsoleBuf), mFileStream(aFileStream) {}

    /**
     * @brief Write a character to both the console and the log file.
     * @param c The character to write.
     * @return The character written, or EOF on failure.
     */
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
            return r1 == EOF || r2 == EOF ? EOF : c; // Return EOF if either write failed
        }
    }

    /**
     * @brief Synchronize the console and file buffers.
     * @return 0 on success, -1 on failure.
     */
    int Logger::LoggerBuf::sync()
    {
        int const r1 = mConsoleBuf->pubsync(); // Flush console buffer to the console
        int const r2 = mFileStream.rdbuf()->pubsync();  // Flush file buffer to the file
        return r1 == 0 && r2 == 0 ? 0 : -1;
    }

    /**
     * @brief Replace the std::cout buffer with the custom logger buffer.
     */
    void Logger::replaceCout()
    {
        std::cout.rdbuf(instance.rdbuf());
    }

    /**
     * @brief Get the original std::cout buffer.
     * @return The original std::cout buffer.
     */
    std::streambuf* Logger::getOriginalCoutBuf()
    {
        return instance.mOriginalCoutBuf;
    }

} // namespace Sean