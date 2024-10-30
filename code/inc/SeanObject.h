#ifndef SEAN_OBJECT_H
#define SEAN_OBJECT_H

#include <utility>

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
        explicit Object(T *aPtr = nullptr) : mPtr(aPtr), mCustomDeleter(nullptr) {}

        /**
         * @brief Constructs an Object with a raw pointer and a custom deleter.
         *
         * @param aPtr A raw pointer to the object to manage.
         * @param aDeleter A custom deleter function to be called instead of the default destructor.
         */
        Object(T *aPtr, void (*aDeleter)(T *)) : mPtr(aPtr), mCustomDeleter(aDeleter) {}

        /**
         * @brief Destructor that deletes the managed object.
         */
        ~Object()
        {
            if (mCustomDeleter)
            {
                mCustomDeleter(mPtr);
            }
            else
            {
                delete mPtr;
            }
        }

        // Disable copy constructor and copy assignment
        Object(const Object &) = delete;
        Object &operator=(const Object &) = delete;

        /**
         * @brief Move constructor that transfers ownership from another Object.
         *
         * @param aOther The Object to move from.
         */
        Object(Object &&aOther) noexcept : mPtr(aOther.mPtr), mCustomDeleter(aOther.mCustomDeleter)
        {
            aOther.mPtr = nullptr;
            aOther.mCustomDeleter = nullptr;
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
                if (mCustomDeleter)
                {
                    mCustomDeleter(mPtr);
                }
                else
                {
                    delete mPtr;
                }
                mPtr = aOther.mPtr;
                mCustomDeleter = aOther.mCustomDeleter;
                aOther.mPtr = nullptr;
                aOther.mCustomDeleter = nullptr;
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
                if (mCustomDeleter)
                {
                    mCustomDeleter(mPtr);
                }
                else
                {
                    delete mPtr;
                }
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

        /**
         * @brief Allows the Sean::Object to be used where a reference to T is expected.
         *
         * @return A reference to the managed object.
         */
        operator T &() const
        {
            return *mPtr;
        }

    private:
        T *mPtr;                     ///< The raw pointer to the managed object.
        void (*mCustomDeleter)(T *); ///< Custom deleter function.
    };

} // namespace Sean

#endif // SEAN_OBJECT_H