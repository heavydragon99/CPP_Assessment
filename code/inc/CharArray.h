#ifndef CHARARRAY_H
#define CHARARRAY_H

#include <iostream>
#include <cstring>

namespace Sean {

/**
 * @class CharArray
 * @brief A class to manage dynamic char arrays.
 */
class CharArray {
public:
    /**
     * @brief Default constructor.
     */
    CharArray() : mData(nullptr) {}

    /**
     * @brief Parameterized constructor.
     * @param aStr The initial string to set.
     */
    CharArray(const char* aStr) : mData(nullptr) {
        set(aStr);
    }

    /**
     * @brief Copy constructor.
     * @param aOther The CharArray object to copy from.
     */
    CharArray(const CharArray& aOther) : mData(nullptr) {
        set(aOther.mData);
    }

    /**
     * @brief Move constructor.
     * @param aOther The CharArray object to move from.
     */
    CharArray(CharArray&& aOther) noexcept : mData(aOther.mData) {
        aOther.mData = nullptr;
    }

    /**
     * @brief Assignment operator.
     * @param aOther The CharArray object to assign from.
     * @return Reference to the assigned CharArray object.
     */
    CharArray& operator=(const CharArray& aOther) {
        if (this != &aOther) {
            set(aOther.mData);
        }
        return *this;
    }

    /**
     * @brief Move assignment operator.
     * @param aOther The CharArray object to move from.
     * @return Reference to the assigned CharArray object.
     */
    CharArray& operator=(CharArray&& aOther) noexcept {
        if (this != &aOther) {
            delete[] mData;
            mData = aOther.mData;
            aOther.mData = nullptr;
        }
        return *this;
    }

    /**
     * @brief Destructor.
     */
    ~CharArray() {
        delete[] mData;
    }

        /**
     * @brief Overloads the << operator to print the contents of the CharArray.
     * @param aOs The output stream.
     * @param aCharArray The CharArray object to print.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& aOs, const CharArray& aCharArray) {
        if (aCharArray.mData) {
            aOs << aCharArray.mData;
        }
        return aOs;
    }

    /**
     * @brief Sets the char array.
     * @param aStr The string to set.
     */
    void set(const char* aStr) {
        delete[] mData; // Free existing memory
        if (aStr) {
            mData = new char[strlen(aStr) + 1];
            strcpy(mData, aStr);
        } else {
            mData = nullptr;
        }
    }

    /**
     * @brief Gets the char array.
     * @return Pointer to the char array.
     */
    const char* get() const {
        return mData;
    }

private:
    char* mData; ///< Pointer to the dynamic char array
};

} // namespace Sean

#endif // CHARARRAY_H