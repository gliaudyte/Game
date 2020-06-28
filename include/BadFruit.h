#ifndef BADFRUIT_H_
#define BADFRUIT_H_


#include "GameObject.h"

class BadFruit : public GameObject
{
public:
	BadFruit(const Vec2& _pbf, unsigned int _w, unsigned int _h);
	virtual void update(float _dt) override;
	virtual void draw() const override;
	Vec2 getPos() const { return m_posbf; }
	void setPos(const Vec2& _pbf) { m_posbf = _pbf; }

private:
	Vec2 m_posbf;

	unsigned int m_width;
	unsigned int m_height;

};


#endif