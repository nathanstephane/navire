// navire.cpp : Builds files for bitofshell.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>
#include <direct.h>

namespace fs = std::filesystem;



#define MAX_CMD_LINE 80


std::string trim(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t\n\r");
	size_t last = str.find_last_not_of(" \t\n\r");

	if (first == std::string::npos || last == std::string::npos)
	{
		return "";
	}
	return str.substr(first, last - first + 1);
}

bool fileExist(const fs::path& filename) {
	return fs::exists(filename);
}


std::string pathNavigator(const std::string pageCat, const std::string pageName)
{
	return "<nav>You are here://<a href=\".. / index.html\">bitofshell</a>/<a href=\".. / " + pageCat + " / index.html\"> " + pageCat + " </a>/" + pageName + "<span class=\"blink\">|</span> </nav>";
}

int copyContent(const std::filesystem::path& source, const std::filesystem::path& dest)
{
	std::fstream source_file_stream;
	std::fstream destination_file_stream;

	std::string line;

	source_file_stream.open(source, std::ios::in);
	destination_file_stream.open(dest, std::ios::out);

	while (!source_file_stream.eof())
	{
		std::getline(source_file_stream, line);

		destination_file_stream << line << std::endl;
	}
	source_file_stream.close();
	destination_file_stream.close();
	return 1;
}


struct ProjectTemplateToken
{
	ProjectTemplateToken()
	{
		title = "<!--token::title_ <title></title> -->";
		item_title = "<!--token::title_ <title></title> -->";
		local_uri_path = "<!-- token::pathNavigator_ <nav>You are here://<a href=\".. / index.html\">bitofshell</a>/<a href=\"../projects/index.html\">projects</a>/&project_name<span class=\"blink\">|</span></nav>";

	}
	std::string title;
	std::string item_title;
	std::string local_uri_path;

};

void injectToken(const std::filesystem::path& filePath)
{
	ProjectTemplateToken* ptt = new ProjectTemplateToken();

	std::fstream fileStream;
	std::string line;
	fileStream.open(filePath,std::ios::in);
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		if (trim(line) == trim(ptt->item_title))
		{

		}
	}

	delete ptt;
}


int main(void)
{


	char* args[MAX_CMD_LINE / 2 + 1];
	int should_run = 0;// make it a bool after
	int argc = 0;

	std::vector<std::string> entered_input;
	std::vector<std::string> command_history;

	//if no arg passed, display menu
	std::cout << "Navire V0.0.1\n";
	while(should_run == 0) {
		int status = 1;
		
		std::string input; //user input variable to initialize
		
		printf("\tOptions: \n");
		printf("->[1] new_page\n");
		printf("->[2] new_category\n");
		printf("->[3] tree\n");
		printf("->[4] quit\n");

		std::cout << "Option input: ";
		std::getline(std::cin, input);

		

		if (input == "tree")
		{
			//TODO- HANDLE TREE
		}

		if (trim(input) == "new_page"|| trim(input) =="1")
		{
			//creates a new page following the right path or directory (category)
			printf("Which type of page would you like to create ?\n");
			printf("->[1] Thoughts\n");
			printf("->[2] Project\n");
			printf("->[3] Wikilog\n");
			
			std::cout << "option : ";
			std::string option;

			//std::cin.ignore();
			//std::cin >> option;
			std::getline(std::cin, option);
			std::cout << "OPTION COUT " << option << std::endl;

			if (trim(option) == "thought" || trim(option) == "thoughts" || trim(option) =="1")
			{
				
				// propmt page name
				std::string name;
				printf("Enter page name : ? ");
				
				std::getline(std::cin, name);

				//get the path to thought 
				std::string path = "C:/Users/Nathan/Desktop/atelier/navire/x64/Debug/hibernath/thoughts";
				fs::path currentPath = fs::current_path();
				std::string filename = "hibernath\\thoughts\\" + name.append(".html");
				fs::path filePath = currentPath / filename;
				
				//std::cout << "FILE PATH IS :" << filePath << std::endl;
				
				// check name does not exist already. If exist then prompt another name.
				int state = 0;
				while (fileExist(filePath) && state == 0)
				{
					
					printf("ERR01: File exist already. Enter a different name ? Y/N: ");
					std::string ans;

					
					std::getline(std::cin, ans);
					//std::cin >> ans;
					if (trim(ans) == "y" || trim(ans) == "Y")
					{
						printf("New file name: ");
						std::cin >> name;
						filename = "hibernath\\thoughts\\" + name.append(".html");
						filePath = currentPath / filename;

					}
					else
					{
						state = 1;
					}
				}

			
				

			
				// create new file by injecting template {mind css injecting, mind you are here section and other styling}(check if templates exist)
					//std::ofstream newFile(filePath);
				std::string project_template = "hibernath\\thoughts\\thought_template.bth";
				auto templatePath = currentPath / project_template;
				//title (<title>%Project_name%)</title>)
				std::string title = "<title>"+name+"</title>"; //<!--token::title_ <title></title> -->
				std::string s_pathNavigator = pathNavigator("thoughts", name); //<!-- token::pathNavigator_ <nav>You are here://<a href="../index.html">bitofshell</a>/<a href="../projects/index.html">projects</a>/&project_name<span class="blink">|</span></nav>
				
				std::string page_name = trim(name);
				std::string itemTitle = "<h2>" + page_name + "</h2>"; //<!--token::itemTitle_ <h2>&itemTitle</h2> -->


				//newFile << pathNavigator("thoughts",name);
				//newFile.close();

				if (copyContent(templatePath, filePath) == 1)
				{
					std::cout << "JOB DONE.." << std::endl;
				}
				else {
					std::cerr << "JOB FAILED" << std::endl;
				}

					//injectToken();
				//create page template for thought


				/*
				//Build thought. index page to include the newly created page.
					procedure:
						-iterate over all the files in the thouhgt folder
						-get the names and store in a vector of strings.
						
					*/

				std::vector<std::string> filesNames;
				//std::cout << "LIST OF FILES: \n";
				for (const auto& entry : fs::directory_iterator(path))
				{
					//std::cout << entry.path().filename().string() << std::endl;
					filesNames.push_back(entry.path().filename().string());
					
				}

				printf("Name from fileNames container\n");
				for (auto v : filesNames) 
				{
					std::cout << v << "\n";
				}
				should_run=1;


				std::cout << "Next Operation ? press any numpad to quit or 0 to continue :  ";
				
				//std::getline(std::cin, should_run);
				std::cin >> should_run;
				std::cin.ignore();

			}


		}
		
		
	}


	printf("EXIT");

	return 0;
}

