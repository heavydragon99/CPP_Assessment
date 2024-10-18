#ifndef SEAN_OBJECT_H
#define SEAN_OBJECT_H

#include <utility> // For std::move

namespace Sean
{
    /**
     * @brief A RAII wrapper for managing a dynamically allocated object.
     *
     * @tparam T The type of the object being managed.
     */
    template <typename T>
    class Object
    {
    public:
        /**
         * @brief Constructs an Object with an optional raw pointer.
         *
         * @param aPtr A raw pointer to the object to manage. Defaults to nullptr.
         */
        explicit Object(T *aPtr = nullptr) : mPtr(aPtr) {}

        /**
         * @brief Destructor that deletes the managed object.
         */
        ~Object()
        {
            delete mPtr;
        }

        // Disable copy constructor and copy assignment
        Object(const Object &) = delete;
        Object &operator=(const Object &) = delete;

        /**
         * @brief Move constructor that transfers ownership from another Object.
         *
         * @param aOther The Object to move from.
         */
        Object(Object &&aOther) noexcept : mPtr(aOther.mPtr)
        {
            aOther.mPtr = nullptr;
        }

        /**
         * @brief Move assignment operator that transfers ownership from another Object.
         *
         * @param aOther The Object to move from.
         * @return A reference to this Object.
         */
        Object &operator=(Object &&aOther) noexcept
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
         * @brief Accesses the raw pointer managed by this Object.
         *
         * @return A raw pointer to the managed object.
         */
        T *get() const
        {
            return mPtr;
        }

        /**
         * @brief Resets the managed pointer to a new pointer.
         *
         * @param aPtr A raw pointer to the new object to manage.
         */
        void reset(T *aPtr = nullptr)
        {
            if (mPtr != aPtr)
            {
                delete mPtr;
                mPtr = aPtr;
            }
        }

        /**
         * @brief Dereferences the managed pointer.
         *
         * @return A reference to the managed object.
         */
        T &operator*() const
        {
            return *mPtr;
        }

        /**
         * @brief Accesses the managed object's members.
         *
         * @return A pointer to the managed object.
         */
        T *operator->() const
        {
            return mPtr;
        }
        /**
         * @brief Releases ownership of the managed object without deleting it.
         *
         * @return A raw pointer to the managed object.
         */
        T *release()
        {
            T *temp = mPtr;
            mPtr = nullptr;
            return temp;
        }
        

    private:
        T *mPtr; ///< The raw pointer to the managed object.
    };

} // namespace Sean

#endif // SEAN_OBJECT_H