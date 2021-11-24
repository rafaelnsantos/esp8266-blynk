#include "Button.h"

void Button::begin()
{
  pinMode(PIN, FUNCTION_3);
  pinMode(PIN, INPUT_PULLUP);

  previousState = digitalRead(PIN);
}

void Button::run()
{
  int currentState = digitalRead(PIN);

  if (currentState != previousState)
  {
    if (currentState == LOW)
    {
      if (onPressCallback)
      {
        onPressCallback();
      }
    }
    else
    {
      if (onReleaseCallback)
      {
        onReleaseCallback();
      }
    }
    previousState = currentState;
  }
}

void Button::onPress(ButtonCallback cb)
{
  onPressCallback = cb;
}

void Button::onRelease(ButtonCallback cb)
{
  onReleaseCallback = cb;
}
