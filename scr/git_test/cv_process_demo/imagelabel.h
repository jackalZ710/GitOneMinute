#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTransform>
#include <QPixmap>
#include <QPoint>
#include <QColor>
#include <QTimer>

class ImageLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ImageLabel(QWidget *parent = nullptr);
    ~ImageLabel();

    // 图像操作
    void setQImage(const QImage &image);
    void clearImage();
    bool hasImage() const { return !_originalPixmap.isNull(); }

    // 信息显示控制
    void setShowInfo(bool show);

    // 视图操作，这个接口开放处理，我们可以在外部增加按钮控件，实现点击放大按钮则放大一次的效果
    void zoomIn();//放大
    void zoomOut();//缩小
    void zoomFit();//自适应
    void zoomOriginal();
    void pan(int dx, int dy);//平移

signals:
    void scaleChanged(double factor);//这个信号开放出来，我们可以在外面接收，然后在一个label上显示当前的缩放比例

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    void setScaleFactor(double factor, const QPointF &zoomCenter = QPointF());
    QPointF imageToWidget(const QPointF &imagePos) const;
    QPointF widgetToImage(const QPointF &widgetPos) const;
    void adjustViewOffset();
    void updateInfoDisplay();
    void updateInfoPosition();
    void setupInfoLabel();

    // 创建显示的图像
    QPixmap createDisplayPixmap() const;

    // 图像显示相关
    QPixmap _originalPixmap;//原始图像
    double _scaleFactor;//缩放比例
    QPoint _viewOffset;//平移位置
    QPoint _lastMousePos;
    bool _isPanning;

    // 信息显示相关
    QLabel *_infoLabel;
    QPoint _currentImagePos;
    QColor _currentPixelColor;

    // 缩放限制
    static const double MIN_SCALE;
    static const double MAX_SCALE;
};

#endif // IMAGELABEL_H
