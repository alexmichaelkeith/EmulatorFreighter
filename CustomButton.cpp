#include "CustomButton.h"
#include "algorithm"

CustomButton::CustomButton( const QString& text, QWidget* parent )
    : QPushButton( text, parent )
{

}

void CustomButton::reverseText()
{
    QString buttonText = text();
    std::reverse(buttonText.begin(), buttonText.end());
    setText( buttonText );
}
