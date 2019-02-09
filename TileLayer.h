#ifndef __TileLayer__
#define __TileLayer__

#include <iostream>
#include <vector>
#include "Layer.h"
#include "Level.h"
#include "vector2d.h"

class TileLayer : public Layer
{
    public:
        TileLayer(int tileSize, const std::vector<Tileset> &tilesets);
        virtual ~TileLayer() {}
        virtual void update();
        virtual void render();

        void setTileIDs(const std::vector<std::vector<int> >& data)
        {
           m_tileIDs = data;
        }
        void setTileSize(int tileSize)
        {
            m_tileSize = tileSize;
        }
        Tileset getTilesetByID(int tileID);

        void setMapWidth(int mapWidth) { m_mapWidth = mapWidth; }
        int getTileSize() { return m_tileSize; }
        const Vector2D getPosition() { return m_position; }
        const std::vector<std::vector<int> >& getTileIDs() { return m_tileIDs; }

        //const std::vector<std::vector<int> >& getTileIDs() { return m_tileIDs; }
        //const Vector2D getPosition() { return m_position; }
        //void setPosition(Vector2D position) { m_position = position;}

    private:
        int m_numColumns;
        int m_numRows;
        int m_tileSize;
        int m_mapWidth;

        Vector2D m_position;
        Vector2D m_velocity;

        const std::vector<Tileset> &m_tilesets;
        std::vector<std::vector<int> > m_tileIDs;
};  
        
#endif

