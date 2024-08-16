#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <thread>
#include <cmath>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <iterator>
using std::cout, std::endl, std::string, std::map, std::this_thread::sleep_for, std::vector;

void printStocks();
float randomFloat(float min, float max, int decimals = 2);
void updateMode(map<string, string> &stockMod);
void updatePrices(map<string, string> stockMod, map<string, float> &stocksDict);
void keyPresses();
void drawGraph(map<string, float> info, const char *item, float prevPrice);

float money = 1000;

string stockNames[10] = {
    "Milk",
    "Eggs",
    "Flour",
    "Gunpowder",
    "Tim",
    "Dio Brando",
    "Pookie",
    "White Phosphorus",
    "Baking Powder",
    "Bitcoin"};
float basePrices[10] = {
    static_cast<float>(2.04) + randomFloat(0, 2),
    static_cast<float>(3.35) + randomFloat(0, 2),
    static_cast<float>(0.54) + randomFloat(0, 2),
    static_cast<float>(30.12) + randomFloat(0, 2),
    static_cast<float>(0.69) + randomFloat(0, 2),
    static_cast<float>(44.44) + randomFloat(0, 2),
    static_cast<float>(1.69) + randomFloat(0, 2),
    static_cast<float>(60.68) + randomFloat(0, 2),
    static_cast<float>(6.19) + randomFloat(0, 2),
    static_cast<float>(53.11) + randomFloat(0, 2)};
string modes[6] = {"stable",
                   "slowClimb",
                   "slowFall",
                   "fastClimb",
                   "fastFall",
                   "chaotic"};

vector<string> stockNamesCopy;

map<string, float> stocks;
map<string, string> stockModes;
map<string, int> storage;

float prevPrices[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
vector<char *> graph = {};
int graphIndex = 0;

const int TICK_SPEED = 5000;

main()
{
    int ticksPassed = 0;
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        stocks[stockNames[i]] = basePrices[i];
        storage[stockNames[i]] = 0;
    }
    for (const auto &item : stockNames)
    {
        stockNamesCopy.push_back(item);
    }
    std::sort(stockNamesCopy.begin(), stockNamesCopy.end());

    std::thread keyObj(keyPresses);
    updateMode(stockModes);

    while (true)
    {
        printStocks();
        sleep_for(std::chrono::milliseconds(TICK_SPEED));
        system("cls");
        ticksPassed++;
        if (ticksPassed % 24 == 0)
        {
            updateMode(stockModes);
        }
        updatePrices(stockModes, stocks);
    }

    return 0;
}

void printStocks()
{
    cout << "MONEY->" << money << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "STOCKS" << endl;
    cout << "--------------------------------------------------" << endl;
    for (const auto &pair : stocks)
    {
        cout << pair.first << "->" << pair.second << endl;
    }
    cout << "--------------------------------------------------" << endl;
    cout << "STORAGE" << endl;
    cout << "--------------------------------------------------" << endl;
    for (const auto &pair : storage)
    {
        cout << pair.first << "->" << pair.second << endl;
    }
    cout << "--------------------------------------------------" << endl;

    cout << "Graph: " << stockNamesCopy[graphIndex] << endl;
    cout << "\n\n\n";
    cout << "\033[50G";

    switch (graphIndex)
    {
    case 0:
        drawGraph(stocks, "Baking Powder", prevPrices[graphIndex]);
        break;
    case 1:
        drawGraph(stocks, "Bitcoin", prevPrices[graphIndex]);
        break;
    case 2:
        drawGraph(stocks, "Dio Brando", prevPrices[graphIndex]);
        break;
    case 3:
        drawGraph(stocks, "Eggs", prevPrices[graphIndex]);
        break;
    case 4:
        drawGraph(stocks, "Flour", prevPrices[graphIndex]);
        break;
    case 5:
        drawGraph(stocks, "Gunpowder", prevPrices[graphIndex]);
        break;
    case 6:
        drawGraph(stocks, "Milk", prevPrices[graphIndex]);
        break;
    case 7:
        drawGraph(stocks, "Pookie", prevPrices[graphIndex]);
        break;
    case 8:
        drawGraph(stocks, "Tim", prevPrices[graphIndex]);
        break;
    case 9:
        drawGraph(stocks, "White Phosphorus", prevPrices[graphIndex]);
        break;
    default:
        break;
    }

    drawGraph(stocks, "Baking Powder", prevPrices[graphIndex]);
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

float randomFloat(float min, float max, int decimals)
{
    float randomF = min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (max - min));

    randomF = static_cast<float>(static_cast<int>(randomF * 100 + 0.5)) / pow(10, decimals);

    return randomF;
}

void updateMode(map<string, string> &stockMod)
{
    for (int i = 0; i < 10; i++)
    {
        stockMod[stockNames[i]] = modes[rand() % 5];
    }
}

void updatePrices(map<string, string> stockMod, map<string, float> &stocksDict)
{
    int j = 0;
    for (const auto &pair : stockMod)
    {
        if (pair.second == modes[0])
        {
            prevPrices[j] = stocksDict[pair.first];
            stocksDict[pair.first] += randomFloat(-0.5, 0.5);
            if (stocksDict[pair.first] <= 0)
            {
                stocksDict[pair.first] += 0.9;
            }
        }
        if (pair.second == modes[1])
        {
            prevPrices[j] = stocksDict[pair.first];
            stocksDict[pair.first] += randomFloat(-0.1, 0.9);
            if (stocksDict[pair.first] <= 0)
            {
                stocksDict[pair.first] += 0.9;
            }
        }
        if (pair.second == modes[2])
        {
            prevPrices[j] = stocksDict[pair.first];
            stocksDict[pair.first] += randomFloat(-0.9, 0.1);
            if (stocksDict[pair.first] <= 0)
            {
                stocksDict[pair.first] += 0.9;
            }
        }
        if (pair.second == modes[3])
        {
            prevPrices[j] = stocksDict[pair.first];
            stocksDict[pair.first] += randomFloat(-0.3, 0.5);
            if (stocksDict[pair.first] <= 0)
            {
                stocksDict[pair.first] += 0.9;
            }
        }
        if (pair.second == modes[4])
        {
            prevPrices[j] = stocksDict[pair.first];
            stocksDict[pair.first] += randomFloat(-0.5, 0.20);
            if (stocksDict[pair.first] <= 0)
            {
                stocksDict[pair.first] += 0.9;
            }
        }
        if (pair.second == modes[5])
        {
            prevPrices[j] = stocksDict[pair.first];
            stocksDict[pair.first] += randomFloat(-0.20, 0.5);
            if (stocksDict[pair.first] <= 0)
            {
                stocksDict[pair.first] += 0.9;
            }
        }
        j++;
    }
}

void keyPresses()
{
    bool previousKeyboardState = false;
    while (true)
    {
        if (GetAsyncKeyState(49) & 0x8000)
        {
            if (!previousKeyboardState)
            {
                money -= stocks["Baking Powder"];
                storage["Baking Powder"]++;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(50) & 0x8000)
        {
            if (!previousKeyboardState)
            {
                money -= stocks["Bitcoin"];
                storage["Bitcoin"]++;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(51) & 0x8000)
        {
            if (!previousKeyboardState)
            {
                money -= stocks["Dio Brando"];
                storage["Dio Brando"]++;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(52) & 0x8000)
        {
            if (!previousKeyboardState)
            {
                money -= stocks["Eggs"];
                storage["Eggs"]++;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(53) & 0x8000)
        {
            if (!previousKeyboardState)
            {
                money -= stocks["Flour"];
                storage["Flour"]++;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(54) & 0x8000)
        {
            if (!previousKeyboardState)
            {
                money -= stocks["Gunpowder"];
                storage["Gunpowder"]++;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(55) & 0x8000)
        {
            if (!previousKeyboardState)
            {
                money -= stocks["Milk"];
                storage["Milk"]++;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(56) & 0x8000)
        {
            if (!previousKeyboardState)
            {
                money -= stocks["Pookie"];
                storage["Pookie"]++;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(57) & 0x8000)
        {
            if (!previousKeyboardState)
            {
                money -= stocks["Tim"];
                storage["Tim"]++;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(48) & 0x8000)
        {
            if (!previousKeyboardState)
            {
                money -= stocks["White Phosphorus"];
                storage["White Phosphorus"]++;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(81) & 0x8000 && storage["Baking Powder"] > 0)
        {
            if (!previousKeyboardState)
            {
                money += stocks["Baking Powder"];
                storage["Baking Powder"]--;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(87) & 0x8000 && storage["Bitcoin"] > 0)
        {
            if (!previousKeyboardState)
            {
                money += stocks["Bitcoin"];
                storage["Bitcoin"]--;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(69) & 0x8000 && storage["Dio Brando"] > 0)
        {
            if (!previousKeyboardState)
            {
                money += stocks["Dio Brando"];
                storage["Dio Brando"]--;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(82) & 0x8000 && storage["Eggs"] > 0)
        {
            if (!previousKeyboardState)
            {
                money += stocks["Eggs"];
                storage["Eggs"]--;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(84) & 0x8000 && storage["Flour"] > 0)
        {
            if (!previousKeyboardState)
            {
                money += stocks["Flour"];
                storage["Flour"]--;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(89) & 0x8000 && storage["Gunpowder"] > 0)
        {
            if (!previousKeyboardState)
            {
                money += stocks["Gunpowder"];
                storage["Gunpowder"]--;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(85) & 0x8000 && storage["Milk"] > 0)
        {
            if (!previousKeyboardState)
            {
                money += stocks["Milk"];
                storage["Milk"]--;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(73) & 0x8000 && storage["Pookie"] > 0)
        {
            if (!previousKeyboardState)
            {
                money += stocks["Pookie"];
                storage["Pookie"]--;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(79) & 0x8000 && storage["Tim"] > 0)
        {
            if (!previousKeyboardState)
            {
                money += stocks["Tim"];
                storage["Tim"]--;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(80) & 0x8000 && storage["White Phosphorus"] > 0)
        {
            if (!previousKeyboardState)
            {
                money += stocks["White Phosphorus"];
                storage["White Phosphorus"]--;
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(65) & 0x8000)
        {
            if (!previousKeyboardState && graphIndex >= 1)
            {
                graphIndex--;
                graph.clear();
                system("cls");
                previousKeyboardState = true;
            }
        }
        else if (GetAsyncKeyState(68) & 0x8000)
        {
            if (!previousKeyboardState && graphIndex < 9)
            {
                graphIndex++;
                graph.clear();
                system("cls");
                previousKeyboardState = true;
            }
        }
        else
        {
            previousKeyboardState = false;
        }
    }
}

void drawGraph(map<string, float> info, const char *item, float prevPrice)
{
    if (graph.size() >= 120)
    {
        graph.erase(graph.begin());
        graph.erase(graph.begin());
    }

    for (const auto &move : graph)
    {
        cout << move;
    }

    if (info[item] - prevPrice > 0)
    {
        graph.push_back("\033[A");
        graph.push_back("*");
    }
    else if (info[item] - prevPrice < 0)
    {
        graph.push_back("\033[B");
        graph.push_back("*");
    }
}