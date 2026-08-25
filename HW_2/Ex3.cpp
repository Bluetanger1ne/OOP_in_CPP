#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<std::string> find_all_elements(const std::string &xml, std::string
tag_name);


int main() {
    std::string filename;
    std::string tag;
    std::string line;
    std::string contents;
    std::cout << "Please enter the name of a file you want to open with \".xml\" included" << std::endl;
    std::cin >> filename;

    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "Error. Unable to open file" << std::endl;
        return 1;
    }

    while (true) {
        std::cout << "Enter a tag name or \"stop\" to quit." << std::endl;
        std::cin >> tag;
        if (tag == "stop") {
            return 0;
        }
        while (std::getline(file, line)) { // Add all xml lines to a string
            contents.append(line);
            line.erase();
        }
        std::vector<std::string> elements = find_all_elements(contents, tag); // Find all elements
        std::cout << tag << ": ";

        for (auto &item: elements) // Print them out
        {
            std::cout << item << " ";
        }
        std::cout << " " << std::endl;
    }
}

std::vector<std::string> find_all_elements(const std::string &xml, std::string tag_name)
{
    std::vector<std::string> elements;

    std::string start_tag = "<" + tag_name + ">";
    std::string end_tag = "</" + tag_name + ">";

    std::size_t start = xml.find(start_tag); // Find the position of the first tag

    while (start != std::string::npos) // While there is stuff to read from the file
    {
        start += start_tag.length();  // move past the start tag
        std::size_t end = xml.find(end_tag, start); // Find the end tag
        elements.push_back(xml.substr(start, end - start)); // add the string/text between the tags and add it to elements
        start = xml.find(start_tag, end); // Move the start to the end of the end tag and continue.
    }

    return elements;
}

