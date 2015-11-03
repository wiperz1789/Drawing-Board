#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include <QUndoStack>
#include <QUndoGroup>

class DrawingBoard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    //QString file= "bmp";
   //QByteArray *filesave;

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

public slots:
    void clearScreen();
   void undo();
   void redo();


private slots:
    void open();
    void save();
    bool backColor();
    void penColor();
    void penWidth();
    void rubWidth();
    void about();
    void line();
    void pline();
    void pen();
    void savef();
    void rubon();
    void text();
    void rect();
   // void prints();
    //void clearScreen();


private:
    void createActions();
    void createMenus();
    void createTool();
    void createStatusBar();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    DrawingBoard *drawingBoard;
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;
    QToolBar *toolMenu;
    QToolBar *toolFile;

    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *rubWidthAct;
    QAction *lineAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *newAct;
    QAction *aboutAct;
    QAction *penAct;
    QAction *undoAct;
    QAction *backAct;
    QAction *saveAct;
    QAction *rubAct;
    QAction *plineAct;
    QAction *textAct;
    QAction *rectAct;
   QAction *redoAct;


};

#endif
