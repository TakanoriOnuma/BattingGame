#ifndef ___Class_EmitionMessage
#define ___Class_EmitionMessage

// MyBall�N���X��emit�̃��b�Z�[�W�𑗂�I�u�U�[�o�[
class EmitionMessage{

public:
	virtual ~EmitionMessage(){ }

	virtual void message() = 0;		// MyBall��emit�������ɒʒm�����֐�
};

#endif