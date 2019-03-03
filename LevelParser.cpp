#include <string>
#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"
#include "GameObjectFactory.h"
#include "Level.h"
#include "base64.h"
#include "zlib.h"


Level* LevelParser::parseLevel(const char *levelFile)
{
    //create a tinyxml and load the map xml
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    //create level object
    Level* pLevel = new Level();

    //get root
    TiXmlElement* pRoot = levelDocument.RootElement();

    pRoot -> Attribute("tilewidth", &m_tileSize);
    pRoot -> Attribute("width", &m_width);
    pRoot -> Attribute("height", &m_height);

    TiXmlElement* pProperties = pRoot->FirstChildElement();

    //parse tilesets
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e =
    e -> NextSiblingElement())
    {
        if(e -> Value() == std::string("tileset"))
        {
            parseTilesets(e, pLevel -> getTilesets());
        }
    }

    //parse textures
    for(TiXmlElement* e = pProperties -> FirstChildElement(); e != NULL;
    e = e -> NextSiblingElement())
    {
        if(e -> Value() == std::string("property"))
        {
            parseTextures(e);
        }
    }
    //parse layers
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e =
    e -> NextSiblingElement())
    {   
        //std::cout<< e << "\n";
        if(e -> Value() == std::string("objectgroup") ||
            e -> Value() == std::string("layer"))
        {
            if(e -> FirstChildElement() -> Value() == std::string("object"))
            {
                std::cout << "parsing object" << "\n";
                parseObjectLayer(e, pLevel->getLayers(), pLevel);
            }
            else if(e -> FirstChildElement() ->  Value() == std::string("data") ||
                   (e -> FirstChildElement() -> NextSiblingElement() != 0  &&
                    e -> FirstChildElement() -> NextSiblingElement() -> Value()
                                    == std::string("data")))
            {
                std::cout << "parsing data" << "\n";
                parseTileLayer(e, pLevel -> getLayers(), pLevel -> getTilesets(), 
                                pLevel -> getCollisionLayers(), 
                                pLevel -> getCollisionSafeLayers());
            } 
        }
    }
   // pLevel->getPlayer()->setCollisionLayers(pLevel->getCollisionLayers())
    return pLevel;
}

void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
    std::cout << "adding texture " << pTextureRoot->Attribute("value") << 
        " with ID " << pTextureRoot->Attribute("name") << std::endl;

    TheTextureManager::Instance() -> load(pTextureRoot ->
        Attribute("value"), pTextureRoot-> Attribute("name"),
        TheGame::Instance() -> getRenderer());
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot,
    std::vector<Tileset>* pTilesets)
{
    std::string assetsTag = "assets/";
    //add tileset to texture manager
    std::cout << "adding texture " << pTilesetRoot->FirstChildElement()->
        Attribute("source") << " with ID " <<
        pTilesetRoot->Attribute("name") << std::endl;

    TheTextureManager::Instance() -> load(assetsTag.append(pTilesetRoot ->
    FirstChildElement()-> Attribute("source")), pTilesetRoot ->
    Attribute("name"), TheGame::Instance() -> getRenderer());

    //create tileset object
    Tileset tileset;
    pTilesetRoot -> FirstChildElement() -> Attribute("width", 
        &tileset.width);
    pTilesetRoot -> FirstChildElement() -> Attribute("height", 
        &tileset.height);
    pTilesetRoot -> Attribute("firstgid", &tileset.firstGridID);
    pTilesetRoot -> Attribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot -> Attribute("tileheight", &tileset.tileHeight);
    pTilesetRoot -> Attribute("spacing", &tileset.spacing);
    pTilesetRoot -> Attribute("margin", &tileset.margin);
    tileset.name = pTilesetRoot -> Attribute("name");
    
    pTilesetRoot -> Attribute("columns", &tileset.numColumns);
    pTilesets -> push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement,
    std::vector<Layer*> *pLayers,
    const std::vector<Tileset>* pTilesets,
    std::vector<TileLayer*> *pCollisionLayers,
    std::vector<TileLayer*> *pCollisionSafeLayers)
{
    TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

    bool collidable = false;
    bool collidableSafe = false;

    //places to store things:
    std::vector<std::vector<int> > data;

    std::string decodedIDs;
    TiXmlElement* pDataNode;

    //search for node:
    for(TiXmlElement* e = pTileElement -> FirstChildElement(); e != NULL; 
    e = e -> NextSiblingElement())
    {
        if(e -> Value() == std::string("properties"))
        {
            for(TiXmlElement* property = e -> FirstChildElement();
                property != NULL;
                property = property -> NextSiblingElement())
            {
                if(property -> Value() == std::string("property"))
                {
                    if(property -> Attribute("name") ==
                                    std::string("collidable"))
                    {
                        collidable = true;
                        std::cout << "hot dog this layer be collidable" << "\n";
                    }

                    if(property -> Attribute("name") ==
                                    std::string("collidableSafe"))
                    {
                        collidableSafe = true;
                        std::cout << "cant go through this" << "\n";
                    }
                }
            }
        }
        if(e -> Value() == std::string("data"))
        {
            pDataNode = e;
        }
    }

    //get text from node and use base64 to decode it:
    for(TiXmlNode* e = pDataNode -> FirstChild(); e!=NULL; 
    e = e -> NextSibling())
    {
        TiXmlText* text = e -> ToText();
        std::string t = text -> Value();
        decodedIDs = base64_decode(t);
    }
    //what we have now is a base64 decoded string
    //uncompress this with zlib 
    uLongf numGids = m_width * m_height * sizeof(int);

    std::vector<unsigned> gids(numGids);

    uncompress((Bytef*)&gids[0], &numGids, 
        (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

    //fill vector with tile ids
    std::vector<int> layerRow(m_width);

    for(int j=0; j<m_height; j++)
    {
        data.push_back(layerRow);
    }

    //fill data with correct values
    for(int rows = 0; rows<m_height ; rows++)
    {
        for(int cols = 0; cols<m_width; cols++)
        {
            data[rows][cols] = gids[rows * m_width + cols];
            //std::cout << data[rows][cols] << "\n";
        }
    }

    pTileLayer -> setTileIDs(data);
    pTileLayer->setMapWidth(m_width);
    if(collidable)
    {
        pCollisionLayers->push_back(pTileLayer);
    }
    if(collidableSafe)
    {
        pCollisionSafeLayers->push_back(pTileLayer);
    }
    pLayers -> push_back(pTileLayer);
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement,
    std::vector<Layer*> *pLayers, Level* pLevel)
{
    //create object layer
    ObjectLayer* pObjectLayer = new ObjectLayer();
    std::cout << pObjectElement -> FirstChildElement() -> Value() << "\n";

    for(TiXmlElement* e = pObjectElement -> FirstChildElement();
        e != NULL; e = e -> NextSiblingElement())
    {
        std::cout << e -> Value() << "\n";
        if(e -> Value() == std::string("object"))
        {
            int x, y, width, height, numFrames, callbackID, animSpeed;
            std::string textureID;
            std::string type;

            e -> Attribute("x", &x);
            e -> Attribute("y", &y);
            
            type = e->Attribute("type");
            GameObject* pGameObject = TheGameObjectFactory::Instance()->create(type);
            //get property values
            for(TiXmlElement* properties = e -> FirstChildElement();
                properties != NULL;
                properties = properties -> NextSiblingElement())
            {
                if(properties -> Value() == std::string("properties"))
                {
                    for(TiXmlElement* property = properties -> FirstChildElement();
                        property != NULL;
                        property = property -> NextSiblingElement())
                    {
                        if(property -> Value() == std::string("property"))
                        {
                            if(property->Attribute("name") == std::string("numFrames"))
                            {
                                property->Attribute("value", &numFrames);
                            }
                            else if(property->Attribute("name") == std::string("textureHeight"))
                            {
                                property->Attribute("value", &height);
                            }
                            else if(property->Attribute("name") == std::string("textureID"))
                            {
                                textureID = property->Attribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureWidth"))
                            {
                                property->Attribute("value", &width);
                            }
                            else if(property->Attribute("name") == std::string("callbackID"))
                            {
                                property->Attribute("value", &callbackID);
                            }
                            else if(e->Attribute("name") == std::string("animSpeed"))
                            {
                                property->Attribute("value", &animSpeed);
                            }
                        }
                    }
                }
            }
            //x = x%32;
            //std::cout << x << "\n";
            //y = y%32;
            pGameObject -> load(std::unique_ptr<LoaderParams>(new
                LoaderParams(x, y, width, height, textureID, numFrames,
                    callbackID, animSpeed)));

            pGameObject->setCollisionLayers(pLevel->getCollisionLayers());
            pGameObject->setCollisionSafeLayers(pLevel->getCollisionSafeLayers());

            if(type == "Player")
            {
                pLevel -> setPlayer(dynamic_cast<Player*>(pGameObject));
            }

            pObjectLayer -> getGameObjects() -> push_back(pGameObject);
        }
    }
    pLayers -> push_back(pObjectLayer);
}

