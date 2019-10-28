#include "charactermap.h"

#include <QQuickWindow>
#include <QDebug>
#include <QPainter>
#include <QFont>
#include <QImage>

CharacterMap::CharacterMap()
    : m_mapWidth(32)
    , m_mapHeight(32)
    , m_geometryChanged(false)
{
    setFlag(ItemHasContents, true);

    m_charWidth = 8;
    m_charHeight = 8;

    ch_empty = " ";
    ch_wall = "#";
    ch_avatar = "@";

    m_charList.push_back(ch_empty);
    m_charList.push_back(ch_wall);
    m_charList.push_back(ch_avatar);

    // init map
    for(int y=0; y < m_mapHeight; ++y){
        m_map.push_back(URow(m_mapWidth, ch_empty));
    }

    genFeatures();

//    for(int y=0; y < m_mapHeight; ++y){
//        qInfo() << m_map[y];
//    }

    // generate image list
    //genImageList();
    //connect(this, &QQuickItem::windowChanged, this, &CharacterMap::windowReady);
}

CharacterMap::~CharacterMap()
{
    clearTextureList();
}

void CharacterMap::genFeatures()
{
    // top and bottom walls
    m_map[0] = URow(m_mapWidth, ch_wall);
    m_map[m_mapHeight-1] = URow(m_mapWidth, ch_wall);

    // side walls
    for(int y=1; y < m_mapHeight-1; ++y){
        m_map[y][0] = ch_wall;
        m_map[y][m_mapWidth-1] = ch_wall;
    }
}

void CharacterMap::genImageList()
{
//    for(auto ch: m_charList){
//        m_imageList[ch] = new CharacterNode(this->window(), ch, m_charWidth, m_charHeight, QColor("white"));
//    }
}

class DrawNode : public QSGNode
{
public:
    std::vector<CharacterNode*> chNodes;
    void addNode(CharacterNode* node){
        chNodes.push_back(node);
        appendChildNode(node);
    }
};

QSGNode *CharacterMap::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData)
{
    DrawNode *n= static_cast<DrawNode *>(oldNode);

    QRectF bounds = boundingRect();

    if (bounds.isEmpty()) {
        delete n;
        return nullptr;
    }

    qreal xb = bounds.x();
    qreal yb = bounds.y();
    qreal wb = bounds.width();
    qreal hb = bounds.height();

    bool wider = wb>hb;

    qreal aw = wb/m_mapWidth;
    qreal ah = hb/m_mapHeight;

    wider ? aw = ah : ah = aw;

    qreal xoff = wider ? (wb-hb)/2 : 0;
    qreal yoff = wider ? 0 : (hb-wb)/2;

    qInfo() << aw << ah << xoff << yoff;

    // gen textures
    static bool texturesReady = false;
    if(!texturesReady){
        clearTextureList();

        QColor color("steelblue");
        QRect rect(0,0,aw, ah);
        for(auto ch: m_charList){
            QImage canvas(rect.width(), rect.height(), QImage::Format_RGBA8888);
            canvas.fill(QColor("transparent"));
            QPainter painter(&canvas);

            QFont font = painter.font();
            //font.setPixelSize(48);
            font.setPixelSize(rect.width());
            font.setBold(true);
            painter.setFont(font);
            painter.setPen(color);

            QRect bounding = QRect(0, 0, rect.width(), rect.height());
            painter.drawText(0, 0, rect.width(), rect.height(), Qt::AlignCenter, ch, &bounding);

            QSGTexture *texture = this->window()->createTextureFromImage(canvas);
            m_textureList[ch] = texture;
        }

        //texturesReady = true;
    }

    //qInfo() << bounds;

    qInfo().noquote() << "updatePaintNode" << aw << ah;
    qInfo() << m_mapHeight << m_mapWidth;

    if(m_geometryChanged){
        delete n;
        n = nullptr;
    }

    if(!n){
        n = new DrawNode;
        for(int y=0; y < m_mapHeight; ++y){
            for(int x=0; x < m_mapWidth; ++x){
                QString ch = m_map[y][x];
                QRect trect(xoff+x*aw, yoff+y*ah, aw, ah);
                CharacterNode* tnode = new CharacterNode(m_textureList[ch], trect);
                //n->chNodes.push_back(tnode);
                //n->appendChildNode(tnode);
                n->addNode(tnode);
            }
        }
    }

    if(m_geometryChanged && false){
        qInfo() << "geo changed" << n->chNodes.size();
        for(auto tnode: n->chNodes){
            //tnode->markDirty(QSGNode::DirtyGeometry);
            //tnode->markDirty(QSGNode::DirtyMaterial);
            //tnode->setRect()
        }
    }

    m_geometryChanged = false;

    return n;
}

void CharacterMap::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    m_geometryChanged = true;
    update();
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

void CharacterMap::clearTextureList()
{
    for(auto ch: m_charList){
        delete m_textureList[ch];
    }
    m_textureList.clear();
}

void CharacterMap::windowReady()
{
    if(this->window()){
        //connect(this->window(), &QQuickWindow::sceneGraphInitialized, this, &CharacterMap::sceneGraphReady);
    }
}

void CharacterMap::sceneGraphReady()
{
    //genImageList();
}
