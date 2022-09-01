#include "pch.h"
#include "KeyHandling.h"
#if __has_include("KeyHandling.g.cpp")
#include "KeyHandling.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::testgame::implementation
{
    KeyHandling::KeyHandling()
    {
        InitializeComponent();
    }

    int32_t KeyHandling::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void KeyHandling::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void KeyHandling::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
