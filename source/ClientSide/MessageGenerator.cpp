#include "MessageGenerator.h"

#include <QRandomGenerator>

MessageGenerator::MessageGenerator(QLineEdit* ipLineEdit, QObject* ipParent)
  : QThread(ipParent)
  , _pLineEdit(ipLineEdit)
{
  _messages = {
    "Hello",
    "Hi",
    "I’m so pleased to meet you",
    "I’ve heard so much about you",
    "It’s good to have you here!",
    "I’d like you to meet someone!",
    "I am indeed! And you must be…",
    "I’ll leave you two to get acquainted!",
    "Please, call me…",
    "I almost did not recognize you!"
  };
}

void MessageGenerator::run()
{
  QRandomGenerator* random = QRandomGenerator::global();

  while(isRunning())
  {
    // get next message 
    if (_currentMessage.isEmpty())
    {
      const int messageDelay = random->bounded(_messageDelay / 10, _messageDelay);
      msleep(messageDelay);
      _currentMessage = _messages[random->bounded(0, _messages.size() - 1)];
    }

    // print message to input box
    while (!_currentMessage.isEmpty())
    {
      const int printingDelay = random->bounded(_printingDelay / 10, _printingDelay);
      msleep(printingDelay);

      auto text = _pLineEdit->text();
      text += _currentMessage.front();
      _pLineEdit->setText(text);
      _pLineEdit->setCursorPosition(text.size());

      _currentMessage.remove(0, 1);
    }

    emit messageFinished(_pLineEdit->text());
    _pLineEdit->setText("");
  }
}