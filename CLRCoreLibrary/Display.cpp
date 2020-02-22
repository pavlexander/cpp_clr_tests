#include "Display.h"

namespace CLRCoreLibrary
{
    void Display::Print(System::String^ message)
    {
        System::Console::WriteLine(message);
    }
}