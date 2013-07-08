#ifndef ___Class_EmitionMessage
#define ___Class_EmitionMessage

// MyBallクラスのemitのメッセージを送るオブザーバー
class EmitionMessage{

public:
	virtual ~EmitionMessage(){ }

	virtual void message() = 0;		// MyBallがemitした時に通知される関数
};

#endif