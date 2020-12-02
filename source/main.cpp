#include <QApplication>

#include "MainWindow.h"
#include "ServerSide/Server.h"
#include "ClientSide/UserController.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  const QHostAddress host = QHostAddress::LocalHost;
  const int port = 57077;

  // init server
  Server server(host, port);

  // init users
  UserController userController(host, port);

  // connect signals/slots to main window
  MainWindow mainWindow(&server, &userController);
  mainWindow.show();

  return app.exec();
}
