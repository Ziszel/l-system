#include "../include/data-manager.hpp"

Data_Manager::Data_Manager()
{
}

Lsystem_Data Data_Manager::Load(std::string file_path)
{
    Lsystem_Data ls_data;
    // ':' is used to delimit between the prop name, and prop value
    std::string delimiter = ":";
    // load a file by way of the file path parameter
    std::ifstream file_data(file_path, std::ifstream::in);

    // ensure the file has been loaded successfully else throw and error
    if (file_data)
    {
        for (std::string line; std::getline(file_data, line);)
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
        file_data.close();
    }
    // handle the error and return useful information back to the user
    else {
        std::cout << "error reading ruleset file." << "\n";
        std::cout << "Error: " << strerror(errno);
    }

    std::string rules_path = file_path + ".rules";

    std::ifstream rules_data(rules_path, std::ifstream::in);

    // rules are stored in a separate file due to the structure of a rule object
    // and due to rulesets being dynamic in quantity.
    // bringing them in separately and merging them into the same struct keeps the code clean elsewhere
    if (rules_data)
    {
        for(std::string line; std::getline(rules_data, line);)
        {
            int delim_location = line.find(delimiter);

            char prop = line[0];
            std::string value = line.substr(delim_location + 1, line.length());
            Rule rule = {prop, value};
            ls_data.ruleset.push_back(rule);
        }
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
        // convert string to integer
        ls_data->alpha = stoi(value);
        return 0;
    }
    else if (prop == "theta")
    {
        // convert string to floating point value
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