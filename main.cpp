#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stack>
using namespace std;



int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <brainfuck_file> <output_exe>\n";
        return 1;
    }

    ifstream input_file(argv[1]);
    if (!input_file) {
        cout << "Could not open file " << argv[1] << "\n";/*tanczacejajcomaciezki*/
        return 1;
    }

    string brainfuck_code((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
    ofstream output_file("temp.c");
    output_file << "#include <stdio.h>\n#include <conio.h>\n\nint main(void) {\nint array[30000] = {0};\nint indexer=0;\n";

    for (char c : brainfuck_code) {
        switch (c)
        {
        case '+':
            output_file<<"array[indexer] = array[indexer] + 1;";
            break;
        case '-':
            output_file<<"array[indexer] = array[indexer] - 1;";
            break;
        case '>':
            output_file<<"indexer += 1;";
            break;
        case '<':
            output_file<<"indexer -= 1;";
            break;
        case '[':
            output_file<<"while(array[indexer] != 0) {";
            break;
        case ']':
            output_file<<"}";
            break;
        case '.':
            output_file<<"putch(array[indexer]);";
        case ',':
            output_file<<"array[indexer] = getch();";
        case ':':
            output_file<<"printf(\"%d\", array[indexer]);";
        case '0':
            output_file<<"array[indexer] = 0;";

        //TODO: add file saving and reading operators!
        default:
            break;
        }
    }

    output_file << "return 0;\n}";
    output_file.close();
    string gcccommand = "gcc temp.c -o " + string(argv[2]);
    //compile using gcc
    system(gcccommand.c_str());


    // Remove the temporary file
    if (remove("temp.c") != 0) {
        perror("Error deleting temporaryC from disk.");
    } else {
        cout << "Compiled successfuly!";
    }
    return 0;
}