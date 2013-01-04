#ifndef FILEOPENER_H
#define FILEOPENER_H

#include <fstream>
namespace imac2gl3 {
    class FileOpener
    {
        private:
            std::ifstream& m_file;
            
        public:
            FileOpener(std::ifstream& file, const char* fileName): m_file(file)
            { 
                m_file.open(fileName); 
            }
            
            ~FileOpener()
            { 
                m_file.close(); 
            }
    };
}

#endif