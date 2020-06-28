#ifndef FRUIT_H_
#define FRUIT_H_


#include "GameObject.h"

class Fruit : public GameObject
{
public:
	Fruit(const Vec2& _pf, unsigned int _w, unsigned int _h);
	virtual void update(float _dt) override;
	virtual void draw() const override;
	Vec2 getPos() const { return m_posf; }
	void setPos(const Vec2& _pf) { m_posf = _pf; }

private:
	Vec2 m_posf;

	unsigned int m_width;
	unsigned int m_height;

};


#endif