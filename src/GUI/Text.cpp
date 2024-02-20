#include "Text.hpp"

Text::Text() : m_font(nullptr)
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindVertexArray(0);
}

Text::~Text()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

void Text::setFont(Font *font)
{
    m_font = font;
}

void Text::render(const std::string &text, float x, float y, float scale)
{
    m_font->getShader()->bind();
    glBindTexture(GL_TEXTURE_2D, m_font->getTexture());
    glBindVertexArray(m_vao);

    struct point {
        GLfloat x;
        GLfloat y;
        GLfloat s;
        GLfloat t;
    } coords[6 * text.length()];

    int n = 0;

    for(size_t i = 0; i < text.length(); i++) 
    {
        Character c = (*m_font)[text[i]];
        float x2 =  x + c.bl * scale;
        float y2 = -y - c.bt * scale;
        float w = c.bw * scale;
        float h = c.bh * scale;

        /* Advance the cursor to the start of the next character */
        x += c.ax * scale;
        y += c.ay * scale;

        /* Skip glyphs that have no pixels */
        if(!w || !h)
            continue;

        coords[n++] = (point){x2,     -y2    , c.tx,                                            0};
        coords[n++] = (point){x2 + w, -y2    , c.tx + c.bw / m_font->getAtlasWidth(),   0};
        coords[n++] = (point){x2,     -y2 - h, c.tx,                                          c.bh / m_font->getAtlasWidth()}; //remember: each glyph occupies a different amount of vertical space
        coords[n++] = (point){x2 + w, -y2    , c.tx + c.bw / m_font->getAtlasWidth(),   0};
        coords[n++] = (point){x2,     -y2 - h, c.tx,                                          c.bh / m_font->getAtlasWidth()};
        coords[n++] = (point){x2 + w, -y2 - h, c.tx + c.bw / m_font->getAtlasWidth(),                 c.bh / m_font->getAtlasWidth()};
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, n);
}
