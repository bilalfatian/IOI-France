#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

using namespace std;

// Forward declaration of classes
class File;
class Directory;
class TextFile;
class ExecFile;

// Enum to represent the different file types
enum class FileType {
  TextFile,
  ExecFile,
  Directory
};
// File class
class File {
private:
  string name;
  string location;
  string permissions;
  string date_of_creation;

public:
  File(string name, string location, string permissions, string date_of_creation)
      : name(name), location(location), permissions(permissions), date_of_creation(date_of_creation) {}
  
  virtual ~File() {}
  
  // Getters and setters
  string getName() { return name; }
  void setName(string name) { this->name = name; }
  string getLocation() { return location; }
  void setLocation(string location) { this->location = location; }
  string getPermissions() { return permissions; }
  void setPermissions(string permissions) { this->permissions = permissions; }
  string getDateOfCreation() { return date_of_creation; }
  void setDateOfCreation(string date_of_creation) { this->date_of_creation = date_of_creation; }

  // Return the file type (TextFile, ExecFile, or Directory)
  virtual FileType getType() = 0;
};
// Directory class
class Directory : public File {
private:
  Directory* parent_directory;
  vector<Directory*> sub_directories;
  vector<TextFile*> text_files;
  vector<ExecFile*> exec_files;

public:
  Directory(string name, string location, string permissions, string date_of_creation, Directory* parent_directory)
      : File(name, location, permissions, date_of_creation), parent_directory(parent_directory) {}
  
  ~Directory() {
    // Delete all subdirectories and files in this directory
    for (Directory* sub_dir : sub_directories) {
    delete sub_dir;
    }
    for (TextFile* text_file : text_files) {
    delete text_file;
    }
    for (ExecFile* exec_file : exec_files) {
    delete exec_file;
    }
    // Clear vectors to remove references to deleted objects
    sub_directories.clear();
    text_files.clear();
    exec_files.clear();
  }
  // Getters and setters
  Directory* getParentDirectory() { return parent_directory; }
  void setParentDirectory(Directory* parent_directory) { this->parent_directory = parent_directory; }
  vector<Directory*> getSubDirectories() { return sub_directories; }
  void addSubDirectory(Directory* directory) { sub_directories.push_back(directory); }
  void removeSubDirectory(Directory* directory) {
    auto it = find(sub_directories.begin(), sub_directories.end(), directory);
    if (it != sub_directories.end()) {
      sub_directories.erase(it);
    }
  }
  vector<TextFile*> getTextFiles() { return text_files; }
  void addTextFile(TextFile* file) { text_files.push_back(file); }
  void removeTextFile(TextFile* file) {
    auto it = find(text_files.begin(), text_files.end(), file);
    if (it != text_files.end()) {
      text_files.erase(it);
    }
  }
  vector<ExecFile*> getExecFiles() { return exec_files; }
  void addExecFile(ExecFile* file) { exec_files.push_back(file); }
  void removeExecFile(ExecFile* file) {
    auto it = find(exec_files.begin(), exec_files.end(), file);
    if (it != exec_files.end()) {
      exec_files.erase(it);
    }
  }

  // Return the file type (TextFile, ExecFile, or Directory)
  FileType getType() override { return FileType::Directory; }
};
// TextFile class
class TextFile : public File {
public:
  TextFile(string name, string location, string permissions, string date_of_creation)
      : File(name, location, permissions, date_of_creation) {}
  
  // Return the file type (TextFile, ExecFile, or Directory)
  FileType getType() override { return FileType::TextFile; }
};

// ExecFile class
class ExecFile : public TextFile {
private:
  bool operates_on_all_file_types;
  function<void()> execute_function;

public:
  ExecFile(string name, string location, string permissions, string date_of_creation, bool operates_on_all_file_types,
           function<void()> execute_function)
      : TextFile(name, location, permissions, date_of_creation), operates_on_all_file_types(operates_on_all_file_types),
        execute_function(execute_function) {}
  
  // Getters and setters
  bool getOperatesOnAllFileTypes() { return operates_on_all_file_types; }
  void setOperatesOnAllFileTypes(bool operates_on_all_file_types) { this->operates_on_all_file_types = operates_on_all_file_types; }
  function<void()> getExecuteFunction() { return execute_function; }
  void setExecuteFunction(function<void()> execute_function) { this->execute_function = execute_function; }

  // Return the file type (TextFile, ExecFile, or Directory)
  FileType getType() override { return FileType::ExecFile; }
};

// Shell class
class Shell {
private:
  unordered_map<string, ExecFile*> supported_commands;

public:
  Shell() {
    // Initialize the list of supported commands
    supported_commands["mkdir"] = nullptr;
    supported_commands["rm"] = nullptr;
    supported_commands["ls"] = nullptr;
    supported_commands["cd"] = nullptr;
    supported_commands["find"] = nullptr;
  }
  
  // Getters and setters
  unordered_map<string, ExecFile*> getSupportedCommands() { return supported_commands; }
  void addSupportedCommand(string command_name, ExecFile* exec_file) { supported_commands[command_name] = exec_file; }
  void removeSupportedCommand(string command_name) { supported_commands.erase(command_name); }
};
int main() {
  // Create the root and bin directories
  Directory* root_dir = new Directory("home", "/", "rwx", getCurrentDate(), nullptr);
  Directory* bin_dir = new Directory("bin", "/home", "rwx", getCurrentDate(), root_dir);
  root_dir->addSubDirectory(bin_dir);

  // Create the executable files
  ExecFile* mkdir_exec = new ExecFile("mkdir", "/home/bin", "rwx", getCurrentDate(), false, []() {
    // Implementation of the mkdir command goes here
  });
  ExecFile* rm_exec = new ExecFile("rm", "/home/bin", "rwx", getCurrentDate(), true, []() {
    // Implementation of the rm command goes here
  });
  ExecFile* ls_exec = new ExecFile("ls", "/home/bin", "rwx", getCurrentDate(), false, []() {
    // Implementation of the ls command goes here
  });
  ExecFile* cd_exec = new ExecFile("cd", "/home/bin", "rwx", getCurrentDate(), false, []() {
    // Implementation of the cd command goes here
  });
  ExecFile* find_exec = new ExecFile("find", "/home/bin", "rwx", getCurrentDate(), false, []() {
    // Implementation of the find command goes here
  });
  bin_dir->addExecFile(mkdir_exec);
  bin_dir->addExecFile(rm_exec);
  bin_dir->addExecFile(ls_exec);
  bin_dir->addExecFile(cd_exec);
  bin_dir->addExecFile(find_exec);

  // Create the Shell instance
  Shell shell;

  // Add the executable files to the list of supported commands
  shell.addSupportedCommand("mkdir", mkdir_exec);
  shell.addSupportedCommand("rm", rm_exec);
  shell.addSupportedCommand("ls", ls_exec);
  shell.addSupportedCommand("cd", cd_exec);
  shell.addSupportedCommand("find", find_exec);

  // Set the current directory to the root directory
  Directory* current_dir = root_dir;

  // Prompt the user for input and execute commands until the user quits
  string input;
  while (true) {
    cout << "Enter a command (or 'quit' to exit): ";
    cin >> input;
    if (input == "quit") {
      break;
    }

    // Split the input into the command and argument
    vector<string> input_tokens = split(input, ' ');
    string command = input_tokens[0];
    string arg = input_tokens[1];

    // Execute the command
    ExecFile* exec_file = shell.getSupportedCommands()[command];
    if (exec_file != nullptr) {
      exec_file->getExecuteFunction()();
    } else {
      cout << "Unsupported command" << endl;
    }
  }

  return 0;
}
