#include <QtWidgets>
#ifndef QT_NO_PRINTER
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include<QtPrintSupport/QtPrintSupport>
#endif

#include "drawingboard.h"

DrawingBoard::DrawingBoard(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    isChanged = false;
    drawing = false;
    myRubWidth =3;
    myPenWidth = 1;
    myPenColor = Qt::red;
    mybackColor= Qt::white;
    myLine= false;
    mypLine=false;
    myPen = false;
    myRub= false;
    myText = false;
    myRect= false;
    myUndo =false;
    myRedo= false;
  //  cap=Qt::RoundCap;
 //   join =Qt::RoundJoin;
 //   style-Qt::SolidLine;
    text= "Hello world";
    //cap("Qt::RoundCap");
    //join=Qt::RoundJoin;
   // style=Qt::SolidLine;

}

bool DrawingBoard::openImage(const QString &fileName)
{
    QImage imageLoaded;
    if (!imageLoaded.load(fileName))
        return false;
   // saving(&image).save();

    QSize newSize = imageLoaded.size().expandedTo(size());
    resizeImage(&imageLoaded, newSize);
    image = imageLoaded;
    isChanged = false;
    update();
    return true;

}

bool DrawingBoard::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage imageOnBoard = image;
    resizeImage(&imageOnBoard, size());

    if (imageOnBoard.save(fileName, fileFormat)) {
        isChanged = false;
        return true;
    } else {
        return false;
    }
}

void DrawingBoard::restore()
{
    if(myUndo){

    QSize newSize = bUp.size().expandedTo(size());
    resizeImage(&bUp, newSize);
    bdown=image;
    image=bUp;
myUndo =false;
myRedo =true;
  //  isChanged = false;
    update();
}}
void DrawingBoard::store()
{
   // if(isChanged)
  //  {
    bUp =image;
    myUndo =true;
    myRedo =true;

//    }

}
void DrawingBoard::istore()
{
   // if(isChanged)
  //  {
    bdown =image;
    myUndo =true;
    myRedo =true;

//    }

}
void DrawingBoard::iRedo()
{
    if(myRedo){
    QSize newSize = bdown.size().expandedTo(size());
    resizeImage(&bdown, newSize);
    bUp=image;
    image=bdown;
myRedo =false;
myUndo = true;
  //  isChanged = false;
    update();
}
}
void DrawingBoard::setPenColor(const QColor &newColor)
{
    myPenColor=newColor;
   // pen.setBrush(newColor);
   // line.setBrush(newColor);
}
void DrawingBoard::setbackColor(const QColor &bColor)
{
   // mybackColor = bColor;
   // QPixmap back;
    mybackColor = bColor;
    image.fill(bColor);
}


void DrawingBoard::setPenWidth(int newWidth)
{
    myPenWidth=newWidth;
   // myRubWidth= newWidth;
//    pen.setWidth(newWidth);
   // line.setWidth(newWidth);
}
void DrawingBoard::setRubWidth(int rubWidth)
{
    myRubWidth= rubWidth;

}
void DrawingBoard::setLineOn()
{
    myLine = true;
    myPen = false;
    myRub = false;
    mypLine= false;
    myText = false;
    myRect = false;


}
void DrawingBoard::setpLineOn()
{
    myLine = false;
    myPen = false;
    myRub = false;
    mypLine= true;
    myText = false;
    myRect = false;


}
void DrawingBoard::setPenOn()
{
    myPen = true;
    myLine =false;
    myRub =false;
    mypLine= false;
    myText = false;
    myRect = false;


}
void DrawingBoard::setRubOn()
{
    myRub =true;
    myPen = false;
    myLine = false;
    mypLine= false;
    myText = false;
    myRect = false;

}
void DrawingBoard::setTextOn()
{
    myRub =false;
    myPen = false;
    myLine = false;
    mypLine= false;
    myText = true;
    myRect = false;


}

void DrawingBoard::setRectOn()
{
    myRub =false;
    myPen = false;
    myLine = false;
    mypLine= false;
    myText = false;
    myRect = true;


}


/*void DrawingBoard::undo(){

   // saving(&image).restore();
}*/

void DrawingBoard::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    isChanged = true;
    update();
}

bool DrawingBoard::clearImage1()
{
    if(isChanged&&drawing){
            image.fill(qRgb(255, 255, 255));
    isChanged = false;
    update();
    return true;
    }
    return false;
}

void DrawingBoard::clearImage2()
{
        image.fill(qRgb(255, 255, 255));
    isChanged = false;
    update();
}
/*void DrawingBoard::clearScreen()
{
    image.fill(qRgb(255, 255, 255));
    isChanged = true;
    update();
}
*/

void DrawingBoard::mousePressEvent(QMouseEvent *event)
{
    if(myLine){
        if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
        drawing = true;
    }}
    else if(myText)
    {
        if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
        drawing = true;
        }
    }
    else if(myRect)
        {
            if (event->button() == Qt::LeftButton) {
            startPoint = event->pos();
            drawing = true;
            }
    }
    else if(myPen)
    {
        if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
        }
    }else if(myRub)
    {
        if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
        }
    }else if(mypLine)
    {
        if (event->button() == Qt::LeftButton) {
       // startPoint = event->pos();
        drawing = true;
        }
    }
    else
    {
        if (event->button() == Qt::LeftButton) {
        QMessageBox::about(this, tr("Mouse Event detection"),
                tr("You have Clicked Left Button. Now, close and select your preferences"));
    }


}
}

void DrawingBoard::mouseMoveEvent(QMouseEvent *event)
{
    if(myLine){
        if ((event->buttons() & Qt::LeftButton) && drawing){
           // backUp.push_back(image);
           // store();

        drawLineThru(startPoint,startPoint);
        }
        else if (event->button() == Qt::RightButton) {

            QMessageBox::about(this, tr("Mouse Event detection"),
                    tr("You have Clicked right button. To draw Please press left button on mouse"));
        }
    }
  else if(myRect){
        if ((event->buttons() & Qt::LeftButton) && drawing){
           // backUp.push_back(image);
            //store();

        drawRectTo(event->pos());
         // istore();

        }
        else if (event->button() == Qt::RightButton) {

            QMessageBox::about(this, tr("Mouse Event detection"),
                    tr("You have Clicked right button. To draw Please press left button on mouse"));
        }
    }
    else if(myText){
        if ((event->buttons() & Qt::LeftButton) && drawing){
           // backUp.push_back(image);
            store();

        drawTexts(startPoint,QString::fromStdString(text));
        istore();

        }
        else if (event->button() == Qt::RightButton) {

            QMessageBox::about(this, tr("text Event detection"),
                    tr("You have Clicked right button. To draw Please press left button on mouse"));
        }
    }
    else if(myPen)
     {
        if ((event->buttons() & Qt::LeftButton) && drawing){
           // backUp.push_back(image);
            store();

        drawLineTo(event->pos());
        istore();

        }
        else if (event->button() == Qt::RightButton) {

            QMessageBox::about(this, tr("Mouse Event detection"),
                    tr("You have Clicked right button. To draw Please press left button on mouse"));
        }
    }
    else if(mypLine){
        if ((event->buttons() & Qt::LeftButton) && drawing){
           // backUp.push_back(image);
            store();
        drawLineTemp(startPoint,startPoint);
           istore();
        }
        else if (event->button() == Qt::RightButton) {

            QMessageBox::about(this, tr("Mouse Event detection"),
                    tr("You have Clicked right button. To draw Please press left button on mouse"));
        }
    }
    else if(myRub)
     {
        if ((event->buttons() & Qt::LeftButton) && drawing){
          //  backUp.push_back(image);

        erase(event->pos());//to change

        }
        else if (event->button() == Qt::RightButton) {

            QMessageBox::about(this, tr("Mouse Event detection"),
                    tr("You have Clicked right button. To erase Please press left button on mouse"));
        }
    }
    else
    {
        if (event->button() == Qt::LeftButton) {
        QMessageBox::about(this, tr("Mouse Event detection"),
                tr("You have Clicked Left Button. Now, close and select your preferences"));
    }
        else if (event->button() == Qt::RightButton) {

            QMessageBox::about(this, tr("Mouse Event detection"),
                    tr("You have Clicked right button. Now, close and select your preferences"));
        }

}
}

void DrawingBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if(myLine){
        if (event->button() == Qt::LeftButton && drawing) {
           // backUp.push_back(image);
            store();

            drawLineThru(startPoint, event->pos());
istore();
            drawing = false;
            }
        else if (event->button() == Qt::RightButton) {
           // QString str1 = QString::number(myPenWidth);
           // myPenWidth = 1;
           // QString str2 = QString::(myPenColor);

           // myPenColor = Qt::red;
            bool ok;
            int newWidth = QInputDialog::getInt(this, tr("Line Size"),
                                                tr("Select the size of line:"),
                                                penWidth(),
                                                1, 50, 1, &ok);
              // bool ok;
            //QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                       //                             tr("Season:"), items, 0, false, &ok);

            if (ok){
                setPenWidth(newWidth);
               // statusBar()->showMessage(tr("qweewqewdasdsakdl"));
            }
        }
    }
    else  if(myRect){
          if ((event->buttons() & Qt::LeftButton) && drawing){
             // backUp.push_back(image);
            // store();

          drawRectTo(event->pos());
        //   istore();
          drawing = false;

          }
          else if (event->button() == Qt::RightButton) {

              bool ok;
              int newWidth = QInputDialog::getInt(this, tr("Rectangle border size"),
                                                  tr("Select the size of the border:"),
                                                  penWidth(),
                                                  1, 50, 1, &ok);
                // bool ok;
              //QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                         //                             tr("Season:"), items, 0, false, &ok);

              if (ok){
                  setPenWidth(newWidth);
                 // statusBar()->showMessage(tr("qweewqewdasdsakdl"));
              }
          }
      }

    else if(myText){
        if ((event->buttons() & Qt::LeftButton) && drawing){
           // backUp.push_back(image);
            store();

        drawTexts(event->pos(),QString::fromStdString(text));
        istore();
        drawing = false;

        }
        else if (event->button() == Qt::RightButton) {
           // QString str =QString::fromStdString(text);
            bool ok;
            QString txt = QInputDialog::getText(this, tr("Enter the text you want to print"),
                                                 tr("Message"), QLineEdit::Normal,tr("Type your message"),
                                                  &ok);
            if (ok){
                text=txt.toStdString();
                //text=txt;
        }}
    }
    else if(myPen)
    {
    if (event->button() == Qt::LeftButton && drawing) {
       // backUp.push_back(image);
        store();

        drawLineTo(event->pos());
istore();
        drawing = false;
    }
    else if (event->button() == Qt::RightButton) {

        bool ok;
        int newWidth = QInputDialog::getInt(this, tr("Pen Size"),
                                            tr("Select the size of pen:"),
                                            penWidth(),
                                            1, 50, 1, &ok);
          // bool ok;
          // QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                       //                         tr("Season:"), items, 0, false, &ok);

        if (ok){
            setPenWidth(newWidth);
           // statusBar()->showMessage(tr("qweewqewdasdsakdl"));
        }
        //QMessageBox::about(this, tr("Pen tool properties"),
             //   tr("You have Clicked right button. To draw Please press left button on mouse"));
    }
    }
    else if(mypLine){
        if (event->button() == Qt::LeftButton && drawing) {
           // backUp.push_back(image);
            store();

            drawLineTemp(startPoint, event->pos());
            istore();
            drawing = false;
            }
        else if (event->button() == Qt::RightButton) {
            bool ok;
            int newWidth = QInputDialog::getInt(this, tr("Select polyline Size"),
                                                tr("Select the size of Polyline:"),
                                                penWidth(),
                                                1, 50, 1, &ok);
            if (ok)
                setPenWidth(newWidth);
          //  QMessageBox::about(this, tr("PolyLine tool properties"),
            //        tr("You have Clicked right button. To draw Please press left button on mouse"));
        }
    }
    else if(myRub)
    {
    if (event->button() == Qt::LeftButton && drawing) {
      //  backUp.push_back(image);
        store();

        erase(event->pos());//to change
istore();
        drawing = false;
    }
    else if (event->button() == Qt::RightButton) {

        bool ok;
        int newWidth = QInputDialog::getInt(this, tr("Eraser Size"),
                                            tr("Select the size of Eraser:"),
                                            rubWidth(),
                                            1, 50, 1, &ok);
        if (ok)
            setRubWidth(newWidth);
    }
    }
    else
    {
        if (event->button() == Qt::LeftButton) {
        QMessageBox::about(this, tr("Mouse Event detection"),
                tr("You have Clicked Left Button. Now, close and select your preferences"));
    }

        else if (event->button() == Qt::RightButton) {

            QMessageBox::about(this, tr("Mouse Event1 detection"),
                    tr("You have Clicked right button. Now, close and select your preferences to see the properties of tool"));
        }

}
}

void DrawingBoard::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(mypLine){
    myLine = true;
    myPen = false;
    myRub = false;
    mypLine= false;
    myText = false;
    myRect= false;

}}
void DrawingBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

/*void DrawingBoard::paintback()
{
    QImage img =backUp.first();
    QPainter painter(this);
    //QRect dirtyRect = event->rect();
    painter.drawImage(img);
}*/

void DrawingBoard::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}


void DrawingBoard::drawLineTo(const QPoint &endPoint)
{
    //saving(&image).save();
  //  store();
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    isChanged = true;
        int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void DrawingBoard::drawRectTo(const QPoint &endpoint)
{
    //store();

    int sx = startPoint.x();
    int sy = startPoint.y();

    int ex = endpoint.x();
    int ey = endpoint.y();
    QPainter painter(&image);
       painter.setPen(QPen(myPenColor, myPenWidth));
  //  painter.setPen(QPen(myPenColor));
        //painter.setFont(QFont("Arial", 30));
        painter.drawRect(QRect(startPoint,endpoint));
        isChanged = true;
        update();
lastPoint = endpoint;


}

void DrawingBoard::drawTexts(const QPoint &startpoint,const QString &txt)
{
    //store();

    int sx = startpoint.x();
    int sy = startpoint.y();
    //QSize s(30,30);
    QPainter painter(&image);
        painter.setPen(QPen(myPenColor));
        painter.setFont(QFont("Arial", 30));
        painter.drawText(QRect(sx,sy,1500,1500),txt);
        isChanged = true;
        update();

       // update(QRect(startpoint,startpoint).normalized());
   // startPoint = startpoint;

}

void DrawingBoard::drawLineThru(const QPoint &startpoint, const QPoint &endpoint)
{
    //store();

    //saving(&image).save();
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(startpoint,endpoint);
    isChanged = true;
    update();
   // int rad = (myPenWidth / 2) + 2;
    //update(QRect(startPoint, endpoint).normalized()
                                    // .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endpoint;
}

void DrawingBoard::erase(const QPoint &endpoint)
{
    //store();

    //saving(&image).save();
    QPainter painter(&image);

    int sx = endpoint.x();
    int sy = endpoint.y();

    //int rad = (myRubWidth / 2)+4;

    painter.eraseRect(sx, sy,myRubWidth+2,myRubWidth+2);
   // painter.eraseRect(sx,sy,myRubWidth+2,myRubWidth+2);
    isChanged = true;

  //painter.eraseRect(QRect(sx,sy,myRubWidth,myRubWidth).normalized().adjusted(-rad, -rad, +rad, +rad));
 update();
   //int rad = (myRubWidth / 2) + 2;
   // update(QRect(startPoint, endpoint).normalized()
                         //           .adjusted(-rad, -rad, +rad, +rad));
  //  startPoint = endpoint;
}
void DrawingBoard::drawLineTemp(const QPoint &startpoint, const QPoint &endpoint)
{
   // store();

    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(startpoint,endpoint);
    isChanged = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(startPoint, endpoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    startPoint = endpoint;
}

void DrawingBoard::resizeImage(QImage *image, const QSize &newSize)
{

    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(mybackColor);
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void DrawingBoard::print()
{
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog printDialog(&printer, this);
    printDialog.setWindowTitle("Print Document");
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
               QRect rect = painter.viewport();
               QSize size = image.size();
               size.scale(rect.size(), Qt::KeepAspectRatio);
               painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
               painter.setWindow(image.rect());
               painter.drawImage(0, 0, image);
    }

#endif

}
