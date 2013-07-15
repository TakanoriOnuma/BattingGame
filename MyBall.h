#ifndef ___Class_MyBall
#define ___Class_MyBall

#include "MySphere.h"
#include "IAnimation.h"
#include "MyVector.h"
#include "EmitionMesseage.h"

class MyBall : public MySphere, public IAnimation{
public:
	enum class State{
		ISOLATED,		// 独立している
		HANDED,			// 誰かに持たれている
	};

	// --- 球種 --- //
	enum class Variety{
		STRAIGHT,		// ストレート
		CURVE,			// カーブ
		SHOOT,			// シュート
		SLIDER,			// スライダー
		FOLK,			// フォーク
		CHENGEUP,		// チェンジアップ
		GYRO,			// ジャイロボール
	};

private:
	State    state;		// 内部状態
	Variety  variety;	// 球種
	Vector3d vec;		// 移動ベクトル
	double   gravity;	// 重力

	EmitionMessage* message;		// emitを実行した時に通知するオブザーバー

public:
	using DrawableObject::draw;

	MyBall(double radius = 1.0, int sides = 16);
	MyBall(double x, double y, double z, double radius = 1.0, int sides = 16);

	void update() override;

	const State& getState() const{
		return state;
	}

	// 解き放つ
	void emit(Variety variety){
		state = State::ISOLATED;
		this->variety = variety;	// 球種をセット
		if(message != NULL){
			message->message();		// メッセージを送る
		}
	}

	// 誰かに持たれる
	void handed(){
		state = State::HANDED;
	}

	void setEmitionMessage(EmitionMessage* message){
		this->message = message;
	}

	void setVector(double x, double y, double z){
		vec.x = x;
		vec.y = y;
		vec.z = z;
	}
	const Vector3d& getVector() const{
		return vec;
	}
	double getGravity() const{
		return gravity;
	}
};

#endif