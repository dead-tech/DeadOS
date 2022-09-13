#include "String.hpp"

namespace dts {

void strcpy(char *dst, const char *src)
{
    u32 len = 0;

    for (u32 i = 0; src[len] != 0; ++i) { dst[i] = src[i]; }

    dst[len] = '\0';
}

bool strcmp(const char *lhs, const char *rhs)
{
    if (lhs == nullptr || rhs == nullptr) { return false; }

    while (*lhs != 0) {
        if (*lhs != *rhs) { return false; }
        ++lhs;
        ++rhs;
    }

    return true;
}

String::String(const char *cstr)
  : m_size{ strlen(cstr) },
    m_capacity{ m_size },
    m_data{ reinterpret_cast<char *>(malloc(m_capacity * sizeof(char))) }
{
    memcpy(m_data, cstr, m_size);
}

String::String(const char *begin, const char *end)
  : m_size{ static_cast<dts::u32>(end - begin) },
    m_capacity{ m_size },
    m_data{ reinterpret_cast<char *>(malloc(m_capacity * sizeof(char))) }
{
    memcpy(m_data, begin, m_size);
}

String::~String() { free(m_data); }

String::String(const dts::String &other)
  : m_size{ other.size() },
    m_capacity{ m_size },
    m_data{ reinterpret_cast<char *>(malloc(m_capacity * sizeof(char))) }
{
    memcpy(m_data, other.data(), other.size());
}

String::String(dts::String &&other) noexcept
{
    if (&other == this) {
        m_size     = other.size();
        m_capacity = other.capacity();
        m_data = reinterpret_cast<char *>(malloc(m_capacity * sizeof(char)));
        memcpy(m_data, other.data(), other.size());
    } else {
        m_size     = move(other.size());
        m_capacity = move(other.capacity());
        m_data     = move(other.data());
    }
}

String &String::operator=(const String &other)
{
    if (&other != this) {
        m_size     = other.size();
        m_capacity = other.capacity();
        m_data = reinterpret_cast<char *>(malloc(m_capacity * sizeof(char)));
        memcpy(m_data, other.c_str(), other.size());
    }
    return *this;
}

// FIXME: Properly implement the move-assignment operator
String &String::operator=(String &&other) noexcept
{
    m_size     = move(other.size());
    m_capacity = move(other.capacity());
    m_data     = move(other.data());
    return *this;
}

String String::with_capacity(const dts::u32 capacity)
{
    return String{ capacity };
}


String String::reverse(const dts::String &str)
{
    String   ret = str;
    dts::u32 len = str.size();

    for (dts::u32 i = 0; i < len / 2; ++i) { swap(ret[i], ret[len - i - 1]); }

    return ret;
}

const char &String::operator[](const dts::u32 index) const
{
    return m_data[index];
}

char &String::operator[](const dts::u32 index) { return m_data[index]; }

const char &String::at(const dts::u32 index) const
{
    assert(
      index <= m_size - 1,
      "[ERROR] String::at(dts::u32 index): Index was greater than string size."
    );
    return m_data[index];
}

char &String::at(const dts::u32 index)
{
    assert(
      index <= m_size - 1,
      "[ERROR] String::at(dts::u32 index): Index was greater than string size."
    );
    return m_data[index];
}

const char *String::c_str() const
{
    auto *ret   = m_data;
    ret[m_size] = '\0';
    return ret;
}

char *String::data() const { return m_data; }

const char &String::front() const { return m_data[0]; }

char &String::front() { return m_data[0]; }

const char &String::back() const { return m_data[m_size - 1]; }

char &String::back() { return m_data[m_size - 1]; }

const char *String::cbegin() const { return m_data; }

char *String::begin() const { return m_data; }

const char *String::cend() const { return m_data + m_size; }

char *String::end() const { return m_data + m_size; }

dts::u32 String::size() const { return m_size; }

dts::u32 String::capacity() const { return m_capacity; }

bool String::empty() const { return !(m_size > 0); }

void String::shrink_to_fit()
{
    if (m_capacity / 2 > m_size) {
        m_capacity = m_size;
        auto *new_data =
          reinterpret_cast<char *>(malloc(m_capacity * sizeof(char)));
        memcpy(new_data, m_data, m_size);
        free(m_data);

        m_data = new_data;
    }
}

void String::clear()
{
    memset(m_data, 0, m_size);
    m_size = 0;
}

void String::push_back(const char ch)
{
    grow_if_necessary(1);
    m_data[m_size++] = ch;
}

void String::pop_back() { m_data[--m_size] = '\0'; }

String &String::operator+=(const char *other)
{
    const auto other_len = strlen(other);
    grow_if_necessary(other_len);

    for (dts::u32 i = 0; i < other_len; ++i) { m_data[m_size++] = other[i]; }
    return *this;
}

String &String::operator+=(const dts::String &other)
{
    const auto other_len = other.size();
    grow_if_necessary(other_len);

    for (dts::u32 i = 0; i < other_len; ++i) { m_data[m_size++] = other[i]; }
    return *this;
}

bool String::operator==(const dts::String &rhs) const
{
    return strcmp(c_str(), rhs.c_str());
}

bool String::operator!=(const dts::String &rhs) const
{
    return !strcmp(c_str(), rhs.c_str());
}

bool String::starts_with(const char other) { return front() == other; }

bool String::starts_with(const char *other)
{
    const auto other_len = strlen(other);

    if (m_size < other_len) { return false; }

    for (dts::u32 i = 0; i < other_len; ++i) {
        if (m_data[i] != other[i]) { return false; }
    }

    return true;
}

bool String::starts_with(const dts::String &other)
{
    if (m_size < other.size()) { return false; }

    for (dts::u32 i = 0; i < other.size(); ++i) {
        if (m_data[i] != other[i]) { return false; }
    }

    return true;
}

bool String::ends_with(const char other) { return back() == other; }

bool String::ends_with(const char *other)
{
    const auto other_len = strlen(other);

    if (m_size < other_len) { return false; }

    for (dts::u32 i = 0; i < other_len; ++i) {
        if (m_data[m_size - i] != other[other_len - i]) { return false; }
    }

    return true;
}

bool String::ends_with(const dts::String &other)
{
    if (m_size < other.size()) { return false; }

    for (dts::u32 i = 0; i > other.size(); ++i) {
        if (m_data[m_size - i] == other[other.size() - i]) { return false; }
    }

    return true;
}

bool String::contains(const char other)
{
    for (const auto it : *this) { // NOLINT
        if (it == other) { return true; }
    }

    return false;
}

bool String::contains(const char *other)
{
    const auto other_len = strlen(other);

    for (dts::u32 i = 0; i < m_size; ++i) {
        dts::u32 j = 0;
        if (m_data[i] == other[j]) {
            dts::u32 initial_value = i;
            while (m_data[i] == other[j]) {
                ++i;
                ++j;
            }
            if (j == other_len) {
                return true;
            } else {
                i = initial_value;
            }
        }
    }

    return false;
}

bool String::contains(const String &other)
{
    for (dts::u32 i = 0; i < m_size; ++i) {
        dts::u32 j = 0;
        if (m_data[i] == other[j]) {
            dts::u32 initial_value = i;
            while (m_data[i] == other[j]) {
                ++i;
                ++j;
            }
            if (j == other.size()) {
                return true;
            } else {
                i = initial_value;
            }
        }
    }

    return false;
}

String String::substr(const dts::u32 pos, const dts::u32 len) const
{
    if (len == 0) { return ""; }

    return { m_data + pos, m_data + pos + len };
}

dts::u32 String::find_first_of(const char other) const
{
    for (dts::u32 idx = 0; idx < size(); ++idx) {
        if (m_data[idx] == other) { return idx; }
    }

    return npos;
}

dts::u32 String::find_first_of(const char *other) const
{
    const auto other_len = strlen(other);

    dts::u32 idx = 0;
    while (idx < other_len) {
        if (m_data[idx] == other[idx]) {
            const auto *lhs = m_data + idx;
            const auto *rhs = other + idx;
            while (*lhs == *rhs) {
                ++lhs;
                ++rhs;

                if (*rhs != *lhs) { return npos; }
            }
        }
    }

    return idx;
}

dts::u32 String::find_first_of(const String &other) const
{
    dts::u32 idx = 0;
    while (idx < other.size()) {
        if (m_data[idx] == other[idx]) {
            const auto *lhs = m_data + idx;
            const auto *rhs = other.c_str() + idx;
            while (*lhs == *rhs) {
                ++lhs;
                ++rhs;

                if (*rhs != *lhs) { return npos; }
            }
        }
    }

    return idx;
}

dts::u32 String::find_last_of(const char other) const
{
    for (dts::u32 idx = size() - 1; idx > 0; --idx) {
        if (m_data[idx] == other) { return idx; }
    }

    return npos;
}

dts::u32 String::find_last_of(const char *other) const
{
    const auto other_len = strlen(other);

    dts::u32 idx = other_len;
    while (idx > 0) {
        if (m_data[idx] == other[idx]) {
            const auto *lhs = m_data + idx;
            const auto *rhs = other + idx;
            while (*lhs == *rhs) {
                ++lhs;
                ++rhs;

                if (*rhs != *lhs) { return npos; }
            }
        }
    }

    return idx;
}

dts::u32 String::find_last_of(const String &other) const
{
    dts::u32 idx = other.size();
    while (idx > 0) {
        if (m_data[idx] == other[idx]) {
            const auto *lhs = m_data + idx;
            const auto *rhs = other.c_str() + idx;
            while (*lhs == *rhs) {
                ++lhs;
                ++rhs;

                if (*rhs != *lhs) { return npos; }
            }
        }
    }

    return idx;
}

String::String(const dts::u32 capacity)
  : m_capacity{ capacity },
    m_data{ reinterpret_cast<char *>(malloc(m_capacity * sizeof(char))) }
{}

void String::grow([[maybe_unused]] const dts::u32 new_size)
{
    m_capacity += new_size + 1;

    auto *new_data =
      reinterpret_cast<char *>(malloc(m_capacity * sizeof(char)));
    memcpy(new_data, m_data, m_size);
    free(m_data);

    m_data = new_data;
}

void String::grow_if_necessary(const dts::u32 new_size)
{
    if (m_capacity <= m_size + new_size) { grow(new_size); }
}

} // namespace dts
