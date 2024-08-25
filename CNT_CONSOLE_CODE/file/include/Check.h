// Native header file
#include <iostream>
#include <string>
#include <vector>

class check{
    private:
        bool checkSrc(int argc, char **argv)
        {
            if (argc <= 1)
                return false;
        }
    public:
        void inputCommandVecList(int argc, char **argv, std::vector <std::string>& commandList){
            if(!checkSrc(argc, argv)) commandList.push_back("undefined"); 
            for(int i = 2 ; i < argc ; ++i) commandList.push_back(argv[i]);
        }
};