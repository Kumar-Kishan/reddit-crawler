#include<reddit/reddit.hpp>
#include<iostream>
#include<fstream>
using namespace reddit;


void clearScreen(){
    std::cout << "\033c";
}

bool checkSelection(){
    char c;
    std::cin >> c;
    return c == 'Y' || c == 'y';
}
//I don't want to write a lot of these..
//Please don't  say i am making python
std::string getInputString(std::string prompt=""){
    std::cout << prompt;
    std::string temp;
    std::cin >> temp;
    return temp;
}

template<class T>
T getValuefromJson(json j,std::string key, T defaultValue){
    return j.find(key) == j.end() ? defaultValue : (T)j[key];
}


int getInputInt(std::string  prompt=""){
    std::cout << prompt;
    int temp;
    std::cin >> temp;
    return temp;
}


int main(){
    using namespace std::string_literals;
    Reddit reddit;
    clearScreen();
    std::ifstream configFile("crawler.json");
    json config;
    configFile >> config;

    for(auto subreddit: config["subreddits"]){
        clearScreen();
        int num_of_image_posts = 0;
        std::string subredditName = subreddit["subreddit"];
        std::cout << "Current Subreddit: " << subredditName << std::endl;
        reddit.setSubreddit(subredditName);
        std::string outfile = subreddit["outfile"];
        int num_of_required = subreddit["count"];
        auto posts = json();
        //int count = 1;
        while(true){
            //clearScreen();
            std::cout << "Progress: " << num_of_image_posts << "/" << num_of_required << std::endl;
            if(reddit.hasEnded()) break;
            auto childrens = reddit.getNextBatch();
            for(auto &post: childrens){
                if(isImagePost(post["data"])){
                    auto data = post["data"];
                    //std::cout << "true that" << std::endl;
                    num_of_image_posts++;
                    
                    json postJson = {{
                        { "url" , getValuefromJson<std::string>(data, "url", "") },
                        { "author" , getValuefromJson<std::string>(data,"author","") },
                        { "title", getValuefromJson<std::string>(data,"title","") },
                        { "upvotes" , getValuefromJson<int>(data,"ups", 0) },
                        { "permalink" , getValuefromJson<std::string>(data,"permalink","") }
                    }};
                    posts.push_back(postJson);
                }
            }
            
            if(num_of_image_posts > num_of_required) break;
        }
        auto results = json();
        results["subreddit"] = reddit.getSubreddit();
        results["posts"] = posts;
        results["count"] = num_of_image_posts;
        std::ofstream file(outfile);
        file << results;
    }

    
    

    return 0;
}