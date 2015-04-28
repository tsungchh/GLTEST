#include "solarsystem.h"
#include <QtMath>

solarsystem::solarsystem()
{
    geom = new Geometry();
    sun = new Patch(geom);
    // create sun
    float yellow[]={1.0f, 1.0f, 0.0f, 1.0f};
    CreateSphere(2.0f, sun, geom, yellow);


    earth = new Patch(geom);
    // create earth
    float red[]={1.0f, 0.0f, 0.0f, 1.0f};
    CreateSphere(2.0f, earth, geom, red);


    geom->loadArrays();

}

void solarsystem::draw() {
    // matrix for sun

    sun->draw();
    glPushMatrix();
    glPopMatrix();
    earth->rotate(60,QVector3D(0.0f,1.0f,0.0f));
    earth->translate(QVector3D(5.0f,0.0f,0.0f));
    earth->draw();


}


bool solarsystem::CreateSphere(float radius, // 半徑
                  Patch* patch,
                  Geometry* geom,
                  float *color, // 球的顏色
                  int stacks, // 緯度的切面數目
                  int slices // 徑度的切面數目
                  )
{
    //*ppVertices = NULL;

    int num_vertices = (stacks+1)*(slices+1);
    int num_triangles = stacks*slices*2;

    g_iNumSphereVertices = num_vertices;
    g_iNumSphereTriangles = num_triangles;
    g_iNumSphereIndices = num_triangles * 3;
    patch->count = g_iNumSphereIndices;
    geom->colors = new Color[num_vertices];

    float default_color[] = {1.0f, 1.0f, 1.0f, 1.0f};
    if ( color==NULL )
        color = default_color;

    const float theta_start_degree = 0.0f;
    const float theta_end_degree = 360.0f;
    const float phi_start_degree = -90.0f;
    const float phi_end_degree = 90.0f;

    float ts = qDegreesToRadians(theta_start_degree);
    float te = qDegreesToRadians(theta_end_degree);
    float ps = qDegreesToRadians(phi_start_degree);
    float pe = qDegreesToRadians(phi_end_degree);

    float theta_total = te - ts;
    float phi_total = pe - ps;
    float theta_inc = theta_total/stacks;
    float phi_inc = phi_total/slices;

    int i,j;
    int index = 0;
    qreal theta = ts;

    float sin_theta, cos_theta;
    float sin_phi, cos_phi;

    float r = color[0];
    float g = color[1];
    float b = color[2];
    float a = color[3];



    for ( i=0; i<=stacks; i++ )
    {
        qreal phi = ps;
        sin_theta = qSin(theta);
        cos_theta = qCos(theta);

        for ( j=0; j<=slices; j++, index++ )
        {
            sin_phi = qSin(phi);
            cos_phi = qCos(phi);
            // vertex
            QVector3D point;
            point[0] = radius * cos_phi * cos_theta;
            point[1] = radius * sin_phi;
            point[2] = radius * cos_phi * sin_theta;
            geom->vertices.append(point);
            // Color
            float shading = (float) j / (float) slices;
            //float shading = 1.0f;
            /*
            QVector4D color;
            color[0] = 255 * r * shading;
            color[1] = 255 * g * shading;
            color[2] = 255 * b * shading;
            color[3] = 255 * a * shading;
            geom->colors.append(color);
            */
            geom->colors[index].m_RGBA[0] = 255 * r * shading;
            geom->colors[index].m_RGBA[1] = 255 * g * shading;
            geom->colors[index].m_RGBA[2] = 255 * b * shading;
            geom->colors[index].m_RGBA[3] = 255 * a * shading;
            // inc phi
            phi += phi_inc;
        }
        // inc theta
        theta += theta_inc;
    }

    int base = 0;
    index = 0;

    if ( geom )
    {


        // triangle list
        for ( i=0; i<stacks; i++ )
        {
            for ( j=0; j<slices; j++ )
            {
                geom->faces.append(base);
                geom->faces.append(base+1);
                geom->faces.append(base+slices+1);

                geom->faces.append(base+1);
                geom->faces.append(base+slices+2);
                geom->faces.append(base+slices+1);

                base++;
            }
            base++;
        }
    }

    return true;
}
