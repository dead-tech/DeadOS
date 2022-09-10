#pragma once

#include "Assert.hpp"
#include "Memory.hpp"
#include "Types.hpp"
#include "Utility.hpp"

#include <initializer_list>

namespace dts {

template<typename T>
class Vector
{
  public:
    Vector() = default;
    Vector(const T *begin, const T *end);
    Vector(std::initializer_list<T> initializer_list);
    Vector(const Vector &other);
    Vector(Vector &&other) noexcept;
    Vector &operator=(const Vector &other);
    Vector &operator=(Vector &&other) noexcept;
    ~Vector();

    [[nodiscard]] static Vector<T> with_capacity(const dts::u32 capacity);
    [[nodiscard]] static Vector<T> with_capacity(
      std::initializer_list<T> initializer_list,
      const dts::u32           capacity
    );

    [[nodiscard]] const T &operator[](const dts::u32 index) const;
    [[nodiscard]] T       &operator[](const dts::u32 index);
    [[nodiscard]] const T &at(const dts::u32 index) const;
    [[nodiscard]] T       &at(const dts::u32 index);
    [[nodiscard]] const T &data() const;
    [[nodiscard]] T       &data();
    [[nodiscard]] const T &front() const;
    [[nodiscard]] T       &front();
    [[nodiscard]] const T &back() const;
    [[nodiscard]] T       &back();

    [[nodiscard]] const T *cbegin() const;
    [[nodiscard]] T       *begin() const;
    [[nodiscard]] const T *cend() const;
    [[nodiscard]] T       *end() const;


    [[nodiscard]] dts::u32 size() const;
    [[nodiscard]] dts::u32 capacity() const;
    [[nodiscard]] bool     empty() const;
    void                   shrink_to_fit();

    // TODO: Add insert, emplace, erase, swap
    void clear();
    void push_back(const T &value);
    template<typename... Args>
    void               emplace_back(Args &&...params);
    void               pop_back();
    [[nodiscard]] bool operator==(const Vector &rhs) const;
    [[nodiscard]] bool operator!=(const Vector &rhs) const;
    [[nodiscard]] bool contains(const T &elem) const;

  private:
    explicit Vector(const dts::u32 capacity);
    Vector(const T *begin, const T *end, const dts::u32 capacity);

    void grow();
    void grow_if_necessary(const dts::u32 size);

    dts::u32 m_size     = 0;
    dts::u32 m_capacity = 0;
    T       *m_data     = nullptr;
};


template<typename T>
Vector(const T *begin, const T *end) -> Vector<T>;

template<typename T>
Vector(std::initializer_list<T> initializer_list) -> Vector<T>;

template<typename T>
Vector<T>::Vector(const T *begin, const T *end)
  : m_size{ static_cast<dts::u32>(end - begin) },
    m_capacity{ m_size },
    m_data{ reinterpret_cast<T *>(malloc(m_capacity * sizeof(T))) }
{
    memcpy(m_data, begin, m_size);
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> initializer_list)
  : Vector<T>(initializer_list.begin(), initializer_list.end())
{}

template<typename T>
Vector<T>::Vector(const Vector<T> &other)
  : m_size{ other.size() },
    m_capacity{ other.capacity() },
    m_data{ reinterpret_cast<T *>(malloc(m_capacity * sizeof(T))) }
{
    memcpy(m_data, other.data(), m_size);
}

template<typename T>
Vector<T>::Vector(Vector<T> &&other) noexcept
  : m_size{ move(other.size()) },
    m_capacity{ move(other.capacity()) },
    m_data{ move(other.data()) }
{}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    if (this != other) {
        m_size     = other.size();
        m_capacity = other.capacity();
        m_data     = reinterpret_cast<T *>(malloc(m_capacity * sizeof(T)));
        memcpy(m_data, other.data(), m_size);
    }

    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept
{
    m_size     = move(other.size());
    m_capacity = move(other.capacity());
    m_data     = move(other.data());

    return *this;
}

template<typename T>
Vector<T>::~Vector()
{
    free(m_data);
}

template<typename T>
Vector<T> Vector<T>::with_capacity(const dts::u32 capacity)
{
    return Vector(capacity);
}

template<typename T>
Vector<T> Vector<T>::with_capacity(
  std::initializer_list<T> initializer_list,
  const dts::u32           capacity
)
{
    return Vector(initializer_list.begin(), initializer_list.end(), capacity);
}


template<typename T>
const T &Vector<T>::operator[](const dts::u32 index) const
{
    return m_data[index];
}

template<typename T>
T &Vector<T>::operator[](const dts::u32 index)
{
    return m_data[index];
}

template<typename T>
const T &Vector<T>::at(const dts::u32 index) const
{
    assert(
      index <= m_size - 1,
      "[ERROR] Vector::at(dts::u32 index): Index was greater than size."
    );

    return m_data[index];
}

template<typename T>
T &Vector<T>::at(const dts::u32 index)
{
    assert(
      index <= m_size - 1,
      "[ERROR] Vector::at(dts::u32 index): Index was greater than size."
    );

    return m_data[index];
}

template<typename T>
const T &Vector<T>::data() const
{
    return m_data;
}

template<typename T>
T &Vector<T>::data()
{
    return m_data;
}

template<typename T>
const T &Vector<T>::front() const
{
    return m_data[0];
}

template<typename T>
T &Vector<T>::front()
{
    return m_data[0];
}

template<typename T>
const T &Vector<T>::back() const
{
    return m_data[m_size - 1];
}

template<typename T>
T &Vector<T>::back()
{
    return m_data[m_size - 1];
}

template<typename T>
const T *Vector<T>::cbegin() const
{
    return m_data;
}

template<typename T>
T *Vector<T>::begin() const
{
    return m_data;
}

template<typename T>
const T *Vector<T>::cend() const
{
    return m_data + m_size;
}

template<typename T>
T *Vector<T>::end() const
{
    return m_data + m_size;
}

template<typename T>
dts::u32 Vector<T>::size() const
{
    return m_size;
}

template<typename T>
dts::u32 Vector<T>::capacity() const
{
    return m_capacity;
}

template<typename T>
bool Vector<T>::empty() const
{
    return !(m_size > 0);
}

template<typename T>
void Vector<T>::shrink_to_fit()
{
    if (m_capacity / 2 > m_size) {
        m_capacity     = m_size;
        auto *new_data = reinterpret_cast<T *>(malloc(m_capacity * sizeof(T)));
        memcpy(new_data, m_data, m_size);
        free(m_data);

        m_data = new_data;
    }
}

template<typename T>
void Vector<T>::clear()
{
    memset(m_data, 0, m_size);
    m_size = 0;
}

template<typename T>
void Vector<T>::push_back(const T &value)
{
    grow_if_necessary(1);
    m_data[m_size++] = value;
}

template<typename T>
template<typename... Args>
void Vector<T>::emplace_back(Args &&...params)
{
    grow_if_necessary(1);
    m_data[m_size++] = T(dts::forward<Args>(params)...);
}

template<typename T>
void Vector<T>::pop_back()
{
    m_data[--m_size] = T();
}

template<typename T>
bool Vector<T>::operator==(const Vector<T> &rhs) const
{
    if (m_size != rhs.size()) { return false; }

    for (dts::u32 i = 0; i < m_size; ++i) {
        if (m_data[i] != rhs[i]) { return false; }
    }

    return true;
}

template<typename T>
bool Vector<T>::operator!=(const Vector<T> &rhs) const
{
    if (m_size != rhs.size()) { return true; }

    for (dts::u32 i = 0; i < m_size; ++i) {
        if (m_data[i] == rhs[i]) { return false; }
    }

    return true;
}

template<typename T>
void Vector<T>::grow()
{
    const auto new_capacity = m_capacity * 2;

    auto *new_data = reinterpret_cast<T *>(malloc(new_capacity * sizeof(T)));

    memcpy(new_data, m_data, m_size);
    free(m_data);

    m_capacity = new_capacity;
    m_data     = new_data;
}

template<typename T>
void Vector<T>::grow_if_necessary(const dts::u32 new_size)
{
    if (m_size + new_size > m_capacity) { grow(); }
}

template<typename T>
Vector<T>::Vector(const dts::u32 capacity)
  : m_capacity{ capacity },
    m_data{ reinterpret_cast<T *>(malloc(m_capacity * sizeof(T))) }
{
    memset(m_data, 0, m_size);
}

template<typename T>
Vector<T>::Vector(const T *begin, const T *end, const dts::u32 capacity)
  : m_size{ static_cast<dts::u32>(begin - end) },
    m_capacity{ capacity },
    m_data{ reinterpret_cast<T *>(malloc(m_capacity * sizeof(T))) }
{
    memcpy(m_data, begin, m_size);
}
} // namespace dts
