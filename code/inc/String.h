#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstring>

namespace Sean
{

    /**
     * @class String
     * @brief A simple string class for managing dynamic character arrays.
     */
    class String
    {
    public:
        /**
         * @brief Default constructor. Initializes an empty string.
         */
        String() : mData(nullptr), mSize(0) {}

        /**
         * @brief Constructor that initializes the string with a C-string.
         * @param aStr The C-string to initialize with.
         */
        String(const char *aStr) : mData(nullptr), mSize(0)
        {
            set(aStr);
        }

        /**
         * @brief Copy constructor.
         * @param aOther The other String object to copy from.
         */
        String(const String &aOther) : mData(nullptr), mSize(0)
        {
            set(aOther.mData);
        }

        /**
         * @brief Move constructor.
         * @param aOther The other String object to move from.
         */
        String(String &&aOther) noexcept : mData(aOther.mData), mSize(aOther.mSize)
        {
            aOther.mData = nullptr;
            aOther.mSize = 0;
        }

        /**
         * @brief Copy assignment operator.
         * @param aOther The other String object to copy from.
         * @return Reference to this String object.
         */
        String &operator=(const String &aOther)
        {
            if (this != &aOther)
            {
                set(aOther.mData);
            }
            return *this;
        }

        /**
         * @brief Move assignment operator.
         * @param aOther The other String object to move from.
         * @return Reference to this String object.
         */
        String &operator=(String &&aOther) noexcept
        {
            if (this != &aOther)
            {
                // Free existing resource
                delete[] mData;

                // Transfer ownership of resource
                mData = aOther.mData;
                mSize = aOther.mSize;

                // Nullify the source object
                aOther.mData = nullptr;
                aOther.mSize = 0;
            }
            return *this;
        }

        /**
         * @brief Destructor. Cleans up the allocated memory.
         */
        ~String()
        {
            delete[] mData;
        }

        /**
         * @brief Sets the string to a new C-string.
         * @param aStr The new C-string to set.
         */
        void set(const char *aStr)
        {
            if (aStr)
            {
                size_t newSize = strlen(aStr);
                char *newData = new char[newSize + 1];
                try
                {
                    strcpy(newData, aStr);
                }
                catch (...)
                {
                    delete[] newData;
                    throw;
                }

                delete[] mData;
                mData = newData;
                mSize = newSize;
            }
            else
            {
                delete[] mData;
                mData = nullptr;
                mSize = 0;
            }
        }

        /**
         * @brief Gets the C-string representation of the string.
         * @return The C-string representation.
         */
        const char *get() const
        {
            return mData;
        }

        /**
         * @brief Gets the size of the string.
         * @return The size of the string.
         */
        size_t size() const
        {
            return mSize;
        }

        /**
         * @brief Checks if the string is empty.
         * @return True if the string is empty, false otherwise.
         */
        bool empty() const
        {
            return mSize == 0;
        }

        /**
         * @brief Clears the string, making it empty.
         */
        void clear()
        {
            delete[] mData;
            mData = nullptr;
            mSize = 0;
        }

        /**
         * @brief Appends a C-string to the current string.
         * @param aStr The C-string to append.
         * @return Reference to this String object.
         */
        String &append(const char *aStr)
        {
            if (aStr)
            {
                size_t newSize = mSize + strlen(aStr);
                char *newData = new char[newSize + 1];
                try
                {
                    if (mData)
                    {
                        strcpy(newData, mData);
                        strcat(newData, aStr);
                    }
                    else
                    {
                        strcpy(newData, aStr);
                    }
                }
                catch (...)
                {
                    delete[] newData;
                    throw;
                }

                delete[] mData;
                mData = newData;
                mSize = newSize;
            }
            return *this;
        }

        /**
         * @brief Concatenation operator.
         * @param aOther The other String object to concatenate.
         * @return A new String object that is the concatenation of this and aOther.
         */
        String operator+(const String &aOther) const
        {
            String result(*this);
            result.append(aOther.mData);
            return result;
        }

        /**
         * @brief Equality operator.
         * @param aOther The other String object to compare.
         * @return True if the strings are equal, false otherwise.
         */
        bool operator==(const String &aOther) const
        {
            return strcmp(mData, aOther.mData) == 0;
        }

        /**
         * @brief Equality operator for comparing with a C-string.
         * @param aStr The C-string to compare.
         * @return True if the strings are equal, false otherwise.
         */
        bool operator==(const char *aStr) const
        {
            return strcmp(mData, aStr) == 0;
        }

        /**
         * @brief Inequality operator.
         * @param aOther The other String object to compare.
         * @return True if the strings are not equal, false otherwise.
         */
        bool operator!=(const String &aOther) const
        {
            return !(*this == aOther);
        }

        /**
         * @brief Subscript operator for non-const objects.
         * @param index The index to access.
         * @return Reference to the character at the given index.
         */
        char &operator[](size_t index)
        {
            return mData[index];
        }

        /**
         * @brief Subscript operator for const objects.
         * @param index The index to access.
         * @return Const reference to the character at the given index.
         */
        const char &operator[](size_t index) const
        {
            return mData[index];
        }

        /**
         * @brief Stream insertion operator.
         * @param aOs The output stream.
         * @param aCharArray The String object to insert into the stream.
         * @return Reference to the output stream.
         */
        friend std::ostream &operator<<(std::ostream &aOs, const String &aCharArray)
        {
            if (aCharArray.mData)
            {
                aOs << aCharArray.mData;
            }
            return aOs;
        }

        /**
         * @brief Gets the C-string representation of the string.
         * @return The C-string representation.
         */
        const char *c_str() const
        {
            return mData;
        }

    private:
        char *mData;  ///< Pointer to the character array.
        size_t mSize; ///< Size of the string.
    };

} // namespace Sean

#endif // STRING_H