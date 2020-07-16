//
// Created by Adam Szokalski on 20/11/2019.
//

#ifndef WEBMASTER_GENERATOR_H
#define WEBMASTER_GENERATOR_H

#include <source/source.h>
#include <vector>

namespace generator{

    class Generator {
    private:
        source::Source src;             //Template source with tags
        std::string temp = {};          //Template without the tags
        std::string curr_product = {};  //Product that is currently being created
        std::vector<std::string> pending_products = {};

        std::vector<std::pair<std::string, int>> tags = {}; //Tag vector <tag_text, tag_head_index>
        std::vector<std::pair<std::string, int>> curr_tags = {}; //Copy of tags for current product

        void copyTags();                 //Copies tags to curr_tags
    public:
        Generator();                    //Default constructor

        explicit Generator(source::Source s);   //Main constructor

        int find_tag(const std::string& tag_name);  //finds a given tag and deletes it from array

        std::string fetch();                        //Returns current product and clears it

        void feedOne(const std::string& tag_name, const std::string& value);  //Replaces one tag with given value

        void feedMany(std::vector<std::pair<std::string, std::string>> tag_info);       //Replaces given tags in one product (in order)
    };

}

#endif //WEBMASTER_GENERATOR_H
