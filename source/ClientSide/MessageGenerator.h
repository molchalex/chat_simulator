#pragma once
#include <QThread>

#include "UserWidget.h"

// Class MessageGenerator
// generates random messages and sends its to input box on chat widget
class MessageGenerator: public QThread
{
  Q_OBJECT
public:
  MessageGenerator(QLineEdit* ipLineEdit, QObject* ipParent);

private:
  void run() override;

signals:
  void messageStarted();
  void messageFinished(const QString& iMessage);

private:
  QLineEdit* _pLineEdit;

  QString _currentMessage;
  int _printingDelay = 150;
  int _messageDelay = 3000;

  QList<QString> _messages;
};
