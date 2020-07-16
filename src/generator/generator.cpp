//
// Created by Adam Szokalski on 20/11/2019.
//

#include <generator/generator.h>
#include <iostream>

#include <exception>

class tag_not_found: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Specified tag was not found in the source";
    }
} notag;

class too_many_tags: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Too many tags given";
    }
} toomuch;

generator::Generator::Generator() {
    src = source::Source();
}

generator::Generator::Generator(source::Source s) {
    src = s;
    temp = "";

    bool in_tag = false;
    std::string curr_tag = "";

    while(s.curr() != source::END_OF_TEXT){

        if(s.curr() == '{' && s.peek() == '%'){
            in_tag = true;
            s.bump();
            s.bump();
        }
        else if(s.curr() == '%' && s.peek() == '}'){
            in_tag = false;
            s.bump();
            s.bump();

            tags.emplace_back(curr_tag, temp.size() - 1);
            //std::cout<< curr_tag << " -> " << temp.size() - 1 <<std::endl;
            curr_tag = "";
        }

        if(in_tag){
            if(s.curr() != ' ') {
                curr_tag += s.curr();
            }
        } else{
            temp += s.curr();
        }
        s.bump();
    }

    copyTags();
    curr_product = temp;

    //std::cout<< temp <<std::endl;

}

int generator::Generator::find_tag(const std::string& tag_name) {
    int i;
    for(i = 0; i < curr_tags.size(); ++i){
        if(curr_tags[i].first == tag_name)
            break;
    }

    if(curr_tags[i].first != tag_name){
        return -1;
    } else{
        int ret = curr_tags[i].second;
        curr_tags.erase(curr_tags.begin() + i);
        return ret;
    }
}

void generator::Generator::feedOne(const std::string& tag_name, const std::string& value) {
    int index = find_tag(tag_name);
    if(index == -1){
        throw notag;
    }
    std::string new_product = "";
    for (int i = 0; i < curr_product.size(); ++i) {
        new_product += curr_product[i];
        if(i == index)
            new_product += value;
    }

    curr_product = new_product;
}

bool srt(std::pair<int, std::string> a, std::pair<int, std::string> b){
    return a.first < b.first;
}

void generator::Generator::feedMany(std::vector<std::pair<std::string, std::string>> tag_info) {
    if(tag_info.size() > curr_tags.size()){
        //exception
        throw toomuch;
    }
    std::vector<std::pair<int, std::string>> values;
    for (const auto& tag : tag_info) {
        int index = find_tag(tag.first);
        if(index == -1){
            throw notag;
        }
        values.emplace_back(index, tag.second);
    }
    std::sort(values.begin(), values.end(), srt);

    std::string new_product = "";
    for (int i = 0; i < temp.size(); ++i) {
        new_product += temp[i];
        if(i == values[0].first){

            new_product += values[0].second;

            values.erase(values.begin());
        }
    }
    curr_product = new_product;
}

std::string generator::Generator::fetch() {
    std::string ret;
    if(pending_products.empty()) {
        ret = curr_product;
        curr_product.clear();
        copyTags();
        curr_product = temp;
    } else {
        ret = pending_products.front();
        pending_products.erase(pending_products.begin());
    }

    return ret;

}

void generator::Generator::copyTags() {
    curr_tags.clear();
    for (int i=0; i<tags.size(); i++)
        curr_tags.push_back(tags[i]);
}



