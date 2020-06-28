#include "Arena.h"
#include <iostream>
#include <ngl/Image.h>
#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include "RenderGlobals.h"

#include "Player.h"
#include "Fruit.h"
#include "BadFruit.h"



const static char* Player1 = "Player1";
const static char* Wall = "Wall";
const static char* Empty = "Empty";
const static char* Fruit1 = "Fruit1";
const static char* BadFruit1 = "BadFruit1";



Arena::Arena(unsigned int _w, unsigned int _h)
{
    m_width = _w;
    m_height = _h;
    m_items.resize(m_width * m_height);
    createDefaultObjects();
}



//code allowing to read a map and build the arena from it 
Arena::Arena(const std::string& _filename)
{

    ngl::Image img(_filename);
    m_width = img.width();
    m_height = img.height();
    m_items.resize(m_width * m_height);
    createDefaultObjects();
    for (unsigned int y = 0; y < m_height; ++y)
    {
        for (unsigned int x = 0; x < m_width; ++x)
        {
            if (img.getColour(x, y) == ngl::Vec4::zero())
            {
                setItem(x, y, ItemType::Wall, m_objects[Wall]);
            }
            else
            {
                setItem(x, y, ItemType::Empty, m_objects[Empty]);
            }
        }
    }

    ngl::VAOPrimitives::instance()->createTrianglePlane("floor", m_width, m_height, 1.0f, 1.0f, ngl::Vec3::up());

}





void Arena::createDefaultObjects()
{
    //Creating the objects in the arena
    int num_elements;

    m_objects[Wall] = new GameObject();
    m_objects[Empty] = new GameObject();
    m_objects[Fruit1] = new Fruit(Vec2(10, 10), m_width, m_height);
    m_objects[BadFruit1] = new BadFruit(Vec2(5, 10), m_width, m_height);
    m_objects[Player1] = new Player(Vec2(2, 2), m_width, m_height);

}

void Arena::keyEvent(int _x, int _y)
{
    std::cout << _x << ' ' << _y << '\n';
    m_objects[Player1]->moveEvent(Vec2(_x, _y));
}




void Arena::draw() const
{
    auto shader = ngl::ShaderLib::instance();
    shader->use(ngl::nglDiffuseShader);
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif
    shader->setUniform("Colour", 0.2f, 0.2f, 0.7f, 1.0f);  
    size_t index = 0;
    for (size_t y = 0; y < m_height; ++y)
    {
        for (size_t x = 0; x < m_width; ++x)
        {
            switch (m_items[index++].type)
            {
            case ItemType::Empty: std::cout << ' '; break;
            case ItemType::Player: std::cout << 'P'; break;
            case ItemType::Fruit: std::cout << 'F'; break;
            case ItemType::BadFruit: std::cout << 'B'; break;
            case ItemType::Wall: std::cout << 'W'; drawWall(x, y);  break;
            }
        }
        std::cout << '\n';
    }

    for (auto& o : m_objects)
    {
        o.second->draw();
    }
    shader->use(ngl::nglCheckerShader);
    ngl::Transformation tx;
    tx.setPosition(0.0f, -0.6f, 0.0f);
    shader->setUniform("MVP", RenderGlobals::getVPMatrix() * tx.getMatrix());
    ngl::VAOPrimitives::instance()->draw("floor");
}



void Arena::update(float _dt)
{

        std::cout << "update \n";
        std::cout << "points: " << points ;




        for (auto& o : m_objects)
        {
            o.second->update(_dt);

        }


        //pointers to player and fruit, bad fruit data
        Player* p = static_cast<Player*>(m_objects[Player1]);
        Fruit* pf = static_cast<Fruit*>(m_objects[Fruit1]);
        BadFruit* pbf = static_cast<BadFruit*>(m_objects[BadFruit1]);


        //Fruit positions
        auto posf = pf->getPos();
        Vec2 newPosf = posf;


        //Bad fruit positions
        auto posbf = pbf->getPos();
        Vec2 newPosbf = posbf;


        //Player position and direction
        auto pos = p->getPos();
        auto dir = p->getDir();
        Vec2 newPos = pos;





        auto getItem = [=](unsigned int _x, unsigned int _y)
        {
            size_t index = _y * m_width + _x;
            return m_items[index].type;
        };




        //rotate the troll according to the direction

        if (dir.x != 0 && dir.x < 2)
        {
            p->angle = 90;
        }


        if (dir.x != 0 && dir.x > 2)
        {
            p->angle = -90;
        }


        if (dir.y != 0 && dir.y > 2)
        {
            p->angle = 180;
        }


        if (dir.y != 0 && dir.y < 2)
        {
            p->angle = 0;
        }
        

        
        //detect player with wall collision 
        
        if (dir.x != 0 && getItem(pos.x + dir.x, pos.y + dir.y) == ItemType::Empty)
        {
            newPos.x = pos.x + dir.x;
        }

        if (dir.y != 0 && getItem(pos.x + dir.x, pos.y + dir.y) == ItemType::Empty)
        {
            newPos.y = pos.y + dir.y;
        }
        
        p->setPos(newPos);
        setItem(pos.x, pos.y, ItemType::Empty, m_objects[Empty]);
        setItem(newPos.x, newPos.y, ItemType::Player, m_objects[Player1]);


        count++; //counting



        


        //Place the fruit in a random position when the player touches it
        if (pos.x == posf.x && pos.y == posf.y)
        {
            points++;
           // std::cout << points;

           
            newPosf.x = rand() % (m_height - 1);
            newPosf.y = rand() % (m_width - 1);



            while (getItem(newPosf.x , newPosf.y ) == ItemType::Wall)
            {
                newPosf.x = rand() % (m_height - 1);

                newPosf.y = rand() % (m_width - 1);
            }



            pf->setPos(newPosf);

            setItem(posf.x, posf.y, ItemType::Empty, m_objects[Empty]);


        }


        //Bad fruit changes position if update count can be divided by 4
        if (count % 4 == 0)
        {
            newPosbf.x = rand() % (m_height - 1);
            newPosbf.y = rand() % (m_width - 1);

            while (getItem(newPosbf.x, newPosbf.y) == ItemType::Wall)
            {
                newPosbf.x = rand() % (m_height - 1);

                newPosbf.y = rand() % (m_width - 1);
            }



            pbf->setPos(newPosbf);

            setItem(posbf.x, posbf.y, ItemType::Empty, m_objects[Empty]);



        }

        //if the player touches the bad fruit game is over
        if (pos.x == posbf.x && pos.y == posbf.y)
        {

            std::cout << "\n GAME OVER ";
            exit(3);



        }



}




void Arena::setItem(unsigned int _x, unsigned int _y, ItemType _type, GameObject* _obj)
{
    size_t index = _y * m_width + _x;
    m_items[index].type = _type;
    m_items[index].obj = _obj;
}


void Arena::drawWall(unsigned int _x, unsigned int _y) const
{


    float halfZ = -(m_height / 2.0f);
    float halfX = -(m_width / 2.0f);
    ngl::Transformation tx;
    tx.setPosition(halfX + _x, 0.0f, halfZ + _y);
    auto shader = ngl::ShaderLib::instance();
    shader->setUniform("MVP", RenderGlobals::getVPMatrix() * tx.getMatrix());
    ngl::VAOPrimitives::instance()->draw(ngl::cube);

}