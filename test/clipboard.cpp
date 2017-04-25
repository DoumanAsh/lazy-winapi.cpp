#include "windows.h"
#include "clipboard.hpp"
#include "gtest/gtest.h"

class ClipboardTest: public ::testing::Test
{
    public:
        Clipboard clip;

    protected:
        virtual void SetUp()
        {
        }

        virtual void TearDown()
        {
        }
};

TEST_F(ClipboardTest, ShouldSetClipboardText)
{
    const unsigned long format = CF_TEXT;
    const char text[] = "For my waifu!";
    const size_t text_len = sizeof(text);
    char extract_text[50] = {0};

    ASSERT_TRUE(this->clip.set(format, text, text_len));
    ASSERT_TRUE(Clipboard::is_format_avail(format));
    ASSERT_EQ(Clipboard::count_formats(), 1);
    ASSERT_EQ(this->clip.size(format), text_len);

    ASSERT_EQ(this->clip.get(format, extract_text, sizeof(extract_text)), text_len);
    ASSERT_STREQ(extract_text, text);
}

TEST_F(ClipboardTest, ShouldSetClipboardString)
{
    const unsigned long format = CF_TEXT;
    const char text[] = "For my waifu!";
    const size_t text_len = sizeof(text);

    ASSERT_TRUE(this->clip.set_string(text));
    ASSERT_TRUE(Clipboard::is_format_avail(format));
    ASSERT_EQ(Clipboard::count_formats(), 1);
    ASSERT_EQ(this->clip.size(format), text_len);

    const auto result = this->clip.get_string();
    ASSERT_STREQ(result.c_str(), text);
}

TEST_F(ClipboardTest, ShouldSetClipboardStdString)
{
    const unsigned long format = CF_TEXT;
    const std::string text = "Loli for win!";

    ASSERT_TRUE(this->clip.set_string(text));
    ASSERT_TRUE(Clipboard::is_format_avail(format));
    ASSERT_EQ(Clipboard::count_formats(), 1);
    ASSERT_EQ(this->clip.size(format), text.size() + 1);

    const auto result = this->clip.get_string();
    ASSERT_EQ(result, text);
}

TEST_F(ClipboardTest, ShouldSetClipboardWideString)
{
    const unsigned long format = CF_UNICODETEXT;
    const wchar_t text[] = L"For my waifu! 2";
    const size_t text_len = sizeof(text);

    ASSERT_TRUE(this->clip.set_string(text));
    ASSERT_TRUE(Clipboard::is_format_avail(format));
    ASSERT_EQ(Clipboard::count_formats(), 1);
    ASSERT_EQ(this->clip.size(format), text_len);

    const auto result = this->clip.get_wstring();
    ASSERT_STREQ(result.c_str(), text);
}

TEST_F(ClipboardTest, ShouldSetClipboardStdWideString)
{
    const unsigned long format = CF_UNICODETEXT;
    const std::wstring text = L"For my waifu! 2";

    ASSERT_TRUE(this->clip.set_string(text));
    ASSERT_TRUE(Clipboard::is_format_avail(format));
    ASSERT_EQ(Clipboard::count_formats(), 1);
    ASSERT_EQ(this->clip.size(format), (text.size() + 1) * sizeof(wchar_t));

    const auto result = this->clip.get_wstring();
    ASSERT_EQ(result, text);
}

TEST_F(ClipboardTest, ShouldEmpty) {
    const unsigned long format = CF_UNICODETEXT;
    const std::wstring text = L"For my waifu! 2";

    ASSERT_TRUE(this->clip.set_string(text));
    ASSERT_TRUE(Clipboard::is_format_avail(format));

    ASSERT_TRUE(this->clip.empty());
    ASSERT_FALSE(Clipboard::is_format_avail(format));
    ASSERT_EQ(Clipboard::count_formats(), 0);

    const auto result = this->clip.get_string();
    ASSERT_EQ(result.size(), 0);
}

TEST_F(ClipboardTest, RegisterFormat) {
    const std::wstring name = L"LOLI format";
    const auto format = Clipboard::register_format(name);

    ASSERT_TRUE(format);

    const auto result = Clipboard::get_format_name(format);

    ASSERT_EQ(result, name);

    const char data[] = {1, 2, 3, 55, 2, 0};
    const size_t data_len = sizeof(data);

    ASSERT_TRUE(this->clip.set(format, data, data_len));

    ASSERT_TRUE(Clipboard::is_format_avail(format));

    char extract_data[50] = {0};

    ASSERT_EQ(this->clip.get(format, extract_data, sizeof(extract_data)), data_len);

    ASSERT_STREQ(data, extract_data);
}

TEST_F(ClipboardTest, ShouldGetSeqNum)
{
    ASSERT_TRUE(Clipboard::seq_num());
}

