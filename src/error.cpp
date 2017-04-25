/**
 * @file
 *
 * @ref Error source code.
 */

#include "error.hpp"

#include <windows.h>

Error::Error() : code(GetLastError()) {
}

Error::Error(unsigned long code) : code(code) {
}

/**
 * Performs error handling for FormatMessageW.
 *
 * @param[out] buffer Memory for string. Cannot be NULL.
 * @param size Size of memory. Cannot be 0.
 *
 * @return buffer
 */
static const wchar_t* format_message_error(wchar_t *buffer, size_t size) {
    switch (GetLastError()) {
        case 122:
            /* Insufficient space so output is truncated. */
            break;
        case 317:
            /* Unknown error */
        default:
            /* Unclear what are possible errors, so treat
             * as unknown for now. */
            buffer[0] = 0;
            wcsncat_s(buffer, size, L"Unknown Error.", size);
            break;
    }

    return buffer;
}

/**
 * Clean FormatMessageW's result of newline.
 *
 * @param[out] buffer Memory for string. Cannot be NULL.
 * @param len Message length taken from FormatMessageW.
 *
 * @return buffer
 */
static const wchar_t* format_message_ok(wchar_t *buffer, size_t len) {
    for (size_t idx = len - 1; idx > 0; idx--) {
        /*                 \n                   \r */
        if (buffer[idx] == 10 || buffer[idx] == 13) buffer[idx] = 0;
        else break;
    }

    return buffer;
}

const wchar_t* Error::description(wchar_t *buffer, size_t len) const {
    const DWORD flags = FORMAT_MESSAGE_IGNORE_INSERTS |
                        FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_ARGUMENT_ARRAY;

    const DWORD size = FormatMessageW(flags, 0, this->code, 0, buffer, (DWORD)len, 0);

    return size == 0 ? format_message_error(buffer, len) : format_message_ok(buffer, size);
}

std::wstring Error::description() const {
    wchar_t buffer[512] = {0};
    this->description(buffer, sizeof(buffer) / sizeof(buffer[0]));
    return std::wstring(buffer);
}
