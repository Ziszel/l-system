#include "../include/data-manager.hpp"

Data_Manager::Data_Manager()
{
    // constructor
}

Lsystem_Data Data_Manager::Load(std::string file_path)
{
    Lsystem_Data ls_data;
    // ':' is used to delimit between the prop name, and prop value
    std::string delimiter = ":";
    // load a file by way of the file path parameter
    std::ifstream file(file_path, std::ifstream::in);

    // ensure the file has been loaded successfully else throw and error
    if (file)
    {
        for (std::string line; std::getline(file, line);)
        {
            int delim_location = line.find(delimiter);

            // Get property of data structure
            std::string prop = line.substr(0, delim_location);
            // Get value of data
            // delim_location + 1 ensures that I move past the delimiter and get only the value
            std::string value = line.substr(delim_location + 1, line.length());
            // Assign the correct prop and value inside of the struct from the file data
            if(Assign_Data(&ls_data, prop, value) == -1)
            {
                std::cout << "illegal data inside of data file. Error: " << strerror(errno);
            }
        }
        file.close();
    }
    // handle the error and return useful information back to the user
    else {
        std::cout << "error reading ruleset file." << "\n";
        std::cout << "Error: " << strerror(errno);
    }

    return ls_data;
}

int Data_Manager::Assign_Data(Lsystem_Data *ls_data, std::string prop, std::string value)
{
    // If / else is used because a 'switch' can only operate on integral types
    if (prop == "axiom")
    {
        ls_data->axiom = value;
        return 0;
    }
    else if (prop == "red")
    {
        ls_data->red = stoi(value);
        return 0;
    }
    else if (prop == "green")
    {
        ls_data->green = stoi(value);
        return 0;
    }
    else if (prop == "blue")
    {
        ls_data->blue = stoi(value);
        return 0;
    }
    else if (prop == "alpha")
    {
        ls_data->alpha = stoi(value);
        return 0;
    }
    else if (prop == "theta")
    {
        ls_data->theta = stof(value);
        return 0;
    }
    else if (prop == "line_length")
    {
        ls_data->line_length = stof(value);
        return 0;
    }
    
    // -1 should NEVER be returned. If it has an error should be thrown as there
    // is illegal data inside of the file that has been loaded by mistake
    return -1;
}