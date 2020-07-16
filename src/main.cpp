//
// Created by Adam Szokalski on 20/11/2019.
//
#include <iostream>
#include "../inc/source/source.h"
#include <generator/generator.h>
#include <vector>

using namespace std;

string base = "<!DOCTYPE html>\n"
              "<html>\n"
              "\t<head>\n"
              "{% include %}\n"
              "\t</head>\n"
              "\t<body>\n"
              "\t\t<h1>\n"
              "\t\t\t{% title %}\n"
              "\t\t</h1>\n"
              "\t\t<h2>\n"
              "\t\t\t{% news %}\n"
              "\t\t</h2>\n"
              "\t\t<h2>\n"
              "\t\t\t{% news %}\n"
              "\t\t</h2>\n"
              "\t\t<p>\n"
              "\t\t\t{% description %}\n"
              "\t\t</p>\n"
              "\t</body>\t\n"
              "</html>";

int main(){
    source::Source a(base);
    generator::Generator g(a);

    g.feedMany({{"news", "Article 1"}, {"news", "Article 2"}});
    cout << g.fetch() << endl;
    g.feedMany({{"news", "Article 3"}, {"news", "Article 4"}});
    cout << g.fetch() << endl;
    return 0;
}

