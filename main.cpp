// Project UID db1f506d06d84ab787baf250c265e24e
// p5-ml.cpp : This file contains the 'main' function. Program 
// execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "csvstream.h"
#include <set>
#include <map>
#include <cmath>
#include <limits>
using namespace std;

// EFFECTS: Return a set of unique whitespace delimited words.x
set<string> unique_words(const string& str) {
    //use this to get content into a vector
    //for then counting each word in map
    istringstream source(str);
    set<string> words;
    string word;
    while (source >> word) {
        words.insert(word);
    }
    return words;
}

class Classifier {
public:

    Classifier(string fileName, bool isDebug)
    {
        numPosts = 0;
        csvstream csv(fileName);
        map<string, string> row;
        //read in posts from file
        if (isDebug)
        {
            cout << "training data:" << endl;
        }
        while ( csv >> row )
        {   
            if (isDebug)
            {
                cout << "  label = " << row["tag"] << ", content = " 
                      << row["content"] << endl;
            }
            numPosts++;            
            set<string> words = unique_words(row["content"]);
            for (string word : words)
            {
                ++numPostsWithWord[word];   
                ++wordsAndLabels[{row["tag"], word}];
            }
            ++numPostsWithLabel[row["tag"]];
        }
        cout << "trained on " << numPosts << " examples" << endl;
        if (isDebug)
        {
            cout << "vocabulary size = " << numPostsWithWord.size() << endl;
        }
        cout << endl;

        if (isDebug)
        {
            cout << "classes:" << endl;
            for (pair<string, int> label : numPostsWithLabel)
            {
                cout << "  " << label.first << ", " << label.second
                    << " examples, log-prior = " << logPrior(label.first) << endl;
            }
            cout << "classifier parameters:" << endl;
            for (pair<pair<string, string>, int> word : wordsAndLabels)
            {
                cout << "  " << word.first.first << ":" << word.first.second 
                    << ", count = " << word.second
                    << ", log-likelihood = " 
                    << logLikelihood(word.first.second, word.first.first) << endl;
            }
            cout << endl;
        }
    }

    std::pair<string, double> predictLabel(string content)
    {
        set<string> words = unique_words(content);

        double max = -numeric_limits<double>::infinity();
        string maxLabel;

        for (pair<string, int> label : numPostsWithLabel)
        {          
            double prob = logProb(words, label.first);
            if (prob > max)
            {
                max = prob;
                maxLabel = label.first;
            }
        }
        return { maxLabel, max };
    }

    double logPrior(string label)
    {       
        return log(numPostsWithLabel[label] / (double)numPosts);
    }

    double logLikelihood(string word, string label)
    {
        if (numPostsWithWord.find(word) == numPostsWithWord.end())
        {
            return log(1.0 / numPosts);
        }
        if ( wordsAndLabels.find( {label, word}) == wordsAndLabels.end())
        {
            return log( numPostsWithWord[word] / (double)numPosts);
        }
        return log(wordsAndLabels[{label, word}] / (double)numPostsWithLabel[label]);
    }

    double logProb( set<string> words, string label)
    {
        double probability = logPrior(label);
        for (string word : words)
        {
            probability += logLikelihood(word, label);
        }
        return probability;
    }

private:
    int numPosts;
    map<string, int> numPostsWithWord;
    map<string, int> numPostsWithLabel;
    map<std::pair<string, string>, int> wordsAndLabels;
};




int main(int argc, const char* argv[])
{
    cout.precision(3);

    if (argc < 3 || argc > 4) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }
    
    
    if (argc == 4 && argv[3] != string("--debug"))
    {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }
    
    bool isDebug = (argc == 4);

    // read in 
    string trainName = argv[1];
    string testName = argv[2];

    try
    {
        Classifier classifier(trainName, isDebug);
        csvstream csv(testName);
        map<string, string> row;
        int correctPreds = 0;
        int numPosts = 0;
        cout << "test data:" << endl;
        while ( csv >> row )
        {
            pair<string, double> label = classifier.predictLabel(row["content"]);
            cout << "  correct = " << row["tag"] << ", predicted = " << label.first
                << ", log-probability score = " << label.second << endl;
            cout << "  content = " << row["content"] << endl;
            cout << endl;
            if (label.first == row["tag"])
            {
                correctPreds++;
            }
            numPosts++;
        }
        cout << "performance: " << correctPreds << " / " << numPosts 
            << " posts predicted correctly" << endl;
    }
    catch( csvstream_exception const &e)
    {
       cout << e.what() << endl;
       return 1;
    }
}
