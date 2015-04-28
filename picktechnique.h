#ifndef PICKTECHNIQUE_H
#define PICKTECHNIQUE_H
#include "technique.h"

class pickTechnique : public technique
{
public:
    pickTechnique();
    ~pickTechnique();
    virtual bool init(QObject* parent);

    void SetWVP(const QMatrix4x4 WVP);

    void SetObjectIndex(uint ObjectIndex);

    void DrawStartCB(uint DrawIndex);

private:
    GLuint m_WVPLocation;
    GLuint m_drawIndexLocation;
    GLuint m_objectIndexLocation;
};

#endif // PICKTECHNIQUE_H
