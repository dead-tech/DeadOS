#pragma once

#include "String.hpp"
#include "Types.hpp"

namespace dts {

template<typename T>
struct Formatter;

class StringView
{
  public:
    using Iterator      = const char *;
    using ConstIterator = const char *;

    constexpr static dts::u32 npos = -1;

    constexpr StringView() noexcept  = default;
    constexpr ~StringView() noexcept = default;
    constexpr explicit StringView(const char *cstr) noexcept;
    constexpr StringView(const char *cstr, const dts::u32 len) noexcept;
    constexpr StringView(const char *begin, const char *end) noexcept;

    constexpr StringView(const StringView &rhs) noexcept            = default;
    constexpr StringView(StringView &&rhs) noexcept                 = default;
    constexpr StringView &operator=(const StringView &rhs) noexcept = default;
    constexpr StringView &operator=(StringView &&rhs) noexcept      = default;

    [[nodiscard]] constexpr const char *begin() const;
    [[nodiscard]] constexpr const char *cbegin() const;
    [[nodiscard]] constexpr const char *end() const;
    [[nodiscard]] constexpr const char *cend() const;

    [[nodiscard]] constexpr const char &operator[](const dts::u32 index) const;
    [[nodiscard]] constexpr const char &at(const dts::u32 index) const;
    [[nodiscard]] constexpr const char &front() const;
    [[nodiscard]] constexpr const char &back() const;
    [[nodiscard]] constexpr const char *data() const;

    [[nodiscard]] constexpr dts::u32 size() const;
    [[nodiscard]] constexpr bool     empty() const;

    constexpr void shift_from_start(const dts::u32 shift_factor);
    constexpr void shift_from_end(const dts::u32 shift_factor);

    [[nodiscard]] constexpr StringView
      substr(const dts::u32 pos, const dts::u32 len) const;
    [[nodiscard]] constexpr bool     compare(const StringView &rhs) const;
    [[nodiscard]] constexpr bool     starts_with(const char ch) const;
    [[nodiscard]] constexpr bool     starts_with(const char *cstr) const;
    [[nodiscard]] constexpr bool     starts_with(const StringView &view) const;
    [[nodiscard]] constexpr bool     ends_with(const char ch) const;
    [[nodiscard]] constexpr bool     ends_with(const char *cstr) const;
    [[nodiscard]] constexpr bool     ends_with(const StringView &view) const;
    [[nodiscard]] constexpr bool     contains(const char ch) const;
    [[nodiscard]] constexpr bool     contains(const char *cstr) const;
    [[nodiscard]] constexpr bool     contains(const StringView &view) const;
    [[nodiscard]] constexpr dts::u32 find_first_of(const char ch) const;
    [[nodiscard]] constexpr dts::u32 find_first_of(const char *cstr) const;
    [[nodiscard]] constexpr dts::u32 find_first_of(const StringView &view
    ) const;
    [[nodiscard]] constexpr dts::u32 find_last_of(const char ch) const;
    [[nodiscard]] constexpr dts::u32 find_last_of(const char *cstr) const;
    [[nodiscard]] constexpr dts::u32 find_last_of(const StringView &view) const;

  private:
    dts::u32    m_size = 0;
    const char *m_data = nullptr;
};

constexpr StringView::StringView(const char *cstr) noexcept
  : m_size{ strlen(cstr) },
    m_data{ cstr }
{}

constexpr StringView::StringView(const char *cstr, const dts::u32 len) noexcept
  : m_size{ len },
    m_data{ cstr }
{}

constexpr StringView::StringView(const char *begin, const char *end) noexcept
  : m_size{ static_cast<dts::u32>(end - begin) },
    m_data{ begin }
{}

constexpr const char *StringView::begin() const { return m_data; }

constexpr const char *StringView::cbegin() const { return m_data; }

constexpr const char *StringView::end() const { return m_data + m_size; }

constexpr const char *StringView::cend() const { return m_data + m_size; }

constexpr const char &StringView::operator[](const dts::u32 index) const
{
    return m_data[index];
}

constexpr const char &StringView::at(const dts::u32 index) const
{
    assert(
      index < m_size,
      "[ERROR] dts::StringView::at(): index was greater than size."
    );
    return m_data[index];
}

constexpr const char &StringView::front() const { return *m_data; }

constexpr const char &StringView::back() const { return *(m_data + m_size); }

constexpr const char *StringView::data() const { return m_data; }

constexpr dts::u32 StringView::size() const { return m_size; }

constexpr bool StringView::empty() const { return !(m_size > 0); }

constexpr void StringView::shift_from_start(const dts::u32 shift_factor)
{
    m_data += shift_factor;
    m_size -= shift_factor;
}
constexpr void StringView::shift_from_end(const dts::u32 shift_factor)
{
    m_size -= shift_factor;
}

constexpr StringView
  StringView::substr(const dts::u32 pos, const dts::u32 len) const
{
    if (len == 0) { return StringView{ "" }; }

    return { m_data + pos, m_data + pos + len };
}

constexpr bool StringView::compare(const StringView &rhs) const
{
    return m_data == rhs.data();
}

constexpr bool StringView::starts_with(const char ch) const
{
    return front() == ch;
}

constexpr bool StringView::starts_with(const char *cstr) const
{
    const auto other_len = strlen(cstr);

    if (m_size < other_len) { return false; }

    for (dts::u32 i = 0; i < other_len; ++i) {
        if (m_data[i] != cstr[i]) { return false; }
    }

    return true;
}

constexpr bool StringView::starts_with(const StringView &view) const
{
    if (m_size < view.size()) { return false; }

    for (dts::u32 i = 0; i < view.size(); ++i) {
        if (m_data[i] != view[i]) { return false; }
    }

    return true;
}

constexpr bool StringView::ends_with(const char ch) const
{
    return back() == ch;
}

constexpr bool StringView::ends_with(const char *cstr) const
{
    const auto other_len = strlen(cstr);

    if (m_size < other_len) { return false; }

    for (dts::u32 i = 0; i < other_len; ++i) {
        if (m_data[m_size - i] != cstr[other_len - i]) { return false; }
    }

    return true;
}

constexpr bool StringView::ends_with(const StringView &view) const
{
    if (m_size < view.size()) { return false; }

    for (dts::u32 i = 0; i > view.size(); ++i) {
        if (m_data[m_size - i] == view[view.size() - i]) { return false; }
    }

    return true;
}

constexpr bool StringView::contains(const char ch) const
{
    for (const auto it : *this) { // NOLINT
        if (it == ch) { return true; }
    }

    return false;
}

constexpr bool StringView::contains(const char *cstr) const
{
    const auto other_len = strlen(cstr);

    for (dts::u32 i = 0; i < m_size; ++i) {
        dts::u32 j = 0;
        if (m_data[i] == cstr[j]) {
            dts::u32 initial_value = i;
            while (m_data[i] == cstr[j]) {
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

constexpr bool StringView::contains(const StringView &view) const
{
    for (dts::u32 i = 0; i < m_size; ++i) {
        dts::u32 j = 0;
        if (m_data[i] == view[j]) {
            dts::u32 initial_value = i;
            while (m_data[i] == view[j]) {
                ++i;
                ++j;
            }
            if (j == view.size()) {
                return true;
            } else {
                i = initial_value;
            }
        }
    }

    return false;
}

constexpr dts::u32 StringView::find_first_of(const char ch) const
{
    for (dts::u32 idx = 0; idx < size(); ++idx) {
        if (m_data[idx] == ch) { return idx; }
    }

    return npos;
}

constexpr dts::u32 StringView::find_first_of(const char *cstr) const
{
    const auto other_len = strlen(cstr);

    dts::u32 idx = 0;
    while (idx < other_len) {
        if (m_data[idx] == cstr[idx]) {
            const auto *lhs = m_data + idx;
            const auto *rhs = cstr + idx;
            while (*lhs == *rhs) {
                ++lhs;
                ++rhs;

                if (*rhs != *lhs) { return npos; }
            }
        }
    }

    return idx;
}

constexpr dts::u32 StringView::find_first_of(const StringView &view) const
{
    dts::u32 idx = 0;
    while (idx < view.size()) {
        if (m_data[idx] == view[idx]) {
            const auto *lhs = m_data + idx;
            const auto *rhs = view.data() + idx;
            while (*lhs == *rhs) {
                ++lhs;
                ++rhs;

                if (*rhs != *lhs) { return npos; }
            }
        }
    }

    return idx;
}

constexpr dts::u32 StringView::find_last_of(const char ch) const
{
    for (dts::u32 idx = size() - 1; idx > 0; --idx) {
        if (m_data[idx] == ch) { return idx; }
    }

    return npos;
}

constexpr dts::u32 StringView::find_last_of(const char *cstr) const
{
    const auto other_len = strlen(cstr);

    dts::u32 idx = other_len;
    while (idx > 0) {
        if (m_data[idx] == cstr[idx]) {
            const auto *lhs = m_data + idx;
            const auto *rhs = cstr + idx;
            while (*lhs == *rhs) {
                ++lhs;
                ++rhs;

                if (*rhs != *lhs) { return npos; }
            }
        }
    }

    return idx;
}

constexpr dts::u32 StringView::find_last_of(const StringView &view) const
{
    dts::u32 idx = view.size();
    while (idx > 0) {
        if (m_data[idx] == view[idx]) {
            const auto *lhs = m_data + idx;
            const auto *rhs = view.data() + idx;
            while (*lhs == *rhs) {
                ++lhs;
                ++rhs;

                if (*rhs != *lhs) { return npos; }
            }
        }
    }

    return idx;
}

inline namespace literals {
constexpr StringView operator""_sv(const char *cstr, const dts::u32 len)
{
    return StringView{ cstr, len };
}
} // namespace literals

template<>
struct Formatter<StringView>
{
    static String format(const StringView &view)
    {
        return String{ view.data() };
    }
};

} // namespace dts

using namespace dts::literals;
