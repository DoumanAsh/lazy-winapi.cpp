#include "error.hpp"
#include "gtest/gtest.h"

struct error_desc_test {
    unsigned long error;
    wchar_t *expect_desc;
};

TEST(ErrorTest, KnownErrorDesc) {
    wchar_t buffer[512] = {0};
    const size_t len = sizeof(buffer) / sizeof(buffer[0]);

    static struct error_desc_test params[] = {
        {
            0,
            L"The operation completed successfully."
        },
        {
            1,
            L"Incorrect function."
        },
        {
            666,
            L"Unknown Error."
        }
    };

    const size_t params_len = sizeof(params) / sizeof(params[0]);
    for (size_t idx = 0; idx < params_len; idx++) {
        const auto error = Error(params[idx].error);
        error.description(buffer, len);

        ASSERT_STREQ(buffer, params[idx].expect_desc);
    }
}

TEST(ErrorTest, KnownErrorDescWideString) {
    const auto error = Error(1);
    const std::wstring expect_desc = L"Incorrect function.";

    ASSERT_EQ(error.description(), expect_desc);
}

TEST(ErrorTest, TruncEmpty) {
    wchar_t buffer[1] = {0};
    const size_t len = sizeof(buffer) / sizeof(buffer[0]);
    const wchar_t expect_desc[] = L"";
    const auto error = Error(0);

    ASSERT_TRUE(error.description(buffer, len));

    ASSERT_STREQ(buffer, expect_desc);
}

TEST(ErrorTest, ShouldTrunc) {
    wchar_t buffer[20] = {0};
    const size_t len = sizeof(buffer) / sizeof(buffer[0]);
    const wchar_t expect_desc[] = L"The operation compl";
    const auto error = Error(0);

    ASSERT_TRUE(error.description(buffer, len));

    ASSERT_STREQ(buffer, expect_desc);
}
