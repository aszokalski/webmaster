//
// Created by Adam Szokalski on 20/11/2019.
//

#ifndef WEBMASTER_SOURCE_H
#define WEBMASTER_SOURCE_H

#include <string>

namespace source{

    constexpr char END_OF_TEXT = '\3';

    class Source {
    private:
        std::string raw;                    //Template html
        int i;                              //Index
    public:
        Source();                           //Default Constructor

        explicit Source(std::string s);     //Main Constructor

        int pos();                    //Returns the current index

        char curr();                  //Returns the current char

        char peek();                  //Shows the next char

        void bump();                        //Increments the index

        void pos(int p);                    //Sets the index to p

        std::string getRaw();               //Returns raw
    };

}


#endif //WEBMASTER_SOURCE_H
