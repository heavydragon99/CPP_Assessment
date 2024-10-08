#include <iostream>

namespace Sean
{
    /**
     * @brief A unique pointer implementation that manages a single object.
     *
     * @tparam T The type of the object to manage.
     */
    template <typename T>
    class UniquePtr
    {
    private:
        T *mPtr; ///< Raw pointer to the managed object.

    public:
        /**
         * @brief Constructor that initializes the UniquePtr with a raw pointer.
         *
         * The 'explicit' keyword prevents implicit conversions and copy-initialization.
         * Example:
         * @code
         * Sean::UniquePtr<int> ptr = new int(5); // Error: no viable conversion from 'int*' to 'UniquePtr<int>'
         * Sean::UniquePtr<int> ptr(new int(5)); // Correct: explicit constructor call
         * @endcode
         *
         * @param aPtr Raw pointer to the object to manage. Defaults to nullptr.
         */
        explicit UniquePtr(T *aPtr = nullptr) : mPtr(aPtr) {}

        /**
         * @brief Destructor that deletes the managed object.
         */
        ~UniquePtr()
        {
            delete mPtr;
        }

        /**
         * @brief Move constructor that transfers ownership from another UniquePtr.
         *
         * @param aOther The UniquePtr to move from.
         */
        UniquePtr(UniquePtr &&aOther) noexcept : mPtr(aOther.mPtr)
        {
            aOther.mPtr = nullptr;
        }

        /**
         * @brief Move assignment operator that transfers ownership from another UniquePtr.
         *
         * The parameter aOther is an rvalue reference to another UniquePtr object. The double ampersand (&&) indicates that aOther is an rvalue reference,
         * which means it can bind to temporary objects.
         * This is essential for move semantics, as it allows the resources of the temporary UniquePtr to be transferred to the current instance without copying.
         * 'noexcept' indicates that this operator does not throw any exceptions, which is important for performance and safety.
         * If a move constructor or move assignment operator throws an exception,
         * it can leave objects in a partially moved-from state,
         * which can lead to resource leaks or undefined behavior.
         *
         * @param aOther The UniquePtr to move from.
         * @return UniquePtr& Reference to the current instance.
         */
        UniquePtr &operator=(UniquePtr &&aOther) noexcept
        {
            if (this != &aOther)
            {
                delete mPtr;
                mPtr = aOther.mPtr;
                aOther.mPtr = nullptr;
            }
            return *this;
        }

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        UniquePtr(const UniquePtr &) = delete;

        /**
         * @brief Deleted copy assignment operator to prevent copying.
         *
         * @return UniquePtr& Reference to the current instance.
         */
        UniquePtr &operator=(const UniquePtr &) = delete;

        /**
         * @brief Dereference operator to access the managed object.
         *
         * @return T& Reference to the managed object.
         */
        T &operator*() const
        {
            return *mPtr;
        }

        /**
         * @brief Arrow operator to access the managed object's members.
         *
         * @return T* Pointer to the managed object.
         */
        T *operator->() const
        {
            return mPtr;
        }

        /**
         * @brief Get the raw pointer to the managed object.
         *
         * @return T* Raw pointer to the managed object.
         */
        T *get() const
        {
            return mPtr;
        }

                // Custom move method
        UniquePtr move()
        {
            UniquePtr temp(mPtr);
            mPtr = nullptr;
            return temp;
        }
    };
} // namespace Sean