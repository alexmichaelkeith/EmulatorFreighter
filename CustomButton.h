#pragma once

#include <QPushButton>

class CustomButton : public QPushButton
{
public:
    CustomButton( const QString& text, QWidget* parent = 0 );

    // Enhancement, it will reverse the button text
    void reverseText();
};
