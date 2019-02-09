#include "TileLayer.h"
#include "Game.h"
#include "TextureManager.h"

//extern int TS;
//extern int MS;

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) : 
    m_tileSize(tileSize), m_tilesets(tilesets), m_position(0,0), m_velocity(0,0)
{
    //size of our game
    m_numColumns = (TheGame::Instance() -> getGameWidth() / m_tileSize) + 1;
    m_numRows    = (TheGame::Instance() -> getGameHeight() / m_tileSize);
}

void TileLayer::update() 
{
    if(m_position.getX() < ((m_mapWidth * m_tileSize) - 
                    TheGame::Instance()->getGameWidth()) - m_tileSize)
    {
        m_velocity.setX(TheGame::Instance()->getScrollSpeed());
        m_position += m_velocity;
    }
    else
    {
        m_velocity.setX(0);
    }

}
void TileLayer::render() 
{
    int x, y, x2, y2 = 0;

    x = m_position.getX() / m_tileSize;
    y = m_position.getY() / m_tileSize;

    //TS = m_tileSize;

    x2 = int(m_position.getX()) % m_tileSize;
    y2 = int(m_position.getY()) % m_tileSize;

    const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    const unsigned FLIPPED_VERTICALLY_FLAG   = 0x40000000;
    const unsigned FLIPPED_DIAGONALLY_FLAG   = 0x20000000;
    //just loop through size of game, not size of tile,
    //only want to draw things we'll see
    for(int i=0; i< m_numRows; i++)
    {
        for(int j=0; j<m_numColumns; j++)
        {
            //current tile id
            int id = m_tileIDs[i+y][j + x ];
            
            //what if the tile has been flipped?
            bool f_h = (id & FLIPPED_HORIZONTALLY_FLAG);
            bool f_v   = (id & FLIPPED_VERTICALLY_FLAG);
            bool f_d   = (id & FLIPPED_DIAGONALLY_FLAG);
            id &= ~(FLIPPED_HORIZONTALLY_FLAG |
                    FLIPPED_VERTICALLY_FLAG |
                    FLIPPED_DIAGONALLY_FLAG);

            if(id == 0)
            {
                continue;
            }
            //if id aint 0, get correct tileset
            Tileset tileset = getTilesetByID(id);
            //need this so we always draw proper tile
            id--;

            TheTextureManager::Instance() -> drawTile(tileset.name, 
            tileset.margin, tileset.spacing, 
            //where we want to draw tiles at:
            (j * m_tileSize) - x2, (i * m_tileSize) - y2, m_tileSize, m_tileSize, 
            //location of tile on tilesheet:
            (id - (tileset.firstGridID -1)) / tileset.numColumns, 
            (id - (tileset.firstGridID -1)) % tileset.numColumns,
            f_h, f_v, f_d,
            TheGame::Instance() -> getRenderer());  
        }
    }
}

Tileset TileLayer::getTilesetByID( int tileID)
{
    for(int i=0; i<m_tilesets.size(); i++)
    {
        if( i+1 <= m_tilesets.size() -1)
        {
            if(tileID >= m_tilesets[i].firstGridID && tileID < 
                m_tilesets[i + 1].firstGridID)
            {
                return m_tilesets[i];
            }
        }
        else
        {
            return m_tilesets[i];
        }
    }

    std::cout << "did not find tileset, returning empty tileset\n";
    Tileset t;
    return t;
}
