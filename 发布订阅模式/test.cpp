#include <iostream>

using namespace std;

namespace TJVictor.DesignPattern.SubscribePublish
{
	//���嶩���¼�
	public delegate void SubscribeHandle(string str);

	//���嶩�Ľӿ�
	public interface ISubscribe
	{
		event SubscribeHandle SubscribeEvent;
	}
}


/*
namespace first
{
	int a;
	int b;
}

int main()
{
	cout << first::a << endl;
	cout << first::b << endl;
}
*/