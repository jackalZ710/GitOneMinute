#include "imagelabel.h"
#include <QPainter>
#include <QDebug>
#include <QApplication>

const double ImageLabel::MIN_SCALE = 0.01;
const double ImageLabel::MAX_SCALE = 50.0;

ImageLabel::ImageLabel(QWidget *parent)
    : QLabel(parent)
    , _scaleFactor(1.0)
    , _isPanning(false)
    , _infoLabel(nullptr)
    , _currentImagePos(-1, -1)
{
    setAlignment(Qt::AlignCenter);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(100, 100);
    setMouseTracking(true);
    setStyleSheet("QLabel { background-color: #2b2b2b; }");

    // 创建信息显示Label
    setupInfoLabel();
}

ImageLabel::~ImageLabel()
{
    if (_infoLabel) {
        _infoLabel->deleteLater();
    }
}

void ImageLabel::setupInfoLabel()
{
    if (!_infoLabel) {
        _infoLabel = new QLabel(this);
        _infoLabel->setObjectName("infoLabel");
        _infoLabel->setMinimumHeight(40);
        _infoLabel->setMaximumHeight(40);
        _infoLabel->setStyleSheet(
            "#infoLabel {"
            "  background-color: rgba(0, 0, 0, 168);"
            "  color: white;"
            "  font-family: 'Consolas', 'Monaco', 'Courier New', monospace;"
            "  font-size: 10pt;"
            "  padding: 5px 10px;"
            "}"
            );
        _infoLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        _infoLabel->setText("无图像");
        _infoLabel->show();

        // 初始位置
        updateInfoPosition();
    }
}

void ImageLabel::setQImage(const QImage &image)
{
    _originalPixmap = QPixmap::fromImage(image);
    zoomFit();
}

void ImageLabel::clearImage()
{
    _originalPixmap = QPixmap();
    _scaleFactor = 1.0;
    _viewOffset = QPoint(0, 0);
    _currentImagePos = QPoint(-1, -1);
    _currentPixelColor = QColor();

    // 清空显示
    setPixmap(QPixmap());
    setText("无图像");

    // 更新信息显示
    updateInfoDisplay();
}

void ImageLabel::zoomIn()
{
    setScaleFactor(_scaleFactor * 1.2, rect().center());
}

void ImageLabel::zoomOut()
{
    setScaleFactor(_scaleFactor / 1.2, rect().center());
}

void ImageLabel::zoomFit()
{
    if (_originalPixmap.isNull()) return;

    QSize widgetSize = size();
    QSize imageSize = _originalPixmap.size();

    double scaleX = (double)widgetSize.width() / imageSize.width();
    double scaleY = (double)widgetSize.height() / imageSize.height();

    _scaleFactor = qMin(scaleX, scaleY) * 0.95;
    _viewOffset = QPoint(0, 0);
    _currentImagePos = QPoint(-1, -1);

    // 更新显示
    setPixmap(createDisplayPixmap());

    // 更新信息显示
    updateInfoDisplay();

    emit scaleChanged(_scaleFactor);
}

void ImageLabel::zoomOriginal()
{
    _scaleFactor = 1.0;
    _viewOffset = QPoint(0, 0);
    _currentImagePos = QPoint(-1, -1);

    // 更新显示
    setPixmap(createDisplayPixmap());

    // 更新信息显示
    updateInfoDisplay();

    emit scaleChanged(_scaleFactor);
}

void ImageLabel::pan(int dx, int dy)
{
    _viewOffset += QPoint(dx, dy);
    adjustViewOffset();

    // 更新显示
    setPixmap(createDisplayPixmap());

    // 更新信息显示（因为图像位置变了，可能需要更新坐标）
    updateInfoDisplay();
}

void ImageLabel::setScaleFactor(double factor, const QPointF &zoomCenter)
{
    if (_originalPixmap.isNull()) return;

    double oldFactor = _scaleFactor;
    factor = qBound(MIN_SCALE, factor, MAX_SCALE);

    if (qFuzzyCompare(factor, oldFactor)) return;

    // 计算缩放中心在图像上的位置
    QPointF imagePosBefore = widgetToImage(zoomCenter);

    // 更新缩放因子
    _scaleFactor = factor;

    // 计算缩放后的偏移量，保持缩放中心点不变
    QPointF widgetPosAfter = imageToWidget(imagePosBefore);
    QPointF delta = zoomCenter - widgetPosAfter;

    // 应用偏移
    _viewOffset += delta.toPoint();

    adjustViewOffset();

    // 更新显示
    setPixmap(createDisplayPixmap());

    // 更新信息显示
    updateInfoDisplay();

    emit scaleChanged(_scaleFactor);
}

QPixmap ImageLabel::createDisplayPixmap() const
{
    if (_originalPixmap.isNull()) {
        return QPixmap();
    }

    // 创建绘制的图像
    QSize scaledSize = _originalPixmap.size() * _scaleFactor;
    QPixmap displayPixmap(scaledSize);
    displayPixmap.fill(Qt::transparent);

    QPainter painter(&displayPixmap);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // 绘制图像到临时pixmap
    painter.drawPixmap(QRect(QPoint(0, 0), scaledSize), _originalPixmap);

    // 创建最终显示的图像（包含偏移）
    QPixmap finalPixmap(size());
    finalPixmap.fill(QColor("#2b2b2b"));  // 背景色

    QPainter finalPainter(&finalPixmap);
    finalPainter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // 计算绘制位置（居中 + 偏移）
    QRect drawRect(QPoint(0, 0), scaledSize);
    drawRect.moveCenter(QPoint(width() / 2, height() / 2) + _viewOffset);

    // 只绘制在可见区域内的部分
    finalPainter.setClipRect(rect());
    finalPainter.drawPixmap(drawRect, displayPixmap);

    return finalPixmap;
}

void ImageLabel::updateInfoDisplay()
{
    if (!_infoLabel) return;

    QString infoText;

    if (hasImage()) {
        // 第一行：图像大小和缩放比例
        QString line1 = QString("图像: %1 × %2 | 缩放: %3%")
                            .arg(_originalPixmap.width())
                            .arg(_originalPixmap.height())
                            .arg(_scaleFactor * 100, 0, 'f', 1);

        // 第二行：鼠标位置和RGB值
        QString line2;
        if (_currentImagePos.x() >= 0 && _currentImagePos.y() >= 0) {
            QString posText = QString("坐标: (%1, %2)")
                                  .arg(_currentImagePos.x())
                                  .arg(_currentImagePos.y());

            QString colorText;
            if (_currentPixelColor.isValid()) {
                if (_currentPixelColor.alpha() < 255) {
                    colorText = QString(" | RGBA: (%1, %2, %3, %4)")
                    .arg(_currentPixelColor.red())
                        .arg(_currentPixelColor.green())
                        .arg(_currentPixelColor.blue())
                        .arg(_currentPixelColor.alpha());
                } else {
                    colorText = QString(" | RGB: (%1, %2, %3)")
                    .arg(_currentPixelColor.red())
                        .arg(_currentPixelColor.green())
                        .arg(_currentPixelColor.blue());
                }
            } else {
                colorText = " | RGB: (---, ---, ---)";
            }

            line2 = posText + colorText;
        } else {
            line2 = "坐标: (----, ----) | RGB: (---, ---, ---)";
        }

        infoText = line1 + "\n" + line2;
    } else {
        infoText = "无图像";
    }

    _infoLabel->setText(infoText);
}

void ImageLabel::updateInfoPosition()
{
    if (!_infoLabel) return;

    // 计算信息Label的位置（位于底部，横跨整个宽度）
    int infoWidth = width();  // 留10像素边距
    int infoHeight = 40;           // 固定高度
    int infoX = 0;                // 左边距
    int infoY = height() - infoHeight;  // 底部边距

    // 设置信息Label的位置和大小
    _infoLabel->setGeometry(infoX, infoY, infoWidth, infoHeight);
    _infoLabel->raise();  // 确保在最上层
}

void ImageLabel::wheelEvent(QWheelEvent *event)
{
    if (_originalPixmap.isNull()) {
        event->ignore();
        return;
    }

    QPoint numDegrees = event->angleDelta() / 8;
    if (!numDegrees.isNull()) {
        // 获取鼠标位置作为缩放中心
        QPointF zoomCenter = event->position();

        if (numDegrees.y() > 0) {
            setScaleFactor(_scaleFactor * 1.2, zoomCenter);
        } else {
            setScaleFactor(_scaleFactor / 1.2, zoomCenter);
        }
        event->accept();
    } else {
        event->ignore();
    }
}

void ImageLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && hasImage()) {
        _lastMousePos = event->pos();
        _isPanning = true;
        setCursor(Qt::ClosedHandCursor);
        event->accept();
    }
    return QLabel::mousePressEvent(event);
}

void ImageLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && hasImage()) {
        // 左键双击自适应窗口
        zoomFit();
        event->accept();
    }
    return QLabel::mouseDoubleClickEvent(event);
}

void ImageLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (_isPanning) {
        QPoint delta = event->pos() - _lastMousePos;
        _lastMousePos = event->pos();
        pan(delta.x(), delta.y());
        event->accept();
    } else {
        // 更新鼠标位置信息
        _currentImagePos = QPoint(-1, -1);
        _currentPixelColor = QColor();
        QPointF imagePos = widgetToImage(event->pos());

        if (imagePos.x() >= 0 && imagePos.y() >= 0) {
            QPoint intImagePos = imagePos.toPoint();
            _currentImagePos = intImagePos;

            // 检查是否在图像范围内
            if (_originalPixmap.rect().contains(_currentImagePos)) {
                // 获取像素颜色
                QImage image = _originalPixmap.toImage();
                if (image.valid(_currentImagePos)) {
                    _currentPixelColor = image.pixelColor(_currentImagePos);
                }
            }
        }

        // 更新信息显示
        updateInfoDisplay();
    }
    return QLabel::mouseMoveEvent(event);
}

void ImageLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && _isPanning) {
        _isPanning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
    }
    return QLabel::mouseReleaseEvent(event);
}

void ImageLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);

    // 重新计算图像显示
    if (hasImage()) {
        adjustViewOffset();
        setPixmap(createDisplayPixmap());
    }

    // 更新信息Label位置
    updateInfoPosition();
}

void ImageLabel::showEvent(QShowEvent *event)
{
    QLabel::showEvent(event);
    // 更新信息Label位置
    updateInfoPosition();
}

QPointF ImageLabel::imageToWidget(const QPointF &imagePos) const
{
    if (_originalPixmap.isNull()) return QPointF();

    QSize scaledSize = _originalPixmap.size() * _scaleFactor;
    QRect drawRect(QPoint(0, 0), scaledSize);
    drawRect.moveCenter(QPoint(width() / 2, height() / 2) + _viewOffset);

    QPointF widgetPos = drawRect.topLeft() + imagePos * _scaleFactor;
    return widgetPos;
}

QPointF ImageLabel::widgetToImage(const QPointF &widgetPos) const
{
    if (_originalPixmap.isNull()) return QPointF(-1, -1);

    QSize scaledSize = _originalPixmap.size() * _scaleFactor;
    QRect drawRect(QPoint(0, 0), scaledSize);
    drawRect.moveCenter(QPoint(width() / 2, height() / 2) + _viewOffset);

    if (!drawRect.contains(widgetPos.toPoint())) {
        return QPointF(-1, -1);
    }

    QPointF imagePos = (widgetPos - drawRect.topLeft()) / _scaleFactor;

    // 限制在图像范围内
    imagePos.setX(qBound(0.0, imagePos.x(), (double)_originalPixmap.width() - 1));
    imagePos.setY(qBound(0.0, imagePos.y(), (double)_originalPixmap.height() - 1));

    return imagePos;
}

void ImageLabel::adjustViewOffset()
{
    if (_originalPixmap.isNull()) return;

    QSize scaledSize = _originalPixmap.size() * _scaleFactor;
    QRect drawRect(QPoint(0, 0), scaledSize);
    drawRect.moveCenter(QPoint(width() / 2, height() / 2) + _viewOffset);

    // 限制偏移，避免图像完全移出视图
    QRect widgetRect = rect();

    // 如果图像小于窗口，则居中对齐
    if (scaledSize.width() <= widgetRect.width()) {
        _viewOffset.setX(0);
    } else {
        int maxOffsetX = (scaledSize.width() - widgetRect.width()) / 2;
        _viewOffset.setX(qBound(-maxOffsetX, _viewOffset.x(), maxOffsetX));
    }

    if (scaledSize.height() <= widgetRect.height()) {
        _viewOffset.setY(0);
    } else {
        int maxOffsetY = (scaledSize.height() - widgetRect.height()) / 2;
        _viewOffset.setY(qBound(-maxOffsetY, _viewOffset.y(), maxOffsetY));
    }
}

void ImageLabel::setShowInfo(bool show)
{
    if (_infoLabel) {
        _infoLabel->setVisible(show);
    }
}
