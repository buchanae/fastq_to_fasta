#include <iostream>
#include <fstream>

#include <tclap/CmdLine.h>

#define VERSION "0.1"

using namespace std;

int main (int argc, char* argv[])
{
    string input_file_path, output_file_path;

    try
    {
        TCLAP::CmdLine cmd("Convert FASTQ format to FASTA format", ' ', VERSION);

        TCLAP::ValueArg<string> inputFileArg("i", "input", "Input FASTQ file", 
                                             true, "", "input.fastq", cmd);
        TCLAP::ValueArg<string> outputFileArg("o", "output", "Output file", 
                                              true, "", "output.fasta", cmd);

        cmd.parse(argc, argv);

        input_file_path = inputFileArg.getValue();
        output_file_path = outputFileArg.getValue();

    }
    catch (TCLAP::ArgException &e)
    {
        cerr << "Error: " << e.error() << " " << e.argId() << endl;
    }

    ifstream input(input_file_path.c_str());
    if (!input.is_open())
    {
        cerr << "Error, couldn't open input file: " << input_file_path << endl;
        return 1;
    }

    ofstream output(output_file_path.c_str(), ios::out | ios::trunc);
    if (!output.is_open())
    {
        cerr << "Error, couldn't open output file: " << output_file_path << endl;
        return 1;
    }

    string line;
    bool ignore = false;

    while (std::getline(input, line).good())
    {
        if (line.at(0) == '@')
        {
            ignore = false;
            output << "<" << line.substr(1) << endl;
        }
        else if (line.at(0) == '+')
        {
            ignore = true;
        }
        else if (!ignore)
        {
            output << line << endl;
        }
    }
}
