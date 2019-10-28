#ifndef CHARACTERMAP_H
#define CHARACTERMAP_H

// provides map for displaying characters as tiles

#include <QQuickItem>

#include <string>

#include <characternode.h>

class CharacterMap : public QQuickItem
{
    Q_OBJECT

    using UChar = QString;
    using URow = std::vector<UChar>;
    using UMap = std::vector<URow>;

    UChar ch_empty;
    UChar ch_wall;
    UChar ch_avatar;

    //Q_PROPERTY(unsigned mapWidth READ getMapWidth WRITE setMapWidth NOTIFY mapWidthChanged)
    //Q_PROPERTY(unsigned mapHeight READ getMapHeight WRITE setMapHeight NOTIFY mapHeightChanged)
public:
    CharacterMap();
    ~CharacterMap();

    unsigned getMapWidth() const
    {
        return m_mapWidth;
    }
    unsigned getMapHeight() const
    {
        return m_mapHeight;
    }

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData);
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    void clearTextureList();

signals:

    void mapSizeChanged();
    void mapWidthChanged(unsigned mapWidth);
    void mapHeightChanged(unsigned mapHeight);

public slots:
    void windowReady();
    void sceneGraphReady();

//    void setMapWidth(unsigned mapWidth)
//    {
//        if (m_mapWidth == mapWidth)
//            return;

//        m_mapWidth = mapWidth;

//        emit mapWidthChanged(mapWidth);
//        emit mapSizeChanged();
//    }
//    void setMapHeight(unsigned mapHeight)
//    {
//        if (m_mapHeight == mapHeight)
//            return;

//        m_mapHeight = mapHeight;

//        emit mapHeightChanged(mapHeight);
//        emit mapSizeChanged();
//    }

private:
    void genFeatures();
    void genImageList();

    UMap m_map;
    unsigned m_mapWidth;
    unsigned m_mapHeight;

    qreal m_charWidth;
    qreal m_charHeight;

    std::map<UChar,QSGTexture*> m_textureList;
    std::vector<UChar> m_charList;

    bool m_geometryChanged;
};

#endif // CHARACTERMAP_H
