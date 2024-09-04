#include <iostream>
#include <memory>
#include <deque>

//this is working moc by Master-Slave Model.

struct GrobalInfo {
	int A;
	int B;
	int C;
};

enum class Task {
	None,
	A,
	B,
	C,
};

typedef std::shared_ptr<GrobalInfo> SGrobalInfo;

struct Slave;
typedef std::shared_ptr<Slave> SSlave;

struct Master
{
	SGrobalInfo Info = std::make_shared<GrobalInfo>();
	std::deque<SSlave> S;
	Task T = Task::None;

	SSlave MakeSlave(Task T) {
		SSlave SS = std::make_shared<Slave>();
		SS->T = T;
		SS->Info = *Info;
		S.push_back(SS);
		return SS;
	}
};

struct SlaveLocal
{
	int X;
	int Y;
	int Z;
};

struct SlavePublic
{
	int Q;
	int A;
	int Z;
};

typedef std::shared_ptr<SlavePublic> SSlavePublic;

struct Slave
{
	GrobalInfo Info;//reflesh by time of master;
	SlaveLocal SL{};
	SSlavePublic SP = std::make_shared<SlavePublic>();
	Task T = Task::None;


	bool BeWork() { return true; };
	bool BeSleep() { return true; };

	bool NeedInfo() { return false; }
	bool Reflesh(const Master& M) { return false; }
	bool Sync(const Slave& S) { return true; }
};



int main() {
	Master M;

	SSlave A = M.MakeSlave(Task::A);
	SSlave B = M.MakeSlave(Task::A);
	SSlave C = M.MakeSlave(Task::B);

	A->BeWork();
	B->BeSleep();
	C->Sync(*A);

	return 0;


}