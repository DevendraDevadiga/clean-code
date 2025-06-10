#include <iostream>
#include <vector>
#include <string>

// Helper function to check if a string starts with a prefix
bool startsWith(const std::string& str, const std::string& prefix) {
    return str.compare(0, prefix.length(), prefix) == 0;
}

int main() {
    std::vector<std::string> names = {
        "ramesh", "suresh", "rama", "shyama", "bhama", "ramanujan", "ramit"
    };

    std::string prefix = "ram";

    std::cout << "Names starting with \"" << prefix << "\":" << std::endl;
    for (const std::string& name : names) {
        if (startsWith(name, prefix)) {
            std::cout << name << std::endl;
        }
    }

    return 0;
}
