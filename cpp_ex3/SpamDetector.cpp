#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include "HashMap.hpp"

#define NUM_OF_ARGS 4
#define INVALID_NUM_MSG "Usage: SpamDetector <database path> <message path> <threshold>"
#define INVALID_INPUT_MSG "Invalid input"
#define SPAM_MSG "SPAM"
#define NOT_SPAM_MSG "NOT_SPAM"
#define DELIM ','
#define BAD_ALLOC_MSG "Bad allocate"

/**
 * Shortcut method to print to the stderr invalud input msg and exit from the prog with exit
 * failure.
 * @param msg - msg to be out to the ctderr.
 */
void exitFailure(const std::string &msg)
{
    std::cerr << msg << std::endl;
    if (msg == INVALID_NUM_MSG)
    {
        throw std::invalid_argument(msg);
    }
    throw std::out_of_range(msg);
}

/**
 * Checks the number of the arguments from the CLI.
 * @param num - the number of the input args.
 */
void checkNumArgs(int num)
{
    if (num != NUM_OF_ARGS)
    {
        exitFailure(INVALID_NUM_MSG);
    }
}


/**
 * Checks if the string is an int.
 * @param num - string to check if it is a num.
 * @return - true if it can, false if not.
 */
bool isInteger(const std::string &num)
{
    for (char i : num)
    {
        if (!isdigit(i))
        {
            return false;
        }
    }
    return true;
}

/**
 * Convert string number to an int. If it can't it will exit the prog.
 * @param num - String to convert.
 * @return - the number after converting.
 */
int stringToInteger(const std::string &num)
{
    if (!isInteger(num))
    {
        exitFailure(INVALID_INPUT_MSG);
    }
    return stoi(num);
}

/**
 * Check if threshold number is valid. if it is not, it will exit the prog.
 * @param thresholdToCheck - string from the cli to check if valid threshold.
 * @return - the threshold number after converting from string to int.
 */
int checkThresholdNumber(const std::string &thresholdToCheck)
{
    int threshold = stringToInteger(thresholdToCheck);
    if (threshold <= 0)
    {
        exitFailure(INVALID_INPUT_MSG);
    }
    return threshold;
}

/**
 * Checks if all the args from the input is valid. If the prog can run and has it all its need to
 * start.
 * @param num - number of args from the CLI.
 * @param argv - string array of the input.
 * @return - The threshold number if all success.
 */
int checkIfValidInput(int num, char **argv)
{
    checkNumArgs(num);

    return checkThresholdNumber(argv[3]);
}

/**
 * Method that check if the file if open currectly. If not it will raise an exception.
 * @param databaseString - file path.
 * @return - if all goes right, its return the file.
 */
std::ifstream checkIfFileOpen(const std::string &databaseString)
{
    std::ifstream file(databaseString);
    if (!file.is_open())
    {
        exitFailure(INVALID_INPUT_MSG);
    }
    return file;
}

/**
 * Method that transform all the string to lower case.
 * @param src - reference string to transform.
 */
void stringToLowerCase(std::string &src)
{
    for (auto &word : src)
    {
        word = tolower(word);
    }
}

/**
 * insert the object to the vectors.
 * @param badPhraseVector - vector of bad phrases.
 * @param scoreVector - vector of the score of the bad phrases.
 * @param resVector - the vector input from the file. including badpharse at the first and the
 * score at the second position.
 */
void updateVectors(std::vector<std::string> &badPhraseVector, std::vector<int> &scoreVector,
                   std::vector<std::string> resVector)
{
    if (resVector.size() != 2)
    {
        exitFailure(INVALID_INPUT_MSG);
    }
    stringToLowerCase(resVector[0]);
    badPhraseVector.push_back(resVector[0]);
    int scoreNum = stringToInteger(resVector[1]);
    if (scoreNum < 0)
    {
        exitFailure(INVALID_INPUT_MSG);
    }
    scoreVector.push_back(scoreNum);
}

/**
 * Read every line in the csv file. It will update the vectors and throw an exceptions if the
 * input is wrong.
 * @param databaseString - the path of the csv file.
 * @param badPhraseVector - vector of bad phrases.
 * @param scoreVector - vector of the score of the bad phrases.
 */
void readCsvFile(std::string &databaseString, std::vector<std::string> &badPhraseVector,
                 std::vector<int> &scoreVector)
{
    std::ifstream databaseFile = checkIfFileOpen(databaseString);
    try
    {
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        std::string line;
        boost::char_separator<char> sep{","};
        while (getline(databaseFile, line))
        {
            int flag = 0;
            tokenizer tok(line, sep);
            std::vector<std::string> resVector;
            int num = std::count(line.begin(), line.end(), DELIM);
            if (num != 1 || line.length() < 3)
            {
                exitFailure(INVALID_INPUT_MSG);
            }
            for (const std::string &t : tok)
            {
                if (flag < 2)
                {
                    resVector.push_back(t);
                    flag++;
                }
                else
                {
                    databaseFile.close();
                    exitFailure(INVALID_INPUT_MSG);
                }
            }
            updateVectors(badPhraseVector, scoreVector, resVector); // only if valid
        }
        databaseFile.close();
    } catch (std::out_of_range &e)
    {
        databaseFile.close();
        throw std::out_of_range(e);
    }
}

/**
 * Method that check if the path is correct and open the file and takes all the text into one
 * string.
 * @param contentPath - the path of the file.
 * @param content - string that will contain all the string from the text file.
 */
void moveWholeTextIntoOneString(std::string &contentPath, std::string &content)
{
    std::ifstream contentFile = checkIfFileOpen(contentPath);
    //file to one string
    getline(contentFile, content, (char) contentFile.eof());

    //String to lowercase string
    stringToLowerCase(content);
    contentFile.close();
}

/**
 * Check if the mail is spam. Its check if the bad phrases from the csv file if in the content.
 * if it is its count the score of every bad phrase.
 * @param content - The src to search in.
 * @param databaseMap - the map that contain bad phrases and there scores.
 * @return - the grade from the mail.
 */
int checkSpam(std::string &content, HashMap<std::string, int> &databaseMap)
{
    int counterSpamScore = 0;
    for (const auto &it : databaseMap)
    {
        size_t found = content.find(it.first, 0);

        while (found != std::string::npos)
        {
            counterSpamScore += it.second;
            found = content.find(it.first, found + 1);
        }
    }
    return counterSpamScore;
}

/**
 * Check if the text is spam according to the map. It checks if the grade from the mail is lower
 * than the threshold input.
 * @param msgScore - the text score.
 * @param threshold - the input score for the mail.
 */
void ifSpamPrint(int &msgScore, int &threshold)
{
    if (threshold <= msgScore)
    {
        std::cout << SPAM_MSG << std::endl;
    }
    else
    {
        std::cout << NOT_SPAM_MSG << std::endl;
    }
}

/**
 * A program that receives two files - csv file for collect bad phrases and there score and text.
 * and one number that hold the threshold score. The prog checks if the texts file is not a spam.
 * @param argc - number of input from the CLI
 * @param argv - array of the input.
 * @return - 0 if all goes right , otherwise 1.
 */
int main(int argc, char **argv)
{
    try
    {
        int threshold = checkIfValidInput(argc, argv);
        std::string filePathDatabase = argv[1], filePathMSG = argv[2];

        std::vector<std::string> badPhraseVector;
        std::vector<int> scoreVector;
        readCsvFile(filePathDatabase, badPhraseVector, scoreVector);

        HashMap<std::string, int> databaseMap(badPhraseVector, scoreVector);
        std::string content;

        moveWholeTextIntoOneString(filePathMSG, content);

        int msgScore = checkSpam(content, databaseMap);

        ifSpamPrint(msgScore, threshold);
        return 0;
    } catch (std::bad_alloc &e)
    {
        std::cout << BAD_ALLOC_MSG << std::endl;
        return EXIT_FAILURE;
    } catch (...)
    {
        return EXIT_FAILURE;
    }
}

