#ifndef CHARACTERNODE_H
#define CHARACTERNODE_H

#include <QSGTexture>
#include <QSGSimpleTextureNode>

class CharacterNode : public QSGSimpleTextureNode
{

    using UChar = QString;
public:
    CharacterNode(QSGTexture* texture, QRect rect);

private:

};

#endif // CHARACTERNODE_H
