#ifndef TILEDIMAGE_H
#define TILEDIMAGE_H

#include <QObject>
#include <QColor>
#include <QUrl>
#include <QPoint>
#include <QLoggingCategory>

class TMXImageLayer;

class TiledImage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(QColor transparentColor READ transparentColor WRITE setTransparentColor NOTIFY transparentColorChanged)
    Q_PROPERTY(qreal verticalOffset READ verticalOffset WRITE setVerticalOffset NOTIFY verticalOffsetChanged)
    Q_PROPERTY(qreal horizontalOffset READ horizontalOffset WRITE setHorizontalOffset NOTIFY horizontalOffsetChanged)
    Q_PROPERTY(QUrl imageUrl READ imageUrl)
public:
    explicit TiledImage(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    bool isVisible() const;
    void setVisible(bool visible);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    QColor transparentColor() const;
    void setTransparentColor(QColor transparentColor);

    qreal verticalOffset() const;
    void setVerticalOffset(qreal verticalOffset);

    qreal horizontalOffset() const;
    void setHorizontalOffset(qreal horizontalOffset);

    QUrl imageUrl() const;
    QPointF offset() const;

    void setTmxImageLayer(const TMXImageLayer &tmxImageLayer);
signals:
    void nameChanged();
    void visibleChanged();
    void opacityChanged();
    void transparentColorChanged();
    void verticalOffsetChanged();
    void horizontalOffsetChanged();
private:
    QString m_name;
    bool m_visible;
    qreal m_opacity;
    QColor m_transparentColor;
    qreal m_verticalOffset;
    qreal m_horizontalOffset;
    QUrl m_imageUrl;
    bool m_verticalOffsetValid;
    bool m_horizontalOffsetValid;
};

Q_DECLARE_LOGGING_CATEGORY(tiledImage);

#endif // TILEDIMAGE_H
