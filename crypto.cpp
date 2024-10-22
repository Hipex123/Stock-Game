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
void initKeys();

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

vector<string> stockNamesCopy(stockNames, stockNames + 10);

map<string, float> stocks = {};
map<string, string> stockModes;
map<string, int> storage;
map<int, string> mapKeyPresses;

float prevPrices[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
vector<char *> graph = {};
int graphIndex = 0;
int keys[20];

const int TICK_SPEED = 5000;

main()
{
    std::sort(stockNamesCopy.begin(), stockNamesCopy.end());
    initKeys();

    int ticksPassed = 0;
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        stocks[stockNames[i]] = basePrices[i];
        storage[stockNames[i]] = 0;
    }

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

void initKeys()
{
    int sellKeys[10] = {81, 87, 69, 82, 84, 89, 85, 73, 79, 80};
    string nameHolder;

    for (struct { int i = 49;  int j = 0; } s; s.j < 10; s.i++, s.j++)
    {
        keys[s.j] = s.i;
    }
    keys[9] = 48;

    for (int i = 10; i < 20; i++)
    {
        keys[i] = sellKeys[i - 10];
    }

    for (int i = 0; i < 20; i++)
    {
        mapKeyPresses[keys[i]] = stockNamesCopy[i % 10];
    }
}

void printStocks()
{
    cout << "MONEY->" << money << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "STOCKS" << endl;
    cout << "--------------------------------------------------" << endl;
    for (const auto pair : stocks)
    {
        cout << pair.first << "->" << pair.second << endl;
    }
    cout << "--------------------------------------------------" << endl;
    cout << "STORAGE" << endl;
    cout << "--------------------------------------------------" << endl;
    for (const auto pair : storage)
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
    int i = 0;
    for (const auto &pair : stockMod)
    {
        float randomPriceChange[6] = {
            randomFloat(-0.5, 0.5),
            randomFloat(-0.3, 0.5),
            randomFloat(-0.5, 0.2),
            randomFloat(-0.1, 0.9),
            randomFloat(-0.9, 0.1),
            randomFloat(-0.9, 0.9)};

        prevPrices[i] = stocksDict[pair.first];

        for (int j = 0; j < 6; j++)
        {
            if (pair.second == modes[j])
            {
                stocksDict[pair.first] += randomPriceChange[j];
            }
        }

        if (stocksDict[pair.first] <= 0)
        {
            stocksDict[pair.first] += 0.9;
        }

        i++;
    }
}

void keyPresses()
{
    map<int, bool> previousKeyboardState;
    bool cont;

    while (true)
    {
        cont = false;
        for (const auto pair : mapKeyPresses)
        {
            if (GetAsyncKeyState(pair.first) & 0x8000)
            {
                if (!previousKeyboardState[pair.first])
                {
                    cont = true;
                    if (pair.first >= 48 && pair.first <= 57 && money - stocks[pair.second] >= 0)
                    {
                        money -= stocks[pair.second];
                        storage[pair.second]++;
                    }
                    else if ((pair.first < 48 || pair.first > 57) && storage[pair.second] > 0)
                    {
                        money += stocks[pair.second];
                        storage[pair.second]--;
                    }
                    previousKeyboardState[pair.first] = true;
                }
            }
            else
            {
                previousKeyboardState[pair.first] = false;
            }
        }

        if (GetAsyncKeyState(65) & 0x8000)
        {
            if (!previousKeyboardState[65] && graphIndex >= 1)
            {
                graphIndex--;
                graph.clear();
                system("cls");
                previousKeyboardState[65] = true;
            }
        }
        else
        {
            previousKeyboardState[65] = false;
        }

        if (GetAsyncKeyState(68) & 0x8000)
        {
            if (!previousKeyboardState[68] && graphIndex < 9)
            {
                graphIndex++;
                graph.clear();
                system("cls");
                previousKeyboardState[68] = true;
            }
        }
        else
        {
            previousKeyboardState[68] = false;
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
