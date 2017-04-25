/**
 * @file
 *
 * Source code of @ref Clipboard module.
 */

#pragma once

#if (_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4577)
#pragma warning(disable: 4530)
#endif
#include <string>
#if (_MSC_VER)
#pragma warning(pop)
#endif

///WinAPI Clipboard Accessor.
///
///@note You can have only one instance of this class across your program.
class Clipboard {
    public:
        ///Opens clipboard
        ///
        ///@throws runtime_error When fails to open Clipboard.
        Clipboard();

        ///Closes Clipboard.
        ~Clipboard();

        ///Empties Clipboard.
        ///
        ///@retval true Success.
        ///@retval false Failed to perform operation.
        bool empty() const;

        ///@return Size of Clipboard content, in bytes.
        ///@param format Clipboard format to examine.
        ///@retval 0 If format is not available.
        size_t size(unsigned int format) const;

        ///Retrieves Clipboard content of specified format.
        ///
        ///@param[in] format Format to retrieve.
        ///@param[out] buf Buffer to hold content of clipboard. Cannot be NULL.
        ///@param[in] len Size of buffer.
        ///
        ///@return Number of copied bytes.
        ///@retval 0 On failure.
        size_t get(unsigned int format, char* buf, size_t len) const;

        ///Retrieves string from Clipboard.
        ///
        ///@note It uses `CF_TEXT`.
        ///@return String with content. If nothing is available then empty string.
        std::string get_string() const;

        ///Retrieves wide string from Clipboard.
        ///
        ///@note It uses `CF_UNICODETEXT`.
        ///@return String with content. If nothing is available then empty string.
        std::wstring get_wstring() const;

        ///Sets data onto Clipboard.
        ///
        ///@param[in] format Format to set onto.
        ///@param[in] buf Buffer with data.
        ///@param[in] len Size of buffer.
        ///@retval true On success.
        ///@retval false Otherwise.
        bool set(unsigned int format, const char* buf, size_t len) const;

        ///Sets string onto Clipboard.
        ///
        ///@param[in] text String to set.
        ///
        ///@note It uses `CF_TEXT`.
        ///
        ///@retval true On success.
        ///@retval false Otherwise.
        bool set_string(const char* text) const;

        ///Sets string onto Clipboard.
        ///
        ///@param[in] text String to set.
        ///
        ///@note It uses `CF_TEXT`.
        ///
        ///@retval true On success.
        ///@retval false Otherwise.
        bool set_string(const std::string& text) const;

        ///Sets wide string onto Clipboard.
        ///
        ///@param[in] text String to set.
        ///
        ///@note It uses `CF_UNICODETEXT`.
        ///
        ///@retval true On success.
        ///@retval false Otherwise.
        bool set_string(const wchar_t* text) const;

        ///Sets wide string onto Clipboard.
        ///
        ///@param[in] text String to set.
        ///
        ///@note It uses `CF_UNICODETEXT`.
        ///
        ///@retval true On success.
        ///@retval false Otherwise.
        bool set_string(const std::wstring& text) const;

        ///Determines whether format is available on Clipboard.
        ///@retval true Format is available.
        ///@retval false Otherwise.
        static bool is_format_avail(unsigned int format);

        ///@return Clipboard sequence number.
        static unsigned long seq_num();

        ///@return Number of available formats on Clipboard.
        static unsigned long count_formats();

        ///@return Format identifier.
        ///@param name Name for new format.
        ///@retval 0 On failure.
        static unsigned long register_format(const wchar_t* name);

        ///@return Format identifier.
        ///@param name Name for new format.
        ///@retval 0 On failure.
        static unsigned long register_format(const std::wstring& name);

        ///Retrieves name of Clipboard format.
        ///@param[in] format Format ID.
        ///@param[out] buffer Storage for name.
        ///@param[in] len Length of buffer.
        ///@return Number of written characters.
        ///@retval 0 On unknown format.
        static int get_format_name(unsigned long format, wchar_t* buffer, size_t len);

        ///Retrieves name of Clipboard format.
        ///@param[in] format Format ID.
        ///@return Name or empty string on unknown format.
        static std::wstring get_format_name(unsigned long format);

        private:
            Clipboard (const Clipboard&) = delete;
            Clipboard& operator= (const Clipboard&) = delete;

};
