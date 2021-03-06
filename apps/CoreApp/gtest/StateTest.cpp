#include <cstdlib>
#include <iostream>
#include <gtest/gtest.h>

#include "iApp.h"
#include <map>
#include <bits/stl_map.h>

    
flexd::core::iApp appka;
flexd::core::iApp appka1;
flexd::core::iApp a;
std::map<std::string, flexd::core::iApp> listOfApp;

TEST(AppState, State)
{
    ASSERT_FALSE(appka.freezing());
    ASSERT_TRUE(appka.starting());
    ASSERT_FALSE(appka.updating());
    ASSERT_TRUE(appka.freezing());
    ASSERT_TRUE(appka.stoping());
    ASSERT_FALSE(appka.unfreezing());
    ASSERT_TRUE(appka.starting());
    ASSERT_TRUE(appka.freezing());
    ASSERT_FALSE(appka.starting());
    ASSERT_TRUE(appka.unfreezing());
    ASSERT_TRUE(appka.stoping());
    ASSERT_TRUE(appka.updating());
    
    ASSERT_EQ(appka.getState(),3);
    ASSERT_EQ(appka1.getState(),3);  
}

TEST(AppState, Testing_with_Map){
    
    ASSERT_TRUE(listOfApp.insert(std::make_pair("snake", appka)).second); //move and return false if exist pair with snake
    ASSERT_TRUE(listOfApp.insert(std::make_pair("dumy", a)).second);
    listOfApp["earth"] = appka1; //copy and rewrite if exist pair with earth
    ASSERT_FALSE(listOfApp.insert(std::make_pair("earth", appka1)).second);

    if(listOfApp.find("earth") != listOfApp.end())
        ASSERT_TRUE(true);

    ASSERT_TRUE(listOfApp.at("dumy").starting());
    ASSERT_TRUE(listOfApp.at("dumy").freezing());
    listOfApp.clear();
}

TEST(AppState, Testing_couting_and_erasing_sharedpointer){
    flexd::core::iApp ppp;
    listOfApp.insert(std::make_pair("a", ppp));
    std::cout<<"deleting copy of make pair"<<std::endl;
    ppp.~iApp();
    std::cout<<"deleting copy of first object"<<std::endl;
}

TEST(AppState, Testing_erasing_map){
    listOfApp.clear();
}
