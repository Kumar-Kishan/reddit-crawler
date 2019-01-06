#pragma once

#ifndef __REDDIT__
#define __REDDIT__

#include<cpr/cpr.h>
#include<nlohmann/json.hpp>
#include<string>
#include<iostream>
#include<fstream>
//I know it's bad But i don't have other json libraries And don't plan to make one
using namespace nlohmann;

namespace reddit{

    bool isImagePost(json post){
        return (post.find("is_self") !=  post.end()) && (post["is_self"] == false) && (post.find("post_hint") != post.end()) && (post["post_hint"] == "image"); 
    }

    class Reddit {
        std::string base_url;
        std::string suffix;
        std::string user_agent;
        std::string after; 
        std::string subreddit;
        bool isEnd;
    public:
        Reddit(){
            base_url = "https://www.reddit.com/";
            suffix = ".json";
            after = "";
            isEnd = false;
            user_agent = "temp:iwillcrawl:v0.0.0";
            subreddit = "foodporn";
        }
        std::string getSubreddit(){
            return subreddit;
        }
        void setSubreddit(std::string subreddit){
            this->subreddit = subreddit;
            this->after = "";
            this->isEnd = false;
        }
        bool hasEnded(){
            return this->isEnd;
        }
        json getNextBatch(int limit=100){
            using namespace cpr;
            auto url = ( subreddit == "" ? "" : "r/"  + subreddit)  + suffix;
            if(after != ""){
                url += "?after=" + after + "&limit=" + std::to_string(limit);
            }else{
                url += "?limit="+ std::to_string(limit);
            }
            auto r = Get(Url(base_url + url), Header{{
                "User-Agent" , user_agent
            }}, VerifySsl(false));
            std::cout << "Request Url: " << r.url << "\t Status Code: " << r.status_code << std::endl;
            if(r.status_code == 200){
                try{
                    auto response = json::parse(r.text);
                    if(response["data"].find("after") != response["data"].end()) {
                        if (response["data"]["after"] != nullptr) {
                            after = response["data"]["after"];
                        }else{
                            isEnd = true;
                        }
                    }
                    return response["data"]["children"];
                }catch(json::exception e){
                    std::cout << e.what() << std::endl;
                }
                                
            }
            return json();
        }
    };

}



#endif