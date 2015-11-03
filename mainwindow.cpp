    #include <QtWidgets>

    #include "mainwindow.h"
    #include "drawingboard.h"

    MainWindow::MainWindow()
    {
        drawingBoard = new DrawingBoard;
        setCentralWidget(drawingBoard);
        createActions();
        createMenus();
        createTool();
        createStatusBar();
        //QPainter back;
        //back.background(drawingBoard->mybackColor);
        setWindowTitle(tr("Paint Application"));
        resize(700, 600);
    }

    void MainWindow::closeEvent(QCloseEvent *event)
    {
        if (maybeSave()) {
            event->accept();
        } else {
            event->ignore();
        }
    }

    void MainWindow::open()
    {
        if (maybeSave()) {
            QString fileName = QFileDialog::getOpenFileName(this,
                                       tr("Open File"), QDir::currentPath());
            if (!fileName.isEmpty())
                drawingBoard->openImage(fileName);
            statusBar()->showMessage(tr("Image Loaded"));
        }

    }

    void MainWindow::save()
    {
        QAction *action = qobject_cast<QAction *>(sender());
        QByteArray fileFormat = action->data().toByteArray();
        saveFile(fileFormat);

    }

    void MainWindow::penColor()
    {
        QColor newColor = QColorDialog::getColor(drawingBoard->penColor());
        if (newColor.isValid())
            drawingBoard->setPenColor(newColor);
    }
    bool MainWindow::backColor()
    {
        if (drawingBoard->changed()) {
           QMessageBox::StandardButton ret;
           ret = QMessageBox::warning(this, tr("Confirmation"),
                              tr("You have selected new background it will destroy previos image\n"
                                 "Do you want to save  changes?"),
                              QMessageBox::Save | QMessageBox::No
                              | QMessageBox::Cancel);
            if (ret == QMessageBox::Save) {
               return saveFile("bmp");
            } else if (ret == QMessageBox::Cancel) {
                return false;
            }
        }

        QColor aColor = QColorDialog::getColor();
        if (aColor.isValid()){
      //  QBrush bColor =aColor;
        drawingBoard->setbackColor(aColor);
         }

        return true;

    }

    void MainWindow::penWidth()
    {
        bool ok;
        int newWidth = QInputDialog::getInt(this, tr("Pen Size"),
                                            tr("Select the size of pen:"),
                                            drawingBoard->penWidth(),
                                            1, 50, 1, &ok);
        if (ok)
            drawingBoard->setPenWidth(newWidth);
    }

    void MainWindow::rubWidth()
    {
        bool ok;
        int newWidth = QInputDialog::getInt(this, tr("Eraser Size"),
                                            tr("Select the size of Eraser:"),
                                            drawingBoard->rubWidth(),
                                            1, 50, 1, &ok);
        if (ok)
            drawingBoard->setRubWidth(newWidth);
    }
    void MainWindow::line()
    {
        drawingBoard->setLineOn();
        statusBar()->showMessage(tr("Line On"));
    }
    void MainWindow::pen()
    {
        drawingBoard->setPenOn();
        statusBar()->showMessage(tr("Pen On"));
    }
    void MainWindow::about()
    {
        QMessageBox::about(this, tr("Paint Application"),
                tr("Name: Alpesh Kothari"
                   "<p>Paint Appilcation as assignment #3</p>"
                   "Please read readme file for more details"
                   "<p>1.New                                   "
                   "<p>2.Open                                   "
                   "<p>3.Save                                   "
                   "<p>4.SaveAS (Extra feature with all formats saving support)                                   "
                   "<p>5. Size of pen, Line, Polyline, Rectangle                                   "
                   "<p>6.Eraser (Extra feaures)                                   "
                   "<p>7. Size of earser(Extra feature)                                   "
                   "<p>8. clear                                   "
                   "<p>9.exit                                   "
                   "<p>10. Undo                                   "
                   "<p>11. Redo                                   "
                   "<p>12. Events implementation(Right click, left click, Double click)                                   "
                   "<p>13.Loading an Image from computer                                   "
                   "<p>14. Toolbar                                   "
                   "<p>15. Foreground and background color selection                                   "
                   "<p>16. Text box(Extra features)                                   "
                   "<p>17. Right click properties popup                                   "));
    }

    void MainWindow::createActions()
    {
        openAct = new QAction(QIcon(":images/open_icon.bmp"),tr("&Open..."), this);
        openAct->setShortcuts(QKeySequence::Open);
        openAct->setStatusTip(tr("Open a file"));
        connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

        newAct = new QAction(QIcon(":images/new_icon.bmp"),tr("&New..."), this);
        newAct->setShortcuts(QKeySequence::New);
        newAct->setStatusTip(tr("Create a new file"));
        connect(newAct, SIGNAL(triggered()), this, SLOT(clearScreen()));

        saveAct = new QAction(QIcon(":images/save_icon.bmp"),tr("&Save..."), this);
        saveAct->setShortcuts(QKeySequence::Save);
        saveAct->setStatusTip(tr("Save Image"));
        connect(saveAct, SIGNAL(triggered()), this, SLOT(savef()));


        rubAct = new QAction(QIcon(":images/eraser_icon.bmp"),tr("&Eraser..."), this);
        //rubAct->setShortcuts(QKeySequence::Save);
        rubAct->setStatusTip(tr("Eraser"));
        connect(rubAct, SIGNAL(triggered()), this, SLOT(rubon()));

        foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
            QString text = tr("%1...").arg(QString(format).toUpper());

            QAction *action = new QAction(text, this);
            action->setData(format);
            connect(action, SIGNAL(triggered()), this, SLOT(save()));
            saveAsActs.append(action);
        }

        printAct = new QAction(QIcon(":images/print_icon.ico"),tr("&Print..."), this);
        printAct->setStatusTip(tr("Print the image"));
        connect(printAct, SIGNAL(triggered()), drawingBoard, SLOT(print()));

        exitAct = new QAction(QIcon(":images/exit_icon.ico"),tr("&Exit"), this);
        exitAct->setShortcut(tr("Ctrl+Q"));
        exitAct->setShortcuts(QKeySequence::Quit);
        exitAct->setStatusTip(tr("Exit"));
        connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

        backAct = new QAction(QIcon(":images/bcolor_icon.bmp"),tr("&Background Color..."), this);
        backAct->setStatusTip(tr("Set background color"));
        connect(backAct, SIGNAL(triggered()), this, SLOT(backColor()));

        penColorAct = new QAction(QIcon(":images/fcolor_icon.bmp"),tr("&Foreground Color..."), this);
        penColorAct->setStatusTip(tr("Set foreground color"));
        connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

        textAct = new QAction(QIcon(":images/text_icon.png"),tr("&Text..."), this);
        textAct->setStatusTip(tr("Insert Text"));
        connect(textAct, SIGNAL(triggered()), this, SLOT(text()));

        rectAct = new QAction(QIcon(":images/rect-icon.png"),tr("&Rectangle..."), this);
        rectAct->setStatusTip(tr("Rectangle"));
        connect(rectAct, SIGNAL(triggered()), this, SLOT(rect()));

        penWidthAct = new QAction(QIcon(":images/size_icon.ico"),tr("Pen &Width..."), this);
        penWidthAct->setStatusTip(tr("Set pen/line width"));
        connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

        rubWidthAct = new QAction(QIcon(":images/size_icon.ico"),tr("Eraser &Width..."), this);
        rubWidthAct->setStatusTip(tr("Set eraser width"));
        connect(rubWidthAct, SIGNAL(triggered()), this, SLOT(rubWidth()));

        lineAct = new QAction(QIcon(":images/line_icon.bmp"),tr("Line"), this);
        lineAct->setStatusTip(tr("Line"));
        connect(lineAct, SIGNAL(triggered()), this, SLOT(line()));

        plineAct = new QAction(QIcon(":images/pline.png"),tr("PolyLine"), this);
        plineAct->setStatusTip(tr("PolyLine"));
        connect(plineAct, SIGNAL(triggered()), this, SLOT(pline()));

        penAct = new QAction(QIcon(":images/pen_icon.bmp"),tr("Pen"), this);
        penAct->setStatusTip(tr("Pen/ Pencil"));
        connect(penAct, SIGNAL(triggered()), this, SLOT(pen()));

        undoAct = new QAction(QIcon(":images/undo_icon.bmp"),tr("Undo"), this);
        undoAct->setShortcut(QKeySequence::Undo);
        undoAct->setStatusTip(tr("Undo"));
         connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

         redoAct = new QAction(QIcon(":images/redo_icon.bmp"),tr("Redo"), this);
         redoAct->setShortcut(QKeySequence::Redo);
         redoAct->setStatusTip(tr("redo"));
          connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

        clearScreenAct = new QAction(QIcon(":images/clearall_icon.bmp"),tr("&Clear Screen"), this);
        clearScreenAct->setShortcut(tr("Ctrl+L"));
        clearScreenAct->setStatusTip(tr("Clear Screen"));
        connect(clearScreenAct, SIGNAL(triggered()),
                drawingBoard, SLOT(clearImage()));

        aboutAct = new QAction(tr("&About"), this);
        aboutAct->setStatusTip(tr("About Application"));
        connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));


    }

    void MainWindow::createMenus()
    {
        saveAsMenu = new QMenu(tr("&Save As"), this);
        foreach (QAction *action, saveAsActs)
            saveAsMenu->addAction(action);

        fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addAction(openAct);
        fileMenu->addAction(newAct);
        fileMenu -> addAction(saveAct);
        fileMenu->addMenu(saveAsMenu);
        fileMenu->addAction(printAct);
        fileMenu->addSeparator();
        fileMenu->addAction(exitAct);

        optionMenu = menuBar()->addMenu(tr("&Preference"));
        optionMenu->addAction(backAct);
        optionMenu->addAction(penColorAct);
        optionMenu->addAction(penWidthAct);
        optionMenu->addAction(rubWidthAct);



       optionMenu->addSeparator();
       optionMenu->addAction(textAct);
       optionMenu->addAction(rectAct);
        optionMenu->addAction(lineAct);
        optionMenu->addAction(plineAct);
        optionMenu->addAction(penAct);
        optionMenu->addAction(rubAct);
        optionMenu->addSeparator();
        optionMenu->addAction(undoAct);
        optionMenu->addAction(redoAct);

        optionMenu->addAction(clearScreenAct);

        helpMenu = menuBar()->addMenu(tr("&Help"));
        helpMenu->addAction(aboutAct);

    }

    void MainWindow::createTool()
    {
        toolFile = addToolBar(tr("File"));
        toolFile-> addAction(newAct);
        toolFile -> addAction(openAct);
        toolFile -> addAction(saveAct);
        toolFile -> addAction(printAct);
        toolFile -> addAction(exitAct);
        toolFile -> setFloatable(true);
        toolFile-> setMovable(true);
        toolFile->adjustSize();

        toolMenu = addToolBar(tr("Tools"));
        toolMenu -> addAction(backAct);
        toolMenu -> addAction(penColorAct);
        toolMenu -> addAction(penWidthAct);
        toolMenu -> addAction(rubWidthAct);
        toolMenu -> addAction(penAct);
        toolMenu -> addAction(textAct);
        toolMenu -> addAction(rectAct);
        toolMenu -> addAction(undoAct);
        toolMenu -> addAction(redoAct);
        toolMenu -> addAction(clearScreenAct);

        toolMenu -> addAction(lineAct);
        toolMenu -> addAction(plineAct);
        toolMenu -> addAction(rubAct);
        toolMenu -> setFloatable(true);
        toolMenu-> setMovable(true);
        toolMenu->adjustSize();

   }

    void MainWindow::createStatusBar()
    {
        statusBar()->showMessage(tr("Ready"));

    }

    bool MainWindow::maybeSave()
    {
        if (drawingBoard->changed()) {
           QMessageBox::StandardButton ret;
           ret = QMessageBox::warning(this, tr("Confirmation"),
                              tr("Image changed!!!!\n"
                                 "Do you want to save  changes?"),
                              QMessageBox::Save | QMessageBox::Discard
                              | QMessageBox::Cancel);
            if (ret == QMessageBox::Save) {
                return saveFile("bmp");
            } else if (ret == QMessageBox::Cancel) {
                return false;
            }
        }
        return true;
    }

    void MainWindow::undo()
    {
       drawingBoard->restore();
       statusBar()->showMessage(tr("Undo on"));


    }
    void MainWindow::redo()
    {
       drawingBoard->iRedo();
       statusBar()->showMessage(tr("Redo on"));


    }



    bool MainWindow::saveFile(const QByteArray &fileFormat)
    {
        QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

        QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                   initialPath,
                                   tr("%1 Files (*.%2);;All Files (*)")
                                   .arg(QString::fromLatin1(fileFormat.toUpper()))
                                   .arg(QString::fromLatin1(fileFormat)));
        if (fileName.isEmpty()) {
            return false;
        } else {
            return drawingBoard->saveImage(fileName, fileFormat.constData());
        }
      //  statusBar()->showMessage(tr("File Saved Successfully"));
    }
    void MainWindow::clearScreen()
    {
         if(drawingBoard->clearImage1())
         {    }else if(maybeSave()){ drawingBoard->clearImage2();}
    }
    void MainWindow::savef()
    {
        saveFile("bmp");

    }

    void MainWindow::text()
    {
        drawingBoard->setTextOn();
        statusBar()->showMessage(tr("Text on"));
    }
    void MainWindow::rect()
    {
        drawingBoard->setRectOn();
        statusBar()->showMessage(tr("Rectangle active"));
    }
    void MainWindow::rubon()
    {
        drawingBoard->setRubOn();
        statusBar()->showMessage(tr("Eraser On"));
    }

    void MainWindow::pline()
    {
        drawingBoard->setpLineOn();
        statusBar()->showMessage(tr("PolyLine activated"));
    }
    /*void MainWindow::undoM(){
        drawingBoard->undo();

    }*/


