# Crawl Reddit for images and get all the image links

Clone the repo recursively..

### Usage Instruction
Make sure you have `CMAKE`, `Ninja-Build`, And `libcurl` installed.
You can use any generator you like. I prefer ninja

    cmake -G Ninja -H. -Bbuild
    ninja -C build
    bin/crawler

Make sure to have a sample *`crawler.json`* file in the directory from where crawler is ran

    {
        "subreddits" : [
            {
                "subreddit": "space",
                "count" : 2000,
                "outfile" : "space.json"
            }
        ]
    }

It will try to get 2000 or more images. But sometimes may fail due to shortage of images. Also for sorting via new or top use `space/top` or `space/new`


### Sample Output

space.json

    {
        "count": 97,
        "posts": [
            [
                {
                    "author": "...",
                    "permalink": "...",
                    "title": "...",
                    "upvotes": 5522,
                    "url": "https://i.imgur.com/950KYZv.jpg"
                }
            ],
            ...
            [
                {
                    "author": "...",
                    "permalink": "...",
                    "title": "...",
                    "upvotes": 38,
                    "url": "https://i.redd.it/urd2uhw3dy521.png"
                }
            ]
        ],
        "subreddit": "space"
    }




*Please note that this codebase is made in 3-4 hours of work. So, it doesn't contain much good code.*