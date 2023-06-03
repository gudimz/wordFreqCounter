#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>

void writeToOutputFile(std::string filename, std::vector<std::pair<std::string, size_t>>& sortedFreqDictionary) {
    std::ofstream file(filename);

    if (!file) {
        std::cerr << "Error: failed to open output file." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (auto pair : sortedFreqDictionary) {
        file << pair.second << " " << pair.first << std::endl;
    }

    file.close();
}

std::unordered_map<std::string, size_t> countWordFrequency(std::string filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error: failed to open input file." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::unordered_map<std::string, size_t> freqDictionary;
    std::string line;
    std::string word;

    while (std::getline(file, line)) {
        /* Replace letters with lowercase, rest of characters with spaces */
        std::transform(line.begin(), line.end(), line.begin(),
                        [](char c) -> char {
                            if (!std::isalpha(c)) {
                                return ' ';
                            }
                            return std::tolower(c);
                        });

        std::stringstream ss;
        ss << line;

        while (ss >> word) {
            if (!freqDictionary.count(word)) {
                freqDictionary[word] = 1;
            }
            else {
                freqDictionary[word]++;
            }
        }
    }

    file.close();
    return freqDictionary;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Error: too few parameters." << std::endl;
        std::cerr << "Usage: " << argv[0] << " [input_file] [output_file]" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inpuFilename = argv[1];
    std::string outputFilename = argv[2];

    std::unordered_map<std::string, size_t> freqDictionary = countWordFrequency(inpuFilename);

    std::vector<std::pair<std::string, size_t>> sortedFreqDictionary(freqDictionary.begin(), freqDictionary.end());
    std::sort(sortedFreqDictionary.begin(), sortedFreqDictionary.end(),
                [](const std::pair<std::string, size_t> left, const std::pair<std::string, size_t> right) {
                    if (left.second == right.second) {
                        return left.first < right.first;
                    }
                    return left.second > right.second;

                });

    writeToOutputFile(outputFilename, sortedFreqDictionary);

    return EXIT_SUCCESS;
}