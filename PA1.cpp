#include <iostream>
#include <stack>
#include <vector>
#include "PA1.h"

using std::stack;
// declare vector
std::vector<stack<int>> HanoiGame;
static int move_count=0;
static int boardWidth = 5;
int main()
{

    // std::vector<std::string> num_stacks ={"Start","Dest","A1","A2","A3"} ;
    int n = 10;

    for (int i = 0; i < boardWidth; i++)
    {
        HanoiGame.push_back(stack<int>());
        // HanoiGame.push_back(num_stacks.at(i));
    }

    for (int i = n; i > 0; i--)
    {
        HanoiGame.at(0).push(i);
    }

    std::cout << "initial state: " << std::endl;
    show_board();

    // player_move(1, 4);
    // player_move(2, 3);
    // player_move(1, 2);

    moveCursor(n,boardWidth-1);
    moveCursor(n,1);

    // std::cout << "final state: " << std::endl;
    // show_board();
    // std::cout<<"Numbers of Move :"<< move_count<<std::endl;
}
// how to move the disk around; solving the problem disk -> dest
void moveCursor(int disk, int goalPos)
{
    if (disk < 1)
    {
        return;
    }
    // determine the direction to move to
    int diskCurPos = getPos(disk);
    // move x-1 to p
    moveCursor(disk - 1, goalPos);
    // solve case0 (move x-1 on top of x at p)
    if (diskCurPos == goalPos)
    {
        return;
    }

    if (goalPos == boardWidth - 1) // goalposition is at the far right(end of stack)
    {
        // move opposite end of where we want to go, with one space from end
        player_move(disk, 2);    // manually move disk to one space(1,2..) from the left end
        moveCursor(disk - 1, 1); // move the disk-1(rest of the smaller disk) to the far left(1,...)
    }
    else if (goalPos == 1) // the p is on the lefthand side
    {
        // move opposite end of where we want to go, with one space from end
        player_move(disk, boardWidth - 2);    // manually move disk to the right end (...,,4)
        moveCursor(disk - 1, boardWidth - 1); // move the disk-1(rest of the smaller disk) to the far right(...3,4)
    }
    else
    {
        int dir = getDir(diskCurPos, goalPos); // scaning the direction from the current to the goalpos
        moveCursor(disk - 1, boardWidth + dir);
    }
    // case1
    player_move(disk, goalPos);
    moveCursor(disk - 1, goalPos);
}

void player_move(int disk, int goalPos)
{
    // std::cout << "trying to move disk " << disk << " to position " << goalPos << std::endl;
    if (goalPos < 1)
    {
        throw std::invalid_argument("Error! you move to start");
    }
    // validate the movement
    if (disk < 1)
    {
        return;
    }

    if (goalPos < 1 || goalPos > HanoiGame.size() - 1) // if the goal is within the boardgame range,then you can move
    {
        throw std::invalid_argument("Error! you move to invalid position!");
    }

    
    // define current position of the tower
    int currentPos = getPos(disk);
    // if the current position is not found throw errors
    if (disk!=HanoiGame.at(currentPos).top())
    {
        throw std::invalid_argument("Disk is not accessiable!");
    }
    // find the smaller disk in between start to dest
    int direction = getDir(currentPos, goalPos);
    // if (currentPos > goalPos)
    // {
    //     direction = -1;
    // }

    // cursor in between current pos and the destination
    for (int i = currentPos; i - direction != goalPos; i += direction)
    {
        if (HanoiGame.at(i).empty())
        {
            continue;
        }
        if (HanoiGame.at(i).top() < disk)
        {
            throw std::invalid_argument("Invalid disk movement: bigger disk is not allowed to jump on smaller disk!");
        }
    }

    HanoiGame.at(currentPos).pop();
    HanoiGame.at(goalPos).push(disk);
    move_count++;
    // show_board();
    if(move_count<=100){
        std::cout<<"Moves: "<<move_count<<std::endl;
        show_board();
    }
    
    
}

void show_board()
{
    for (int i = 0; i < HanoiGame.size(); i++)
    {
        auto tower = HanoiGame.at(i);
        stack<int> temp;

        // printing out the stack bottom to top ; left to the right
        std::cout<< "Stack " << i << " (size " << tower.size() << "):";
        while (!tower.empty())
        {
            temp.push(tower.top());
            tower.pop();
        }
        // printing out the stack top to bottom ; right to the left
        while (!temp.empty())
        {
            std::cout << " " << temp.top();
            tower.push(temp.top());
            temp.pop();
        }
        std::cout << std::endl;
    }
}
int getPos(int disk)
{
    int foundPos = -1;
    stack<int> temp;
    for (int i = 0; i < boardWidth; i++)
    {
        while (!HanoiGame.at(i).empty())
        {
            if (HanoiGame.at(i).top() == disk)
            {
                foundPos = i;
                break;
            }
            temp.push(HanoiGame.at(i).top());
            HanoiGame.at(i).pop();
        }
        while (!temp.empty())
        {
            HanoiGame.at(i).push(temp.top());
            temp.pop();
        }
        if (foundPos != -1)
        {
            break;
            std::cout << "the tower is Found" << std::endl;
        }
    }

    return foundPos;
}
int getDir(int start, int end)
{
    return start == end ? 0 : start < end ? 1 : -1;
}
