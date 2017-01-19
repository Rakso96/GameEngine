#include "../include/texture.h"
#include "../include/stb_image.h"
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data =stbi_load(fileName.c_str() , &width , &height , &numComponents , 4);

    if(data == NULL)
		std::cerr << "Unable to load texture: " << fileName << std::endl;

    glGenTextures(1, &m_texture);

    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);


    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_MAX_ANISOTROPY_EXT , 8.0f);
    stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);

}
