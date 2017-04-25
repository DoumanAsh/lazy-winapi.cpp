/**
 * @file
 *
 * @ref Error header.
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

///WinAPI Error wrapper.
///
///@note Not all error code produces valid error message.
///      In these cases description returns "Unknown Error."
///
///You can find out meaning of error over [there](https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx)
class Error {
    public:
        ///Underlying WinAPI Error code.
        unsigned long code;

        ///Creates new instance from last error.
        Error();

        ///Creates new instance from error code.
        ///@param code WinAPI Error Code from `GetLastError()`.
        Error(unsigned long code);

        ///@return Error description.
        std::wstring description() const;
        ///@return Error description.
        ///@param buffer Storage for description.
        ///@param len Length of storage.
        const wchar_t* description(wchar_t *buffer, size_t len) const;
};
