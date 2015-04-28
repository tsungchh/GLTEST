#ifndef RENDERTECHNIQUE_H
#define RENDERTECHNIQUE_H
#include "technique.h"

struct BaseLight
{
    QVector3D Color;
    float AmbientIntensity;
    float DiffuseIntensity;

    BaseLight()
    {
        Color = QVector3D(0.0f, 0.0f, 0.0f);
        AmbientIntensity = 0.0f;
        DiffuseIntensity = 0.0f;
    }
};

struct DirectionalLight : public BaseLight
{
    QVector3D Direction;

    DirectionalLight()
    {
        Direction = QVector3D(0.0f, 0.0f, 0.0f);
    }
};

struct PointLight : public BaseLight
{
    QVector3D Position;

    struct
    {
        float Constant;
        float Linear;
        float Exp;
    } Attenuation;

    PointLight()
    {
        Position = QVector3D(0.0f, 0.0f, 0.0f);
        Attenuation.Constant = 1.0f;
        Attenuation.Linear = 0.0f;
        Attenuation.Exp = 0.0f;
    }
};

struct SpotLight : public PointLight
{
    QVector3D Direction;
    float Cutoff;

    SpotLight()
    {
        Direction = QVector3D(0.0f, 0.0f, 0.0f);
        Cutoff = 0.0f;
    }
};

class rendertechnique : public technique {
public:

    //static const unsigned int MAX_POINT_LIGHTS = 2;
    //static const unsigned int MAX_SPOT_LIGHTS = 2;

    rendertechnique();
    ~rendertechnique();
    virtual bool init(QObject* parentr);

    void SetWVP(const QMatrix4x4& WVP);
    void SetWorldMatrix(const QMatrix4x4& WVP);
    void SetDirectionalLight(const DirectionalLight& Light);
    /*void SetPointLights(unsigned int NumLights, const PointLight* pLights);
    void SetSpotLights(unsigned int NumLights, const SpotLight* pLights);
    */
    void SetEyeWorldPos(const QVector3D& EyeWorldPos);
    void SetMatSpecularPower(float Power);
    void SetMatSpecularIntensity(float Intensity);    
    void SetTextureUnit(unsigned int textureunit);
private:

    GLuint m_WorldMatrixLocation;
    GLuint m_WVPLocation;
    GLuint m_samplerLocation;
    GLuint m_eyeWorldPosLocation;
    GLuint m_matSpecularIntensityLocation;
    GLuint m_matSpecularPowerLocation;
    //GLuint m_numPointLightsLocation;
    //GLuint m_numSpotLightsLocation;

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Direction;
    } m_dirLightLocation;
    /*
    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        struct {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } m_pointLightsLocation[MAX_POINT_LIGHTS];

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        GLuint Direction;
        GLuint Cutoff;
        struct {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } m_spotLightsLocation[MAX_SPOT_LIGHTS];
    */
};


#endif // RENDERTECHNIQUE_H
