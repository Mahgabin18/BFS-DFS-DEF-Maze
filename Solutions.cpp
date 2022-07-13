#include "Maze.cpp"
//#include "MazeNode.hpp"
//#include "MazeNode.cpp"

#include <stack>
#include <queue>

using namespace std;

namespace solutions
{

int getNumberOfWalls(MazeNode *a_node)
{
    int wall_counter = 0;
    for (directions::nesw dir = directions::NORTH; dir < directions::EAST; dir = directions::nesw(dir + 1))
    {
        if (a_node->getDirectionNode(dir) == nullptr || a_node->getDirectionNode(dir)->isWall() || a_node->getDirectionNode(dir)->isVisited())
        {
            wall_counter++;
        }
    }
    return wall_counter;
}

bool canTravel(MazeNode *a_node)
{

    
    
        if (a_node == nullptr || a_node->isVisited() || a_node->isWall())
        {
            return false;
        }  
    

    return true;
}

int amountofNeighbors(MazeNode *a_maze) // helper function for our BFS!
{
    int numNum = 0;

    if (canTravel(a_maze->getDirectionNode(directions::NORTH)))
    {
        numNum++;
    }
    if (canTravel(a_maze->getDirectionNode(directions::EAST)))
    {
        numNum++;
    }
    if (canTravel(a_maze->getDirectionNode(directions::SOUTH)))
    {
        numNum++;
    }
    if (canTravel(a_maze->getDirectionNode(directions::WEST)))
    {
        numNum++;
    }

    return numNum;
}


std::vector<MazeNode> solveDFS(Maze &a_maze)
{
   stack <MazeNode> Astack; // make an empty stack
   stack <MazeNode> NewStack; // copied stack
   vector<MazeNode> orderedDFS;
   //Astack.push(*a_maze.getFirstNode());// push the first value into the stack
   a_maze.getFirstNode()->setVisited();
   a_maze.setCurrentNode(a_maze.getFirstNode());
        while (a_maze.getCurrentNode() != a_maze.getLastNode())// 
        {
         
            if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::NORTH)))
            {
                Astack.push(*a_maze.getCurrentNode());
                a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::NORTH));
                a_maze.getCurrentNode()->setVisited();

            }

            else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::EAST)))
            {
                Astack.push(*a_maze.getCurrentNode());
                a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::EAST));
                a_maze.getCurrentNode()->setVisited();
                
            }

            else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH)))
            {
                Astack.push(*a_maze.getCurrentNode());
                a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH));
                a_maze.getCurrentNode()->setVisited();
                
            }

             else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::WEST)))
             {
                Astack.push(*a_maze.getCurrentNode());
                a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::WEST));
                a_maze.getCurrentNode()->setVisited();
                
             }

            else 
            {
                 MazeNode *pointer = &Astack.top();
                 Astack.pop();
                 a_maze.setCurrentNode(pointer);
            }
        }
    if (a_maze.getCurrentNode() == a_maze.getLastNode())
    {
         Astack.push(*a_maze.getCurrentNode());
          a_maze.getCurrentNode()->setVisited();

    }
        

        while(!Astack.empty())
        {
        NewStack.push(Astack.top());
        Astack.pop();
        }

        while(!NewStack.empty())
        {
            orderedDFS.push_back(NewStack.top());
            NewStack.pop();
        }

return orderedDFS;
   }

std::vector<MazeNode> solveBFS(Maze &a_maze)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////// ATTEMPT 1
   /* queue <MazeNode> Queued;
    vector <MazeNode> collector;

   //Queued.push(a_maze.getFirstNode());
    a_maze.setCurrentNode(a_maze.getFirstNode());

while (a_maze.getCurrentNode()!=a_maze.getLastNode() && !Queued.empty())
{
    a_maze.getFirstNode()->setVisited();
    //collector.push_back(a_maze.getFirstNode());
    
        Queued.pop();

        if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::NORTH)))
        {
            a_maze.getCurrentNode()->setVisited();
            Queued.push(*a_maze.getCurrentNode());
            collector.push_back(*a_maze.getCurrentNode());
        }
        else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::EAST)))
        {
            a_maze.getCurrentNode()->setVisited();
            Queued.push(*a_maze.getCurrentNode());
             collector.push_back(*a_maze.getCurrentNode());
        }
        else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::WEST)))
        {
            a_maze.getCurrentNode()->setVisited();
            Queued.push(*a_maze.getCurrentNode());
             collector.push_back(*a_maze.getCurrentNode());
        }
        else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH)))
        {
            a_maze.getCurrentNode()->setVisited();
            Queued.push(*a_maze.getCurrentNode());
             collector.push_back(*a_maze.getCurrentNode());
        }

        else
        {
            collector.push_back(*a_maze.getCurrentNode());
        }
    
}
return collector;
*////////////////////////////////////////////////////////////////////////////////////////////////////////////// END OF ATTTEMPT 1
    queue <MazeNode> Queued; // the queue
    vector<MazeNode> finalReversal; // holds the vector with the shortest path
    vector <pair<MazeNode ,MazeNode> > parentTracker; // keeps track of the child and parent through an ordered pair
    vector<MazeNode> finalPathReverse; // holds the vector with the shortest path through reversal since itll be backwards beforehand
    
    
    Queued.push(*(a_maze.getCurrentNode())); // first node is pushed into the queue and set as visited 
    a_maze.getFirstNode()->setVisited();
   
    vector<MazeNode> finalized; // the one being returned as a vector

    bool lastFound = false; // helps keep track of when the end got reached 

    
    while (!lastFound) // WHILE THE END ISNT FOUND 
    {
        a_maze.setCurrentNode(&(Queued.front())); // & is put there because of it being an object type 
        Queued.pop(); // uts popped from the queue

                if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::NORTH)))
                {
                                a_maze.getCurrentNode()->getDirectionNode(directions::NORTH)->setVisited();
                                Queued.push(*(a_maze.getCurrentNode()->getDirectionNode(directions::NORTH)));
                                parentTracker.push_back(std::make_pair(*a_maze.getCurrentNode()->getDirectionNode(directions::NORTH), *a_maze.getCurrentNode()));
                                if (a_maze.getCurrentNode()->getDirectionNode(directions::NORTH) == (a_maze.getLastNode()))
                                {
                                    lastFound = true;
                                }

                } 
        if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::EAST)))
        {
                        a_maze.getCurrentNode()->getDirectionNode(directions::EAST)->setVisited();
                        Queued.push(*(a_maze.getCurrentNode()->getDirectionNode(directions::EAST)));
                        parentTracker.push_back(std::make_pair(*a_maze.getCurrentNode()->getDirectionNode(directions::EAST), *a_maze.getCurrentNode()));
                        if (a_maze.getCurrentNode()->getDirectionNode(directions::EAST) == a_maze.getLastNode())
                        {
                            lastFound = true;
                        }
            
        } 
                if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH)))
                {
                                a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH)->setVisited();
                                Queued.push(*(a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH)));
                                parentTracker.push_back(std::make_pair(*a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH), *a_maze.getCurrentNode()));
                                if (a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH) == a_maze.getLastNode())
                                {
                                    lastFound = true;
                                }
                } 
        if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::WEST)))
        {
                    a_maze.getCurrentNode()->getDirectionNode(directions::WEST)->setVisited();
                    Queued.push(*(a_maze.getCurrentNode()->getDirectionNode(directions::WEST)));
                    parentTracker.push_back(std::make_pair(*a_maze.getCurrentNode()->getDirectionNode(directions::WEST), *a_maze.getCurrentNode()));
                    if (a_maze.getCurrentNode()->getDirectionNode(directions::WEST) == a_maze.getLastNode())
                    {
                        lastFound = true;
                    }
         
        } 
    } 

    a_maze.setCurrentNode(a_maze.getLastNode());

    int i = parentTracker.size() - 1;
    while ((i >= 0) )
    {
        if (parentTracker[i].first.getStrPos() == a_maze.getCurrentNode()->getStrPos())
        {
            finalReversal.push_back(parentTracker[i].second);
            a_maze.setCurrentNode(&(parentTracker[i].second));
        }
        i--;
    }
   

for (int j = finalReversal.size() - 1; j >= 0; j--)
 {
 finalized.push_back(finalReversal[j]);
 }
        finalized.push_back(*(a_maze.getLastNode()));



return finalized;

}

std::vector<MazeNode> solveDEF(Maze &a_maze)
{
    std::vector<MazeNode> final; // the vector being returned 
    std::vector<MazeNode> deadends; // gets all the dead ends to be filled inside a vector
    vector<MazeNode> EVERYNodes = a_maze.getNodes(); // gets all the nodes in the maze 
    vector<MazeNode> anotherVector;
    for (int i = 0; i < EVERYNodes.size(); i++)
    {
        a_maze.setCurrentNode(&EVERYNodes[i]);
        if (!a_maze.getCurrentNode()->isWall() && (a_maze.getCurrentNode() != nullptr))
        {
            if ((a_maze.getCurrentNode()->getStrPos() != a_maze.getFirstNode()->getStrPos()) && (a_maze.getCurrentNode()->getStrPos() != a_maze.getLastNode()->getStrPos()))
            { // convert the positions to the ordered pairing being needed 
                int counttheneighbors =amountofNeighbors(a_maze.getCurrentNode());
                if (counttheneighbors == 1)
                {
                    deadends.push_back(*a_maze.getCurrentNode()); // counting the number of deadends needed here 
                }

            }
        } 
    } 


    int adjacents = 0;
    for (int i = 0; i < deadends.size(); i++)
    {
        a_maze.setCurrentNode(&deadends[i]);
        adjacents = amountofNeighbors(a_maze.getCurrentNode());

    while (adjacents == 1)
         {
                    if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::NORTH)))
                    {
                        a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::NORTH));
                        a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH)->setWall();
                        adjacents = amountofNeighbors(a_maze.getCurrentNode());
                    }
                    else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::EAST)))
                    {
                        a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::EAST));
                        a_maze.getCurrentNode()->getDirectionNode(directions::WEST)->setWall();
                        adjacents = amountofNeighbors(a_maze.getCurrentNode());
                        
                    }
                    else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH)))
                    {
                        a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH));
                        a_maze.getCurrentNode()->getDirectionNode(directions::NORTH)->setWall();
                        adjacents = amountofNeighbors(a_maze.getCurrentNode());
                        
                    }
                    else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::WEST)))
                    {
                        a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::WEST));
                        a_maze.getCurrentNode()->getDirectionNode(directions::EAST)->setWall();
                        adjacents = amountofNeighbors(a_maze.getCurrentNode());
                            
                    } // look for the dead ends and mark them to be walls. After, the backtracking will start  to count how many dead ends are present in the maze
         }
      }

    

    a_maze.setCurrentNode(a_maze.getFirstNode()); // first node = current node

    final.push_back(*(a_maze.getCurrentNode())); // the vector being returned will get the current node 

    while (a_maze.getCurrentNode() != a_maze.getLastNode())
    {

        
        if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::NORTH)))
        {
            final.push_back(*a_maze.getCurrentNode()->getDirectionNode(directions::NORTH));
            a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::NORTH));
            a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH)->setVisited();
        } 
        else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::EAST)))
        {
            final.push_back(*a_maze.getCurrentNode()->getDirectionNode(directions::EAST));
            a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::EAST));
            a_maze.getCurrentNode()->getDirectionNode(directions::WEST)->setVisited();
        } 
        else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH)))
        {
            final.push_back(*a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH));
            a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH));
            a_maze.getCurrentNode()->getDirectionNode(directions::NORTH)->setVisited();
        } 
        else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::WEST)))
        {
            final.push_back(*a_maze.getCurrentNode()->getDirectionNode(directions::WEST));
            a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::WEST));
            a_maze.getCurrentNode()->getDirectionNode(directions::EAST)->setVisited();
        } 
    } // until it gets to the last node, get all the nodes for the vector that has the shortest path being registered 
    return final;
    
}


std::vector<MazeNode> solveCustom(Maze &a_maze)
{
      stack <MazeNode> Astack; // make an empty stack
   stack <MazeNode> NewStack; // copied stack
   vector<MazeNode> orderedDFS;
   //Astack.push(*a_maze.getFirstNode());// push the first value into the stack
   a_maze.getFirstNode()->setVisited();
   a_maze.setCurrentNode(a_maze.getFirstNode());
        while (a_maze.getCurrentNode() != a_maze.getLastNode())// 
        {
         
            if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::NORTH)))
            {
                Astack.push(*a_maze.getCurrentNode());
                a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::NORTH));
                a_maze.getCurrentNode()->setVisited();

            }

            else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::EAST)))
            {
                Astack.push(*a_maze.getCurrentNode());
                a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::EAST));
                a_maze.getCurrentNode()->setVisited();
                
            }

            else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH)))
            {
                Astack.push(*a_maze.getCurrentNode());
                a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::SOUTH));
                a_maze.getCurrentNode()->setVisited();
                
            }

             else if (canTravel(a_maze.getCurrentNode()->getDirectionNode(directions::WEST)))
             {
                Astack.push(*a_maze.getCurrentNode());
                a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(directions::WEST));
                a_maze.getCurrentNode()->setVisited();
                
             }

            else 
            {
                 MazeNode *pointer = &Astack.top();
                 Astack.pop();
                 a_maze.setCurrentNode(pointer);
            }
        }
    if (a_maze.getCurrentNode() == a_maze.getLastNode())
    {
         Astack.push(*a_maze.getCurrentNode());
          a_maze.getCurrentNode()->setVisited();

    }
        

        while(!Astack.empty())
        {
        NewStack.push(Astack.top());
        Astack.pop();
        }

        while(!NewStack.empty())
        {
            orderedDFS.push_back(NewStack.top());
            NewStack.pop();
        }

return orderedDFS;
}

} // namespace solutions
