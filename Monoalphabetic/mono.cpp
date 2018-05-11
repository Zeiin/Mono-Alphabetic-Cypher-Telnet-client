#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>

int main(int argc, char** argv) {
    
    if(argc != 5){
        std::cerr<<"Invalid number of arguments."<<std::endl<<"Usage: ./mono <inputfile> <outputfile> <seed> 1/0"<<std::endl;
        exit(3);
    }
   char ar[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; //Initializing two alphabet arrays for shuffle and comparison.
   char ar2[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
   
   std::ifstream input;
   std::ofstream output;
   
   std::srand(std::stoi(argv[3]));
   std::random_shuffle(ar,ar+26);
   
   //Prints shuffled alphabet compared to regular alphabet
   for(int i=0;i<25;i++){
       std::cerr<<ar2[i]<<" - "<<ar[i]<<", ";
   }
       std::cerr<<ar2[25]<<" - "<<ar[25]<<std::endl;
    //Attempts to open provided input file to read in.    
    input.open(argv[1]);
    if(!input.is_open()){
        std::cerr<<"Invalid input file."<<std::endl;
        exit(3);
    }
    output.open(argv[2]);
    if(!output.is_open()){
        std::cerr<<"Invalid output file."<<std::endl;
        exit(3);
    }
   std::string inp;
   getline(input,inp); //Input file should only have a single line of valid length.
   if(std::atoi(argv[4]) == 1){
       std::string encrypted = "";
       for(int i=0;i<inp.length();i++){
           encrypted += ar[inp[i]-97]; //inp[i] references character at the index of our input string, -97 is to find the index from 0 to 26 to access the shuffled array.
       }
     output << encrypted;
   }
   else if(std::atoi(argv[4]) == 0){
       std::string decrypted = "";
        for(int i=0;i<inp.length();i++){
            int idx = std::distance(ar,std::find(ar,ar+26,inp[i]));//Distance finds distance from memory address of first param and the memory address of the second. find returns pointer to the char specified in shuffled array.
           decrypted += ar2[idx]; //returns decrypted letter
       }
      output << decrypted;
   }
   else{
    std::cerr<<"Invalid mode number. 1 for encrypt, 0 for decrypt"<<std::endl;
   }
}
