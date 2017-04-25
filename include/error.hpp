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
class Error {
    public:
        ///Underlying WinAPI Error code.
        unsigned long code;

        ///Creates new instance from last error.
        ///@constructor
        Error();

        ///Creates new instance from error code.
        ///@constructor
        Error(unsigned long code);

        ///@return Error description.
        std::wstring description() const;
        ///@return Error description.
        ///@param buffer Storage for description.
        ///@param len Length of storage.
        const wchar_t* description(wchar_t *buffer, size_t len) const;
};
