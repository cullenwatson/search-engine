# Search Engine

This repository was created and maintained by Cullen Watson.

Email: cgwatson@smu.edu

## Functionality

This program is a search engine for a large collection of financial news
articles from Jan - May 2018. The dataset contains more than 300,000 articles. Included in the repo 
is the first 25,000 articles to test the search engine with.

It uses a self-implemented AVL Tree for storage of word objects and a HashTable for the associated people and organizations of the article.
The articles are ranked in the search results by term-frequency/inverse document frequency (tf/idf) metric.

Link to the full dataset can be found [here](https://www.kaggle.com/datasets/jeet2016/us-financial-news-articles?resource=download&select=2018_02_112b52537b67659ad3609a234388c50a)
## How to Query with Examples

After loading in the dataset, you can view statistics about the index, including most popular words, average words per 
article, etc. 

There are many ways to query the articles:

* **markets** <br/>
This query returns all articles that contain the word markets.
* **AND social network** <br/>
This query returns all articles that contain the words “social” and “network”
(doesn’t have to be as a 2-word phrase)
* **AND social network PERSON cramer** <br/>
This query returns all articles that contain the words social and network and that
mention cramer as a person entity.
* **AND social network ORG facebook PERSON cramer** <br/>
This query returns all articles that contain the words social and network, that
have an entity organization of facebook and that mention cramer as a person entity.
* **OR snap facebook** <br/>
 This query returns all articles that contain either snap OR facebook
* **OR facebook meta NOT profits** <br/>
This query returns all articles that contain facebook or meta but that do not
contain the word profits.
* **bankruptcy NOT facebook** <br/>
This query returns all articles that contain bankruptcy, but not facebook.
* **OR facebook instagram NOT bankruptcy ORG snap PERSON cramer** <br/>
This query returns any article that contains the word facebook OR instagram but
that does NOT contain the word bankruptcy, and the article should have an organization
entity with Snap and a person entity of cramer


## How to Run (must use WSL)

Compile and build with CMAKE. There are no command-line arguments.

First, load in the dataset by entering option one in the menu and then specifying the location of the dataset.

Type `../data` to use the 25,000 articles included in the repo. The index will be created after around a minute. You can then begin querying.

