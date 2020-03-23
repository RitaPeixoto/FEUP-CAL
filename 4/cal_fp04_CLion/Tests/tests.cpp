#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Graph.h"
#include "Person.h"

using namespace std;
using testing::Eq;

void createNetwork(Graph<Person> & net1)
{
    Person p1("Ana",19);
    Person p2("Carlos",33);
    Person p3("Filipe", 20);
    Person p4("Ines", 18);
    Person p5("Maria", 24);
    Person p6("Rui",21);
    Person p7("Vasco",28);
    net1.addVertex(p1); net1.addVertex(p2);
    net1.addVertex(p3); net1.addVertex(p4);
    net1.addVertex(p5); net1.addVertex(p6); net1.addVertex(p7);
    net1.addEdge(p1,p2,0);
    net1.addEdge(p1,p3,0);
    net1.addEdge(p1,p4,0);
    net1.addEdge(p2,p5,0);
    net1.addEdge(p5,p6,0);
    net1.addEdge(p5,p1,0);
    net1.addEdge(p3,p6,0);
    net1.addEdge(p3,p7,0);
    net1.addEdge(p6,p2,0);
}

TEST(CAL_FP04, test_addVertex) {
    /* //uncomment test body below!
    Graph<Person> net1;
    Person p1("Ana",19);
    Person p2("Carlos",33);
    Person p3("Filipe", 20);
    Person p4("Ines", 18);
    net1.addVertex(p1); net1.addVertex(p2);
    net1.addVertex(p3); net1.addVertex(p4);
    EXPECT_EQ(false, net1.addVertex(p2));
    EXPECT_EQ(4, net1.getNumVertex());
     */
}

TEST(CAL_FP04, test_removeVertex) {
    /* //uncomment test body below!
    Graph<Person> net1;
    Person p1("Ana",19);
    Person p2("Carlos",33);
    Person p3("Filipe", 20);
    Person p4("Ines", 18);
    net1.addVertex(p1); net1.addVertex(p2);
    net1.addVertex(p3); net1.addVertex(p4);
    EXPECT_EQ(true, net1.removeVertex(p2));
    EXPECT_EQ(false, net1.removeVertex(p2));
    EXPECT_EQ(3, net1.getNumVertex());
     */
}

TEST(CAL_FP04, test_addEdge) {
    /* //uncomment test body below!
    Graph<Person> net1;
    Person p1("Ana",19);
    Person p2("Carlos",33);
    Person p3("Filipe", 20);
    Person p4("Ines", 18);
    Person p5("Maria", 24);
    net1.addVertex(p1); net1.addVertex(p2);
    net1.addVertex(p3); net1.addVertex(p4);
    EXPECT_EQ(true, net1.addEdge(p1,p2,0));
    EXPECT_EQ(true, net1.addEdge(p1,p3,0));
    EXPECT_EQ(true, net1.addEdge(p1,p4,0));
    EXPECT_EQ(false, net1.addEdge(p2,p5,0));
     */
}

TEST(CAL_FP04, test_removeEdge) {
    /* //uncomment test body below!
    Graph<Person> net1;
    Person p1("Ana",19);
    Person p2("Carlos",33);
    Person p3("Filipe", 20);
    Person p4("Ines", 18);
    Person p5("Maria", 24);
    net1.addVertex(p1); net1.addVertex(p2);
    net1.addVertex(p3); net1.addVertex(p4);
    EXPECT_EQ(true, net1.addEdge(p1,p2,0));
    EXPECT_EQ(true, net1.addEdge(p1,p3,0));
    EXPECT_EQ(true, net1.addEdge(p1,p4,0));
    EXPECT_EQ(true, net1.addEdge(p2,p4,0));
    EXPECT_EQ(true, net1.removeEdge(p1,p3));
    EXPECT_EQ(false, net1.removeEdge(p1,p5));
    EXPECT_EQ(false, net1.removeEdge(p2,p3));
     */
}

TEST(CAL_FP04, test_dfs) {
    /* //uncomment test body below!
    Graph<Person> net1;
    createNetwork(net1);
    vector<Person> v1 = net1.dfs();
    string names[] = {"Ana", "Carlos", "Maria", "Rui", "Filipe", "Vasco", "Ines"};
    for (unsigned i = 0; i < 7; i++)
        if (i < v1.size())
            EXPECT_EQ(names[i], v1[i].getName());
        else
            EXPECT_EQ(names[i], "(null)");
     */
}

TEST(CAL_FP04, test_bfs) {
    /* //uncomment test body below!
    Graph<Person> net1;
    createNetwork(net1);
    vector<Person> v1 = net1.bfs(Person("Ana",19));
    string names[] = {"Ana", "Carlos", "Filipe", "Ines", "Maria", "Rui", "Vasco"};
    for (unsigned i = 0; i < 7; i++)
        if (i < v1.size())
            EXPECT_EQ(names[i], v1[i].getName());
        else
            EXPECT_EQ(names[i], "(null)");
     */
}

TEST(CAL_FP04, test_removeVertex_Again) {
    /* //uncomment test body below!
    Graph<Person> net1;
    createNetwork(net1);
    Person p2("Carlos",33);
    EXPECT_EQ(true, net1.removeVertex(p2));
    vector<Person> v1=net1.dfs();
    string names[] = {"Ana", "Filipe", "Rui", "Vasco", "Ines", "Maria"};
    for (unsigned i = 0; i < 6; i++)
        EXPECT_EQ(names[i], v1[i].getName());
     */
}

TEST(CAL_FP04, test_removeEdge_Again) {
    /* //uncomment test body below!
    Graph<Person> net1;
    createNetwork(net1);
    Person p5("Maria", 24);
    Person p6("Rui",21);
    EXPECT_EQ(true, net1.removeEdge(p5,p6));
    vector<Person> v1=net1.dfs();
    string names[] = {"Ana", "Carlos", "Maria", "Filipe", "Rui", "Vasco", "Ines"};
    for (unsigned i = 0; i < 7; i++)
        EXPECT_EQ(names[i], v1[i].getName());
     */
}

TEST(CAL_FP04, test_maxNewChildren) {
    /* //uncomment test body below!
    Graph<Person> net1;
    Person p1("Ana",19);
    Person p2("Carlos",33);
    Person p3("Filipe", 20);
    Person p4("Ines", 18);
    Person p5("Maria", 24);
    Person p6("Rui",21);
    Person p7("Vasco",28);
    net1.addVertex(p1); net1.addVertex(p2);
    net1.addVertex(p3); net1.addVertex(p4);
    net1.addVertex(p5); net1.addVertex(p6); net1.addVertex(p7);
    net1.addEdge(p1,p2,0);
    net1.addEdge(p1,p3,0);
    net1.addEdge(p2,p5,0);
    net1.addEdge(p3,p4,0);
    net1.addEdge(p5,p6,0);
    net1.addEdge(p5,p1,0);
    net1.addEdge(p3,p6,0);
    net1.addEdge(p3,p7,0);
    net1.addEdge(p3,p2,0);
    Person pt;
    EXPECT_EQ(3, net1.maxNewChildren(Person("Ana",19), pt));
    EXPECT_EQ("Filipe", pt.getName());
     */
}

TEST(CAL_FP04, test_isDAG) {
    /* //uncomment test body below!
    Graph<int> myGraph;

    myGraph.addVertex(0);myGraph.addVertex(1); myGraph.addVertex(2);
    myGraph.addVertex(3); myGraph.addVertex(4); myGraph.addVertex(5);
    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(4, 1, 0);
    myGraph.addEdge(5, 1, 0);
    myGraph.addEdge(2, 3, 0);
    myGraph.addEdge(3, 1, 0);
    myGraph.addEdge(0, 4, 0);

    EXPECT_EQ(false, myGraph.isDAG());

    myGraph.removeEdge(4, 1);
    myGraph.removeEdge(5, 1);
    myGraph.removeEdge(2, 3);

    EXPECT_EQ(true, myGraph.isDAG());

    myGraph.addEdge(1, 4, 0);

    EXPECT_EQ(true, myGraph.isDAG());
     */
}

TEST(CAL_FP04, test_topsort) {
    /* //uncomment test body below!
    Graph<int> myGraph;
    myGraph.addVertex(1); myGraph.addVertex(2); myGraph.addVertex(3); myGraph.addVertex(4);
    myGraph.addVertex(5); myGraph.addVertex(6); myGraph.addVertex(7);
    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(1, 4, 0);
    myGraph.addEdge(1, 3, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(2, 4, 0);
    myGraph.addEdge(3, 6, 0);
    myGraph.addEdge(4, 3, 0);
    myGraph.addEdge(4, 6, 0);
    myGraph.addEdge(4, 7, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(5, 7, 0);
    myGraph.addEdge(7, 6, 0);

    vector<int> topOrder;

    topOrder = myGraph.topsort();
    stringstream ss;
    for( unsigned int i = 0; i < topOrder.size(); i++)
        ss << topOrder[i] << " ";
    EXPECT_EQ("1 2 5 4 3 7 6 ", ss.str());

    //para testar a inclusao de um ciclo no grafo!
    myGraph.addEdge(3, 1, 0);

    topOrder = myGraph.topsort();
    ss.str("");
    for( unsigned int i = 0; i < topOrder.size(); i++)
        ss << topOrder[i] << " ";
    EXPECT_EQ("", ss.str());
     */
}

