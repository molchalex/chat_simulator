#pragma once

#include "ui_UserWidget.h"

class User;
class MessageGenerator;
class QStringListModel;

// Widget represent of chat
// contains list of messages and input box
class UserWidget: public QWidget, Ui::UserWidget
{
  Q_OBJECT
public:
  UserWidget(User* ipUser, QWidget* ipParent);
  ~UserWidget();

private slots:
  void printMessage(const QString& iMessage) const;

private:
  User* _pUser;
  QStringListModel* _messages;
  MessageGenerator* _pMessageGenerator;
};
