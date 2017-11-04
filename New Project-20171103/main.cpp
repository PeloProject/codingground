#include <iostream>
#include "class/Components.cpp"

using namespace std;

Manager gManager;
auto& newPlayer(gManager.AddEntity());

int main()
{
    newPlayer.AddComponent<PositionComponent>();
    gManager.Update();
    cout << newPlayer.GetComponent<PositionComponent>().x() << "," << newPlayer.GetComponent<PositionComponent>().y() << endl; 
    cout << "Hello World" << endl; 
   
    return 0;
}


