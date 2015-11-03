#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

class DrawingBoard : public QWidget
{
    Q_OBJECT

public:
    DrawingBoard(QWidget *parent = 0);
    //void paintback();
   // QPen &pens;
    //QPen &lines;
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setbackColor(const QColor &bColor);
    void setPenWidth(int newWidth);
    void setRubWidth(int rubWidth);
    void setLineOn();
    void setpLineOn();
    void setTextOn();
    void setPenOn();
    void setRubOn();
    void setRectOn();
    void store();
    void restore();
    void iRedo();
    void istore();
    //QPainter saving(QImage &image);
    bool changed() const { return isChanged; }
    QColor penColor() const { return myPenColor; }
    QColor backColor() const { return mybackColor; }
    //void undo();

    int penWidth() const { return myPenWidth; }
    int rubWidth() const {return myRubWidth;}


public slots:
    void clearImage();
    bool clearImage1();
    void clearImage2();


    void print();
    //void clearScreen();

protected:

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
   // void paintback(QImage * image);
private:
    void drawLineTo(const QPoint &endPoint);
    void drawLineThru(const QPoint &startpoint, const QPoint &endpoint);
    void drawLineTemp(const QPoint &startpoint, const QPoint &endpoint);
    void drawTexts(const QPoint &startPoint,const QString &text);
    void erase( const QPoint &endpoint);
    void resizeImage(QImage *image, const QSize &newSize);
    void drawRectTo( const QPoint &endpoint);


    bool isChanged;
    bool drawing;
    bool myLine;
    bool mypLine;
    bool myPen;
    bool myRub;
    bool myText;
    bool myRect;
    bool myUndo;
    bool myRedo;
    int myPenWidth;
    int myRubWidth;
   // int rubWidth;

    //QVector<QImage> backUp;

    QColor myPenColor;
    QColor mybackColor;
    QImage image;
    QPoint lastPoint;
    QPoint startPoint;
    std::string text;
    QImage bUp;
    QImage bdown;
   // Qt::PenCapStyle cap;
   // Qt::PenJoinStyle join;
  //  Qt::PenStyle style;
  //  Qt join;
   // Qt style;


};

#endif
