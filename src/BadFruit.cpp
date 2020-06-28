#include "BadFruit.h"
#include <iostream>
#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include "RenderGlobals.h"



BadFruit::BadFruit(const Vec2& _pbf, unsigned int _w, unsigned int _h) : GameObject()
{
	m_posbf = _pbf;
	m_width = _w;
	m_height = _h;
}



void BadFruit::update(float _dt)
{


}



void BadFruit::draw() const
{
	float halfZ = -(m_height / 2.0f);
	float halfX = -(m_width / 2.0f);
	ngl::Transformation tx;
	tx.setPosition(halfX + m_posbf.x, 0.0f, halfZ + m_posbf.y);
	tx.setRotation(0.0f, 180.0f, 0.0f);
	tx.setScale(1.5, 1.0, 2.0);		//scaling down the fruit
	auto shader = ngl::ShaderLib::instance();
	shader->setUniform("MVP", RenderGlobals::getVPMatrix() * tx.getMatrix());
	shader->setUniform("Colour", 1.0f, 0.0f, 0.2f, 1.0f);

	ngl::VAOPrimitives::instance()->draw(ngl::troll);
}







