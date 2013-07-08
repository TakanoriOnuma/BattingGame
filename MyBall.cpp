#include "MyBall.h"

MyBall::MyBall(double radius, int sides)
	: MySphere(radius, sides), state(State::HANDED), message(NULL)
{
}

MyBall::MyBall(double x, double y, double z, double radius, int sides)
	: MySphere(x, y, z, radius, sides), state(State::HANDED), message(NULL)
{
}

void MyBall::update()
{
	// ’N‚©‚É‚½‚ê‚Ä‚¢‚éó‘Ô‚Å‚È‚¯‚ê‚Î
	if(state != State::HANDED){
		move(vec);			// ©•ª‚ÌÀ•W‚ğˆÚ“®‚·‚é
	}
}