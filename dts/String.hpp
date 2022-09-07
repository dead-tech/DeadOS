#pragma once

#include <dts/Algorithm.hpp>
#include <dts/Assert.hpp>
#include <dts/Memory.hpp>
#include <dts/Types.hpp>
#include <dts/Utility.hpp>

namespace dts {

u32  strlen(const char *str);
void strcpy(char *dst, char *src);
bool strcmp(const char *lhs, const char *rhs);

char *itoa(u64 integer, u8 base = 10);

// FIXME: Add capacity to reduce malloc system calls
class String
{
  public:
    constexpr static dts::u32 npos = -1;

    String(const char *cstr); // NOLINT
    ~String();
    String(const String &other);
    String(String &&other) noexcept;
    String &operator=(const String &other);
    String &operator=(String &&other) noexcept;

    // TODO: Make this a Integral concept
    // FIXME: Very basic implementation
    template<typename T>
    [[nodiscard]] static String from(const T number);

    [[nodiscard]] static String reverse(const String &str);

    [[nodiscard]] const char &operator[](const dts::u32 index) const;
    [[nodiscard]] char       &operator[](const dts::u32 index);
    [[nodiscard]] const char &at(const dts::u32 index) const;
    [[nodiscard]] char       &at(const dts::u32 index);
    [[nodiscard]] const char *c_str() const;
    [[nodiscard]] char       *data() const;
    [[nodiscard]] const char &front() const;
    [[nodiscard]] char       &front();
    [[nodiscard]] const char &back() const;
    [[nodiscard]] char       &back();

    [[nodiscard]] const char *cbegin() const;
    [[nodiscard]] char       *begin() const;
    [[nodiscard]] const char *cend() const;
    [[nodiscard]] char       *end() const;

    [[nodiscard]] dts::u32 size() const;
    [[nodiscard]] bool     empty() const;

    void               clear();
    void               push_back(const char ch);
    void               pop_back();
    String            &operator+=(const char *other);
    String            &operator+=(const String &other);
    [[nodiscard]] bool operator==(const String &rhs) const;
    [[nodiscard]] bool operator!=(const String &rhs) const;
    [[nodiscard]] bool starts_with(const char other);
    [[nodiscard]] bool starts_with(const char *other);
    [[nodiscard]] bool starts_with(const String &other);
    [[nodiscard]] bool ends_with(const char other);
    [[nodiscard]] bool ends_with(const char *other);
    [[nodiscard]] bool ends_with(const String &other);
    // FIXME: I'm absolutely broken
    [[nodiscard]] bool     contains(const char other);
    [[nodiscard]] bool     contains(const char *other);
    [[nodiscard]] bool     contains(const String &other);
    [[nodiscard]] String   substr(const dts::u32 pos, const dts::u32 len) const;
    [[nodiscard]] dts::u32 find_first_of(const char other) const;
    [[nodiscard]] dts::u32 find_first_of(const char *other) const;
    [[nodiscard]] dts::u32 find_first_of(const String &other) const;
    [[nodiscard]] dts::u32 find_last_of(const char other) const;
    [[nodiscard]] dts::u32 find_last_of(const char *other) const;
    [[nodiscard]] dts::u32 find_last_of(const String &other) const;

  private:
    dts::u32 m_size = 0;
    char    *m_data = nullptr;
};

template<typename T>
String String::from(const T number)
{
    char     buffer[32]  = { 0 };
    dts::u32 buffer_size = 0;

    for (dts::u32 i = number; i > 0; i /= 10) {
        buffer[buffer_size++] = "0123456789ABCDEF"[i % 10];
    }

    return reverse(String(buffer)); // NOLINT
}

} // namespace dts
