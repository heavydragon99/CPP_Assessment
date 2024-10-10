#ifndef SEAN_OBJECT_H
#define SEAN_OBJECT_H

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
         * @param ptr A raw pointer to the object to manage. Defaults to nullptr.
         */
        explicit Object(T *ptr = nullptr) : ptr_(ptr) {}

        /**
         * @brief Destructor that deletes the managed object.
         */
        ~Object()
        {
            delete ptr_;
        }

        // Disable copy constructor and copy assignment
        Object(const Object &) = delete;
        Object &operator=(const Object &) = delete;

        /**
         * @brief Move constructor that transfers ownership from another Object.
         *
         * @param other The Object to move from.
         */
        Object(Object&& other) noexcept : ptr_(other.ptr_) {
            other.ptr_ = nullptr;
        }

        /**
         * @brief Move assignment operator that transfers ownership from another Object.
         *
         * @param other The Object to move from.
         * @return A reference to this Object.
         */
        Object& operator=(Object&& other) noexcept {
            if (this != &other) {
                delete ptr_;
                ptr_ = other.ptr_;
                other.ptr_ = nullptr;
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
            return ptr_;
        }

    private:
        T *ptr_; ///< The raw pointer to the managed object.
    };

} // namespace Sean

#endif // SEAN_OBJECT_H