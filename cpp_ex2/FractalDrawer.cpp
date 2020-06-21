// ------------------------------ includes ------------------------------
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include "Fractal.h"

// -------------------------- const definitions -------------------------
#define NUM_OF_ARGS 2
#define INVALID_NUM_MSG "Usage: FractalDrawer <file path>"
#define INVALID_INPUT_MSG "Invalid input"
#define NUM_OF_TYPE_TREE 3
#define FILE_TYPE ".csv"

// ------------------------------ functions -----------------------------
/**
 *Holds type of fractal tree from the option of the user can have, and the diminetion
 */
struct data
{
    Tree treeType;
    int dim;
};

/**
 * shortcut method to print to the stderr invalid input msg and exit from the prog.
  * @param msg - The msg to print in the ctderr.
  */
void exitFailure(const std::string &msg)
{
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}

/**
 * check if the dim is bigger than 0 or smaller than 7. If it is not, the prog will exit.
 * @param num - The number to check.
 */
void validDim(int num)
{
    if (num <= 0 || num > 6)
    {
        exitFailure(INVALID_INPUT_MSG);
    }
}

/**
 * checks for valid string of name of the tree the prog can handle with.
 * @param treeCheck - The name of the tree to check.
 */
void validTreeName(const int treeCheck)
{
    if (treeCheck > NUM_OF_TYPE_TREE || treeCheck < 1)
    {
        exitFailure(INVALID_INPUT_MSG);
    }
}


/**
 * Checks for the valid input from the user in the cli.
 * @param num - The input number of args.
 * @param argv - The array of inputs thats include the directory.
 */
void validInput(int num, char **argv)
{
    if (num != NUM_OF_ARGS)
    {
        exitFailure(INVALID_NUM_MSG);
    }
    std::string filePath = argv[1];
    if (!boost::filesystem::exists(filePath))
    {
        exitFailure(INVALID_INPUT_MSG);
    }
    if (boost::filesystem::path(filePath).extension() != FILE_TYPE)
    {
        exitFailure(INVALID_INPUT_MSG);
    }
}

/**
 * Checks if the string can be an int.
 * @param string - The string to check on.
 * @return - true if it can be int, false otherwise.
 */
bool isInteger(const std::string &string)
{

    for (int i = 0; i < (int) string.length(); i++)
    {
        if (!isdigit(string[i]))
        {
            return false;
        }
    }
    return true;
}

/**
 * Reading the csv file and send the information to the data vector. It check for valid input in
 * the file and parse it into data struct. Then it add it to the dataVector.
 * @param csvPath - The directory of the csv file.
 * @param dataVector - Vector that include data from the csv file.
 */
void readCsvFile(const std::string &csvPath, std::vector<data> &dataVector)
{

    std::ifstream file(csvPath);

    if (!file.is_open())
    {
        exitFailure(INVALID_INPUT_MSG);
    }

    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    std::vector<std::string> vector;
    std::string line;
    boost::char_separator<char> sep{", "};
    while (getline(file, line))
    {
        int flag = 0;
        tokenizer tok(line, sep);
        int *resArray = new int[2];
        for (const auto &t: tok)
        {
            if (isInteger(t) && flag < 2)
            {
                resArray[flag] = stoi(t);
                flag++;
            }
            else
            {
                exitFailure(INVALID_INPUT_MSG);
            }
        }
        validTreeName(resArray[0]);
        validDim(resArray[1]);
        data newData = {static_cast<Tree>(resArray[0]), resArray[1]};
        dataVector.push_back(newData);
        delete[] resArray;
    }
}

/**
 * Factory design for extract all the data from the dataVector. It pass throw the array by revese
 * iterator and add the specific fractal object (pointer) to the fractal pointer vector.
 * The delete of the new object will be in a different method.
 * @param dataVector - the vector that include all the data from the file.
 * @param vectorFractal - The vector of fractals pointers.
 */
void fractalFactory(std::vector<data> &dataVector, std::vector<Fractal *> &vectorFractal)
{
    for (auto it = dataVector.rbegin(); it != dataVector.rend(); it++)
    {
        switch ((*it).treeType)
        {
            case sierpinskiCarpet:
            {
                auto insertNewFractal = new SierpinskiCarpet((*it).dim);
                vectorFractal.push_back(insertNewFractal);
                break;
            }
            case sierpinskiTriangle:
            {
                auto insertNewFractal = new SierpinskiTriangle((*it).dim);
                vectorFractal.push_back(insertNewFractal);
                break;
            }
            case vicsekFractal:
            {
                auto insertNewFractal = new VicsekFractal((*it).dim);
                vectorFractal.push_back(insertNewFractal);
                break;
            }
        }
    }
}

/**
 * A method that ask to draw from the fractal and print it.
 * @param vectorFractal - the vector that contain all the fractals pointers.
 */
void drawAndPrintAllFractal(std::vector<Fractal *> &vectorFractal)
{
    for (auto &fractal : vectorFractal)
    {
        fractal->drawFractal();
        fractal->print();
    }
}

/**
 * Delete method to all the objects that the factory created.
 * @param vectorFractal - the vector that contain all the fractals pointers.
 */
void deleteFractalsInVector(std::vector<Fractal *> vectorFractal)
{
    for (auto &fractal : vectorFractal)
    {
        delete (fractal);
    }
}

/**
 * program that read csv file from a directory and first check if all the inputs is valid.
 * Then it collect all the data of fractals into to vector and then send it and ask to draw and
 * print all the fractals.
 * @param argc - The number of the inputs.
 * @param argv - The inputs.
 * @return - 0 if success 1 otherwise.
 */
int main(int argc, char **argv)
{
    validInput(argc, argv);
    std::vector<data> dataArray;
    readCsvFile(argv[1], dataArray);

    std::vector<Fractal *> vectorFractal;
    fractalFactory(dataArray, vectorFractal);

    drawAndPrintAllFractal(vectorFractal);

    deleteFractalsInVector(vectorFractal);
}
