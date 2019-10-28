#include "characternode.h"

CharacterNode::CharacterNode(QSGTexture* texture, QRect rect)
    : QSGSimpleTextureNode()
{
    setRect(rect);
    setSourceRect(0,0,rect.width(),rect.height());

    setRect(rect);
    setTexture(texture);
}
