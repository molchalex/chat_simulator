#pragma once

#include <QInputDialog>

#include "ui_MainWindow.h"

class Server;
class User;
class UserController;
class QStringListModel;

class MainWindow: public QMainWindow, Ui::MainWindow
{
  Q_OBJECT
public:
  MainWindow(Server* ipServer, UserController* ipUserController);
  
private slots:
  void onAddButtonClicked();
  void addUserWidget(User* ipUser);
  void printLog(const QString& iMessage) const;

signals:
  void newUser(const QString& iUserName);

private:
  QStringListModel* _serverLog;
};
