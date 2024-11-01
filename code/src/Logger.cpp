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
        : mLogFile(),                                  // Initialize the log file
          mLoggerBufCout(std::cout.rdbuf(), mLogFile), // Initialize the custom stream buffer cout with console and file buffers
          mLoggerBufCin(std::cin.rdbuf(), mLogFile),   // Initialize the custom stream buffer cin with console and file buffers
          mOriginalCoutBuf(std::cout.rdbuf()),         // Save the original cout buffer with unique_ptr
          mOriginalCinBuf(std::cin.rdbuf())            // Save the original cin buffer with unique_ptr
    {
    }

    /**
     * @brief Destructor: Closes the log file and restores the original buffers.
     */
    Logger::~Logger()
    {
        if (mLogFile.is_open())
        {
            mLogFile.close();
        }

        // Restore the original std::cout and std::cin buffers
        std::cout.rdbuf(mOriginalCoutBuf);
        std::cin.rdbuf(mOriginalCinBuf);
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
        if (instance.mLogFile.is_open())
        {
            instance.mLogFile.close();
        }
        std::string folderPath = "../../../log";

        // Ensure the folder exists
        if (!std::filesystem::exists(folderPath) && !std::filesystem::create_directories(folderPath))
        {
            throw std::runtime_error("Failed to create log directory: " + folderPath);
        }

        std::string fileName = folderPath + "/GameLog_" + getCurrentDateTime() + ".log";
        instance.mLogFile.open(fileName, std::ios_base::out | std::ios_base::app);

        if (!instance.mLogFile.is_open())
        {
            throw std::runtime_error("Failed to open log file: " + fileName);
        }
    }

    /**
     * @brief Constructor: Initializes the custom stream buffer with console and file buffers.
     * @param aConsoleBufCout The original console buffer.
     * @param aFileStream The log file stream.
     */
    Logger::LoggerBufCout::LoggerBufCout(std::streambuf *aConsoleBufCout, std::ofstream &aFileStream)
        : mConsoleBufCout(aConsoleBufCout), mFileStream(aFileStream) {}

    /**
     * @brief Write a character to both the console and the log file.
     * @param c The character to write.
     * @return The character written, or EOF on failure.
     */
    int Logger::LoggerBufCout::overflow(int c)
    {
        if (c == EOF)
        {
            return !EOF;
        }
        else
        {
            int const r1 = mConsoleBufCout->sputc(c);     // Write to console
            int const r2 = mFileStream.rdbuf()->sputc(c); // Write to file buffer
            return r1 == EOF || r2 == EOF ? EOF : c;      // Return EOF if either write failed
        }
    }

    /**
     * @brief Synchronize the console and file buffers.
     * @return 0 on success, -1 on failure.
     */
    int Logger::LoggerBufCout::sync()
    {
        int const r1 = mConsoleBufCout->pubsync();     // Flush console buffer to the console
        int const r2 = mFileStream.rdbuf()->pubsync(); // Flush file buffer to the file
        return r1 == 0 && r2 == 0 ? 0 : -1;
    }

    /**
     * @brief LoggerBufCin constructor: Initializes with cin and file buffers.
     */
    Logger::LoggerBufCin::LoggerBufCin(std::streambuf *aCinBuf, std::ofstream &aFileStream)
        : mCinBuf(aCinBuf), mFileStream(aFileStream) {}

    /**
     * @brief LoggerBufCin uflow: Get a character from cin and log it to the file.
     * @return The character read from cin.
     */
    int Logger::LoggerBufCin::uflow()
    {
        int ch = mCinBuf->sbumpc(); // Get a character from std::cin
        if (ch != EOF)
        {
            mFileStream.put(static_cast<char>(ch)); // Log the character to the file
            mFileStream.flush();
        }
        return ch;
    }

    /**
     * @brief LoggerBufCin underflow: Peek the next character from cin.
     * @return The next character from cin.
     */
    int Logger::LoggerBufCin::underflow()
    {
        return mCinBuf->sgetc(); // Peek the next character from std::cin
    }

    /**
     * @brief Replace std::cout with the custom logger buffer.
     */
    void Logger::replaceCoutCin()
    {
        std::cout.rdbuf(&instance.mLoggerBufCout);
        std::cin.rdbuf(&instance.mLoggerBufCin);
    }

    /**
     * @brief Get the original std::cout buffer.
     * @return The original std::cout buffer.
     */
    std::streambuf *Logger::getOriginalCoutBuf()
    {
        return instance.mOriginalCoutBuf;
    }

    /**
     * @brief Get the original std::cin buffer.
     * @return The original std::cin buffer.
     */
    std::streambuf *Logger::getOriginalCinBuf()
    {
        return instance.mOriginalCinBuf;
    }

} // namespace Sean
