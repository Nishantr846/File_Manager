#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

// Function to list files and subdirectories in the current directory
void ListContents(const fs::path &dir)
{
    std::cout << "Contents of " << dir << ":\n";

    for (const auto &entry : fs::directory_iterator(dir))
    {
        if (fs::is_directory(entry.status()))
        {
            std::cout << "[D] " << entry.path().filename() << "\n";
        }
        else
        {
            std::cout << "[F] " << entry.path().filename() << "\n";
        }
    }
}

// Function to create a new directory
void CreateDirectory(const fs::path &dir)
{
    if (!fs::exists(dir))
    {
        if (fs::create_directory(dir))
        {
            std::cout << "Directory created: " << dir << "\n";
        }
        else
        {
            std::cerr << "Failed to create directory: " << dir << "\n";
        }
    }
    else
    {
        std::cerr << "Directory already exists: " << dir << "\n";
    }
}

// Function to copy a file
void CopyFile(const fs::path &source, const fs::path &destination)
{
    if (fs::is_regular_file(source))
    {
        try
        {
            fs::copy_file(source, destination, fs::copy_options::overwrite_existing);
            std::cout << "File copied: " << source.filename() << " to " << destination << "\n";
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "Failed to copy file: " << e.what() << "\n";
        }
    }
    else
    {
        std::cerr << "Source is not a file: " << source << "\n";
    }
}

// Function to move a file
void MoveFile(const fs::path &source, const fs::path &destination)
{
    if (fs::is_regular_file(source))
    {
        try
        {
            fs::rename(source, destination);
            std::cout << "File moved: " << source.filename() << " to " << destination << "\n";
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "Failed to move file: " << e.what() << "\n";
        }
    }
    else
    {
        std::cerr << "Source is not a file: " << source << "\n";
    }
}

int main()
{
    fs::path current_directory = fs::current_path();
    std::string user_command;

    while (true)
    {
        std::cout << "Current directory: " << current_directory << "\n";
        std::cout << "Enter a command\nls(List)\nmkdir(Make Directory)\ncp(Copy)\nmv(Move)\ncd(Change Directory)\nexit\n";
        std::cin >> user_command;

        if (user_command == "ls")
        {
            ListContents(current_directory);
        }
        else if (user_command == "mkdir")
        {
            std::string new_dir_name;
            std::cout << "Enter the name of the new directory: ";
            std::cin >> new_dir_name;
            CreateDirectory(current_directory / new_dir_name);
        }
        else if (user_command == "cp")
        {
            std::string source, destination;
            std::cout << "Enter the source file path: ";
            std::cin >> source;
            std::cout << "Enter the destination file path: ";
            std::cin >> destination;
            CopyFile(current_directory / source, current_directory / destination);
        }
        else if (user_command == "mv")
        {
            std::string source, destination;
            std::cout << "Enter the source file path: ";
            std::cin >> source;
            std::cout << "Enter the destination file path: ";
            std::cin >> destination;
            MoveFile(current_directory / source, current_directory / destination);
        }
        else if (user_command == "cd")
        {
            std::string new_dir;
            std::cout << "Enter the directory to navigate to: ";
            std::cin >> new_dir;
            current_directory /= new_dir;
        }
        else if (user_command == "exit")
        {
            break;
        }
        else
        {
            std::cout << "Invalid command. Try again.\n";
        }
    }

    return 0;
}
