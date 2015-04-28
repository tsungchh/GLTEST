/*

    Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include "texture.h"
#include "MYMACRO.h"

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
    m_textureTarget = TextureTarget;
    m_fileName      = FileName;
    // m_textureObj = 0;
}


bool Texture::Load()
{

    if(!img.load(m_fileName.c_str())) {
        printf("Texture path %s ERROR!\n", m_fileName.c_str());
        return false;
    }
    QImage glimg = QGLWidget::convertToGLFormat(img);
    DEBUG_GL();
    glGenTextures(1, &m_textureObj);
    DEBUG_GL();
    glBindTexture(m_textureTarget, m_textureObj);
    DEBUG_GL();
    glTexImage2D(m_textureTarget, 0, GL_RGBA, glimg.size().width(), glimg.size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, glimg.bits());
    DEBUG_GL();
    // `設定顯示貼圖被縮小時使用線性內插 `
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // `設定顯示貼圖被放大時使用線性外插 `
    glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // GL_TEXTURE_WRAP_S `設定水平方向解讀模式`
    glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // GL_TEXTURE_WRAP_T `設定垂直方向解讀模式`
    glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(m_textureTarget, 0);

    DEBUG_GL();
    return true;
}

void Texture::Bind(GLenum TextureUnit)
{
    DEBUG_GL();
    glActiveTexture(TextureUnit);
    DEBUG_GL();
    glBindTexture(m_textureTarget, m_textureObj);
    DEBUG_GL();
}
