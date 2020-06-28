#include "Fruit.h"
#include <iostream>
#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include "RenderGlobals.h"



Fruit::Fruit(const Vec2& _pf, unsigned int _w, unsigned int _h) : GameObject()
{
	m_posf = _pf;
	m_width = _w;
	m_height = _h;
}



void Fruit::update(float _dt)
{


}



void Fruit::draw() const
{
	float halfZ = -(m_height / 2.0f);
	float halfX = -(m_width / 2.0f);
	ngl::Transformation tx;
	tx.setPosition(halfX + m_posf.x, 0.0f, halfZ + m_posf.y);
	tx.setScale(0.5, 0.5, 0.5);		//scaling down the fruit
	auto shader = ngl::ShaderLib::instance();
	shader->setUniform("MVP", RenderGlobals::getVPMatrix() * tx.getMatrix());
	shader->setUniform("Colour", 0.9f, 1.0f, 0.0f, 1.0f);

	ngl::VAOPrimitives::instance()->draw(ngl::football);
}







