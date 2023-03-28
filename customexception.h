#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H
#include <QException>

class CustomException : QException
{
public:
    CustomException();
    virtual void raiseException() const { raise(); }
    void raise() const override { throw *this; }
    CustomException *clone() const override { return new CustomException(*this); }
};

#endif // CUSTOMEXCEPTION_H
