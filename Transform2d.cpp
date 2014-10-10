#pragma once
#include "Transform2d.h"
#include "Support2d.h"

void Transform2d::translate(Point2d *pct, float tx, float ty){
	pct->x=tx+pct->x;
	pct->y=ty+pct->y;
}

void Transform2d::rotate(Point2d *pct, float angleInRadians){
	float a=pct->x;
	float b=pct->y;
	
	//x’ = x*cos(u) – y*sin(u) y’ = x*sin(u) + y*cos(u)
	pct->x=a*cos(angleInRadians)-b*sin(angleInRadians);
	pct->y=a*sin(angleInRadians)+b*cos(angleInRadians);
}

void Transform2d::rotateRelativeToAnotherPoint(Point2d *pct, Point2d *ref, float angleInRadians){
	translate(pct,-ref->x,-ref->y);
	rotate(pct,angleInRadians);
	translate(pct,ref->x,ref->y);
}
void Transform2d::scale(Point2d *pct, float sx, float sy){
	//x’ = x* factorx; y’ = y* factory;
	pct->x=pct->x*sx;
	pct->y=pct->y*sy;
}

void Transform2d::scaleRelativeToAnotherPoint(Point2d *pct, Point2d *ref, float sx, float sy){
	translate(pct,-ref->x,-ref->y);
	scale(pct,sx,sy);
	translate(pct,ref->x,ref->y);
}
