#include <iostream>
#include <stdexcept>

namespace Sean
{
    /**
     * @brief A dynamic array implementation similar to std::vector.
     *
     * @tparam T The type of the elements stored in the vector.
     */
    template <typename T>
    class Vector
    {
    private:
        T *mData;         ///< Pointer to the array of elements.
        size_t mSize;     ///< Number of elements in the vector.
        size_t mCapacity; ///< Capacity of the vector.

        /**
         * @brief Resizes the vector to a new capacity.
         *
         * @param aNewCapacity The new capacity of the vector.
         */
        void resize(size_t aNewCapacity)
        {
            T *newData = new T[aNewCapacity];
            for (size_t i = 0; i < mSize; ++i)
            {
                newData[i] = std::move(mData[i]);
            }
            delete[] mData;
            mData = newData;
            mCapacity = aNewCapacity;
        }

    public:
        /**
         * @brief Default constructor that initializes an empty vector.
         */
        Vector() : mData(nullptr), mSize(0), mCapacity(0) {}

        /**
         * @brief Destructor that deletes the array of elements.
         */
        ~Vector()
        {
            delete[] mData;
        }

        /**
         * @brief Copy constructor that creates a new vector as a copy of an existing one.
         * @param aOther The vector to copy from.
         */
        Vector(const Vector &aOther) : mData(nullptr), mSize(aOther.mSize), mCapacity(aOther.mCapacity)
        {
            if (mCapacity > 0)
            {
                mData = new T[mCapacity];
                for (size_t i = 0; i < mSize; ++i)
                {
                    mData[i] = aOther.mData[i];
                }
            }
        }

        /**
         * @brief Copy assignment operator that assigns the contents of one vector to another.
         * @param aOther The vector to assign from.
         * @return Reference to the assigned vector.
         */
        Vector &operator=(const Vector &aOther)
        {
            if (this != &aOther)
            {
                // Create a copy of the other vector
                T *newData = new T[aOther.mCapacity];
                for (size_t i = 0; i < aOther.mSize; ++i)
                {
                    newData[i] = aOther.mData[i];
                }

                // Release the current object's resources
                delete[] mData;

                // Assign the new data to the current object
                mData = newData;
                mSize = aOther.mSize;
                mCapacity = aOther.mCapacity;
            }
            return *this;
        }

        /**
         * @brief Move constructor that transfers ownership from a temporary vector to a new one.
         * @param aOther The vector to move from.
         */
        Vector(Vector &&aOther) noexcept : mData(aOther.mData), mSize(aOther.mSize), mCapacity(aOther.mCapacity)
        {
            aOther.mData = nullptr;
            aOther.mSize = 0;
            aOther.mCapacity = 0;
        }

        /**
         * @brief Move assignment operator that transfers ownership from a temporary vector to an existing one.
         * @param aOther The vector to move from.
         * @return Reference to the assigned vector.
         */
        Vector &operator=(Vector &&aOther) noexcept
        {
            if (this != &aOther)
            {
                delete[] mData;
                mData = aOther.mData;
                mSize = aOther.mSize;
                mCapacity = aOther.mCapacity;
                aOther.mData = nullptr;
                aOther.mSize = 0;
                aOther.mCapacity = 0;
            }
            return *this;
        }

        /**
         * @brief Adds an element to the end of the vector.
         *
         * @param aValue The value to add to the vector.
         */
        void push_back(const T &aValue)
        {
            if (mSize == mCapacity)
            {
                resize(mCapacity == 0 ? 1 : mCapacity * 2);
            }
            mData[mSize++] = aValue;
        }

        /**
         * @brief Adds an element to the end of the vector using move semantics.
         *
         * This function is used to add an element to the vector by moving it, which is more efficient
         * than copying when the element is a temporary object or an object that supports move semantics.
         *
         * @param aValue The value to add to the vector.
         */
        void push_back(T &&aValue)
        {
            if (mSize == mCapacity)
            {
                resize(mCapacity == 0 ? 1 : mCapacity * 2);
            }
            mData[mSize++] = std::move(aValue);
        }

        /**
         * @brief Removes the last element from the vector.
         *
         * @throws std::out_of_range if the vector is empty.
         */
        void pop_back()
        {
            if (mSize == 0)
            {
                throw std::out_of_range("Vector is empty");
            }
            --mSize;
        }

        /**
         * @brief Returns the number of elements in the vector.
         *
         * @return The number of elements in the vector.
         */
        size_t size() const
        {
            return mSize;
        }

        /**
         * @brief Returns the capacity of the vector.
         *
         * @return The capacity of the vector.
         */
        size_t capacity() const
        {
            return mCapacity;
        }

        /**
         * @brief Accesses the element at the given index.
         *
         * @param aIndex The index of the element to access.
         * @return A reference to the element at the given index.
         * @throws std::out_of_range if the index is out of range.
         */
        T &operator[](size_t aIndex)
        {
            if (aIndex >= mSize)
            {
                throw std::out_of_range("Index out of range");
            }
            return mData[aIndex];
        }

        /**
         * @brief Accesses the element at the given index (const version).
         *
         * @param aIndex The index of the element to access.
         * @return A const reference to the element at the given index.
         * @throws std::out_of_range if the index is out of range.
         */
        const T &operator[](size_t aIndex) const
        {
            if (aIndex >= mSize)
            {
                throw std::out_of_range("Index out of range");
            }
            return mData[aIndex];
        }

        /**
         * @brief Checks if the vector is empty.
         *
         * @return True if the vector is empty, false otherwise.
         */
        bool empty() const
        {
            if (mSize == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * @brief Returns a pointer to the first element of the vector.
         *
         * This function returns a pointer to the first element of the vector. If the vector is empty,
         * it returns a nullptr.
         *
         * @return A pointer to the first element of the vector.
         */
        T *begin()
        {
            return mData;
        }

        /**
         * @brief Returns a pointer to the element following the last element of the vector.
         *
         * This function returns a pointer to the element following the last element of the vector.
         * This pointer acts as a placeholder; attempting to dereference it results in undefined behavior.
         *
         * @return A pointer to the element following the last element of the vector.
         */
        T *end()
        {
            return mData + mSize;
        }

        /**
         * @brief Returns a pointer to the first element of the vector.
         *
         * This function returns a pointer to the first element of the vector. If the vector is empty,
         * it returns a nullptr.
         *
         * @return A pointer to the first element of the vector.
         */
        const T *begin() const
        {
            return mData;
        }

        /**
         * @brief Returns a pointer to the element following the last element of the vector.
         *
         * This function returns a pointer to the element following the last element of the vector.
         * This pointer acts as a placeholder; attempting to dereference it results in undefined behavior.
         *
         * @return A pointer to the element following the last element of the vector.
         */
        const T *end() const
        {
            return mData + mSize;
        }

        /**
         * @brief Clears the vector.
         *
         * This function deallocates the memory used by the vector's elements and resets the size and capacity to zero.
         */
        void clear()
        {
            delete[] mData;
            mData = nullptr;
            mSize = 0;
            mCapacity = 0;
        }
    };
} // namespace Sean