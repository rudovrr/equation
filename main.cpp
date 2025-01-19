#include "widget.hpp"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Widget window;
    window.setWindowTitle("Решатель кубов");
    window.resize(350, 70);
    window.show(); 
    return app.exec();
}



